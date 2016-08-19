#ifndef _MEASURE_H
#define _MEASURE_H

#define SEMI_MAJOR_AXIS 6378137.0 // WGS84
#define SEMI_MINOR_AXIS 6356752.314245 // WGS84
#define CONV_LIMIT 50 // Stopping point for lambda to converge

double calculateDistance(double lat_1, double long_1, double lat_2, double long_2);

#endif // _MEASURE_H
