// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2000,2001 Alistair Riddoch
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

// $Id: ExternalMind.cpp,v 1.18 2006-10-26 00:48:14 alriddoch Exp $

#include "ExternalMind.h"

#include "Connection_methods.h"

ExternalMind::ExternalMind(Connection & connection,
                           const std::string & id, long intId) :
                           BaseEntity(id, intId), m_connection(connection)
{
}

ExternalMind::~ExternalMind()
{
    // This object does not own the associated entity, so is not
    // responsible for removing it from the connectio.
    // m_connection.removeObject(getIntId());
}

void ExternalMind::operation(const Operation & op, OpVector &)
{
    m_connection.send(op);
}
