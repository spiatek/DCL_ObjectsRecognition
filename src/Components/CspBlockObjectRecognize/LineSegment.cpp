/*
 * LineSegment.cpp
 *
 *  Created on: 09-01-2011
 *      Author: mateusz
 */

#include "LineSegment.hpp"

namespace Processors {

namespace CspBlockObjectRecognize {

LineSegment::LineSegment(const Types::Line& line) :
	line(line)
{
}
/*
LineSegment::LineSegment(int x1, int y1, int x2, int y2)
{
	A = 0.0;
	B = 0.0;
	C = 0.0;
	Math::StraightEquation(x1, -y1, x2, -y2, (boost::shared_ptr<double>) &A, (boost::shared_ptr<double>) &B, (boost::shared_ptr<double>) &C);
}
*/
LineSegment::~LineSegment()
{
}
Types::Line& LineSegment::getLine()
{
	return line;
}

void LineSegment::draw(cv::Mat &image, CvScalar color)
{
	line.draw(image, color);
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
