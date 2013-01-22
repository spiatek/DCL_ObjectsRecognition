/*
 * LinesAngleConstraint.cpp
 *
 *  Created on: 09-01-2011
 *      Author: mateusz
 */

#include "LinesAngleConstraint.hpp"

namespace Processors {

namespace CspBlockObjectRecognize {

LinesAngleConstraint::LinesAngleConstraint(const boost::property_tree::ptree& node)
{
	angleLines = node.get<double>("<xmlattr>.angleLines", 0);

}

LinesAngleConstraint::~LinesAngleConstraint()
{
	// TODO Auto-generated destructor stub
}

bool LinesAngleConstraint::isSatisfied(boost::shared_ptr <AbstractShape> first, boost::shared_ptr <AbstractShape> second)
{
	return false;
}

}
}
