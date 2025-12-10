#include <stdio.h>
#include <string.h>
#include "wordle.h"
#include "solver.h"

int main() {
    Dictionary dict;
    load_dictionary("words.txt", &dict);

    char target[WORD_LEN + 1];
    pick_random_word(&dict, target);

    printf("=== WORDLE GAME ===\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        char guess[WORD_LEN + 1];
        printf("Guess %d: ", attempt);
        scanf("%5s", guess);

        if (!is_valid_word(&dict, guess)) {
            printf("Invalid word.\n");
            attempt--;
            continue;
        }

        FeedbackColor fb[WORD_LEN];
        get_feedback(guess, target, fb);
        print_feedback(guess, fb);

        if (strcmp(guess, target) == 0) {
            printf("You win!\n");
            return 0;
        }
    }

    printf("You lose! Target was: %s\n", target);

    printf("\n--- Auto Solver ---\n");
    solver_play(&dict, target);

    return 0;
}
