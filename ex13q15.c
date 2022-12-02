#include "lab13.h"

void ex13q15(char *filename) {
	// synthesize all global sales
	FILE *gameFPTR = fopen(filename, "r");
	if (!gameFPTR) {return;}
	char line[LINE_MAX];
	fgets(line, sizeof(line), gameFPTR);  // skip the column titles line

	float global[100];
	int i = 0;
	
	while (fgets(line, sizeof(line), gameFPTR)) {
		float Global_sales = sales(line, GLOBAL_SALES_POS);
		global[i] = Global_sales;
		i += 1;
	}
	fclose(gameFPTR);

	// sort global sales in ascending order
	sortGlobalSales(global);

	// calculate mean global sales
	float mean = meanGlobalSales(global);

	// calculate median global sales
	float median = medianGlobalSales(global);

	// calculate range of global sales
	float range = rangeGlobalSales(global);

	// report results
	printf("Mean global sales: %.2f million\n", mean);
	printf("Median global sales: %.2f million\n", median);
	printf("Range global sales: %.2f million\n", range);
}