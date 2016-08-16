#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "calculate.h"
#include "measure.h"


double calculateDistance(double lat_1, double long_1, double lat_2, double long_2)
{
	double A, B, uSquared, deltaSigma, s, reducedLat_1, reducedLat_2, prevLambda;
	int i = 0;
	struct vincentyVars V;

	// Reduce latitudes (output: radians)
	reducedLat_1 = reducedLat(lat_1 * M_PI / 180.0);
	reducedLat_2 = reducedLat(lat_2 * M_PI / 180.0);

	// Convert degrees to radians
	long_1 *= M_PI / 180.0;
	long_2 *= M_PI / 180.0;

	V.lambda = long_2 - long_1;
	prevLambda = 10.;

	while (fabs(V.lambda - prevLambda) > 10e-12 && i < 10)
	{
		prevLambda = V.lambda;
		calculateLambda(reducedLat_1, reducedLat_2, long_1, long_2, &V);
		i++;
	}

	if (i == 50)
	{
		fprintf(stderr, "Lambda does not converge.");
		errno = EDOM;
		return -1.;
	}

	uSquared = V.cosSquaredAlpha * (pow(SEMI_MAJOR_AXIS, 2.) - pow(SEMI_MINOR_AXIS, 2.)) / pow(SEMI_MINOR_AXIS, 2.);
	A = calculateA(uSquared);
	B = calculateB(uSquared);
	deltaSigma = calculateDeltaSigma(B, V);

	return SEMI_MINOR_AXIS * A * (calculateSigma(V.sinSigma, V.cosSigma) - deltaSigma);
}
