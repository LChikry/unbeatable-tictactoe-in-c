#ifndef UNBEATABLE_MODE_H
#define UNBEATABLE_MODE_H

#include <stdbool.h>

int UnbeatableMode(char *board, int number_of_turns,
                   bool *is_winning_algorithm_failed,
                   bool *is_center_and_corner_squares_empty,
                   bool *is_center_and_middle_squares_empty);

int StartingFirstWinningAlgorithm(char *board, int number_of_turns,
                                  bool *is_winning_algorithm_failed);

int StartingSecondWinningAlgorithm(char *board, int number_of_turns,
                                   bool *is_winning_algorithm_failed,
                                   bool *is_center_and_corner_squares_empty,
                                   bool *is_center_and_middle_squares_empty);

int StartingSecondWithEmptyCenterAndMiddleSquares(char *board,
                                                  int number_of_turns);

int StartingSecondWithEmptyCenterAndCornerSquares(
    char *board, int number_of_turns, bool *is_winning_algorithm_failed);

int StartingSecondWithMarkedCenterSquare(char *board, int number_of_turns);

#endif