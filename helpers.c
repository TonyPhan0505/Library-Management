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
	if (line[i] == ',') {
		token[0] = ' ';
		j += 1;
	}
	else {
		while ((line[i] != ',') && (line[i] != '\n')) {
			token[j] = line[i];
			j += 1;
			i += 1;
		}
	}
	token = realloc(token, (j + 1) * sizeof(char));
	token[j] = '\0';
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
		Other_sales = Global_sales - JP_sales - EU_sales - NA_sales;
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

void sortGlobalSales(float global[100]) {
	for (int last = 99; last > 0; last--) {
		for (int cur = 0; cur < last; cur++) {
			if (global[cur] > global[cur+1]) {
				float temp = global[cur];
				global[cur] = global[cur+1];
				global[cur+1] = temp;
			}
		}
	}
	return;
}

float meanGlobalSales(float global[100]) {
	float sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += global[i];
	}
	float mean = sum / 100;
	return mean;
}

float medianGlobalSales(float global[100]) {
	int i = 49;
	int j = 50;
	float median = (global[i] + global[j]) / 2;
	return median;
}

float rangeGlobalSales(float global[100]) {
	float range = global[99] - global[0];
	return range;
}

void freeRecord(struct game *record) {
	free(record->name);
	free(record->platform);
	free(record->genre);
	free(record->publisher);
	free(record);
	return;
}

int name_comparator(const void *p, const void *q) {
	char *l = ((struct game *)p)->name;
	char *r = ((struct game *)q)->name;
	return strcmp(l, r);
}

int na_comparator(const void *p, const void *q) {
	float l = ((struct game *)p)->NA_sales;
	float r = ((struct game *)q)->NA_sales;
	float result = r-l;
	if ((result < 0) && (result > -1)) {return -1;}
	else if ((result > 0) && (result < 1)) {return 1;}
	return result;
}

int eu_comparator(const void *p, const void *q) {
	float l = ((struct game *)p)->EU_sales;
	float r = ((struct game *)q)->EU_sales;
	float result = r-l;
	if ((result < 0) && (result > -1)) {return -1;}
	else if ((result > 0) && (result < 1)) {return 1;}
	return result;
}

int jp_comparator(const void *p, const void *q) {
	float l = ((struct game *)p)->JP_sales;
	float r = ((struct game *)q)->JP_sales;
	float result = r-l;
	if ((result < 0) && (result > -1)) {return -1;}
	else if ((result > 0) && (result < 1)) {return 1;}
	return result;
}

int global_comparator(const void *p, const void *q) {
	float l = ((struct game *)p)->global_sales;
	float r = ((struct game *)q)->global_sales;
	float result = r-l;
	if ((result < 0) && (result > -1)) {return -1;}
	else if ((result > 0) && (result < 1)) {return 1;}
	return result;
}

int year_comparator(const void *p, const void *q) {
	int l = ((struct game *)p)->year;
	int r = ((struct game *)q)->year;
	
	char *Lname = ((struct game *)p)->name;
	char *Rname = ((struct game *)q)->name;

	if (l != r) {return (r-l);}
	else {return strcmp(Lname, Rname);}
}

int platform_comparator(const void *p, const void *q) {
	char *l = ((struct game *)p)->platform;
	char *r = ((struct game *)q)->platform;
	
	char *Lname = ((struct game *)p)->name;
	char *Rname = ((struct game *)q)->name;

	if (strcmp(l, r) != 0) {return strcmp(l, r);}
	else {return strcmp(Lname, Rname);}
}

int genre_comparator(const void *p, const void *q) {
	char *l = ((struct game *)p)->genre;
	char *r = ((struct game *)q)->genre;
	
	char *Lname = ((struct game *)p)->name;
	char *Rname = ((struct game *)q)->name;

	if (strcmp(l, r) != 0) {return strcmp(l, r);}
	else {return strcmp(Lname, Rname);}
}

int publisher_comparator(const void *p, const void *q) {
	char *l = ((struct game *)p)->publisher;
	char *r = ((struct game *)q)->publisher;
	
	char *Lname = ((struct game *)p)->name;
	char *Rname = ((struct game *)q)->name;

	if (strcmp(l, r) != 0) {return strcmp(l, r);}
	else {return strcmp(Lname, Rname);}
}

void sortBy(struct game records[100], char *x) {
	if (strcmp(x, "name") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), name_comparator);
	}
	else if (strcmp(x, "NA_sales") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), na_comparator);
	}
	else if (strcmp(x, "EU_sales") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), eu_comparator);
	}
	else if (strcmp(x, "JP_sales") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), jp_comparator);
	}
	else if (strcmp(x, "global_sales") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), global_comparator);
	}
	else if (strcmp(x, "year") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), year_comparator);
	}
	else if (strcmp(x, "platform") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), platform_comparator);
	}
	else if (strcmp(x, "genre") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), genre_comparator);
	}
	else if (strcmp(x, "publisher") == 0) {
		qsort((void *)records, 100, sizeof(records[0]), publisher_comparator);
	}
	return;
}

char *makeFileName(char *x) {
	char *filename;
	if (strcmp(x, "name") == 0) {
		filename = "gamesales_name.csv";
	}
	else if (strcmp(x, "NA_sales") == 0) {
		filename = "gamesales_NA_sales.csv";
	}
	else if (strcmp(x, "EU_sales") == 0) {
		filename = "gamesales_EU_sales.csv";
	}
	else if (strcmp(x, "JP_sales") == 0) {
		filename = "gamesales_JP_sales.csv";
	}
	else if (strcmp(x, "global_sales") == 0) {
		filename = "gamesales_global_sales.csv";
	}
	else if (strcmp(x, "year") == 0) {
		filename = "gamesales_year.csv";
	}
	else if (strcmp(x, "platform") == 0) {
		filename = "gamesales_platform.csv";
	}
	else if (strcmp(x, "genre") == 0) {
		filename = "gamesales_genre.csv";
	}
	else {
		filename = "gamesales_publisher.csv";
	}
	return filename;
}