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

// $Id: TrustedConnection.cpp,v 1.9 2006-10-26 00:48:15 alriddoch Exp $

#include "TrustedConnection.h"

TrustedConnection::TrustedConnection(CommClient & client,
                                     ServerRouting & svr,
                                     const std::string & addr,
                                     const std::string & id) :
                                     Connection(client, svr, addr, id)
{
}

int TrustedConnection::verifyCredentials(const Account &,
                                         const Atlas::Objects::Root &) const
{
    return 0;
}
