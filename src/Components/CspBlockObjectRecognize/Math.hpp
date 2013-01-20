/*
 * Math.hpp
 *
 *  Created on: 14-12-2012
 *      Author: spiatek
 */

#ifndef MATH_HPP_
#define MATH_HPP_

#include <math.h>
#include <stdlib.h>

#include <boost/shared_ptr.hpp>

class Math {
private:

public:
	static double AngleLines(double a1, double b1, double a2, double b2);
	static void StraightEquation(int x1 ,int y1, int x2, int y2, double *a, double *b, double *c);
};

#endif /* MATH_HPP_ */
