#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/err.h"
#include "../../include/common/graphic.h"
#include "../../include/friends_gameplay/multiple_player_game_checkers.h"
#include "../../include/game_play/game_checkers.h"
#include "../../include/game_play/saving_gameplays.h"

char *MultiplePlayerGameplay(char *board, int number_of_players) {
  GameIntro();

  int number_of_squares = (number_of_players + 1) * (number_of_players + 1);
  int number_of_turns = 0;
  char game_result = MULTIPLE_PLAYER_DRAW_GAME;
  int number_of_winners = 0;

  int cursor = 0;
  char *symbols = calloc(sizeof(char), 5);
  symbols[0] = PLAYER_ONE;
  symbols[1] = PLAYER_TWO;
  symbols[2] = PLAYER_THREE;
  symbols[3] = PLAYER_FOUR;
  symbols[4] = PLAYER_FIVE;

  int board_place_number = 0;
  bool is_function_run_once = false;

  while (number_of_turns < number_of_squares - 1) {
    TerminalCleaner();
    LogoPrinter();
    puts("\n++++++++++++++++++++++ Your Turn: ++++++++++++++++++++++");
    puts("|   Choose the Place You Want By Entering Its Number   |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    MultiplePlayerBoardPrinter(board, number_of_players);

    is_function_run_once = false;
    do {
      if (is_function_run_once) {
        ErrorMessagePrinter();
        MultiplePlayerBoardPrinter(board, number_of_players);
      }
      board_place_number = GetGoodIntegerInput(1, number_of_squares);
      is_function_run_once = true;
    } while (board_place_number == 0 ||
             !IsPlaceEmpty(board, board_place_number));

    if (cursor + 1 > number_of_players) cursor = 0;
    while (isdigit(symbols[cursor])) {
      ++cursor;
      if (cursor + 1 > number_of_players) cursor = 0;
    }
    *(board + board_place_number - 1) = symbols[cursor++];

    // after ++, this variable represent how many marks already exist
    ++number_of_turns;
    if (number_of_turns < number_of_players * 2 + 1) continue;
    game_result =
        MultiplePlayerWinnerChecker(board, number_of_players, symbols);

    if (game_result == MULTIPLE_PLAYER_DRAW_GAME) continue;
    for (int i = 0; i < number_of_players; i++) {
      if (symbols[i] != game_result) continue;
      symbols[i] = '0' + (++number_of_winners);
      break;
    }
    InGameMultiplePlayerWinningMessage(game_result, number_of_winners);
    game_result = MULTIPLE_PLAYER_DRAW_GAME;

    if (number_of_winners == number_of_players - 1) break;
  }  // end of the while loop

  return symbols;
}