/*
 * Copyright (c) 2010-2015:  G-CSC, Goethe University Frankfurt
 * Author: Sam Gimbel
 * 
 * This file is part of UG4.
 * 
 * UG4 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 3 (as published by the
 * Free Software Foundation) with the following additional attribution
 * requirements (according to LGPL/GPL v3 §7):
 * 
 * (1) The following notice must be displayed in the Appropriate Legal Notices
 * of covered and combined works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (2) The following notice must be displayed at a prominent place in the
 * terminal output of covered works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (3) The following bibliography is recommended for citation and must be
 * preserved in all covered files:
 * "Reiter, S., Vogel, A., Heppner, I., Rupp, M., and Wittum, G. A massively
 *   parallel geometric multigrid solver on hierarchically distributed grids.
 *   Computing and visualization in science 16, 4 (2013), 151-164"
 * "Vogel, A., Reiter, S., Rupp, M., Nägel, A., and Wittum, G. UG4 -- a novel
 *   flexible software system for simulating pde based models on high performance
 *   computers. Computing and visualization in science 16, 4 (2013), 165-179"
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 */

#include <iostream>
#include "lib_disc/spatial_disc/user_data/std_glob_pos_data.h"
#include <Python.h>

namespace ug
{
////////////////////////////////////////////////////////////////////////////////
// Executing Python Code from Ug4
// Code has been passed as String to UG4
// More Info here: https://docs.python.org/3/extending/embedding.html#
// and also here: https://docs.python.org/3/c-api/ 
// also make sure to have python3-dev installed to use the python header:
// sudo apt install python3-dev
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PythonUserFunction
// Please Note: This is just a quick fix
// the PythonUserFunction class should be extended like the lua equivalent class
////////////////////////////////////////////////////////////////////////////////

template <typename TData, int dim, typename TRet = void>
class PythonUserData
	: public StdGlobPosData<PythonUserData<TData, dim, TRet>, TData, dim, TRet>
{

	public:
	///	Constructor
	/**
	 * Creates a PythonUserData that uses a Python function to evaluate some data.
	 */
		PythonUserData(const char* func, const char* funcname){ // Constructor with parameter
			PyRun_SimpleString(func);
			PyObject* pModule = PyImport_ImportModule("__main__");
    		pFunc =  PyObject_GetAttrString(pModule, funcname);
			pArgs = PyTuple_New(dim+2);
		}


	///	evaluates the data at a given point and time
		inline TRet evaluate(TData& D, const MathVector<dim>& x, number time, int si) const {
			for(int i=0; i < dim; ++i){
				PyTuple_SetItem(pArgs, i, PyLong_FromDouble(x[i]));
			}
			PyTuple_SetItem(pArgs, dim, PyLong_FromDouble(time));
			PyTuple_SetItem(pArgs, dim+1, PyLong_FromDouble(si));

			PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
			D = PyFloat_AsDouble(pResult);
		};


	protected:
	///	sets that PythonUserData is created by DataFactory (not implemented for python)
		void set_created_from_factory(bool bFromFactory=false) {m_bFromFactory = bFromFactory;}

	protected:
	///	callback name as string
		PyObject* pArgs;
		PyObject* pFunc;

	///	reference to nothing - unused
		int m_callbackRef;
		
	///	flag, indicating if created from factory
		bool m_bFromFactory;

};
} // end of namespace ug
