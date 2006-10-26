// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2005 Alistair Riddoch
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

// $Id: TaskFactory.cpp,v 1.9 2006-10-26 00:48:15 alriddoch Exp $

#include "server/TaskFactory.h"

#include "server/ScriptFactory.h"

#include "rulesets/Py_Task.h"
#include "rulesets/Python_Script_Utils.h"
#include "rulesets/PythonThingScript.h"
#include "rulesets/TaskScript.h"
#include "rulesets/Character.h"

#include "common/log.h"

TaskFactory::~TaskFactory()
{
}

PythonTaskScriptFactory::PythonTaskScriptFactory(const std::string & package,
                                                 const std::string & name) :
                                                 m_module(0), m_class(0),
                                                 m_package(package),
                                                 m_name(name)
{
    // Import the module
    PyObject * package_name = PyString_FromString((char *)m_package.c_str());
    m_module = PyImport_Import(package_name);
    Py_DECREF(package_name);
    if (m_module == NULL) {
        std::string msg = std::string("Missing python module ") + m_package;
        log(ERROR, msg.c_str());
        PyErr_Print();
        return;
    }

    // Get a reference to the class
    std::string classname(m_name);
    classname[0] = toupper(classname[0]);
    m_class = PyObject_GetAttrString(m_module, (char *)classname.c_str());
    if (m_class == NULL) {
        std::string msg = std::string("Could not find python class ")
                        + m_package + "." + classname;
        log(ERROR, msg.c_str());
        PyErr_Print();
        return;
    }
    if (PyCallable_Check(m_class) == 0) {
        std::string msg = std::string("Could not instance python class ")
                        + m_package + "." + classname;
        log(ERROR, msg.c_str());
        Py_DECREF(m_class);
        m_class = 0;
        return;
    }
    return;
}

PythonTaskScriptFactory::~PythonTaskScriptFactory()
{
    if (m_module != 0) {
        Py_DECREF(m_module);
    }
    if (m_class != 0) {
        Py_DECREF(m_class);
    }
}

Task * PythonTaskScriptFactory::newTask(Character & chr)
{
    // Create the task, and use its script to add a script
    if (m_class == 0) {
        std::cout << "No class" << std::endl << std::flush;
        return 0;
    }
    TaskScript * task = new TaskScript(chr);
    task->name() = m_name;
    assert(task != 0);

    PyTask * wrapper = newPyTask();
    assert(wrapper != 0);
    wrapper->m_task = task;
    assert(wrapper->m_task != 0);
    PyObject * script = Create_PyScript((PyObject *)wrapper, m_class);
    assert(script != 0);

    task->setScript(new PythonEntityScript(script, (PyObject *)wrapper));
    
    return task;
}
