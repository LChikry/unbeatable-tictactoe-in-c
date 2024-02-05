#ifndef CHECKING_FUNCTIONS_H
#define CHECKING_FUNCTIONS_H

#include <stdbool.h>

bool IsPlaceEmpty(char *board, int board_place_number);

bool IsPlaceTakenByX(char *board, int board_place_number,
                     const char playing_symbol);

int IsSymbolOccurredXTimes(char *board, const char playing_symbol, int x_times,
                           int direction);

bool IsXCloseToWin(char *board, const char unknown_playing_symbol,
                   bool is_x_the_given_playing_symbol, int *winning_direction,
                   int *squares_location);

int CheckXThenTakeTheCriticalMove(char *board, const char playing_symbol,
                                  bool are_you_checking_the_given_symbol);

bool IsUserMarkedOnlyCorners(char *board, const char computer_playing_symbol);

int WhoWon(char *board, char user_playing_symbol, char computer_playing_symbol);

bool IsUserMiddleMarksAreParallel(char *board,
                                  const char computer_playing_symbol);

#endif