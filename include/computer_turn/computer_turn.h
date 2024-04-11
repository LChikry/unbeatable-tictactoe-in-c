#ifndef COMPUTER_TURN_H
#define COMPUTER_TURN_H

#include <stdbool.h>

int EasyMode(char *board);

int ComputerTurn(char *board, int number_of_turns, int *playing_algorithm_used);

char CounterPlayingSymbol(const char playing_symbol);

#endif