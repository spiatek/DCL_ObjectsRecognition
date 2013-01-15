/*
 * LinesPerpendicularConstraint.hpp
 *
 *  Created on: 14-12-2012
 *      Author: spiatek
 */

#ifndef LINESPERPENDICULARCONSTRAINT_HPP_
#define LINESPERPENDICULARCONSTRAINT_HPP_

/**
 * Klasa sprawdzająca ograniczenie prostopadłości dla prostych
 */
class LinesPrependicularConstraint : public Constraint
{
public:
	/**
	 * Create constraint.
	 * @param node property maxDistance may exist.
	 * @return
	 */
	LinesPrependicularConstraint(const boost::property_tree::ptree& node);
	virtual ~LinesPrependicularConstraint();

	/**
	 * Check if line segments have common ends.
	 * @param first
	 * @param second
	 * @return true if an angle between the lines is nearly 90 degrees.
	 */
	bool isSatisfied(boost::shared_ptr<AbstractShape> first, boost::shared_ptr<AbstractShape> second);
private:
	int maxAngleLines;
};


#endif /* LINESPERPENDICULARCONSTRAINT_HPP_ */
