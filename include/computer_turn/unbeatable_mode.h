#ifndef UNBEATABLE_MODE_H
#define UNBEATABLE_MODE_H

int UnbeatableMode(char *board, char playing_symbol, int number_of_turns,
                   bool *is_winning_algorithm_failed,
                   bool *is_center_and_corner_squares_empty,
                   bool *is_center_and_middle_squares_empty);

int StartingFirstWinningAlgorithm(char *board, const char playing_symbol,
                                  int number_of_turns,
                                  bool *is_winning_algorithm_failed);

int StartingSecondWinningAlgorithm(char *board, const char playing_symbol,
                                   int number_of_turns,
                                   bool *is_winning_algorithm_failed,
                                   bool *is_center_and_corner_squares_empty,
                                   bool *is_center_and_middle_squares_empty);

int StartingSecondWithEmptyCenterAndMiddleSquares(char *board,
                                                  const char playing_symbol,
                                                  int number_of_turns);

int StartingSecondWithEmptyCenterAndCornerSquares(
    char *board, const char playing_symbol, int number_of_turns,
    bool *is_winning_algorithm_failed);

int StartingSecondWithMarkedCenterSquare(char *board, const char playing_symbol,
                                         int number_of_turns);

#endif