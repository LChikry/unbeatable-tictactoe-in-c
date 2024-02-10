#include <stdio.h>
#include <stdlib.h>

#include "../../include/common/common.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/game_play/game_checkers.h"

int MarkTheOppositeCornerOfACorner(char *board) {
  // checks if one of the corners is marked or not by the user
  for (int i = 1; i <= 9; i += 2) {
    if (5 == i) continue;

    if (!IsPlaceEmpty(board, i)) {
      // if the corner is marked, we mark its opposite corner
      *(board + 10 - i - 1) = COMPUTER_PLAYING_SYMBOL;
      return 10 - i;
    }
  }  // end of for-loop

  puts("error in MarkTheOppositeCornerOfACorner");
  exit(1);
}

int MarkARandomOppositeCornerOfAMiddle(char *board) {
  // checks what is the middle square marked by the user
  for (int i = 2; i <= 8; i += 2) {
    if (IsPlaceEmpty(board, i)) continue;

    // we mark a corner that is exists in the opposite row/column of the
    // middle square the user marked
    if (i < 5) {
      *(board + i + 5 - 1) = COMPUTER_PLAYING_SYMBOL;
      return i + 5;
    }

    // this happen when i >= 5
    *(board + i - 5 - 1) = COMPUTER_PLAYING_SYMBOL;
    return i - 5;
  }  // end of the loop

  puts("error in MarkARandomOppositeCornerOfAMiddle");
  exit(1);
}

int MarkARandomCorner(char *board) {
  // checks what is the middle square marked by the user
  for (int i = 1; i <= 9; i += 2) {
    if (5 == i) continue;

    if (IsPlaceEmpty(board, i)) {
      *(board + i - 1) = COMPUTER_PLAYING_SYMBOL;
      return i;
    }
  }

  puts("error in MarkARandomCorner");
  exit(1);
}

int MarkARandomMiddle(char *board) {
  for (int i = 2; i <= 8; i += 2) {
    if (IsPlaceEmpty(board, i)) {
      *(board + i - 1) = COMPUTER_PLAYING_SYMBOL;
      return i;
    }
  }

  puts("error in MarkARandomMiddle");
  exit(1);
}

int MarkATargetedOppositeCornerOfAMiddle(char *board) {
  int first_corner_square_number, second_corner_square_number;

  // checks what is the middle square marked by the user
  for (int i = 2; i <= 8; i += 2) {
    if (IsPlaceEmpty(board, i)) continue;

    // what are the corner squares that are opposite to the middle square
    // the user marked
    switch (i) {
      case 2:
        first_corner_square_number = 7;
        second_corner_square_number = 9;
        break;

      case 4:
        first_corner_square_number = 3;
        second_corner_square_number = 9;
        break;

      case 6:
        first_corner_square_number = 1;
        second_corner_square_number = 7;
        break;

      case 8:
        first_corner_square_number = 1;
        second_corner_square_number = 3;
        break;

      default:
        puts("error in MarkATargetedOppositeCornerOfAMiddle");
        exit(1);
    }  // end of the switch case
  }    // end of the loop

  // we mark the free corner that is exists in the opposite row/column of
  // the middle square the user marked
  for (int i = 1; i <= 9; i += 2) {
    if (5 == i) continue;

    if (!IsPlaceEmpty(board, i)) continue;

    if (i == first_corner_square_number || i == second_corner_square_number) {
      *(board + i - 1) = COMPUTER_PLAYING_SYMBOL;

      return i;
    }
  }

  puts("error in MarkATargetedOppositeCornerOfAMiddle");
  exit(1);
}

int MarkTheAdjacentCornerToAMiddle(char *board) {
  for (int i = 2; i <= 8; i += 2) {
    if (!IsPlaceEmpty(board, i)) {
      if (4 == i || 6 == i) {
        if (IsPlaceEmpty(board, i + 3)) {
          *(board + i + 2) = COMPUTER_PLAYING_SYMBOL;
          return i + 3;
        }

        *(board + i - 4) = COMPUTER_PLAYING_SYMBOL;
        return i - 3;
      }

      if (IsPlaceEmpty(board, i + 1)) {
        *(board + i) = COMPUTER_PLAYING_SYMBOL;
        return i + 1;
      }

      *(board + i - 2) = COMPUTER_PLAYING_SYMBOL;
      return i - 1;
    }
  }

  puts("error in MarkTheAdjacentCornerToAMiddle");
  exit(1);
}

int MakeTheCriticalMove(char *board, int winning_direction,
                        int squares_location) {
  if (winning_direction == HORIZONTAL_DIRECTION) {
    for (int i = 0; i < 3; i++) {
      if (IsPlaceEmpty(board, squares_location * 3 - i)) {
        *(board + squares_location * 3 - i - 1) = COMPUTER_PLAYING_SYMBOL;

        return squares_location * 3 - i;
      }
    }
  }

  if (winning_direction == VERTICAL_DIRECTION) {
    for (int i = 0; i < 3; i++) {
      if (IsPlaceEmpty(board, squares_location + i * 3)) {
        *(board + squares_location + i * 3 - 1) = COMPUTER_PLAYING_SYMBOL;

        return squares_location + i * 3;
      }
    }
  }

  if (squares_location == X_LINE_159) {
    for (int i = 1; i <= 9; i += 4) {
      if (IsPlaceEmpty(board, i)) {
        *(board + i - 1) = COMPUTER_PLAYING_SYMBOL;

        return i;
      }
    }
  }

  if (squares_location == X_LINE_357) {
    for (int i = 3; i <= 7; i += 2) {
      if (IsPlaceEmpty(board, i)) {
        *(board + i - 1) = COMPUTER_PLAYING_SYMBOL;

        return i;
      }
    }
  }

  return 0;  // in case of error
}