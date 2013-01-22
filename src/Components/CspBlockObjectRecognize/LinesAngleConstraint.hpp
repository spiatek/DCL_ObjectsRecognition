/*!
 * \file LinesAngleConstraint.hpp
 * \brief
 * \author mboryn
 * \date 2011-01-22
 */

#ifndef LINESANGLECONSTRAINT_HPP_
#define LINESANGLECONSTRAINT_HPP_

#include <boost/property_tree/ptree.hpp>

#include "Types/Line.hpp"
#include "LineSegment.hpp"
#include "AbstractConstraint.hpp"

namespace Processors {

namespace CspBlockObjectRecognize {

/**
 * Constraint for angle between two line segments.
 * TODO: implement method isSatisifed().
 *
 * Properties:
 *
 * <b>minAngle</b>
 *
 * <b>maxAngle</b>
 */
class LinesAngleConstraint: public Processors::CspBlockObjectRecognize::AbstractConstraint
{
public:
	LinesAngleConstraint(const boost::property_tree::ptree& node);
	virtual ~LinesAngleConstraint();
	virtual bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);
private:
	int angleLines;
};

}

}

#endif /* LINESANGLECONSTRAINT_HPP_ */
