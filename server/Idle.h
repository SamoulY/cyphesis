// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2004-2006 Alistair Riddoch
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

// $Id: Idle.h,v 1.5 2006-10-26 00:48:14 alriddoch Exp $

#ifndef SERVER_IDLE_H
#define SERVER_IDLE_H

#include <time.h>

class CommServer;

/// \brief Base class for any object which needs to be polled regularly.
///
/// This should be treated as an interface, so can cleanly be used in
/// multiple inheritance.
class Idle {
  protected:
    explicit Idle(CommServer & svr);
  public:
    /// Reference to the object that manages all socket communication.
    CommServer & m_idleManager;

    virtual ~Idle();

    /// \brief Perform idle tasks.
    ///
    /// Called from the server's core idle function whenever it is called.
    virtual void idle(time_t t) = 0;
};

#endif // SERVER_IDLE_H
