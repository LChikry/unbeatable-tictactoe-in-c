#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/graphic.h"
#include "../../include/computer_turn/computer_turn.h"
#include "../../include/game_play/game_checkers.h"
#include "../../include/game_play/user_turn.h"

int GamePlay(char *board, int game_mode, bool should_user_play,
             const char user_playing_symbol,
             const char computer_playing_symbol) {
  if (game_mode == 3) {
    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|   This Mode is Designed to Never Lose Against You!   |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("\n\n\n\n");  // just to move the cursor for the design
    sleep(3);
  }

  GameIntro();
  int game_result = DRAW_GAME;
  int number_of_turns = -1;
  bool is_winning_algorithm_failed = false;
  bool is_center_and_middle_squares_empty = false;
  bool is_center_and_corner_squares_empty = false;

  TerminalCleaner();
  LogoPrinter();
  while (number_of_turns < 9) {
    number_of_turns++;
    if (number_of_turns >= 5) {
      game_result = WhoWon(board, user_playing_symbol, computer_playing_symbol);
    }
    if (game_result != DRAW_GAME) break;

    if (should_user_play) {
      puts("\n++++++++++++++++++++++ Your Turn: ++++++++++++++++++++++");
      puts("|   Choose the Place You Want By Entering Its Number   |");
      puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      BoardPrinter(board, computer_playing_symbol);

      UserTurn(board, user_playing_symbol);
      should_user_play = false;
      continue;
    }

    TerminalCleaner();
    LogoPrinter();
    ComputerTurn(game_mode, board, computer_playing_symbol, number_of_turns,
                 &is_winning_algorithm_failed,
                 &is_center_and_corner_squares_empty,
                 &is_center_and_middle_squares_empty);
    should_user_play = true;
  }  // end of the while loop

  return game_result;
}