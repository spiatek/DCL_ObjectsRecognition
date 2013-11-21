/*!
 * \file AbstractConstraint.hpp
 * \brief
 * \author mboryn
 * \date 2011-01-22
 */

#ifndef ABSTRACTCONSTRAINT_HPP_
#define ABSTRACTCONSTRAINT_HPP_

#include <boost/shared_ptr.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "AbstractShape.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

class AbstractShape;

/**
 * Abstract constraint for CSP graph.
 * Constraint represents edge in graph.
 * Contains abstract method isSatisifed(), which returns true if condition is met.
 *
 */
class AbstractConstraint
{
public:
	/**
	 * Constructor.
	 */
	AbstractConstraint();
	/**
	 * Destructor.
	 */
	virtual ~AbstractConstraint();

	/**
	 * Checks if constraint concerning two vertices (for example two line segments) is met.
	 * @param first vertex from.
	 * @param second vertex to.
	 * @return true if condition is met.
	 */
	virtual bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second) = 0;
protected:
	/**
	 * Calculate distance between points.
	 * @param p1
	 * @param p2
	 * @return distance.
	 */
	double dist(cv::Point p1, cv::Point p2);
};

} // namespace Processors
} // namespace CspBlockObjectRecognize

#endif /* ABSTRACTCONSTRAINT_HPP_ */
