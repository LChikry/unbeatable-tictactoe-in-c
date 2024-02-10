#ifndef COMPUTER_TURN_H
#define COMPUTER_TURN_H

#include <stdbool.h>

int EasyMode(char *board);

void ComputerTurn(int game_mode, char *board, int number_of_turns,
                  bool *is_winning_algorithm_failed,
                  bool *is_center_and_corner_squares_empty,
                  bool *is_center_and_middle_squares_empty);

char CounterPlayingSymbol(const char playing_symbol);

#endif