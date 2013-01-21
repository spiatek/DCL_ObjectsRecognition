/*
 * LineColorConstraint.cpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#include <limits>
#include <iostream>

#include "LineColorConstraint.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

using namespace std;

LineColorConstraint::LineColorConstraint(const boost::property_tree::ptree& node)
{
	color = node.get<double>("<xmlattr>.color", 0);
}

LineColorConstraint::~LineColorConstraint()
{
}

bool LineColorConstraint::isSatisifed(boost::shared_ptr <AbstractShape> first, boost::shared_ptr <AbstractShape> second)
{
	if(first != NULL && second != NULL)
	{
		LineSegment* f = dynamic_cast <LineSegment*> (first.get());
		LineSegment* s = dynamic_cast <LineSegment*> (second.get());

		//std::cout << "Kolorki " << color << ", " << f->getColor() << ", " << s->getColor() << ".\n";
		if(color == s->getColor() && color == f->getColor())
		{
			return true;
		}
	}

	return false;
}

}
}
