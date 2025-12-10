#ifndef WORDLE_H
#define WORDLE_H

#define WORD_LEN 5
#define MAX_WORDS 30000
#define MAX_ATTEMPTS 6

typedef struct {
    char word[WORD_LEN + 1];
} Word;

typedef struct {
    int size;
    Word list[MAX_WORDS];
} Dictionary;

typedef enum {
    GRAY = 0,
    YELLOW = 1,
    GREEN = 2
} FeedbackColor;

void load_dictionary(const char *filename, Dictionary *dict);
int is_valid_word(const Dictionary *dict, const char *guess);
void pick_random_word(const Dictionary *dict, char *target);

void get_feedback(const char *guess, const char *target, FeedbackColor fb[]);
void print_feedback(const char *guess, const FeedbackColor fb[]);

#endif
