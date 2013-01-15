/*!
 * \file ParallelLineConstraint.hpp
 * \brief
 * \author spiatek
 * \date 2012-12-13
 */

#ifndef PARALLELLINECONSTRAINT_HPP_
#define PARALLELLINECONSTRAINT_HPP_

#include <boost/property_tree/ptree.hpp>

#include "AbstractConstraint.hpp"

namespace Processors {
namespace CspObjectRecognize {

/**
 * Represents constraint for which is satisfied for parallel line segments.
 * Line segments are considered parallel if ...
 *
 * Property <b>angle</b>
 */
class ParallelLineConstraint: public Processors::CspObjectRecognize::AbstractConstraint
{
public:
	/**
	 * Create constraint.
	 * @param node property angle may exist.
	 * @return
	 */
	ParallelLineConstraint(const boost::property_tree::ptree& node);
	virtual ~ParallelLineConstraint();

	/**
	 * Check if line segments are parallel.
	 * @param first
	 * @param second
	 * @return true if an angle is close enough to 0 degrees.
	 */
	virtual bool isSatisifed(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);
private:
	double angle;
};

} // namespace CspObjectRecognize
} // namespace Processors

#endif /* PARALLELLINECONSTRAINT_HPP_ */
