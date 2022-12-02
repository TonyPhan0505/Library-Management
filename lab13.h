/////////////////// Directives ////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_MAX 500
#define TOKEN_MAX 100
#define RANK_POS 0
#define NAME_POS 1
#define PLATFORM_POS 2
#define YEAR_POS 3
#define GENRE_POS 4
#define PUBLISHER_POS 5
#define NA_SALES_POS 6
#define EU_SALES_POS 7
#define JP_SALES_POS 8
#define OTHER_SALES_POS 9
#define GLOBAL_SALES_POS 10
////////////////////////////////////////////////


/////////////////// Structs ////////////////
struct game {
    int rank;
    int year;
    char *name;
    char *platform;
    char *genre;
    char *publisher;
    
    // sales below represented in millions
    float NA_sales;
    float EU_sales;
    float JP_sales;
    float other_sales;
    float global_sales;
};

struct PublisherCounter {
    char *publisher;
    int count;
};

struct GameCounter {
    char *name;
    int count;
};
////////////////////////////////////////////////


////////////////////////////////// ex13q1's function declarations ///////////////////////////////
void ex13q11(char *filename);
void ex13q12(char *filename);
void ex13q13(char *filename);
void ex13q14(char *filename);
void ex13q15(char *filename);
char *getToken(char line[LINE_MAX], int POS);
int rank(char line[LINE_MAX]);
int year(char line[LINE_MAX]);
float sales(char line[LINE_MAX], int POS);
struct game * buildRecord(char line[LINE_MAX]);
bool isInPublisherCounters(int length, struct PublisherCounter **COUNTERS, char *publisher);
bool isInGameCounters(int length, struct GameCounter **COUNTERS, char *name);
void incrementPublisherCount(int length, struct PublisherCounter **COUNTERS, char *publisher);
void incrementGameCount(int length, struct GameCounter **COUNTERS, char *name);
void sortPublisherCounters(int length, struct PublisherCounter **COUNTERS);
void sortGameCounters(int length, struct GameCounter **COUNTERS);
void sortGlobalSales(float global[100]);
float meanGlobalSales(float global[100]);
float medianGlobalSales(float global[100]);
float rangeGlobalSales(float global[100]);
void freeRecord(struct game *record);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////// ex13q2's function declarations ///////////////////////////////
void ex13q2(void);
int name_comparator(const void *p, const void *q);
int na_comparator(const void *p, const void *q);
int eu_comparator(const void *p, const void *q);
int jp_comparator(const void *p, const void *q);
int global_comparator(const void *p, const void *q);
int year_comparator(const void *p, const void *q);
int platform_comparator(const void *p, const void *q);
int genre_comparator(const void *p, const void *q);
int publisher_comparator(const void *p, const void *q);
void sortBy(struct game records[100], char *x);
char *makeFileName(char *x);
////////////////////////////////////////////////////////////////////////////////////////////////