// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2004 Alistair Riddoch
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

// $Id: Peer.h,v 1.5 2006-10-26 00:48:14 alriddoch Exp $

#ifndef SERVER_PEER_H
#define SERVER_PEER_H

#include "common/OOGThing.h"

class CommClient;
class ServerRouting;

/// \brief Class represening connections from another server that is peered to
/// to this one
///
/// This is the main point of dispatch for any operation from the peer.
class Peer : public OOGThing {
  protected:
    
  public:
    CommClient & m_commClient;
    ServerRouting & m_server;

    Peer(CommClient & client, ServerRouting & svr,
         const std::string & addr, const std::string & id);
    virtual ~Peer();
};

#endif // SERVER_PEER_H
