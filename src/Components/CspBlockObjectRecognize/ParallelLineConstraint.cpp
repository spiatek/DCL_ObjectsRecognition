/*
 * ParallelLineConstraint.cpp
 *
 *  Created on: 13-12-2012
 *      Author: spiatek
 */

#include "ParallelLineConstraint.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

ParallelLineConstraint::ParallelLineConstraint(const boost::property_tree::ptree& node)
{
	angle = node.get<double>("<xmlattr>.angle", 15.0);
}

ParallelLineConstraint::~ParallelLineConstraint()
{
}

bool ParallelLineConstraint::isSatisifed(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second)
{
	double a1 = 0.0, b1 = 0.0, c1 = 0.0;
	double a2 = 0.0, b2 = 0.0, c2 = 0.0;

	double dir = 0.0, ang;

	LineSegment *firstLine = dynamic_cast <LineSegment*> (first.get());
	LineSegment *secondLine = dynamic_cast <LineSegment*> (second.get());

	if(firstLine == NULL || secondLine == NULL) {
		return false;
	}

	firstLine->getLineParams(&a1, &b1, &c1);
	secondLine->getLineParams(&a2, &b2, &c2);

	dir = Math::AngleLines(a1, b1, a2, b2);
	ang = dir*180.0/3.1415926;

	if(ang <= angle) {
		return true;
	}

	return false;
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
