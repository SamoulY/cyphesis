// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2002 Alistair Riddoch

#ifndef SERVER_COMM_META_CLIENT_H
#define SERVER_COMM_META_CLIENT_H

#include "CommIdleSocket.h"

#include <string>

#include <skstream/skstream.h>

/// \brief Handle a socket used to communicate with the metaserver.
class CommMetaClient : public CommIdleSocket {
  private:
    udp_socket_stream clientIos;
    time_t lastTime;

    static const int metaserverPort = 8453;

  public:
    explicit CommMetaClient(CommServer & svr);

    virtual ~CommMetaClient();

    void metaserverKeepalive();
    void metaserverReply();
    void metaserverTerminate();

    int getFd() const;
    bool eof();
    bool isOpen() const;
    bool read();
    void dispatch();

    bool setup(const std::string &);
    void idle(time_t t);
};

#endif // SERVER_COMM_META_CLIENT_H
