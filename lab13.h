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


// Declare functions used in ex13q1
void ex13q11(char *filename);
void ex13q12(char *filename);
void ex13q13(char *filename);
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