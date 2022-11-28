#include "lab13.h"

void ex13q11(char *filename) {
	FILE *gameFPTR = fopen(filename, "r");
	FILE *processingFPTR = fopen("processing.csv", "w");
	if (!gameFPTR) {return;}

	char line[LINE_MAX];
	fgets(line, sizeof(line), gameFPTR);  // skip the column titles line
	fprintf(processingFPTR, "Rank,Name,Platform,Year,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales\n");  // column titles for new csv file
	
	while (fgets(line, sizeof(line), gameFPTR)) {
		struct game *record = buildRecord(line);
		fprintf(processingFPTR, "%d,%s,%s,%d,%s,%s,%f,%f,%f,%f,%f\n", 
			record->rank,
			record->name,
			record->platform,
			record->year,
			record->genre,
			record->publisher,
			record->NA_sales,
			record->EU_sales,
			record->JP_sales,
			record->other_sales,
			record->global_sales
		);

		free(record->name);
		free(record->platform);
		free(record->genre);
		free(record->publisher);
		free(record);
	}

	fclose(gameFPTR);
	fclose(processingFPTR);

	return;
}