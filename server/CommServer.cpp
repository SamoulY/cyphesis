// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#include "CommServer.h"

#include "CommClient.h"
#include "CommMetaClient.h"
#include "ServerRouting_methods.h"
#include "protocol_instructions.h"

#include "common/log.h"
#include "common/debug.h"

#include <iostream>

#include <errno.h>

static const bool debug_flag = false;

/// \brief Construct a new CommServer object, storing a reference to the core
/// server object.
CommServer::CommServer(ServerRouting & svr) : m_server(svr)
{
}

CommServer::~CommServer()
{
    CommSocketSet::const_iterator I = m_sockets.begin();
    for(; I != m_sockets.end(); I++) {
        delete *I;
    }
}

/// \brief Idle function called from the main loop.
///
/// Poll all the CommIdleSocket objects that want to be polled regularly,
/// the call the core server object idle function.
/// @return true if the core server wants to be called again as soon as
/// possible.
bool CommServer::idle()
{
    // Update the time, and get the core server object to process
    // stuff.
    // FIXME These idle methods are now getting called way too often
    // if the core server is busy. Cut it back a bit. Probably can avoid
    // calling them at all if we are busy.
    time_t ctime = time(NULL);
    CommIdleSocketSet::const_iterator I;
    for(I = m_idleSockets.begin(); I != m_idleSockets.end(); ++I) {
        (*I)->idle(ctime);
    }
    // server.idle() is inlined, and simply calls the world idle method,
    // which is not directly accessible from here.
    return m_server.idle();
}

/// \brief Main program loop called repeatedly.
///
/// Call the server idle function to do its processing. If the server is
/// is currently busy, poll all the sockets as quickly as possible.
/// If the server is idle, use select() to sleep on the sockets for
/// a short period of time. If any sockets get broken or disconnected,
/// they are noted and closed down at the end of the process.
void CommServer::loop()
{
    // This is the main code loop.
    // Classic select code for checking incoming data or client connections.
    // It may be beneficial to re-write this code to use the poll(2) system
    // call.
    bool busy = idle();

    fd_set sock_fds;
    int highest = 0;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = (busy ? 0 : 100000);

    FD_ZERO(&sock_fds);

    bool pendingConnections = false;
    CommSocketSet::const_iterator I = m_sockets.begin();
    for(; I != m_sockets.end(); I++) {
       if (!(*I)->isOpen()) {
           pendingConnections = true;
           continue;
       }
       int client_fd = (*I)->getFd();
       FD_SET(client_fd, &sock_fds);
       if (client_fd > highest) {
           highest = client_fd;
       }
    }
    highest++;
    int rval = ::select(highest, &sock_fds, NULL, NULL, &tv);

    if (rval < 0) {
        if (errno != EINTR) {
            perror("select");
            log(ERROR, "Error caused by select() in main loop");
        }
        return;
    }

    if ((rval == 0) && !pendingConnections) {
        return;
    }
    
    std::set<CommSocket *> obsoleteConnections;
    for(I = m_sockets.begin(); I != m_sockets.end(); I++) {
       CommSocket * client = *I;
       if (!client->isOpen()) {
           obsoleteConnections.insert(client);
           continue;
       }
       if (FD_ISSET(client->getFd(), &sock_fds)) {
           if (!client->eof()) {
               if (client->read()) {
                   debug(std::cout << "Removing client due to failed negotiation or timeout" << std::endl << std::flush;);
                   obsoleteConnections.insert(client);
               }
               client->dispatch();
           } else {
               // It is not clear why but on some implementation/circumstances
               // client->eof() is true, and sometimes it isn't.
               // Either way, the stream is now done, and we should remove it
               obsoleteConnections.insert(client);
           }
       }
    }
    std::set<CommSocket *>::const_iterator J = obsoleteConnections.begin();
    for(; J != obsoleteConnections.end(); ++J) {
        removeSocket(*J);
    }
}

/// Remove and delete a CommSocket from the server.
inline void CommServer::removeSocket(CommSocket * client, char * error_msg)
{
    // FIXME This code needs to be moved into CommClient
    // MapType err;
    // err["message"] = error_msg;
    // ListType eargs(1,err);

    // Error e;

    // e.setArgs(eargs);

    // if (client->online() && client->isOpen()) {
        // client->send(e);
    // }
    m_sockets.erase(client);
    delete client;
}

/// Remove and delete a CommSocket from the server.
void CommServer::removeSocket(CommSocket * client)
{
    removeSocket(client,"You caused exception. Connection closed");
}
