/*
 * neumann_boundary_base.h
 *
 *  Created on: 14.10.2010
 *      Author: andreasvogel
 */

#include "neumann_boundary_base.h"
#include "lib_disc/common/groups_util.h"
#include "lib_disc/spatial_disc/user_data/const_user_data.h"

#ifdef UG_FOR_LUA
#include "bindings/lua/lua_user_data.h"
#endif

namespace ug{
////////////////////////////////////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////////////////////////////////////

template<typename TDomain>
NeumannBoundaryBase<TDomain>::NeumannBoundaryBase(const char* function)
 :IElemDisc<TDomain>(function, "")
{
	m_bDiffusion = false;
	if(this->num_fct() != 1)
		UG_THROW("NeumannBoundaryBase: needed exactly one function.");
}

////////////////////////////////////////////////////////////////////////////////
// User Data
////////////////////////////////////////////////////////////////////////////////



template<typename TDomain>
void NeumannBoundaryBase<TDomain>::
update_subset_groups(Data& userData)
{
//	create Function Group and Subset Group
	FunctionGroup functionGroup;

//	convert strings
	try{
		userData.InnerSSGrp = this->approx_space()->subset_grp_by_name(userData.InnerSubsetNames.c_str());
	}UG_CATCH_THROW("NeumannBoundaryBase:"
					" Subsets '"<<userData.InnerSubsetNames<<"' not"
					" all contained in ApproximationSpace.");
	try{
		userData.BndSSGrp = this->approx_space()->subset_grp_by_name(userData.BndSubsetNames.c_str());
	}UG_CATCH_THROW("NeumannBoundaryBase:"
					" Subsets '"<<userData.BndSubsetNames<<"' not"
					" all contained in ApproximationSpace.");
}

template<typename TDomain>
void NeumannBoundaryBase<TDomain>::
add_inner_subsets(const char* InnerSubsets)
{
	std::vector<std::string> vSubsets = this->symb_subsets();
	std::vector<std::string> vNew = TokenizeTrimString(InnerSubsets);
	for(size_t i = 0; i < vNew.size(); ++i)
		if(std::find(vSubsets.begin(), vSubsets.end(), vNew[i]) == vSubsets.end())
			vSubsets.push_back(vNew[i]);
	this->set_subsets(vSubsets);

}

template<typename TDomain>
void NeumannBoundaryBase<TDomain>::
add(number val, const char* function, const char* subsets)
{
	SmartPtr<CplUserData<number, dim> > sp = make_sp(new ConstUserNumber<dim>(val));
	add(sp, function, subsets);
}

template<typename TDomain>
void NeumannBoundaryBase<TDomain>::
add(const std::vector<number>& val, const char* function, const char* subsets)
{
	SmartPtr<CplUserData<MathVector<dim>, dim> > sp = make_sp(new ConstUserVector<dim>(val));
	add(sp, function, subsets);
}





#ifdef UG_FOR_LUA
template <typename TDomain>
void NeumannBoundaryBase<TDomain>::
add(const char* name, const char* function, const char* subsets)
{
	if(LuaUserData<number, dim>::check_callback_returns(name)){
		SmartPtr<CplUserData<number, dim> > sp =
							LuaUserDataFactory<number, dim>::create(name);
		add(sp, function, subsets);
		return;
	}
	if(LuaUserData<number, dim, bool>::check_callback_returns(name)){
		SmartPtr<CplUserData<number, dim, bool> > sp =
				LuaUserDataFactory<number, dim, bool>::create(name);
		add(sp, function, subsets);
		return;
	}
	if(LuaUserData<MathVector<dim>, dim>::check_callback_returns(name)){
		SmartPtr<CplUserData<MathVector<dim>, dim> > sp =
				LuaUserDataFactory<MathVector<dim>, dim>::create(name);
		add(sp, function, subsets);
		return;
	}

//	no match found
	if(!CheckLuaCallbackName(name))
		UG_THROW("NeumannBoundaryBase: Lua-Callback with name '"<<name<<
		               "' does not exist.");

//	name exists but wrong signature
	UG_THROW("NeumannBoundaryBase: Cannot find matching callback "
					"signature. Use one of:\n"
					"a) Number - Callback\n"
					<< (LuaUserData<number, dim>::signature()) << "\n" <<
					"b) Conditional Number - Callback\n"
					<< (LuaUserData<number, dim, bool>::signature()) << "\n" <<
					"c) "<<dim<<"d Vector - Callback\n"
					<< (LuaUserData<MathVector<dim>, dim>::signature()));
}
#endif



#ifdef UG_FOR_LUA
template <typename TDomain>
void NeumannBoundaryBase<TDomain>::
add(const char* nameMatrix, const char* nameVector, const char* function, const char* subsets)
{
	if(LuaUserData<MathVector<dim>, dim>::check_callback_returns(nameVector)){
		SmartPtr<CplUserData<MathVector<dim>, dim> > sp =
			LuaUserDataFactory<MathVector<dim>, dim>::create(nameVector);

		if(LuaUserData<MathMatrix<dim, dim>, dim>::check_callback_returns(nameMatrix)){
			SmartPtr<CplUserData<MathMatrix<dim, dim>, dim> > spM =
				LuaUserDataFactory<MathMatrix<dim, dim>, dim>::create(nameMatrix);

			m_bDiffusion = true;
			add(spM, sp, function, subsets);
			return;
		}
	}

//	no match found
	if(!CheckLuaCallbackName(nameVector))
		UG_THROW("NeumannBoundaryBase: Lua-Callback with name '"<<nameVector<<
		               "' does not exist.");

	if(!CheckLuaCallbackName(nameMatrix))
		UG_THROW("NeumannBoundaryBase: Lua-Callback with name '"<<nameMatrix<<
		               "' does not exist.");


//	name exists but wrong signature
	UG_THROW("NeumannBoundaryBase: Cannot find matching callback "
					"signature. Use one of:\n"
					"a) Number - Callback\n"
					<< (LuaUserData<number, dim>::signature()) << "\n" <<
					"b) Conditional Number - Callback\n"
					<< (LuaUserData<number, dim, bool>::signature()) << "\n" <<
					"c) "<<dim<<"d Vector - Callback\n"
					<< (LuaUserData<MathVector<dim>, dim>::signature()));
}

template <typename TDomain>
void NeumannBoundaryBase<TDomain>::
add(const char* nameMatrix, SmartPtr<CplUserData<MathVector<dim>, dim> > user, const char* function, const char* subsets)
{
	if(LuaUserData<MathMatrix<dim, dim>, dim>::check_callback_returns(nameMatrix)){
		SmartPtr<CplUserData<MathMatrix<dim, dim>, dim> > spM =
			LuaUserDataFactory<MathMatrix<dim, dim>, dim>::create(nameMatrix);

		m_bDiffusion = true;
		add(spM, user, function, subsets);
		return;
	}


	if(!CheckLuaCallbackName(nameMatrix))
		UG_THROW("NeumannBoundaryBase: Lua-Callback with name '"<<nameMatrix<<
		               "' does not exist.");

}







#endif





////////////////////////////////////////////////////////////////////////////////
//	explicit template instantiations
////////////////////////////////////////////////////////////////////////////////

#ifdef UG_DIM_1
template class NeumannBoundaryBase<Domain1d>;
#endif
#ifdef UG_DIM_2
template class NeumannBoundaryBase<Domain2d>;
#endif
#ifdef UG_DIM_3
template class NeumannBoundaryBase<Domain3d>;
#endif

} // namespace ug

