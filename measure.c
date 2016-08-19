#include <errno.h>
#include <math.h>
#include <stdio.h>

#include "calculate.h"
#include "measure.h"


/* Run lat/long pairs through the Vincenty formula to determine distance along
	the Earth's surface. */
double calculateDistance(double lat_1, double long_1, double lat_2, double long_2)
{
	double A, B, uSquared, deltaSigma, s, phi_1, phi_2, lambda_prime;
	int i = 0;
	struct vincentyVars V;

	// Reduce latitudes (output: radians)
	phi_1 = reducedLat(lat_1 * M_PI / 180.0);
	phi_2 = reducedLat(lat_2 * M_PI / 180.0);

	// Convert degrees to radians
	long_1 *= M_PI / 180.0;
	long_2 *= M_PI / 180.0;

	V.lambda = long_2 - long_1;

	do {
		lambda_prime = V.lambda;
		calculateLambda(phi_1, phi_2, long_1, long_2, &V);
		i++;
	} while (fabs(V.lambda - lambda_prime) > 10e-12 && i < CONV_LIMIT);

	if (i == CONV_LIMIT)
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
