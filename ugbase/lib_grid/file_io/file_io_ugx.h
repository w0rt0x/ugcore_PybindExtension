//	created by Sebastian Reiter
//	s.b.reiter@googlemail.com
//	y10 m06 d16

#include <iostream>
#include <vector>
#include "../lg_base.h"
#include "common/parser/rapidxml/rapidxml.hpp"

#ifndef __H__LIB_GRID__FILE_IO_UGX__
#define __H__LIB_GRID__FILE_IO_UGX__

namespace ug
{

////////////////////////////////////////////////////////////////////////
///	Writes a grid to an ugx file. internally uses GridWriterUGX.
//...
////////////////////////////////////////////////////////////////////////
///	Reads a grid to an ugx file. internally uses GridReaderUGX.
//...

////////////////////////////////////////////////////////////////////////
///	Grants write access to ugx files.
/**	Make sure that all elements added via one of the add_* methods
 *	exist until the FileAccessor is destroyed.
 */
class GridWriterUGX
{
	public:
		GridWriterUGX();
		virtual ~GridWriterUGX();
		
	/**	TPositionAttachments value type has to be compatible with MathVector.
	 *	Make sure that aPos is attached to the vertices of the grid.*/
		template <class TPositionAttachment>
		bool add_grid(Grid& grid, const char* name,
					  TPositionAttachment& aPos);
					  
		template <class TPositionAttachment>
		void add_grid(MultiGrid* mg, const char* name,
					  TPositionAttachment& aPos);
					  		
		void add_subset_handler(SubsetHandler* sh, const char* name,
								size_t refGridIndex);
								
		void add_subset_handler(MGSubsetHandler* mgsh, const char* name,
								size_t refGridIndex);
		
		template <class TAttachment>
		void add_vertex_attachment(const TAttachment& attachment,
									const char* name,
									size_t refGridIndex);
									
		virtual bool write_to_stream(std::ostream& out);
		
		bool write_to_file(const char* filename);
		
	protected:
		typedef Grid::VertexAttachmentAccessor<AInt> AAVrtIndex;
		
	protected:
		template <class TAAPos>
		rapidxml::xml_node<>*
		create_vertex_node(VertexIterator vrtsBegin,
						  VertexIterator vrtsEnd,
						  TAAPos& aaPos);
		
	///	adds grid elements (edges, faces, volumes) to the given node.
		void add_elements_to_node(rapidxml::xml_node<>* node,
								  Grid& grid,
								  AAVrtIndex aaIndVRT);
								  
		rapidxml::xml_node<>*
		create_edge_node(EdgeIterator edgesBegin,
						 EdgeIterator edgesEnd,
						 AAVrtIndex aaIndVRT);

		rapidxml::xml_node<>*
		create_triangle_node(TriangleIterator trisBegin,
							 TriangleIterator trisEnd,
							 AAVrtIndex aaIndVRT);

		rapidxml::xml_node<>*
		create_quadrilateral_node(QuadrilateralIterator quadsBegin,
								  QuadrilateralIterator quadsEnd,
								  AAVrtIndex aaIndVRT);
		
		rapidxml::xml_node<>*
		create_tetrahedron_node(TetrahedronIterator tetsBegin,
								  TetrahedronIterator tetsEnd,
								  AAVrtIndex aaIndVRT);
								  
		rapidxml::xml_node<>*
		create_hexahedron_node(HexahedronIterator hexasBegin,
								  HexahedronIterator hexasEnd,
								  AAVrtIndex aaIndVRT);
								  
		rapidxml::xml_node<>*
		create_prism_node(PrismIterator prismsBegin,
							PrismIterator prismsEnd,
							AAVrtIndex aaIndVRT);

		rapidxml::xml_node<>*
		create_pyramid_node(PyramidIterator pyrasBegin,
							PyramidIterator pyrasEnd,
							AAVrtIndex aaIndVRT);
	protected:
	///	the xml_document which stores the data
		rapidxml::xml_document<> m_doc;
		
	///	List of accessible grids
		std::vector<Grid*> m_vGrids;
		
	///	attached to vertices of each grid during add_grid.
		AInt	m_aInt;
};

////////////////////////////////////////////////////////////////////////
///	Grants read access to ugx files.
/**	Before any data can be retrieved using the get_* methods, a file
 *	has to be successfully loaded using load_file.
 *
 *	\todo: Improve performance by using in-situ stringstreams during element creation.
 */
class GridReaderUGX
{
	public:
		GridReaderUGX();
		virtual ~GridReaderUGX();
		
	///	returns the number of grids
		inline size_t num_grids() const	{return m_entries.size();}
		
	///	returns the i-th grid.
	/**	TPositionAttachments value type has to be compatible with MathVector.
	 *	Make sure that a file has already been loaded.*/
		template <class TPositionAttachment>
		bool get_grid(Grid& gridOut, size_t index,
					  TPositionAttachment& aPos);
		
	///	returns the name of the i-th grid
		const char* get_grid_name(size_t index) const;
		
		
	///	parses an xml file
		bool parse_file(const char* filename);
	
	protected:
		struct GridEntry
		{
			GridEntry(rapidxml::xml_node<>* n) : node(n), grid(NULL), mg(NULL)	{}
			
			rapidxml::xml_node<>* node;
			Grid* 		grid;
			MultiGrid* 	mg;
			std::vector<VertexBase*> vertices;
		};
		
	protected:
	///	initializes internal arrays
	/**	searches for all grid-nodes and stores, resizes m_entries and stores
	 *	the node for each entry.
	 *
	 *	If you create your own version of this method, don't forget to call the
	 *	base-class implementation!*/
		virtual bool new_document_parsed();
	
	///	creates vertices from a vertex-node.
	/**	if aaPos has more coordinates per vertex than the vrtNode,
	 *	0's will be appended. If it has less, unused coordinates will
	 *	be ignored.*/
		template <class TAAPos>
		bool create_vertices(Grid& grid, rapidxml::xml_node<>* vrtNode,
							 std::vector<VertexBase*>& vrts, TAAPos aaPos);
							 
		bool create_edges(Grid& grid, rapidxml::xml_node<>* node,
			 			  std::vector<VertexBase*>& vrts);
		
		bool create_triangles(Grid& grid, rapidxml::xml_node<>* node,
							  std::vector<VertexBase*>& vrts);
							  
		bool create_quadrilaterals(Grid& grid, rapidxml::xml_node<>* node,
								   std::vector<VertexBase*>& vrts);
								   
		bool create_tetrahedrons(Grid& grid, rapidxml::xml_node<>* node,
						 		  std::vector<VertexBase*>& vrts);

		bool create_hexahedrons(Grid& grid, rapidxml::xml_node<>* node,
								std::vector<VertexBase*>& vrts);
								
		bool create_prisms(Grid& grid, rapidxml::xml_node<>* node,
							std::vector<VertexBase*>& vrts);
							
		bool create_pyramids(Grid& grid, rapidxml::xml_node<>* node,
							std::vector<VertexBase*>& vrts);
							
	protected:
	///	the xml_document which stores the data
		rapidxml::xml_document<> m_doc;
		
	///	holds grids which already have been created
		std::vector<GridEntry>	m_entries;
};

}//	end of namespace

////////////////////////////////
//	include implementation
#include "file_io_ugx_impl.hpp"

#endif
