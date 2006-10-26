// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2006 Alistair Riddoch
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

// $Id: DynamicProperty.h,v 1.4 2006-10-26 00:48:03 alriddoch Exp $

#ifndef COMMON_DYNAMIC_PROPERTY_H
#define COMMON_DYNAMIC_PROPERTY_H

#include "Property.h"

/// \brief Adaptor class which can make an instance of Property<T>
/// store its own data.
template <typename T>
class DynamicProperty : public Property<T> {
  protected:
    T m_store;
  public:
    // No flags for the time being, though once we work on persistence again
    // it may be required.
    explicit DynamicProperty();
};

/// \brief Adaptor class which can make any property class store its own
/// data.
template <class P, typename T>
class Dynamic : public P {
  protected:
    T m_store;
  public:
    // No flags for the time being, though once we work on persistence again
    // it may be required.
    explicit Dynamic();
};

#endif // COMMON_DYNAMIC_PROPERTY_H
