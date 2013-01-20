/*
 * LinesPerpendicularConstraint.cpp
 *
 *  Created on: 14-12-2012
 *      Author: spiatek
 */

#include "LinesPerpendicularConstraint.hpp"
#include "LineSegment.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

LinesPerpendicularConstraint::LinesPerpendicularConstraint(const boost::property_tree::ptree& node)
{
	maxAngleLines = node.get<double>("maxAngleLines", );
}

LinesPerpendicularConstraint::~LinesPerpendicularConstraint()
{
}

bool LinesPerpendicularConstraint::isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second)
{
	double dir = 0.0;
	double a1, b1, c1;
	double a2, b2, c2;
	double angle;

	LineSegment *firstLine = dynamic_cast <LineSegment*> (first.get());
	LineSegment *secondLine = dynamic_cast <LineSegment*> (second.get());
	if (firstLine == NULL || secondLine == NULL) {
		return false;
	}

	firstLine->getLine(&a1, &b1, &c1);
	secondLine->getLine(&a2, &b2, &c2);

	dir = Math::AngleLines(a1, b1, a2, b2);
	angle = dir * Settings::RAD_NA_ST;

	if(angle >= 90 - maxAngleLines || 90.0 - fabs(angle) >= 90 - maxAngleLines)
	{
		return true;
	}

	return false;
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
