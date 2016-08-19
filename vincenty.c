#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "measure.h"


int main(int argc, char *argv[])
{
	char *letters;
	double distance, latLongPairs[4];

	if (argc != 5)
	{
		fprintf(stderr, "Incorrect number of variables.\nUsage: ./vincenty LAT1 LONG1 LAT2 LONG2\n");
		return 1;
	}

	for (int i=0; i<4; i++)
	{
		latLongPairs[i] = strtod(argv[i+1], &letters);

		if (argv[i+1] == letters)
		{
			fprintf(stderr, "Cast of arg %d could not be casted to double. Exiting.\n", i+1);
			return 1;
		}
	}

	if (errno == ERANGE)
	{
		fprintf(stderr, "Could not store coordinates in double. Exiting.\n");
		return 1;
	}

	if (!(-180. <= latLongPairs[0] && latLongPairs[0] <= 180.) ||
	    !(-180. <= latLongPairs[1] && latLongPairs[1] <= 180.) ||
	    !(-180. <= latLongPairs[2] && latLongPairs[2] <= 180.) ||
	    !(-180. <= latLongPairs[3] && latLongPairs[3] <= 180.))
	{
		fprintf(stderr, "Lat/long out of valid ranges. Exiting.\n");
		return 1;
	}

	distance = calculateDistance(latLongPairs[0], latLongPairs[1], latLongPairs[2], latLongPairs[3]);

	if (errno == EDOM)
		return 1;

	printf("%.0f\n", distance);

	return 0;
}
