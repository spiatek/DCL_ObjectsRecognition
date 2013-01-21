/*
 * LinesLengthConstraint.cpp
 *
 *  Created on: 09-01-2011
 *      Author: mateusz
 */

#include <limits>
#include <iostream>

#include "LinesLengthConstraint.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

using namespace std;

LinesLengthConstraint::LinesLengthConstraint(const boost::property_tree::ptree& node)
{
	minLengthAbsolute = node.get<double>("<xmlattr>.minLengthAbsolute", numeric_limits<double>::infinity());
	maxLengthAbsolute = node.get<double>("<xmlattr>.maxLengthAbsolute", numeric_limits<double>::infinity());
	minLengthRelative = node.get<double>("<xmlattr>.minLengthRelative", numeric_limits<double>::infinity());
	maxLengthRelative = node.get<double>("<xmlattr>.maxLengthRelative", numeric_limits<double>::infinity());
}

LinesLengthConstraint::~LinesLengthConstraint()
{
}

bool LinesLengthConstraint::isSatisifed(boost::shared_ptr <AbstractShape> first, boost::shared_ptr <AbstractShape> second)
{
	double length1;
	double length2;
	double k;

	if(first != NULL && second != NULL)
	{
		LineSegment* f = dynamic_cast <LineSegment*> (first.get());
		LineSegment* s = dynamic_cast <LineSegment*> (second.get());

		length1 = (f->getLine()).getLength();
		length2 = (s->getLine()).getLength();

		if(length1 >= length2)
		{
			k = length1 / length2;
		}
		else
		{
			k = length2 / length1;
		}

		//std::cout << "Dlugosci: " << minLengthRelative << " < " << k << "<" << maxLengthRelative << std::endl;

		if(k >= minLengthRelative && k <= maxLengthRelative)
		{
			return true;
		}
	}

	return false;
}

}
}
