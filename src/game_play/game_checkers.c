#include <ctype.h>
#include <stdbool.h>

#include "../../include/common/common.h"
#include "../../include/computer_turn/computer_moves.h"
#include "../../include/computer_turn/computer_turn.h"

bool IsPlaceEmpty(char *board, int board_place_number) {
  return isdigit(*(board + board_place_number - 1));
}

// board place number is the number shown in the board
bool IsPlaceTakenByX(char *board, int board_place_number,
                     const char playing_symbol) {
  if (*(board + board_place_number - 1) == playing_symbol) {
    return true;
  }

  return false;
}

// direction argument means either Horizontally, Vertically or in X shape
// 1: means Horizontally
// 2: means Vertically
// 3: means in X shape

// return values are the squares location, which range 1-3, 7, and 9.
// 1 to 3 are the number of column/row where the targeted occurrence found
// (start counting from top/right to down/left). Abd 9 for the 1-5-9 X line,
// and 7 for 3-5-7 X line.
int IsSymbolOccurredXTimes(char *board, const char playing_symbol, int x_times,
                           int direction) {
  const char counter_playing_symbol = CounterPlayingSymbol(playing_symbol);

  // Checking Horizontally
  if (direction == HORIZONTAL_DIRECTION) {
    for (int i = 0; i < 3; i++) {
      int symbol_occurrence = 0;

      for (int j = 0; j < 3; j++) {
        if (IsPlaceTakenByX(board, j + i * 3 + 1, playing_symbol)) {
          symbol_occurrence++;
        }

        // this is added because of the use case in which we want to check if
        // the user is close to win or not. As a result, we need to make sure
        // that the remaining place is empty, so we can make sure that the
        // user is actually close to win. And for other use cases, this
        // doesn't effect them at all
        if (IsPlaceTakenByX(board, j + i * 3 + 1, counter_playing_symbol)) {
          symbol_occurrence--;
        }
      }

      if (symbol_occurrence == x_times) return i + 1;  // column number
    }
    return 0;
  }

  // Checking Vertically
  if (direction == VERTICAL_DIRECTION) {
    for (int i = 0; i < 3; i++) {
      int symbol_occurrence = 0;

      for (int j = 0; j < 3; j++) {
        if (IsPlaceTakenByX(board, j * 3 + i + 1, playing_symbol)) {
          symbol_occurrence++;
        }

        // see the previous comment on this
        if (IsPlaceTakenByX(board, j * 3 + i + 1, counter_playing_symbol)) {
          symbol_occurrence--;
        }
      }

      if (symbol_occurrence == x_times) return i + 1;  // row number
    }
    return 0;
  }

  // checking in 1-5-9 X shape
  int symbol_occurrence = 0;
  for (int i = 1; i <= 9; i += 4) {
    if (IsPlaceTakenByX(board, i, playing_symbol)) {
      symbol_occurrence++;
    }

    if (IsPlaceTakenByX(board, i, counter_playing_symbol)) {
      symbol_occurrence--;
    }
  }
  if (symbol_occurrence == x_times) return X_LINE_159;  // first X line number

  // checking in 3-5-7 X shape
  symbol_occurrence = 0;
  for (int i = 3; i <= 7; i += 2) {
    if (IsPlaceTakenByX(board, i, playing_symbol)) {
      symbol_occurrence++;
    }

    if (IsPlaceTakenByX(board, i, counter_playing_symbol)) {
      symbol_occurrence--;
    }
  }
  if (symbol_occurrence == x_times) return X_LINE_357;  // second X line number

  // if no iteration reached X times in the targeted direction
  return DRAW_GAME;
}

// Return yes or not, and if yes, it tells in what direction, and what the
// squares are.
bool IsXCloseToWin(char *board, const char playing_symbol_of_x,
                   bool is_x_the_given_playing_symbol, int *winning_direction,
                   int *squares_location) {
  char the_playing_symbol;
  if (is_x_the_given_playing_symbol) {
    the_playing_symbol = playing_symbol_of_x;
  } else {
    the_playing_symbol = CounterPlayingSymbol(playing_symbol_of_x);
  }

  // Checking Horizontally
  *squares_location = IsSymbolOccurredXTimes(board, the_playing_symbol, 2,
                                             HORIZONTAL_DIRECTION);

  if (*squares_location) {
    *winning_direction = HORIZONTAL_DIRECTION;

    return true;
  }

  // Checking Vertically
  *squares_location =
      IsSymbolOccurredXTimes(board, the_playing_symbol, 2, VERTICAL_DIRECTION);

  if (*squares_location) {
    *winning_direction = VERTICAL_DIRECTION;

    return true;
  }

  // Checking in X shape
  *squares_location =
      IsSymbolOccurredXTimes(board, the_playing_symbol, 2, X_SHAPE_DIRECTION);

  if (*squares_location) {
    *winning_direction = X_SHAPE_DIRECTION;

    return true;
  }

  return false;
}

int CheckXThenTakeTheCriticalMove(char *board, const char playing_symbol,
                                  bool are_you_checking_the_given_symbol) {
  // is the user close to win
  int user_winning_direction = 0, user_winning_squares_location = 0;

  if (IsXCloseToWin(board, playing_symbol, are_you_checking_the_given_symbol,
                    &user_winning_direction, &user_winning_squares_location)) {
    // stop the user from winning and return the board place number
    return MakeTheCriticalMove(board, user_winning_direction,
                               user_winning_squares_location);
  }

  return 0;
}

bool IsUserMarkedOnlyCorners(char *board) {
  for (int i = 1; i <= 9; i++) {
    if (1 == i || 3 == i || 7 == i || 9 == i) continue;

    if (IsPlaceTakenByX(board, i, USER_PLAYING_SYMBOL)) {
      return false;
    }
  }

  return true;
}

// returns value meaning are:
// 0: no one win yet
// 1: computer won
// 2: user won
int WhoWon(char *board) {
  if (IsSymbolOccurredXTimes(board, COMPUTER_PLAYING_SYMBOL, 3,
                             HORIZONTAL_DIRECTION)) {
    return COMPUTER_WON;
  }
  if (IsSymbolOccurredXTimes(board, USER_PLAYING_SYMBOL, 3,
                             HORIZONTAL_DIRECTION)) {
    return USER_WON;
  }

  if (IsSymbolOccurredXTimes(board, COMPUTER_PLAYING_SYMBOL, 3,
                             VERTICAL_DIRECTION)) {
    return COMPUTER_WON;
  }
  if (IsSymbolOccurredXTimes(board, USER_PLAYING_SYMBOL, 3,
                             VERTICAL_DIRECTION)) {
    return USER_WON;
  }

  if (IsSymbolOccurredXTimes(board, COMPUTER_PLAYING_SYMBOL, 3,
                             X_SHAPE_DIRECTION)) {
    return COMPUTER_WON;
  }
  if (IsSymbolOccurredXTimes(board, USER_PLAYING_SYMBOL, 3,
                             X_SHAPE_DIRECTION)) {
    return USER_WON;
  }
  // if no one won yet..
  return DRAW_GAME;
}

bool IsUserMiddleMarksAreParallel(char *board) {
  if (IsPlaceTakenByX(board, 2, USER_PLAYING_SYMBOL) &&
      IsPlaceTakenByX(board, 8, USER_PLAYING_SYMBOL)) {
    return true;
  }

  if (IsPlaceTakenByX(board, 4, USER_PLAYING_SYMBOL) &&
      IsPlaceTakenByX(board, 6, USER_PLAYING_SYMBOL)) {
    return true;
  }

  return false;
}