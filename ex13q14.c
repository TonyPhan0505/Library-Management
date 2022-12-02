#include "lab13.h"

void ex13q14(char *filename) {
	FILE *gameFPTR = fopen(filename, "r");
	if (!gameFPTR) {return;}
	char line[LINE_MAX];
	fgets(line, sizeof(line), gameFPTR);  // skip the column titles line

	while (fgets(line, sizeof(line), gameFPTR)) {
		struct game *record = buildRecord(line);

		char *name = record->name;
		float NA_per = (record->NA_sales) / (record->global_sales) * 100;
		float EU_per = (record->EU_sales) / (record->global_sales) * 100;
		float JP_per = (record->JP_sales) / (record->global_sales) * 100;
		float Other_per = (record->other_sales) / (record->global_sales) * 100;

		printf("%s - NA: %.1f%%, EU: %.1f%%, JP: %.1f%%, Other: %.1f%%\n", 
			name,
			NA_per,
			EU_per,
			JP_per,
			Other_per
		);

		freeRecord(record);
	}

	fclose(gameFPTR);
}