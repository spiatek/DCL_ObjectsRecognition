/*!
 * \file LineSegment.hpp
 * \brief
 * \author mboryn
 * \date 2011-01-22
 */

#ifndef LINESEGMENT_HPP_
#define LINESEGMENT_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/shared_ptr.hpp>

#include "AbstractShape.hpp"
#include "Types/Line.hpp"
#include "Math.hpp"

#define BLUE	1
#define RED		2
#define GREEN	3
#define YELLOW	4

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
	LineSegment(const Types::Line& line, int c);

	LineSegment(int x1, int y1, int x2, int y2);

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
	void getLineParams(double* a, double* b, double* c);

	void setColor(int c);
	int getColor();

	/**
	 * Draw on image.
	 * @param image
	 * @param color
	 */
	virtual void draw(cv::Mat &image, CvScalar color);
private:
	int color;
	/** Line. */
	Types::Line line;
	cv::Point p1, p2;
	double A, B, C;		//Ax + By + C = 0
};

} // namespace CspBlockObjectRecognize
} // namespace Processors

#endif /* LINESEGMENT_HPP_ */
