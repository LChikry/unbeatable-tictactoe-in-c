#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/game_play/game_checkers.h"

static int IsSymbolOccurredXTimesAdvanced(char *board,
                                          const int number_of_players,
                                          const char playing_symbol,
                                          const int x_times,
                                          const int direction) {
  int number_of_squares = (number_of_players + 1) * (number_of_players + 1);
  int symbol_occurrence = 0;

  // Checking Horizontally
  if (direction == HORIZONTAL_DIRECTION) {
    for (int i = 0; i < number_of_players + 1; i++) {
      symbol_occurrence = 0;

      for (int j = 0; j < number_of_players + 1; j++) {
        if (IsPlaceTakenByX(board, j + (i * (number_of_players + 1)) + 1,
                            playing_symbol)) {
          symbol_occurrence++;
        }
      }

      if (symbol_occurrence == x_times) return i + 1;  // column number
    }
    return 0;
  }

  // Checking Vertically
  if (direction == VERTICAL_DIRECTION) {
    for (int i = 0; i < number_of_players + 1; i++) {
      symbol_occurrence = 0;

      for (int j = 0; j < number_of_players + 1; j++) {
        if (IsPlaceTakenByX(board, i + (j * (number_of_players + 1)) + 1,
                            playing_symbol)) {
          symbol_occurrence++;
        }
      }

      if (symbol_occurrence == x_times) return i + 1;  // row number
    }
    return 0;
  }

  //! creating a good strategy to check the X shape

  // puts("\n\nHello there\n\n");
  // sleep(3);
  // checking in 1-5-9 X shape
  symbol_occurrence = 0;
  for (int i = 1; i <= number_of_squares; i += 4) {
    if (IsPlaceTakenByX(board, i, playing_symbol)) {
      symbol_occurrence++;
    }
  }
  if (symbol_occurrence == x_times) return X_LINE_159;  // first X line number

  // puts("\n\nHello there1\n\n");
  // sleep(3);
  // checking in 3-5-7 X shape
  symbol_occurrence = 0;
  for (int i = 3; i <= 7; i += 2) {
    if (IsPlaceTakenByX(board, i, playing_symbol)) {
      symbol_occurrence++;
    }
  }
  if (symbol_occurrence == x_times) return X_LINE_357;  // second X line number

  // if no iteration reached X times in the targeted direction
  return DRAW_GAME;
}

const char MultiplePlayerWinnerChecker(char *board, const int number_of_players,
                                       char *symbols) {
  for (int i = 0; i < number_of_players; ++i) {
    if (isdigit(symbols[i])) continue;

    if (IsSymbolOccurredXTimesAdvanced(board, number_of_players, symbols[i], 3,
                                       HORIZONTAL_DIRECTION)) {
      return symbols[i];
    }

    if (IsSymbolOccurredXTimesAdvanced(board, number_of_players, symbols[i], 3,
                                       VERTICAL_DIRECTION)) {
      return symbols[i];
    }

    if (IsSymbolOccurredXTimesAdvanced(board, number_of_players, symbols[i], 3,
                                       X_SHAPE_DIRECTION)) {
      return symbols[i];
    }
  }
  // if no one won yet..
  return MULTIPLE_PLAYER_DRAW_GAME;
}