// created by Sebastian Reiter
// s.b.reiter@googlemail.com
// 31.05.2011 (m,d,y)

#ifndef __H__UG__hexahedron_rules__
#define __H__UG__hexahedron_rules__

namespace ug{
namespace hex_rules{

////////////////////////////////////////////////////////////////////////////////
//	LOOKUP TABLES

const int NUM_VERTICES	= 8;
const int NUM_EDGES		= 12;
const int NUM_FACES		= 6;
const int NUM_TRIS		= 0;
const int NUM_QUADS		= 6;
const int MAX_NUM_INDS_OUT = 128;//todo: this is just an estimate!

///	the local vertex indices of the given edge
const int EDGE_VRT_INDS[][2] = {	{0, 1}, {1, 2}, {2, 3}, {3, 0},
									{0, 4}, {1, 5}, {2, 6}, {3, 7},
									{4, 5}, {5, 6}, {6, 7}, {7, 4}};

///	the local vertex indices of the given face
const int FACE_VRT_INDS[][4] = {	{0, 3, 2, 1},	{0, 1, 5, 4},
									{1, 2, 6, 5},	{2, 3, 7, 6},
									{3, 0, 4, 7},	{4, 5, 6, 7}};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//	NOTE: The lists below are all generated automatically

///	returns the j-th edge of the i-th face
const int FACE_EDGE_INDS[6][4] = {{3, 2, 1, 0}, {0, 5, 8, 4}, {1, 6, 9, 5},
								  {2, 7, 10, 6}, {3, 4, 11, 7}, {8, 9, 10, 11}};

///	tells whether the i-th face contains the j-th edge
const int FACE_CONTAINS_EDGE[][12] =	{{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
										 {1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
										 {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
										 {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0},
										 {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1},
										 {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

///	Associates the index of the connecting edge with each tuple of vertices.
/**	Use two vertex indices to index into this table to retrieve the index
 * of their connecting edge.
 */
const int EDGE_FROM_VRTS[8][8] =
				{{-1, 0, -1, 3, 4, -1, -1, -1}, {0, -1, 1, -1, -1, 5, -1, -1},
				 {-1, 1, -1, 2, -1, -1, 6, -1}, {3, -1, 2, -1, -1, -1, -1, 7},
				 {4, -1, -1, -1, -1, 8, -1, 11}, {-1, 5, -1, -1, 8, -1, 9, -1},
				 {-1, -1, 6, -1, -1, 9, -1, 10}, {-1, -1, -1, 7, 11, -1, 10, -1}};

///	Associates the index of the connecting face with each triple of vertices.
/**	Use three vertex indices to index into this table to retrieve the index
 * of their connecting face.
 */
const int FACE_FROM_VRTS[8][8][8] =
			{{{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, 0, 0, 1, 1, -1, -1},
			  {-1, 0, -1, 0, -1, -1, -1, -1}, {-1, 0, 0, -1, 4, -1, -1, 4},
			  {-1, 1, -1, 4, -1, 1, -1, 4}, {-1, 1, -1, -1, 1, -1, -1, -1},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, 4, 4, -1, -1, -1}},
			 {{-1, -1, 0, 0, 1, 1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {0, -1, -1, 0, -1, 2, 2, -1}, {0, -1, 0, -1, -1, -1, -1, -1},
			  {1, -1, -1, -1, -1, 1, -1, -1}, {1, -1, 2, -1, 1, -1, 2, -1},
			  {-1, -1, 2, -1, -1, 2, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}},
			 {{-1, 0, -1, 0, -1, -1, -1, -1}, {0, -1, -1, 0, -1, 2, 2, -1},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {0, 0, -1, -1, -1, -1, 3, 3},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, 2, -1, -1, -1, -1, 2, -1},
			  {-1, 2, -1, 3, -1, 2, -1, 3}, {-1, -1, -1, 3, -1, -1, 3, -1}},
			 {{-1, 0, 0, -1, 4, -1, -1, 4}, {0, -1, 0, -1, -1, -1, -1, -1},
			  {0, 0, -1, -1, -1, -1, 3, 3}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {4, -1, -1, -1, -1, -1, -1, 4}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {-1, -1, 3, -1, -1, -1, -1, 3}, {4, -1, 3, -1, 4, -1, 3, -1}},
			 {{-1, 1, -1, 4, -1, 1, -1, 4}, {1, -1, -1, -1, -1, 1, -1, -1},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {4, -1, -1, -1, -1, -1, -1, 4},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {1, 1, -1, -1, -1, -1, 5, 5},
			  {-1, -1, -1, -1, -1, 5, -1, 5}, {4, -1, -1, 4, -1, 5, 5, -1}},
			 {{-1, 1, -1, -1, 1, -1, -1, -1}, {1, -1, 2, -1, 1, -1, 2, -1},
			  {-1, 2, -1, -1, -1, -1, 2, -1}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {1, 1, -1, -1, -1, -1, 5, 5}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {-1, 2, 2, -1, 5, -1, -1, 5}, {-1, -1, -1, -1, 5, -1, 5, -1}},
			 {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, 2, -1, -1, 2, -1, -1},
			  {-1, 2, -1, 3, -1, 2, -1, 3}, {-1, -1, 3, -1, -1, -1, -1, 3},
			  {-1, -1, -1, -1, -1, 5, -1, 5}, {-1, 2, 2, -1, 5, -1, -1, 5},
			  {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, 3, 3, 5, 5, -1, -1}},
			 {{-1, -1, -1, 4, 4, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1},
			  {-1, -1, -1, 3, -1, -1, 3, -1}, {4, -1, 3, -1, 4, -1, 3, -1},
			  {4, -1, -1, 4, -1, 5, 5, -1}, {-1, -1, -1, -1, 5, -1, 5, -1},
			  {-1, -1, 3, 3, 5, 5, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}}};

///	given two edges, the table returns the face, which contains both (or -1)
const int FACE_FROM_EDGES[][12] =	{{0, 0, 0, 0, 1, 1, -1, -1, 1, -1, -1, -1},
									 {0, 0, 0, 0, -1, 2, 2, -1, -1, 2, -1, -1},
									 {0, 0, 0, 0, -1, -1, 3, 3, -1, -1, 3, -1},
									 {0, 0, 0, 0, 4, -1, -1, 4, -1, -1, -1, 4},
									 {1, -1, -1, 4, 1, 1, -1, 4, 1, -1, -1, 4},
									 {1, 2, -1, -1, 1, 1, 2, -1, 1, 2, -1, -1},
									 {-1, 2, 3, -1, -1, 2, 2, 3, -1, 2, 3, -1},
									 {-1, -1, 3, 4, 4, -1, 3, 3, -1, -1, 3, 4},
									 {1, -1, -1, -1, 1, 1, -1, -1, 1, 5, 5, 5},
									 {-1, 2, -1, -1, -1, 2, 2, -1, 5, 2, 5, 5},
									 {-1, -1, 3, -1, -1, -1, 3, 3, 5, 5, 3, 5},
									 {-1, -1, -1, 4, 4, -1, -1, 4, 5, 5, 5, 4}};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**	returns an array of integers, which contains the indices of the objects
 * resulting from the refinement of a pyramid.
 *
 *
 * \param newIndsOut	Array which has to be of size MAX_NUM_INDS_OUT.
 * 						When the algorithm is done, the array will contain
 * 						sequences of integers: {{numInds, ind1, ind2, ...}, ...}.
 * 						Old vertices are referenced by their local index. Vertices
 * 						created on an edge are indexed by the index of the edge +
 * 						NUM_VERTICES.
 * 						Vertices created on a face are referenced by
 * 						NUM_VERTICES + NUM_EDGES + index_of_face.
 * 						If an inner vertex has to be created, it is referenced
 * 						by NUM_VERTICES + NUM_EDGES + NUM_FACES (in this case
 * 						newCenterOut is set to true).
 *
 * \param newEdgeVrts	Array of size NUM_EDGES, which has to contain 1 for each
 * 						edge, which shall be refined and 0 for each edge, which
 * 						won't be refined.
 *
 * \param newCenterOut	If the refinement-rule requires a center vertex, then
 * 						this parameter will be set to true. If not, it is set to
 * 						false.
 *
 * \returns	the number of entries written to newIndsOut or 0, if the refinement
 * 			could not be performed.
 */
int Refine(int* newIndsOut, int* newEdgeVrts, bool& newCenterOut);

}//	end of namespace
}//	end of namespace

#endif
