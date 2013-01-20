/*
 * LineSegment.cpp
 *
 *  Created on: 09-01-2011
 *      Author: mateusz
 *      Edit:	spiatek
 */

#include <boost/pointer_cast.hpp>

#include "LineSegment.hpp"

namespace Processors {

namespace CspBlockObjectRecognize {

LineSegment::LineSegment(const Types::Line& line) :
	line(line)
{
}

LineSegment::LineSegment(int x1, int y1, int x2, int y2)
{
	A = 0.0;
	B = 0.0;
	C = 0.0;
	Math::StraightEquation(x1, -y1, x2, -y2, &A, &B, &C);
}

LineSegment::~LineSegment()
{
}
Types::Line& LineSegment::getLine()
{
	return line;
}

void LineSegment::setColor(int c)
{
	line.setColor(c);
}

int LineSegment::getColor()
{
	return line.getColor();
}

void LineSegment::getLineParams(double* a, double* b, double* c)
{
	A = 0.0;
	B = 0.0;
	C = 0.0;
	Math::StraightEquation(p1.x, -p1.y, p2.x, -p2.y, &A, &B, &C);
	*a = A;
	*b = B;
	*c = C;
}

void LineSegment::draw(cv::Mat &image, CvScalar color)
{
	line.draw(image, color);
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
