#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/graphic.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/game_play/game_checkers.h"
#include "../../include/game_play/saving_gameplays.h"
#include "../../include/game_play/user_turn.h"

int GamePlay(char *board, int game_mode, bool should_user_play,
             GameplayNode **head) {
  if (game_mode == 3) {
    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|   This Mode is Designed to Never Lose Against You!   |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("\n\n\n\n");  // just to move the cursor for the design
    sleep(3);
  }

  GameIntro();
  int number_of_turns = -1;
  int game_result = DRAW_GAME;
  int playing_algorithm_used = game_mode;

  TerminalCleaner();
  LogoPrinter();
  while (number_of_turns < 8) {
    // after ++, this variable represent how many marks already exist
    ++number_of_turns;
    if (number_of_turns >= 5) game_result = WhoWon(board);
    if (game_result != DRAW_GAME) break;
    if (7 <= number_of_turns) {
      int temp = 1;
      if (!IsXCloseToWin(board, USER_PLAYING_SYMBOL, true, &temp, &temp)) {
        if (!IsXCloseToWin(board, COMPUTER_PLAYING_SYMBOL, true, &temp,
                           &temp)) {
          return DRAW_GAME;
        }
      }
    }

    if (should_user_play) {
      puts("\n++++++++++++++++++++++ Your Turn: ++++++++++++++++++++++");
      puts("|   Choose the Place You Want By Entering Its Number   |");
      puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      BoardPrinter(board);

      SaveTheMove(head, UserTurn(board));
      should_user_play = false;
      continue;
    }

    TerminalCleaner();
    LogoPrinter();

    SaveTheMove(head,
                ComputerTurn(board, number_of_turns, &playing_algorithm_used));
    should_user_play = true;
  }  // end of the while loop

  return game_result;
}