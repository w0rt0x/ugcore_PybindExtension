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

#ifndef __H__UG__sphere_projector_impl__
#define __H__UG__sphere_projector_impl__

#include "sphere_projector.h"

namespace ug{

template <class TAPosition>
SphereProjector<TAPosition>::
SphereProjector() :
	m_pGrid(NULL)
{
}

template <class TAPosition>
SphereProjector<TAPosition>::
SphereProjector(Grid& grid, TAPosition& aPos,
				const typename TAPosition::ValueType& center) :
	m_pGrid(&grid),
	m_center(center),
	m_radius(-1)
{
//	we have to make sure that aPos is attached at the grid.
//	This is important to avoid crashes later on.
	if(!grid.has_vertex_attachment(aPos))
		grid.attach_to_vertices(aPos);
	m_aaPos.access(grid, aPos);
}

template <class TAPosition>
SphereProjector<TAPosition>::
SphereProjector(Grid& grid, TAPosition& aPos,
						 const typename TAPosition::ValueType& center,
						 number radius) :
	m_pGrid(&grid),
	m_center(center),
	m_radius(radius)
{
//	we have to make sure that aPos is attached at the grid.
//	This is important to avoid crashes later on.
	if(!grid.has_vertex_attachment(aPos))
		grid.attach_to_vertices(aPos);
	m_aaPos.access(grid, aPos);
}


template <class TAPosition>
SphereProjector<TAPosition>::
~SphereProjector()
{
}

template <class TAPosition>
void SphereProjector<TAPosition>::
new_vertex(Vertex* vrt, Vertex* parent)
{
	assert(m_aaPos.valid() && "make sure to initialise the refiner-callback correctly.");
	m_aaPos[vrt] = m_aaPos[parent];
}

template <class TAPosition>
void SphereProjector<TAPosition>::
new_vertex(Vertex* vrt, Edge* parent)
{
	perform_projection(vrt, parent);
}

template <class TAPosition>
void SphereProjector<TAPosition>::
new_vertex(Vertex* vrt, Face* parent)
{
	perform_projection(vrt, parent);
}

template <class TAPosition>
void SphereProjector<TAPosition>::
new_vertex(Vertex* vrt, Volume* parent)
{
	perform_projection(vrt, parent);
}

template <class TAPosition>
int SphereProjector<TAPosition>::
current_pos(number* coordsOut, Vertex* vrt, int maxCoords)
{
	return IRefinementCallback::current_pos_helper(coordsOut, vrt, maxCoords, m_aaPos);
}

template <class TAPosition>
template <class TElem>
void SphereProjector<TAPosition>::
perform_projection(Vertex* vrt, TElem* parent)
{
	assert(m_aaPos.valid() && "make sure to initialise the refiner-callback correctly.");

//	first calculate the average distance of corners of parent and the parents center
	typename TElem::ConstVertexArray vrts = parent->vertices();
	size_t numVrts = parent->num_vertices();
	number avDist = 0;
	pos_type parentCenter;
	VecSet(parentCenter, 0);

	for(size_t i = 0; i < numVrts; ++i){
		const pos_type& p = m_aaPos[vrts[i]];
		avDist += VecDistance(p, m_center);
		VecAdd(parentCenter, parentCenter, p);
	}

	avDist /= (number)numVrts;
	VecScale(parentCenter, parentCenter, 1. / (number)numVrts);

	if(vrt->is_constrained()){
		m_aaPos[vrt] = parentCenter;
		return;
	}

//	calculate projection
	pos_type cylProj;
	VecSubtract(cylProj, parentCenter, m_center);
	number len = VecLength(cylProj);
	if(len > SMALL * avDist){	// if avDist is very small, len may be small, too
		VecScale(cylProj, cylProj, avDist / len);
		VecAdd(m_aaPos[vrt], cylProj, m_center);
	}
	else
		m_aaPos[vrt] = parentCenter;
}

}// end of namespace

#endif
