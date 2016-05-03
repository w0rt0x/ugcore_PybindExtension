/*
 * Copyright (c) 2014-2015:  G-CSC, Goethe University Frankfurt
 * Author: Sebastian Reiter
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

#ifndef __H__UG__cylindrical_falloff_projector__
#define __H__UG__cylindrical_falloff_projector__

#include "../refinement_callbacks.h"

namespace ug{

///	\addtogroup lib_grid_algorithms_refinement
///	@{

////////////////////////////////////////////////////////////////////////
///	calculates new positions of vertices by projecting on a cylinder
/**	Only vertices inside innerRadius are projected to a cylinder.
 * The ones outside of outerRadius are positioned through normal linear interpolation.
 * The ones in between are gradually processed from cylindrical-projection to
 * linear interpolation.
 *
 * Make sure to initialize the callback correctly. Use the same grid
 *	on which the refinement-operations will be performed. Make sure
 *	that aPos (given in the constructor) is attached to the vertices
 *	of the grid.
 *
 *	An uninitialized refinement-callback may not be used during refinement.
 */
template <class TAPosition>
class CylindricalFalloffProjector : public IRefinementCallback
{
	public:
		CylindricalFalloffProjector();

	///	make sure that aPos is attached to the vertices of the grid.
		CylindricalFalloffProjector(Grid& grid, TAPosition& aPos,
								   const typename TAPosition::ValueType& center,
								   const typename TAPosition::ValueType& axis,
								   number innerRadius, number outerRadius);

		virtual ~CylindricalFalloffProjector();

		virtual void new_vertex(Vertex* vrt, Vertex* parent);
		virtual void new_vertex(Vertex* vrt, Edge* parent);
		virtual void new_vertex(Vertex* vrt, Face* parent);
		virtual void new_vertex(Vertex* vrt, Volume* parent);

		virtual int current_pos(number* coordsOut, Vertex* vrt, int maxCoords);

	protected:
		template <class TElem>
		void perform_projection(Vertex* vrt, TElem* parent);

	protected:
		typedef typename TAPosition::ValueType		pos_type;

		Grid* 										m_pGrid;
		Grid::VertexAttachmentAccessor<TAPosition>	m_aaPos;
		pos_type									m_center;
		pos_type									m_axis;
		number										m_innerRadius;
		number										m_outerRadius;

	private:
		friend class boost::serialization::access;

		template <class Archive>
		void serialize( Archive& ar, const unsigned int version)
		{
			ar & make_nvp("center", m_center);
			ar & make_nvp("axis", m_axis);
			ar & make_nvp("innerRadius", m_innerRadius);
			ar & make_nvp("outerRadius", m_outerRadius);
			UG_EMPTY_BASE_CLASS_SERIALIZATION(CylindricalFalloffProjector, IRefinementCallback);
		}
};

/// @}

}// end of namespace

#include "cylindrical_falloff_projector_impl.h"

#endif
