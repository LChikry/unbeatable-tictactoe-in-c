#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/game_play/game_checkers.h"

/*

2 < 2

1  2  3  4
5  6  7  8
9 10 11 12
13 14 15 16

*/

static int horizontal_checking(char *board, const char playing_symbol,
                               int board_size, int i, int j, int k) {
  if (IsPlaceTakenByX(board, j + (i * board_size) + 1 + k, playing_symbol)) {
    return 1;
  }

  return 0;
}

static int vertical_checking(char *board, const char playing_symbol,
                             int board_size, int i, int j, int k) {
  if (IsPlaceTakenByX(board, i + (j * board_size) + 1 + (k * board_size),
                      playing_symbol)) {
    return 1;
  }

  return 0;
}

static int right_diagonal_checking(char *board, const char playing_symbol,
                                   int board_size, int i, int j, int k) {
  int right_down_jump_length = board_size - 1;

  if (IsPlaceTakenByX(
          board,
          (i * board_size) + board_size - j + (k * right_down_jump_length),
          playing_symbol)) {
    return 1;
  }

  return 0;
}

static int left_diagonal_checking(char *board, const char playing_symbol,
                                  int board_size, int i, int j, int k) {
  int left_down_jump_length = board_size + 1;

  if (IsPlaceTakenByX(board,
                      j + (i * board_size) + 1 + (k * left_down_jump_length),
                      playing_symbol)) {
    return 1;
  }

  return 0;
}

static int IsSymbolOccurredXTimesAdvanced(char *board,
                                          const int number_of_players,
                                          const char playing_symbol,
                                          const int x_times) {
  const int board_size = number_of_players + 1;

  int horizontal_symbol_occurrence = 0;
  int vertical_symbol_occurrence = 0;
  int right_diagonal_symbol_occurrence = 0;
  int left_diagonal_symbol_occurrence = 0;

  for (int i = 0; i < board_size; ++i) {
    for (int j = 0; j < board_size - 2; ++j) {
      horizontal_symbol_occurrence = 0;
      vertical_symbol_occurrence = 0;
      right_diagonal_symbol_occurrence = 0;
      left_diagonal_symbol_occurrence = 0;

      for (int k = 0; k < x_times; ++k) {
        horizontal_symbol_occurrence +=
            horizontal_checking(board, playing_symbol, board_size, i, j, k);

        vertical_symbol_occurrence +=
            vertical_checking(board, playing_symbol, board_size, i, j, k);

        if (i >= board_size - 2) continue;
        right_diagonal_symbol_occurrence +=
            right_diagonal_checking(board, playing_symbol, board_size, i, j, k);

        left_diagonal_symbol_occurrence +=
            left_diagonal_checking(board, playing_symbol, board_size, i, j, k);
      }

      if (horizontal_symbol_occurrence == x_times ||
          vertical_symbol_occurrence == x_times ||
          right_diagonal_symbol_occurrence == x_times ||
          left_diagonal_symbol_occurrence == x_times) {
        return i + 1;
      }
    }
  }

  return DRAW_GAME;
}

const char MultiplePlayerWinnerChecker(char *board, const int number_of_players,
                                       char *symbols) {
  for (int i = 0; i < number_of_players; ++i) {
    if (isdigit(symbols[i])) continue;

    if (IsSymbolOccurredXTimesAdvanced(board, number_of_players, symbols[i],
                                       3)) {
      return symbols[i];
    }
  }
  // if no one won yet..
  return MULTIPLE_PLAYER_DRAW_GAME;
}

bool IsSomeoneCloseToWin(char *board, const int number_of_players,
                         char *symbols) {
  for (int i = 0; i < number_of_players; ++i) {
    if (isdigit(symbols[i])) continue;

    if (IsSymbolOccurredXTimesAdvanced(board, number_of_players, symbols[i],
                                       2)) {
      return true;
    }
  }

  return false;
}