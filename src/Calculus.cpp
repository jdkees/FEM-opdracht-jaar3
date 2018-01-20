/*
 * Calculus.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: majernik
 */

#include "Calculus.h"

Calculus::Calculus()
{
	// Points and Weights for the Gauss–Legendre quadrature on the domain [-1, 1].
	GL10_p[0] = -0.1488743389816312;
	GL10_p[1] = 0.1488743389816312;
	GL10_p[2] = -0.4333953941292472;
	GL10_p[3] = 0.4333953941292472;
	GL10_p[4] = -0.6794095682990244;
	GL10_p[5] = 0.6794095682990244;
	GL10_p[6] = -0.8650633666889845;
	GL10_p[7] = 0.8650633666889845;
	GL10_p[8] = -0.9739065285171717;
	GL10_p[9] = 0.9739065285171717;


	GL10_w[0] = 0.2955242247147529;
	GL10_w[1] = 0.2955242247147529;
	GL10_w[2] = 0.2692667193099963;
	GL10_w[3] = 0.2692667193099963;
	GL10_w[4] = 0.2190863625159820;
	GL10_w[5] = 0.2190863625159820;
	GL10_w[6] = 0.1494513491505806;
	GL10_w[7] = 0.1494513491505806;
	GL10_w[8] = 0.0666713443086881;
	GL10_w[9] = 0.0666713443086881;

}

Calculus::~Calculus() {
	// TODO Auto-generated destructor stub
}

double Calculus::NIntegrate3D (integrationMethod method, double (*f)(double, double, double),
					double xmin, double xmax,
					double ymin, double ymax,
					double zmin, double zmax)
{
	switch(method)
	{
	case GAUSS_LEGENDRE10:
		double ans = 0;

		for(int k = 0; k < 10; k++)
		{
			for(int j = 0; j < 10; j++)
			{
				for(int i = 0; i < 10; i++)
				{
					ans = ans + 0.5*(xmax-xmin) * 0.5*(ymax-ymin) * 0.5*(zmax-zmin) *
										GL10_w[i] * GL10_w[j] * GL10_w[k] *
										f(0.5*(xmax-xmin)*GL10_p[i] + 0.5*(xmin+xmax),
										  0.5*(ymax-ymin)*GL10_p[j] + 0.5*(ymin+ymax),
										  0.5*(zmax-zmin)*GL10_p[k] + 0.5*(zmin+zmax));
				}
			}
		}

		return ans;
	};
}

double Calculus::NIntegrate1D (integrationMethod method, double (*f)(double),
					double xmin, double xmax)
{
	switch(method)
	{
	case GAUSS_LEGENDRE10:
		double ans = 0;

		for(int i = 0; i < 10; i++)
		{
			ans = ans + 0.5*(xmax-xmin) *
								GL10_w[i] *
								f(0.5*(xmax-xmin)*GL10_p[i] + 0.5*(xmin+xmax));
		}

		return ans;
	};
}

