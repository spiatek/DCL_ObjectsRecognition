/*!
 * \file LineSegment.hpp
 * \brief
 * \author mboryn
 * \date 2011-01-22
 */

#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include <cv.h>

#include "AbstractShape.hpp"
#include "Types/Line.hpp"
#include "Math.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

/**
 * The most primitive shape for CspGraph to recognize (I guess).
 * Consists of line segment.
 */
class LineSegment: public Processors::CspBlockObjectRecognize::AbstractShape
{
public:
	/**
	 * Create line segment.
	 * @param line
	 */
	LineSegment(const Types::Line& line);

	//LineSegment(int x1, int y1, int x2, int y2);

	virtual ~LineSegment();

	/**
	 * Get line segment.
	 * @return
	 */
	Types::Line& getLine();

	/**
	 * Get parameters of linear equation.
	 * @return
	 */
void getLineParams(boost::shared_ptr<double> a, boost::shared_ptr<double> b, boost::shared_ptr<double> c);

	/**
	 * Draw on image.
	 * @param image
	 * @param color
	 */
	virtual void draw(cv::Mat &image, CvScalar color);
private:
	/** Line. */
	Types::Line line;
	cv::Point p1, p2;
	double A, B, C;		//Ax + By + C = 0
};

} // namespace CspBlockObjectRecognize
} // namespace Processors

#endif /* LINESEGMENT_HPP_ */
