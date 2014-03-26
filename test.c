#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sasl.h"
#include "base64.h"

int
main(int argc, char **argv)
{
	if (strcmp(sasl_plain("user", "pass"), "AHVzZXIAcGFzcw==")  == 0)
		printf("SASL PLAIN: OK\n");
	else
		printf("SASL PLAIN: FAIL\n");

	char *c = "cmVhbG09ImNhdGFjbHlzbS5jeCIsbm9uY2U9Ik9BNk1HOXRFUUdtMmhoIixx"
	    "b3A9ImF1dGgiLGNoYXJzZXQ9dXRmLTgsYWxnb3JpdGhtPW1kNS1zZXNz";

	char *b = "bm9uY2U9IjQyOTMxNzAxMyIscW9wPSJhdXRoIixjaGFyc2V0PXV0Zi04LGFs"
	    "Z29yaXRobT1tZDUtc2Vzcw==";

	size_t size;
	char *p = base64_decode(c, strlen(c), &size);
	printf("%s\n\n", p);

	p = base64_decode(b, strlen(b), &size);
	printf("%s\n", p);

	return EXIT_SUCCESS;
}
