#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/computer_turn/computer_moves.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/computer_turn/normal_mode.h"
#include "../../include/game_play/game_checkers.h"

int StartingFirstWinningAlgorithm(char *board, int number_of_turns,
                                  int *playing_algorithm_used) {
  int board_place_number;

  switch (number_of_turns) {
    case 0:                                    // the first turn
      *(board + 4) = COMPUTER_PLAYING_SYMBOL;  // always play in the middle
      return 5;

    case 2:
      if (IsUserMarkedOnlyCorners(board)) {
        return MarkTheOppositeCornerOfACorner(board);
      }

      // if a middle square is marked, mark the corner in the opposite
      // row/column of the middle square the user marked
      return MarkARandomOppositeCornerOfAMiddle(board);

    case 4:  // Establishing the Trap or Failing to do so
      board_place_number =
          CheckXThenTakeTheCriticalMove(board, COMPUTER_PLAYING_SYMBOL, true);
      if (board_place_number) {
        return board_place_number;
      }

      board_place_number =
          CheckXThenTakeTheCriticalMove(board, COMPUTER_PLAYING_SYMBOL, false);

      if (board_place_number) {
        bool is_computer_marked_a_middle_square =
            board_place_number == 2 || board_place_number == 4 ||
            board_place_number == 6 || board_place_number == 8;

        if (is_computer_marked_a_middle_square) {
          *playing_algorithm_used = PLAYING_NORMAL_MODE;
        }

        return board_place_number;
      }

      // if we reached here, this mean the user played in a middle square that
      // doesn't make him/her close to win. Therefore, we'll establish the
      // trap successfully if we play in the corner that is not close to where
      // the user played its middle move
      return MarkATargetedOppositeCornerOfAMiddle(board);

    case 6:  // The winning move
      // check which squares and direction you are close to win in
      return CheckXThenTakeTheCriticalMove(board, COMPUTER_PLAYING_SYMBOL,
                                           true);

    default:
      puts("something Went Wrong in StartingFirstWinningAlgorithm");
      exit(1);
      break;
  }  // end of the switch statement
}

int StartingSecondWithMarkedCenterSquare(char *board, int number_of_turns) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always marks the corner square number 1
      return MarkARandomCorner(board);

    case 3:
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        return board_place_number;
      }

      return MarkARandomCorner(board);

    case 5:
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, true))) {
        return board_place_number;
      }

      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        return board_place_number;
      }

      // mark the free adjacent square to the computer first mark (in case 1)
      if (IsPlaceEmpty(board, 2)) {
        *(board + 1) = COMPUTER_PLAYING_SYMBOL;
        return 2;
      }

      *(board + 3) = COMPUTER_PLAYING_SYMBOL;
      return 4;

    case 7:
      return NormalMode(board, number_of_turns);

    default:
      puts("Something Went Wrong in StartingSecondWithMarkedCenterSquare");
      exit(1);
  }
}

int StartingSecondWithEmptyCenterAndCornerSquares(char *board,
                                                  int number_of_turns,
                                                  int *playing_algorithm_used) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always mark the center if possible
      *(board + 4) = COMPUTER_PLAYING_SYMBOL;
      return 5;

    case 3:
      // moves if user played in a corner
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        *playing_algorithm_used = PLAYING_NORMAL_MODE;
        return board_place_number;
      }

      // moves if the user played in a middle
      if (IsUserMiddleMarksAreParallel(board)) {
        return MarkARandomCorner(board);
      }

      return MarkTheAdjacentCornerToAMiddle(board);

    case 5:
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, true))) {
        return board_place_number;
      }

      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        return board_place_number;
      }

      return MarkARandomCorner(board);

    case 7:
      return NormalMode(board, number_of_turns);

    default:
      puts(
          "Something Went Wrong in "
          "StartingSecondWithEmptyCenterAndCornerSquares");
      exit(1);
  }
}

int StartingSecondWithEmptyCenterAndMiddleSquares(char *board,
                                                  int number_of_turns) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always mark the center if possible
      *(board + 4) = COMPUTER_PLAYING_SYMBOL;
      return 5;

    case 3:
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        return board_place_number;
      }

      if (IsUserMarkedOnlyCorners(board)) {
        return MarkARandomMiddle(board);
      }

      return MarkTheOppositeCornerOfACorner(board);

    case 5:
      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, true))) {
        return board_place_number;
      }

      if ((board_place_number = CheckXThenTakeTheCriticalMove(
               board, COMPUTER_PLAYING_SYMBOL, false))) {
        return board_place_number;
      }

      if ((IsPlaceEmpty(board, 4) && IsPlaceEmpty(board, 6)) ||
          (IsPlaceEmpty(board, 2) && IsPlaceEmpty(board, 8))) {
        return MarkARandomMiddle(board);
      }

      return MarkARandomCorner(board);

    case 7:
      return NormalMode(board, number_of_turns);

    default:
      puts(
          "Something Went Wrong in "
          "StartingSecondWithEmptyCenterAndMiddleSquares");
      exit(1);
  }
}

int GetUnbeatableAlgorithm(char *board, int number_of_turns) {
  if (0 == number_of_turns) {
    return PLAYING_FIRST_ALGO;
  }

  if (!IsPlaceEmpty(board, 5)) {
    return PLAYING_SECOND_CENTER;
  }

  if (IsPlaceEmpty(board, 2) && IsPlaceEmpty(board, 4) &&
      IsPlaceEmpty(board, 6) && IsPlaceEmpty(board, 8)) {
    return PLAYING_SECOND_MIDDLE;
  }

  return PLAYING_SECOND_CORNER;
}