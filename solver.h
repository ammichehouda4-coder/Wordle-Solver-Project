#ifndef SOLVER_H
#define SOLVER_H

#include "wordle.h"

void filter_words(Dictionary *possible, const char *guess, const FeedbackColor fb[]);
void copy_dictionary(const Dictionary *src, Dictionary *dest);
void solver_play(const Dictionary *dict, const char *target);

#endif
