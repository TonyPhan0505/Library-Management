#include "lab13.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Missing 1 command line argument!\n");
		return 1;
	}

	ex13q11(argv[1]);

	char *processing = "processing";
	if (strstr(argv[0], processing)) {
		printf("############ Common publishers: ############\n");
		ex13q12(argv[1]);
		printf("\n");

		printf("\n############ Repeated games: ############\n");
		ex13q13(argv[1]);
		printf("\n");

		printf("\n############ Sales Percentages: ############\n");
		ex13q14(argv[1]);
		printf("\n");

		printf("\n############ Summary Statistics: ############\n");
		ex13q15(argv[1]);
	}
	
	char *sorting = "sorting";
	if (strstr(argv[0], sorting)) {ex13q2();}

	return 0;
}