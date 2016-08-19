#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "measure.h"


int main(int argc, char *argv[])
{
	double distance, lat_1, long_1, lat_2, long_2;

	if (argc != 5)
	{
		fprintf(stderr, "Incorrect number of variables.\nUsage: ./vincenty LAT1 LONG1 LAT2 LONG2\n");
		return 1;
	}

	lat_1  = strtod(argv[1], NULL);
	long_1 = strtod(argv[2], NULL);
	lat_2  = strtod(argv[3], NULL);
	long_2 = strtod(argv[4], NULL);

	if (errno == ERANGE)
	{
		fprintf(stderr, "Could not store coordinates in double. Exiting.\n");
		return 1;
	}

	distance = calculateDistance(lat_1, long_1, lat_2, long_2);

	if (errno == EDOM)
		return 1;

	printf("%.0f\n", distance);

	return 0;
}
