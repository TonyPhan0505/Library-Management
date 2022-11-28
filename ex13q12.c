#include "lab13.h"

void ex13q12(char *filename) {
	// count occurrences of publishers
	int length = 0;
	struct PublisherCounter **COUNTERS = malloc(1 * sizeof(struct PublisherCounter *));

	FILE *gameFPTR = fopen(filename, "r");
	if (!gameFPTR) {return;}
	char line[LINE_MAX];
	fgets(line, sizeof(line), gameFPTR);  // skip the column titles line
	
	while (fgets(line, sizeof(line), gameFPTR)) {
		char *publisher = getToken(line, PUBLISHER_POS);
		if (isInPublisherCounters(length, COUNTERS, publisher)) {
			incrementPublisherCount(length, COUNTERS, publisher);
			free(publisher);
		}
		else {
			COUNTERS = realloc(COUNTERS, (length+1) * sizeof(struct PublisherCounter *));
			struct PublisherCounter *counter = malloc(sizeof(struct PublisherCounter));
			counter->publisher = publisher;
			counter->count = 1;
			COUNTERS[length] = counter;
			length += 1;
		}
	}
	fclose(gameFPTR);

	// sort COUNTERS in alphabetical order
	sortPublisherCounters(length, COUNTERS);

	// print publishers in alphabetical order
	for (int cur = 0; cur < length; cur++) {
		printf("%s: %d games\n", COUNTERS[cur]->publisher, COUNTERS[cur]->count);
	}

	// free allocated memories
	for (int i = 0; i < length; i++) {
		free((COUNTERS[i])->publisher);
		free(COUNTERS[i]);
	}
	free(COUNTERS);
}