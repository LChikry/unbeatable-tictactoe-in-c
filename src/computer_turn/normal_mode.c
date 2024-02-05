#include <stdio.h>
#include <stdlib.h>

#include "../../include/common/common.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/game_play/game_checkers.h"

int NormalMode(char *board, char playing_symbol, int number_of_turns) {
  int board_place_number;

  if (number_of_turns >= 4) {
    // check if the computer close to win, then make the winning move if so
    board_place_number =
        CheckXThenTakeTheCriticalMove(board, playing_symbol, true);

    if (board_place_number) return board_place_number;
  }

  // is the computer played first and number_of_turns is 3 or more
  // or is the computer played second and number_of_turns is 4 or more
  if ((number_of_turns >= 3 && 2 != number_of_turns % 2) ||
      (number_of_turns >= 4 && 2 == number_of_turns % 2)) {
    // is the user close to win
    board_place_number =
        CheckXThenTakeTheCriticalMove(board, playing_symbol, false);

    if (board_place_number) return board_place_number;
  }

  // if no one of us close to win, play randomly
  return EasyMode(board, playing_symbol);
}