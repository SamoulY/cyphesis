// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000 Alistair Riddoch

#include "Py_Location.h"
#include "Py_Thing.h"
#include "Py_Vector3D.h"
#include "Py_Quaternion.h"
#include "Py_BBox.h"

#include "Thing.h"

static PyObject * Location_copy(LocationObject *self, PyObject *args)
{
    if (self->location == NULL) {
        PyErr_SetString(PyExc_TypeError, "invalid location");
        return NULL;
    }
    if (!PyArg_ParseTuple(args, "")) {
        PyErr_SetString(PyExc_TypeError, "location.copy() has no args");
        return NULL;
    }
    LocationObject * ret = newLocationObject(NULL);
    ret->location = new Location(self->location->m_loc, self->location->m_pos, self->location->m_velocity);
    ret->own = 1;
    return (PyObject *)ret;
}

static PyMethodDef Location_methods[] = {
    {"copy",		(PyCFunction)Location_copy,	METH_VARARGS},
    {NULL,		NULL}           /* sentinel */
};

static void Location_dealloc(LocationObject *self)
{
    if ((self->own != 0) && (self->location != NULL)) {
        delete self->location;
    }
    PyMem_DEL(self);
}

static PyObject * Location_getattr(LocationObject *self, char *name)
{
    if (self->location == NULL) {
        PyErr_SetString(PyExc_TypeError, "invalid location");
        return NULL;
    }
    if (strcmp(name, "parent") == 0) {
        if (self->location->m_loc == NULL) {
            Py_INCREF(Py_None);
            return Py_None;
        }
        ThingObject * thing = newThingObject(NULL);
        thing->m_thing = self->location->m_loc;
        return (PyObject *)thing;
    }
    if (strcmp(name, "coordinates") == 0) {
        Vector3DObject * v = newVector3DObject(NULL);
        v->coords = self->location->m_pos;
        return (PyObject *)v;
    }
    if (strcmp(name, "velocity") == 0) {
        Vector3DObject * v = newVector3DObject(NULL);
        v->coords = self->location->m_velocity;
        return (PyObject *)v;
    }
    if (strcmp(name, "orientation") == 0) {
        QuaternionObject * v = newQuaternionObject(NULL);
        v->rotation = self->location->m_orientation;
        return (PyObject *)v;
    }
    if (strcmp(name, "bbox") == 0) {
        BBoxObject * b = newBBoxObject(NULL);
        b->box = self->location->m_bBox;
        return (PyObject *)b;
    }
    return Py_FindMethod(Location_methods, (PyObject *)self, name);
}

static int Location_setattr(LocationObject *self, char *name, PyObject *v)
{
    if (self->location == NULL) {
        PyErr_SetString(PyExc_TypeError, "invalid location");
        return -1;
    }
    if (strcmp(name, "parent") == 0) {
        if (!PyThing_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "parent must be a thing");
            return -1;
        }
        ThingObject * thing = (ThingObject *)v;
        if (thing->m_thing == NULL) {
            PyErr_SetString(PyExc_TypeError, "invalid thing");
            return -1;
        }
        self->location->m_loc = thing->m_thing;
        return 0;
    }
    if ((strcmp(name, "bbox") == 0) && PyBBox_Check(v)) {
        BBoxObject * box = (BBoxObject *)v;
        self->location->m_bBox = box->box;
        return 0;
    }
    if ((strcmp(name, "orientation") == 0) && PyQuaternion_Check(v)) {
        QuaternionObject * quat = (QuaternionObject *)v;
        self->location->m_orientation = quat->rotation;
        return 0;
    }
    Vector3D vector;
    if (PyVector3D_Check(v)) {
        Vector3DObject * vec = (Vector3DObject *)v;
        if (!vec->coords.isValid()) {
            fprintf(stderr, "This vector is not set\n");
        }
        vector = vec->coords;
    } else if (PyTuple_Check(v) && (PyTuple_Size(v) == 3)) {
        for(int i = 0; i < 3; i++) {
            PyObject * item = PyTuple_GetItem(v, i);
            if (PyInt_Check(item)) {
                vector[i] = (double)PyInt_AsLong(item);
            } else if (PyFloat_Check(item)) {
                vector[i] = PyFloat_AsDouble(item);
            } else {
                PyErr_SetString(PyExc_TypeError, "Vector3D() must take tuple of floats, or ints");
                return -1;
            }
        }
        vector.set();
    } else if (PyList_Check(v) && (PyList_Size(v) == 3)) {
        for(int i = 0; i < 3; i++) {
            PyObject * item = PyList_GetItem(v, i);
            if (PyInt_Check(item)) {
                vector[i] = (double)PyInt_AsLong(item);
            } else if (PyFloat_Check(item)) {
                vector[i] = PyFloat_AsDouble(item);
            } else {
                PyErr_SetString(PyExc_TypeError, "Vector3D() must take list of floats, or ints");
                return -1;
            }
        }
        vector.set();
    } else {
        PyErr_SetString(PyExc_TypeError, "arg must be a vector");
        return -1;
    }
    if (strcmp(name, "coordinates") == 0) {
        self->location->m_pos = vector;
    }
    if (strcmp(name, "velocity") == 0) {
        self->location->m_velocity = vector;
    }
    if (strcmp(name, "bbox") == 0) {
        self->location->m_bBox = BBox(vector);
    }
    return 0;
}

PyTypeObject Location_Type = {
	PyObject_HEAD_INIT(&PyType_Type)
	0,				/*ob_size*/
	"Location",			/*tp_name*/
	sizeof(LocationObject),		/*tp_basicsize*/
	0,				/*tp_itemsize*/
	/* methods */
	(destructor)Location_dealloc,	/*tp_dealloc*/
	0,				/*tp_print*/
	(getattrfunc)Location_getattr,	/*tp_getattr*/
	(setattrfunc)Location_setattr,	/*tp_setattr*/
	0,				/*tp_compare*/
	0,				/*tp_repr*/
	0,				/*tp_as_number*/
	0,				/*tp_as_sequence*/
	0,				/*tp_as_mapping*/
	0,				/*tp_hash*/
};

LocationObject * newLocationObject(PyObject *arg)
{
	LocationObject * self;
	self = PyObject_NEW(LocationObject, &Location_Type);
	if (self == NULL) {
		return NULL;
	}
        self->location = NULL;
        self->own = 0;
	return self;
}
