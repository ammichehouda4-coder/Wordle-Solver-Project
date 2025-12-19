#include <stdio.h>
#include <string.h>
#include "solver.h"

void copy_dictionary(const Dictionary *src, Dictionary *dest) {
    dest->size = src->size;
    for (int i = 0; i < src->size; i++)
        strcpy(dest->list[i].word, src->list[i].word);
}

int matches_feedback(const char *candidate,
                     const char *guess,
                     const FeedbackColor fb[]) {

    FeedbackColor test_fb[WORD_LEN];
    get_feedback(guess, candidate, test_fb);

    for (int i = 0; i < WORD_LEN; i++) {
        if (test_fb[i] != fb[i])
            return 0;
    }
    return 1;
}

void filter_words(Dictionary *possible, const char *guess, const FeedbackColor fb[]) {
    Dictionary temp;
    temp.size = 0;

    for (int i = 0; i < possible->size; i++) {
        if (matches_feedback(possible->list[i].word, guess, fb)) {
            strcpy(temp.list[temp.size++].word,
                   possible->list[i].word);
        }
    }

    *possible = temp;
}

void solver_play(const Dictionary *dict, const char *target) {
    Dictionary possible;
    copy_dictionary(dict, &possible);

    char guess[WORD_LEN + 1] = "arise";

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
            printf("Solver failed: no candidates left.\n");
            return;
        }

       int idx = rand() % possible.size;
strcpy(guess, possible.list[idx].word);

    }

    printf("Solver failed after 6 attempts.\n");
}
