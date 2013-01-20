/*!
 * \file ParallelLineConstraint.cpp
 * \brief
 * \author spiatek
 * \date 2012-12-13
 */

#include "ParallelLineConstraint.hpp"

#include "LineSegment.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

ParallelLineConstraint::ParallelLineConstraint(const boost::property_tree::ptree& node)
{
	angle = node.get<double>("angle", 15.0);
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

	//firstLine->getLine(&a1, &b1, &c1);
	//secondLine->getLine(&a2, &b2, &c2);

	dir = Math::AngleLines(a1, b1, a2, b2);
	ang = dir*180.0/3.1415926;

	if(ang <= angle) {
		return true;
	}

	return false;
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
