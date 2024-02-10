#ifndef UNBEATABLE_MODE_H
#define UNBEATABLE_MODE_H

#include <stdbool.h>

int GetUnbeatableAlgorithm(char *board, int number_of_turns);

int StartingFirstWinningAlgorithm(char *board, int number_of_turns,
                                  int *playing_algorithm_used);

int StartingSecondWithEmptyCenterAndMiddleSquares(char *board,
                                                  int number_of_turns);

int StartingSecondWithEmptyCenterAndCornerSquares(char *board,
                                                  int number_of_turns,
                                                  int *playing_algorithm_used);

int StartingSecondWithMarkedCenterSquare(char *board, int number_of_turns);

#endif