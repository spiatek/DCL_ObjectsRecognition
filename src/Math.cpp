/*
 * Math.cpp
 *
 *  Created on: 14-12-2012
 *      Author: spiatek
 */

/*
 * Funkcja wyliczajaca rowanie prostej przechodzacej przez dwa punkty
 */
void Math::StraightEquation(int x1 ,int y1, int x2, int y2, boost::shared_ptr<double> a, boost::shared_ptr<double> b, boost::shared_ptr<double> c)
{
	/* y - y2 = ((y2 - y1)/(x2 - x1))*(x - x1)*/

	if(x1 == x2 && y1 != y2)		//rownelegla do osi OY
	{
		boost::shared_ptr<double> a	= -1.0;
		boost::shared_ptr<double> b = 0.0;
		boost::shared_ptr<double> c = (double) x1;
	}
	else if(y1 == y2 && x1 != x2) 	//rownolegla do osi OX
	{
		boost::shared_ptr<double> a	= 0.0;
		boost::shared_ptr<double> b = -1.0;
		boost::shared_ptr<double> c = (double) y1;
	}
	else
	{
		boost::shared_ptr<double> a	= ((double)(y2 - y1))/((double)(x2 - x1));
		boost::shared_ptr<double> b = -1.0;
		boost::shared_ptr<double> c = a * (double)(-x1) + (double)(y1);
	}

	return;
}


/*
 * Funkcja oblicza kat w radianach miedzy prostymi
 * a1 i a2 wsploczynniki kierunkowe prostych
 */
 double Math::AngleLines(double a1, double b1, double a2, double b2)
 {
	double m = 0.0;
 	if(a1 * a2 == -1.0)
 	{
 		return 90.0 / Settings::RAD_NA_ST;
 	}
 	else if(a1 == a2 && b1 !=0 && b2 != 0)
 	{
 		return 0.0;
 	}
 	//a1 jest rownolegla do osi OY lub a2 jest rownolegla do osi OY
 	else if(a1 == -1.0 && b1 == 0.0 || a2 == -1.0 && b2 == 0.0)
 	{
 		if(a1 == -1.0 && b1 == 0.0)
 		{
 			//wyznaczenie kata nachylenia prostej a2
 			double angle = atan(fabs(a2)) * Settings::RAD_NA_ST;
 			return (90.0 - angle) / Settings::RAD_NA_ST;
 		}
 		else
 		{
 			double angle = atan(fabs(a1)) * Settings::RAD_NA_ST;
 			return (90.0 - angle) / Settings::RAD_NA_ST;
 		}
 	}
 	else if(a1 == 0.0 && b1 == -1.0 || a2 == 0.0 && b2 == -1.0 )
 	{
 		if(a1 == 0.0 && b1 == -1.0)
 		{
 			m = fabs(a2);
 			return atan(m);
 		}
 		else
 		{
 			m = fabs(a1);
 			return atan(m);
 		}
 	}
 	else
 	{
  		return atan(fabs((a1 - a2)/(1 + a1*a2)));
 	}
 }
