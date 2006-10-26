// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2000-2004 Alistair Riddoch
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

// $Id: BaseEntity.cpp,v 1.93 2006-10-26 00:48:02 alriddoch Exp $

#include "BaseEntity.h"

#include "log.h"
#include "debug.h"
#include "op_switch.h"
#include "serialno.h"
#include "inheritance.h"

#include "Add.h"
#include "Attack.h"
#include "Burn.h"
#include "Chop.h"
#include "Cut.h"
#include "Eat.h"
#include "Nourish.h"
#include "Setup.h"
#include "Tick.h"
#include "Update.h"

#include <Atlas/Objects/SmartPtr.h>
#include <Atlas/Objects/Operation.h>
#include <Atlas/Objects/Anonymous.h>

#include <iostream>

using Atlas::Message::MapType;
using Atlas::Objects::Root;
using Atlas::Objects::Operation::Error;
using Atlas::Objects::Entity::RootEntity;

static const bool debug_flag = false;

BaseEntity::BaseEntity(const std::string & id, long intId) : m_id(id),
                                                            m_intId(intId)
{
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::addToMessage(MapType & omap) const
{
    debug( std::cout << "BaseEntity::addToMessage" << std::endl << std::flush;);
    omap["objtype"] = "obj";
    omap["id"] = getId();
}

void BaseEntity::addToEntity(const RootEntity & ent) const
{
    debug( std::cout << "BaseEntity::addToEntity" << std::endl << std::flush;);
    ent->setObjtype("obj");
    ent->setId(getId());
}

/// \brief Process an operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::operation(const Operation & op, OpVector & res)
{
    debug( std::cout << "BaseEntity::operation" << std::endl << std::flush;);
    return callOperation(op, res);
}

/// \brief Process a Login operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::LoginOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Logout operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::LogoutOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Action operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::ActionOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Add operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::AddOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Chop operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::ChopOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Combine operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::CombineOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Create operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::CreateOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Cut operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::CutOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Delete operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::DeleteOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Divide operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::DivideOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Eat operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::EatOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Burn operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::BurnOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Get operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::GetOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Imaginary operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::ImaginaryOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Info operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::InfoOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Move operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::MoveOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Nourish operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::NourishOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Set operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::SetOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Sight operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::SightOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Sound operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::SoundOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Talk operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::TalkOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Touch operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::TouchOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Tick operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::TickOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Look operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::LookOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Setup operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::SetupOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Appearance operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::AppearanceOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Attack operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::AttackOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Disappearance operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::DisappearanceOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process an Update operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::UpdateOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Use operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::UseOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Wield operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::WieldOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Other operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::OtherOperation(const Operation & op, OpVector & res)
{
}

/// \brief Process a Error operation.
///
/// @param op The operation to be processed.
/// @param res The result of the operation is returned here.
void BaseEntity::ErrorOperation(const Operation & op, OpVector & res)
{
}

void BaseEntity::callOperation(const Operation & op, OpVector & res)
{
    const OpNo op_no = op->getClassNo();
    OP_SWITCH(op, op_no, res,)
}

/// \brief Report an Error.
///
/// The error reported is noted in the log, and an error operation is
/// genereated.
/// @param op The operation that caused the error.
/// @param errstring A message describing the error.
/// @param res The resulting error operation is returned here.
/// @param to The error operation should be directed to this ID.
void BaseEntity::error(const Operation& op, const char* errstring,
                       OpVector & res, const std::string & to) const
{
    Error e;

    std::string msg = "ERROR generated by " + getId() + " with message [" + errstring + "]";
    log(NOTICE, msg.c_str());

    std::vector<Root> & args = e->modifyArgs();

    Atlas::Objects::Entity::Anonymous arg1;
    arg1->setAttr("message", errstring);
    args.push_back(arg1);
    args.push_back(op);

    if (!to.empty()) {
        if (!op->isDefaultSerialno()) {
            e->setRefno(op->getSerialno());
        }
        e->setTo(to);
    }

    res.push_back(e);
}


/// \brief Report an Error to a client.
///
/// The error reported generates an error operation.
/// This is used instead of error() when an event occurs which is of no
/// interest to the server admin, or world builder, and should only be
/// be reported to the client. It stops the logs from getting filled
/// with reports of authentication failures, and other similar occurences.
/// @param op The operation that caused the error.
/// @param errstring A message describing the error.
/// @param res The resulting error operation is returned here.
/// @param to The error operation should be directed to this ID.
void BaseEntity::clientError(const Operation & op,
                             const std::string & errstring,
                             OpVector & res,
                             const std::string & to) const
{
    Error e;

    std::vector<Root> & args = e->modifyArgs();

    Atlas::Objects::Entity::Anonymous arg1;
    arg1->setAttr("message", errstring);
    args.push_back(arg1);
    args.push_back(op);

    if (!to.empty()) {
        if (!op->isDefaultSerialno()) {
            e->setRefno(op->getSerialno());
        }
        e->setTo(to);
    }

    res.push_back(e);
}

