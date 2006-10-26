// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2003-2004 Alistair Riddoch
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

// $Id: CommLocalClient.h,v 1.6 2006-10-26 00:48:13 alriddoch Exp $

#ifndef SERVER_COMM_LOCAL_CLIENT_H
#define SERVER_COMM_LOCAL_CLIENT_H

#include "CommClient.h"

/// \brief Handle a unix socket connected to a client on the local machine.
class CommLocalClient : public CommClient {
  public:
    CommLocalClient(CommServer & svr, int fd, const std::string & id);
    virtual ~CommLocalClient();

};

#endif // SERVER_COMM_LOCAL_CLIENT_H
