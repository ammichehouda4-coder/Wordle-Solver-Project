#include <stdio.h>
#include <string.h>
#include "solver.h"

void copy_dictionary(const Dictionary *src, Dictionary *dest) {
    dest->size = src->size;
    for (int i = 0; i < src->size; i++)
        strcpy(dest->list[i].word, src->list[i].word);
}

int matches_feedback(const char *word, const char *guess, const FeedbackColor fb[]) {
    int used[WORD_LEN] = {0};

    // Check GREEN
    for (int i = 0; i < WORD_LEN; i++) {
        if (fb[i] == GREEN && word[i] != guess[i]) return 0;
        if (fb[i] == GREEN) used[i] = 1;
    }

    // Check YELLOW & GRAY
    for (int i = 0; i < WORD_LEN; i++) {
        if (fb[i] == YELLOW) {
            int found = 0;
            for (int j = 0; j < WORD_LEN; j++) {
                if (!used[j] && word[j] == guess[i] && guess[j] != word[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found) return 0;
        }

        if (fb[i] == GRAY) {
            int found = 0;
            for (int j = 0; j < WORD_LEN; j++) {
                if (word[j] == guess[i] && !used[j]) {
                    found = 1;
                    break;
                }
            }
            if (found) return 0;
        }
    }

    return 1;
}

void filter_words(Dictionary *possible, const char *guess, const FeedbackColor fb[]) {
    Dictionary temp;
    temp.size = 0;

    for (int i = 0; i < possible->size; i++) {
        if (matches_feedback(possible->list[i].word, guess, fb))
            strcpy(temp.list[temp.size++].word, possible->list[i].word);
    }

    *possible = temp;
}

void solver_play(const Dictionary *dict, const char *target) {
    Dictionary possible;
    copy_dictionary(dict, &possible);

    char guess[WORD_LEN + 1];
    strcpy(guess, "arise");  // good starting word

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        FeedbackColor fb[WORD_LEN];
        get_feedback(guess, target, fb);

        printf("Attempt %d: %s\n", attempt, guess);
        print_feedback(guess, fb);

        if (strcmp(guess, target) == 0) {
            printf("Solver wins in %d attempts!\n", attempt);
            return;
        }

        filter_words(&possible, guess, fb);

        if (possible.size == 0) {
            printf("No more candidates — solver failed.\n");
            return;
        }

        strcpy(guess, possible.list[0].word);  // simple heuristic: pick first
    }

    printf("Solver failed to guess in 6 attempts.\n");
}
