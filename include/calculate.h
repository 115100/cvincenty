#ifndef _CALCULATE_H
#define _CALCULATE_H

#define FLATTENING 0.00335281066


struct vincentyVars
{
        double lambda;
        double cosSigma;
        double sinSigma;
        double cosSquaredAlpha;
        double cosTwoSigma_M;
};

double reducedLat(double lat);
double calculateA(double uSquared);
double calculateB(double uSquared);
double calculateC(double cosSquaredAlpha);
double calculateSigma(double sinSigma, double cosSigma);
double calculateCosSigma(double reducedLat_1, double reducedLat_2, double lambda);
double calculateCosSquaredAlpha(double sinAlpha);
double calculateCosTwoAlpha_M(double reducedLat_1, double reducedLat_2, double cosSquaredAlpha, double cosSigma);
double calculateDeltaSigma(double B, struct vincentyVars V);
void calculateLambda(double reducedLat_1, double reducedLat_2, double long_1, double long_2, struct vincentyVars *V);
double calculateSinSigma(double reducedLat_1, double reducedLat_2, double lambda);
double calculateSinAlpha(double reducedLat_1, double reducedLat_2, double lambda, double sinSigma);

#endif // _CALCULATE_H
