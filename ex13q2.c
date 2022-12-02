#include "lab13.h"

void ex13q2(void) {
	// preparation
	struct game records[100];
	int i = 0;

	FILE *processingFPTR = fopen("processing.csv", "r");
	if (!processingFPTR) {return;}
	char line[LINE_MAX];
	fgets(line, sizeof(line), processingFPTR);  // skip the column titles line
	
	// prompt the user
	char x[20];
	printf("Sort games by: ");
	scanf(" %s", x);
	if (!(
		(strcmp(x, "name") == 0)
		||
		(strcmp(x, "NA_sales") == 0)
		||
		(strcmp(x, "EU_sales") == 0)
		||
		(strcmp(x, "JP_sales") == 0)
		||
		(strcmp(x, "global_sales") == 0)
		||
		(strcmp(x, "year") == 0)
		||
		(strcmp(x, "platform") == 0)
		||
		(strcmp(x, "genre") == 0)
		||
		(strcmp(x, "publisher") == 0)
	)) {printf("Invalid sorting request!\n"); return;}

	// synthesize records
	while (fgets(line, sizeof(line), processingFPTR)) {
		struct game *record = buildRecord(line);
		struct game r = {
			record->rank,
			record->year,
			record->name,
			record->platform,
			record->genre,
			record->publisher,
			record->NA_sales,
			record->EU_sales,
			record->JP_sales,
			record->other_sales,
			record->global_sales
		};
		records[i] = r;
		i += 1;
		free(record);
	}
	fclose(processingFPTR);
	
	// sort the records
	sortBy(records, x);

	// re-rank the games
	int j = 1;
	for (int z = 0; z < 100; z++) {
		records[z].rank = j;
		j += 1;
	}

	// create sorted csv file
	char *filename = makeFileName(x);
	FILE *sortingFPTR = fopen(filename, "w");
	if (!sortingFPTR) {return;}
	fprintf(sortingFPTR, "Rank,Name,Platform,Year,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales\n");  // column titles for new csv file
	for (int w = 0; w < 100; w++) {
		fprintf(sortingFPTR, "%d,%s,%s,%d,%s,%s,%f,%f,%f,%f,%f\n", 
			records[w].rank,
			records[w].name,
			records[w].platform,
			records[w].year,
			records[w].genre,
			records[w].publisher,
			records[w].NA_sales,
			records[w].EU_sales,
			records[w].JP_sales,
			records[w].other_sales,
			records[w].global_sales
		);
	}
	fclose(sortingFPTR);

	// free strings in records
	for (int k = 0; k < 100; k++) {
		free(records[k].name);
		free(records[k].platform);
		free(records[k].genre);
		free(records[k].publisher);
	}

	return;
}