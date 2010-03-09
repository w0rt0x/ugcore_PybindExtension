// created by Sebastian Reiter
// s.b.reiter@googlemail.com
// y09 m12 d09

#include "lib_grid/lg_base.h"
#include "pcl/pcl_communication.h"

#ifndef __H__PLG__COPY_POLICY__
#define __H__PLG__COPY_POLICY__

namespace ug
{

////////////////////////////////////////////////////////////////////////
//	CopyPolicy
///	copies values from a specified attachment to a stream and back.
/**
 * pcl::group_traits::LocalID has to match either VertexBase*, EdgeBase*,
 * Face* or Volume*.
 */
template <class TGeomObj, class TLayout, class TAttachment>
class CopyPolicy : public pcl::ICommunicationPolicy<TLayout>
{
	public:
		typedef TGeomObj						GeomObj;
		typedef typename TLayout::Element		Element;
		typedef typename TLayout::Interface		Interface;
		typedef typename TAttachment::ValueType Value;
		
	///	Initialises the collector with an invalid grid.
	/**	be sure to call set_source before passing it to a communicator.*/
		CopyPolicy();
		
	///	Calls set_target internally.
		CopyPolicy(Grid& grid, TAttachment& attachment);
		
	///	The grid and the attachment from where the data shall be copied.
	/**	Make sure that attachment is attached to the correct
	 *	element-type of the grid.*/
		void set_attachment(Grid& grid, TAttachment& attachment);
		
	///	writes the data for the given interface to the buffer.
	/**	Derived from ICollector
	 *	Make sure that all members of the interface are members of the
	 *	grid too.*/
		virtual bool
		collect(std::ostream& buff, Interface& interface);
		
	///	reads the data from the buffer to the given interface .
	/**	Derived from IExtractor
	 *	Make sure that all members of the interface are members of the
	 *	grid too.*/
		virtual bool
		extract(std::istream& buff, Interface& interface);
		
	protected:
		Grid::AttachmentAccessor<GeomObj, TAttachment>	m_aaVal;
};



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//	implementation of the methods of CollectorCopy
////////////////////////////////////////////////////////////////////////
template <class TGeomObj, class TLayout, class TAttachment>
CopyPolicy<TGeomObj, TLayout, TAttachment>::
CopyPolicy()
{
}

////////////////////////////////////////////////////////////////////////
template <class TGeomObj, class TLayout, class TAttachment>
CopyPolicy<TGeomObj, TLayout, TAttachment>::
CopyPolicy(Grid& grid, TAttachment& attachment)
{
	set_attachment(grid, attachment);
}

////////////////////////////////////////////////////////////////////////
template <class TGeomObj, class TLayout, class TAttachment>
void
CopyPolicy<TGeomObj, TLayout, TAttachment>::
set_attachment(Grid& grid, TAttachment& attachment)
{
	m_aaVal.access(grid, attachment);
}

////////////////////////////////////////////////////////////////////////
template <class TGeomObj, class TLayout, class TAttachment>
bool
CopyPolicy<TGeomObj, TLayout, TAttachment>::
collect(std::ostream& buff, Interface& interface)
{
	for(typename Interface::iterator iter = interface.begin();
		iter != interface.end(); ++iter)
		buff.write((char*)&m_aaVal[interface.get_element(iter)], sizeof(Value));
}

////////////////////////////////////////////////////////////////////////
template <class TGeomObj, class TLayout, class TAttachment>
bool
CopyPolicy<TGeomObj, TLayout, TAttachment>::
extract(std::istream& buff, Interface& interface)
{
	for(typename Interface::iterator iter = interface.begin();
		iter != interface.end(); ++iter)
		buff.read((char*)&m_aaVal[interface.get_element(iter)], sizeof(Value));
}

};

#endif
