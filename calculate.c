#include <math.h>
#include <stdio.h>

#include "calculate.h"

double reducedLat(double lat)
{
	return atan((1. - FLATTENING) * tan(lat));
}


double calculateSinSigma(double phi_1, double phi_2, double lambda)
{
	double firstSqrtOperand = pow(cos(phi_2) * sin(lambda), 2.);
	double secondSqrtOperand = pow(cos(phi_1) * sin(phi_2) - sin(phi_1) * cos(phi_2) * cos(lambda), 2.);

	return sqrt(firstSqrtOperand + secondSqrtOperand);
}


double calculateCosSigma(double phi_1, double phi_2, double lambda)
{
	return sin(phi_1) * sin(phi_2) + cos(phi_1) * cos(phi_2) * cos(lambda);
}


double calculateSigma(double sinSigma, double cosSigma)
{
	return atan2(sinSigma, cosSigma);
}


double calculateSinAlpha(double phi_1, double phi_2, double lambda, double sinSigma)
{
	double numerator;

	numerator = cos(phi_1) * cos(phi_2) * sin(lambda);

	return numerator / sinSigma;
}


double calculateCosSquaredAlpha(double sinAlpha)
{
	return 1. - pow(sinAlpha, 2.);
}


double calculateCosTwoAlpha_M(double phi_1, double phi_2, double cosSquaredAlpha, double cosSigma)
{
	double secondTerm = 2. * sin(phi_1) * sin(phi_2) / cosSquaredAlpha;

	return cosSigma - secondTerm;
}


double calculateC(double cosSquaredAlpha)
{
	return FLATTENING / 16. * cosSquaredAlpha * (
		4. + FLATTENING * (
			4. - 3. * cosSquaredAlpha
		)
	);
}


void calculateLambda(double phi_1, double phi_2, double long_1, double long_2, struct vincentyVars *V)
{
	double C, L, sinAlpha, sigma;

	V->sinSigma = calculateSinSigma(phi_1, phi_2, V->lambda);
	V->cosSigma = calculateCosSigma(phi_1, phi_2, V->lambda);

	sinAlpha = calculateSinAlpha(phi_1, phi_2, V->lambda, V->sinSigma);
	V->cosSquaredAlpha = calculateCosSquaredAlpha(sinAlpha);
	sigma = calculateSigma(V->sinSigma, V->cosSigma);
	V->cosTwoSigma_M = calculateCosTwoAlpha_M(phi_1, phi_2, V->cosSquaredAlpha, V->cosSigma);

	C = calculateC(V->cosSquaredAlpha);
	L = long_2 - long_1;

	V->lambda = L + (
		1. - C
	) * FLATTENING * sinAlpha * (
		sigma + C * V->sinSigma * (
			V->cosTwoSigma_M + C * V->cosSigma * (
				-1. + 2. * pow(V->cosTwoSigma_M, 2.)
			)
		)
	);
}


double calculateA(double uSquared)
{
	return 1. + uSquared / 16384. * (
		4096. + uSquared * (
			-768. + uSquared * (
				320. - 175. * uSquared
			)
		)
	);
}


double calculateB(double uSquared)
{
	return uSquared / 1024. * (
		256. + uSquared * (
			-128. + uSquared * (
				74. - 47. * uSquared
			)
		)
	);
}


double calculateDeltaSigma(double B, struct vincentyVars V)
{
	return B * V.sinSigma * (
		V.cosTwoSigma_M + 0.25 * B * (
			V.cosSigma * (
				-1. * 2. * pow(V.cosTwoSigma_M, 2.)
			) - 1. / 6. * V.cosTwoSigma_M * (
				-3. + 4. * pow(V.sinSigma, 2.)
			) * (
				-3. + 4. * pow(V.cosTwoSigma_M, 2.)
			)
		)
	);
}
