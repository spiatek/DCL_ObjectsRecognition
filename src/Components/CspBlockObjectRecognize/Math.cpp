/*
 * Math.hpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#include "Math.hpp"

/*
 * Funkcja ktora oblicza rowanie prostej przechodzacej przez dwa punkty
 */
void Math::StraightEquation(int x1 ,int y1, int x2, int y2, double *a, double *b, double *c)
{
	if(x1 == x2 && y1 != y2)		//rownelegla do osi OY
	{
		*a = -1.0;
		*b = 0.0;
		*c = (double) x1;
	}
	else if(y1 == y2 && x1 != x2) 	//rownolegla do osi OX
	{
		*a = 0.0;
		*b = -1.0;
		*c = (double) y1;
	}
	else
	{
		*a	= ((double)(y2 - y1)) / ((double)(x2 - x1));
		*b	= -1.0;
		*c	= *a*(double)(-x1) + (double)(y1);
	}

	return ;
}

/*
 * Funkcja oblicza kat miedzy prostymi
 * a1 i a2 wsploczynniki kierunkowe prostych
 * kat zwracany jest w radianach
 */
 double Math::AngleLines(double a1, double b1, double a2, double b2)
 {
/*	double m=0.0;
 	if(a1*a2==-1.0)
 	{
 		return 90.0/Settings::RAD_NA_ST;
 	}
 	else if(a1==a2&&b1!=0&&b2!=0)
 	{
 		return 0.0;
 	}
 	//a1 jest rownolegla do osi OY
 	//lub a2 jest rownolegla do osi OY
 	else if(a1	==	-1.0 && b1==0.0||a2	==	-1.0 && b2==0.0 )
 	{

 		if(a1	==	-1.0 &&b1 == 0.0)
 		{
 			//wyznaczamy kat nachylenia prostej a2
 			double angle = atan(fabs(a2))*Settings::RAD_NA_ST;
 			return (90.0-angle)/Settings::RAD_NA_ST;
 		}
 		else
 		{
 			double angle = atan(fabs(a1))*Settings::RAD_NA_ST;
 			return (90.0-angle)/Settings::RAD_NA_ST;
 		}
// 		if(a1	==	-1.0 &&b1==0.0)
// 		{
// 			x	=	5.0;
// 			y	=	a2*x;
// 			return atan(x/y);
// 		}
// 		else
// 		{
// 			x	=	5.0;
// 			y	=	a1*x;
// 			return atan(x/y);
// 		}
 	}
 	else if(a1	==0.0 && b1==-1.0||a2	==	0.0 && b2==-1.0 )
 	{

 		if(a1	==0.0 && b1==-1.0)
 		{
 			m = fabs(a2);
 			return atan(m);
 		}
 		else
 		{
 			m = fabs(a1);
 			return atan(m);
 		}

// 		if(a1	==0.0 && b1==-1.0)
// 		{
// 			x	=	5.0;
// 			y	=	a2*x;
// 			return atan(y/x);
// 		}
// 		else
// 		{
// 			x	=	5.0;
// 			y	=	a1*x;
// 			return atan(y/x);
// 		}
 	}
 	else
 	{
  		return atan(fabs((a1 -a2)/(1+a1*a2)));
 	}*/
	 return 0.0;
 }
