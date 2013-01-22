/*
 * LineColorConstraint.hpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#ifndef LINECOLORCONSTRAINT_HPP_
#define LINECOLORCONSTRAINT_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>

#include "Types/Line.hpp"
#include "LineSegment.hpp"
#include "AbstractConstraint.hpp"

#define BLUE	1
#define RED		2
#define GREEN	3
#define YELLOW	4

namespace Processors {
namespace CspBlockObjectRecognize {

class LineColorConstraint: public Processors::CspBlockObjectRecognize::AbstractConstraint
{
public:
	/**
	 *
	 * @param node
	 * @return
	 */
	LineColorConstraint(const boost::property_tree::ptree& node);
	virtual ~LineColorConstraint();

	/**
	 * Check if second line has specified length (compared to the first line).
	 * @param first
	 * @param second
	 * @return
	 */
	virtual bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);

private:
	 int color;
};

}
}

#endif /* LINECOLORCONSTRAINT_HPP_ */
