#include "lab13.h"

char *getToken(char line[LINE_MAX], int POS) {
	int i = 0;
	int count = 0;
	while (count < POS) {
		if (line[i] == ',') {count += 1;}
		i += 1;
	}
	char *token = malloc(TOKEN_MAX * sizeof(char));
	int j = 0;
	while ((line[i] != ',') && (line[i] != '\n')) {
		token[j] = line[i];
		j += 1;
		i += 1;
	}
	token[j] = '\0';
	token = realloc(token, (j + 1) * sizeof(char));
	return token;
}

int rank(char line[LINE_MAX]) {
	char *token = getToken(line, RANK_POS);
	int val = atof(token);
	free(token);
	return val;
}

int year(char line[LINE_MAX]) {
	char *token = getToken(line, YEAR_POS);
	int val = atof(token);
	free(token);
	return val;
}

float sales(char line[LINE_MAX], int POS) {
	char *token = getToken(line, POS);
	float val;
	if (strcmp(token, " ") == 0) {val = -1;}
	else {val = atof(token);}
	free(token);
	return val;
}

struct game * buildRecord(char line[LINE_MAX]) {
	float NA_sales = sales(line, NA_SALES_POS);
	float EU_sales = sales(line, EU_SALES_POS);
	float JP_sales = sales(line, JP_SALES_POS);
	float Other_sales = sales(line, OTHER_SALES_POS);
	float Global_sales = sales(line, GLOBAL_SALES_POS);

	if (NA_sales < 0) {
		NA_sales = Global_sales - Other_sales - JP_sales - EU_sales;
	}
	else if (EU_sales < 0) {
		EU_sales = Global_sales - Other_sales - JP_sales - NA_sales;
	}
	else if (JP_sales < 0) {
		JP_sales = Global_sales - Other_sales - EU_sales - NA_sales;
	}
	else if (Other_sales < 0) {
		Other_sales = Global_sales - JP_sales - JP_sales - NA_sales;
	}

	int r = rank(line);
	int y = year(line);

	char *name = getToken(line, NAME_POS);
	char *platform = getToken(line, PLATFORM_POS);
	char *genre = getToken(line, GENRE_POS);
	char *publisher = getToken(line, PUBLISHER_POS);

	struct game *record = malloc(sizeof(struct game));
	record->rank = r;
	record->year = y;
	record->name = name;
	record->platform = platform;
	record->genre = genre;
	record->publisher = publisher;
	record->NA_sales = NA_sales;
	record->EU_sales = EU_sales;
	record->JP_sales = JP_sales;
	record->other_sales = Other_sales;
	record->global_sales = Global_sales;

	return record;
}

bool isInPublisherCounters(int length, struct PublisherCounter **COUNTERS, char *publisher) {
	if (length == 0) {return false;}
	for (int i = 0; i < length; i++) {
		if (strcmp((COUNTERS[i])->publisher, publisher) == 0) {return true;}
	}
	return false;
}

bool isInGameCounters(int length, struct GameCounter **COUNTERS, char *name) {
	if (length == 0) {return false;}
	for (int i = 0; i < length; i++) {
		if (strcmp((COUNTERS[i])->name, name) == 0) {return true;}
	}
	return false;
}

void incrementPublisherCount(int length, struct PublisherCounter **COUNTERS, char *publisher) {
	for (int i = 0; i < length; i++) {
		if (strcmp((COUNTERS[i])->publisher, publisher) == 0) {
			(COUNTERS[i])->count += 1;
			return;
		}
	}
}

void incrementGameCount(int length, struct GameCounter **COUNTERS, char *name) {
	for (int i = 0; i < length; i++) {
		if (strcmp((COUNTERS[i])->name, name) == 0) {
			(COUNTERS[i])->count += 1;
			return;
		}
	}
}

void sortPublisherCounters(int length, struct PublisherCounter **COUNTERS) {
	for (int last = length-1; last > 0; last--) {
		for (int cur = 0; cur < last; cur++) {
			if (strcmp( COUNTERS[cur]->publisher, COUNTERS[cur+1]->publisher ) > 0) {
				struct PublisherCounter *temp = COUNTERS[cur];
				COUNTERS[cur] = COUNTERS[cur+1];
				COUNTERS[cur+1] = temp;
			}
		}
	}
	return;
}

void sortGameCounters(int length, struct GameCounter **COUNTERS) {
	for (int last = length-1; last > 0; last--) {
		for (int cur = 0; cur < last; cur++) {
			if ( (COUNTERS[cur]->count) < (COUNTERS[cur+1]->count) ) {
				struct GameCounter *temp = COUNTERS[cur];
				COUNTERS[cur] = COUNTERS[cur+1];
				COUNTERS[cur+1] = temp;
			}
			else if ( (COUNTERS[cur]->count) == (COUNTERS[cur+1]->count) ) {
				if (strcmp( COUNTERS[cur]->name, COUNTERS[cur+1]->name ) > 0) {
					struct GameCounter *temp = COUNTERS[cur];
					COUNTERS[cur] = COUNTERS[cur+1];
					COUNTERS[cur+1] = temp;
				}
			}
		}
	}
	return;
}