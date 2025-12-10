#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordle.h"

void load_dictionary(const char *filename, Dictionary *dict) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open dictionary file.\n");
        exit(1);
    }

    dict->size = 0;
    while (fscanf(f, "%5s", dict->list[dict->size].word) == 1) {
        dict->size++;
        if (dict->size >= MAX_WORDS) break;
    }

    fclose(f);
}

int is_valid_word(const Dictionary *dict, const char *guess) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->list[i].word, guess) == 0)
            return 1;
    }
    return 0;
}

void pick_random_word(const Dictionary *dict, char *target) {
    srand(time(NULL));
    int idx = rand() % dict->size;
    strcpy(target, dict->list[idx].word);
}

void get_feedback(const char *guess, const char *target, FeedbackColor fb[]) {
    int used[WORD_LEN] = {0};

    // Step 1: GREEN
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == target[i]) {
            fb[i] = GREEN;
            used[i] = 1;
        } else {
            fb[i] = GRAY;
        }
    }

    // Step 2: YELLOW
    for (int i = 0; i < WORD_LEN; i++) {
        if (fb[i] == GREEN) continue;
        for (int j = 0; j < WORD_LEN; j++) {
            if (!used[j] && guess[i] == target[j]) {
                fb[i] = YELLOW;
                used[j] = 1;
                break;
            }
        }
    }
}

void print_feedback(const char *guess, const FeedbackColor fb[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        char c = guess[i];
        if (fb[i] == GREEN) printf("[G]%c", c);
        else if (fb[i] == YELLOW) printf("[Y]%c", c);
        else printf("[ ]%c", c);
    }
    printf("\n");
}
