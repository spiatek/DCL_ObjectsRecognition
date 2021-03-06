/*!
 * \file LinesLengthConstraint.hpp
 * \brief
 * \author mboryn
 * \date 2011-01-22
 */

#ifndef LINESLENGTHCONSTRAINT_HPP_
#define LINESLENGTHCONSTRAINT_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>

#include "Types/Line.hpp"
#include "LineSegment.hpp"
#include "AbstractConstraint.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

/**
 * Check if two line segments has lengths in given proportions.
 *
 * Properties:
 *
 * <b>minLengthAbsolute</b>
 *
 * <b>maxLengthAbsolute</b>
 *
 * <b>minLengthRelative</b>
 *
 * <b>maxLengthRelative</b>
 *
 */
class LinesLengthConstraint: public Processors::CspBlockObjectRecognize::AbstractConstraint
{
public:
	/**
	 *
	 * @param node
	 * @return
	 */
	LinesLengthConstraint(const boost::property_tree::ptree& node);
	virtual ~LinesLengthConstraint();

	/**
	 * Check if second line has specified length (compared to the first line).
	 * @param first
	 * @param second
	 * @return
	 */
	virtual bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);

private:
	 double minLengthAbsolute;
	 double maxLengthAbsolute;
	 double minLengthRelative;
	 double maxLengthRelative;
};

}
}

#endif /* LINESLENGTHCONSTRAINT_HPP_ */
