#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/computer_turn/computer_moves.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/computer_turn/normal_mode.h"
#include "../../include/game_play/game_checkers.h"

int StartingFirstWinningAlgorithm(char *board, const char playing_symbol,
                                  int number_of_turns,
                                  bool *is_winning_algorithm_failed) {
  int board_place_number;

  switch (number_of_turns) {
    case 0:                           // the first turn
      *(board + 4) = playing_symbol;  // always play in the middle
      return 5;

    case 2:
      if (IsUserMarkedOnlyCorners(board, playing_symbol)) {
        return MarkTheOppositeCornerOfACorner(board, playing_symbol);
      }

      // if a middle square is marked, mark the corner in the opposite
      // row/column of the middle square the user marked
      return MarkARandomOppositeCornerOfAMiddle(board, playing_symbol);

    case 4:  // Establishing the Trap or Failing to do so
      board_place_number =
          CheckXThenTakeTheCriticalMove(board, playing_symbol, true);
      if (board_place_number) {
        return board_place_number;
      }

      board_place_number =
          CheckXThenTakeTheCriticalMove(board, playing_symbol, false);

      if (board_place_number) {
        bool is_computer_marked_a_middle_square =
            board_place_number == 2 || board_place_number == 4 ||
            board_place_number == 6 || board_place_number == 8;

        if (is_computer_marked_a_middle_square) {
          *is_winning_algorithm_failed = true;
        }

        return board_place_number;
      }

      // if we reached here, this mean the user played in a middle square that
      // doesn't make him/her close to win. Therefore, we'll establish the
      // trap successfully if we play in the corner that is not close to where
      // the user played its middle move
      return MarkATargetedOppositeCornerOfAMiddle(board, playing_symbol);

    case 6:  // The winning move
      // check which squares and direction you are close to win in
      return CheckXThenTakeTheCriticalMove(board, playing_symbol, true);

    default:
      puts("something Went Wrong in StartingFirstWinningAlgorithm");
      exit(1);
      break;
  }  // end of the switch statement
}

int StartingSecondWithMarkedCenterSquare(char *board, const char playing_symbol,
                                         int number_of_turns) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always marks the corner square number 1
      return MarkARandomCorner(board, playing_symbol);

    case 3:
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        return board_place_number;
      }

      return MarkARandomCorner(board, playing_symbol);

    case 5:
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, true))) {
        return board_place_number;
      }

      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        return board_place_number;
      }

      // mark the free adjacent square to the computer first mark (in case 1)
      if (IsPlaceEmpty(board, 2)) {
        *(board + 1) = playing_symbol;
        return 2;
      }

      *(board + 3) = playing_symbol;
      return 4;

    case 7:
      return NormalMode(board, playing_symbol, number_of_turns);

    default:
      puts("Something Went Wrong in StartingSecondWithMarkedCenterSquare");
      exit(1);
  }
}

int StartingSecondWithEmptyCenterAndCornerSquares(
    char *board, const char playing_symbol, int number_of_turns,
    bool *is_winning_algorithm_failed) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always mark the center if possible
      *(board + 4) = playing_symbol;
      return 5;

    case 3:
      // moves if user played in a corner
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        *is_winning_algorithm_failed = true;
        return board_place_number;
      }

      // moves if the user played in a middle
      if (IsUserMiddleMarksAreParallel(board, playing_symbol)) {
        return MarkARandomCorner(board, playing_symbol);
      }

      return MarkTheAdjacentCornerToAMiddle(board, playing_symbol);

    case 5:
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, true))) {
        return board_place_number;
      }

      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        return board_place_number;
      }

      return MarkARandomCorner(board, playing_symbol);

    case 7:
      return NormalMode(board, playing_symbol, number_of_turns);

    default:
      puts(
          "Something Went Wrong in "
          "StartingSecondWithEmptyCenterAndCornerSquares");
      exit(1);
  }
}

int StartingSecondWithEmptyCenterAndMiddleSquares(char *board,
                                                  const char playing_symbol,
                                                  int number_of_turns) {
  int board_place_number;

  switch (number_of_turns) {
    case 1:
      // always mark the center if possible
      *(board + 4) = playing_symbol;
      return 5;

    case 3:
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        return board_place_number;
      }

      if (IsUserMarkedOnlyCorners(board, playing_symbol)) {
        return MarkARandomMiddle(board, playing_symbol);
      }

      return MarkTheOppositeCornerOfACorner(board, playing_symbol);

    case 5:
      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, true))) {
        return board_place_number;
      }

      if ((board_place_number =
               CheckXThenTakeTheCriticalMove(board, playing_symbol, false))) {
        return board_place_number;
      }

      if ((IsPlaceEmpty(board, 4) && IsPlaceEmpty(board, 6)) ||
          (IsPlaceEmpty(board, 2) && IsPlaceEmpty(board, 8))) {
        return MarkARandomMiddle(board, playing_symbol);
      }

      return MarkARandomCorner(board, playing_symbol);

    case 7:
      return NormalMode(board, playing_symbol, number_of_turns);

    default:
      puts(
          "Something Went Wrong in "
          "StartingSecondWithEmptyCenterAndMiddleSquares");
      exit(1);
  }
}

int StartingSecondWinningAlgorithm(char *board, const char playing_symbol,
                                   int number_of_turns,
                                   bool *is_winning_algorithm_failed,
                                   bool *is_center_and_corner_squares_empty,
                                   bool *is_center_and_middle_squares_empty) {
  // choosing the algorithm we going to use
  if (number_of_turns == 1) {
    if (IsPlaceEmpty(board, 5)) {
      if (IsPlaceEmpty(board, 2) && IsPlaceEmpty(board, 4) &&
          IsPlaceEmpty(board, 6) && IsPlaceEmpty(board, 8)) {
        *is_center_and_middle_squares_empty = true;
      } else {
        *is_center_and_corner_squares_empty = true;
      }
    }
    // automatically we will use the algorithm with marked center
  }

  if (*is_center_and_corner_squares_empty) {
    return StartingSecondWithEmptyCenterAndCornerSquares(
        board, playing_symbol, number_of_turns, is_winning_algorithm_failed);
  }

  if (*is_center_and_middle_squares_empty) {
    return StartingSecondWithEmptyCenterAndMiddleSquares(board, playing_symbol,
                                                         number_of_turns);
  }

  return StartingSecondWithMarkedCenterSquare(board, playing_symbol,
                                              number_of_turns);
}

int UnbeatableMode(char *board, char playing_symbol, int number_of_turns,
                   bool *is_winning_algorithm_failed,
                   bool *is_center_and_corner_squares_empty,
                   bool *is_center_and_middle_squares_empty) {
  // this algorithm should be executed first if the condition is true
  if (*is_winning_algorithm_failed) {
    return NormalMode(board, playing_symbol, number_of_turns);
  }

  if (0 == number_of_turns % 2) {
    return StartingFirstWinningAlgorithm(board, playing_symbol, number_of_turns,
                                         is_winning_algorithm_failed);
  }

  return StartingSecondWinningAlgorithm(
      board, playing_symbol, number_of_turns, is_winning_algorithm_failed,
      is_center_and_corner_squares_empty, is_center_and_middle_squares_empty);
}