/*
 * LinesPerpendicularConstraint.hpp
 *
 *  Created on: 14-12-2012
 *      Author: spiatek
 */

#ifndef LINESPERPENDICULARCONSTRAINT_HPP_
#define LINESPERPENDICULARCONSTRAINT_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>

#include "Types/Line.hpp"
#include "LineSegment.hpp"
#include "AbstractConstraint.hpp"

#define RAD_NA_ST 180.0/3.141592654;

namespace Processors {
namespace CspBlockObjectRecognize {

/**
 * Klasa sprawdzająca ograniczenie prostopadłości dla prostych
 */
class LinesPerpendicularConstraint: public Processors::CspBlockObjectRecognize::AbstractConstraint
{
public:
	/**
	 * Create constraint.
	 * @param node property maxDistance may exist.
	 * @return
	 */
	LinesPerpendicularConstraint(const boost::property_tree::ptree& node);
	virtual ~LinesPerpendicularConstraint();

	/**
	 * Check if line segments have common ends.
	 * @param first
	 * @param second
	 * @return true if an angle between the lines is nearly 90 degrees.
	 */
	virtual bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);
private:
	int maxAngleLines;
};

}
}

#endif /* LINESPERPENDICULARCONSTRAINT_HPP_ */
