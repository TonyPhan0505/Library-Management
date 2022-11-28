#include "lab13.h"

void ex13q13(char *filename) {
	// count occurrences of games
	int length = 0;
	struct GameCounter **COUNTERS = malloc(1 * sizeof(struct GameCounter *));

	FILE *gameFPTR = fopen(filename, "r");
	if (!gameFPTR) {return;}
	char line[LINE_MAX];
	fgets(line, sizeof(line), gameFPTR);  // skip the column titles line
	
	while (fgets(line, sizeof(line), gameFPTR)) {
		char *name = getToken(line, NAME_POS);
		if (isInGameCounters(length, COUNTERS, name)) {
			incrementGameCount(length, COUNTERS, name);
			free(name);
		}
		else {
			COUNTERS = realloc(COUNTERS, (length+1) * sizeof(struct GameCounter *));
			struct GameCounter *counter = malloc(sizeof(struct GameCounter));
			counter->name = name;
			counter->count = 1;
			COUNTERS[length] = counter;
			length += 1;
		}
	}
	fclose(gameFPTR);

	// sort COUNTERS in descending order of counts and dictionary order
	sortGameCounters(length, COUNTERS);

	// print games in descending order of counts and dictionary order
	for (int cur = 0; cur < length; cur++) {
		printf("%s: %d times\n", COUNTERS[cur]->name, COUNTERS[cur]->count);
	}

	// free allocated memories
	for (int i = 0; i < length; i++) {
		free((COUNTERS[i])->name);
		free(COUNTERS[i]);
	}
	free(COUNTERS);
}