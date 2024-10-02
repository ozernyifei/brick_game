#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>



void loadHighScore(int* high_score) {
    FILE* file = fopen(HIGH_SCORE_FILE, "r");
    if (file) {
        if (fscanf(file, "%d", high_score) != 1) {
            *high_score = 0;  
        }
        fclose(file);
    } else {
        *high_score = 0;  
    }
}

void saveHighScore(int high_score) {
    FILE* file = fopen(HIGH_SCORE_FILE, "w");
    if (file) {
        fprintf(file, "%d", high_score);
        fclose(file);
    }
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

unsigned long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);  // Milliseconds
}