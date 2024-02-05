#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/graphic.h"
#include "../../include/computer_turn/normal_mode.h"
#include "../../include/computer_turn/unbeatable_mode.h"
#include "../../include/game_play/game_checkers.h"

char CounterPlayingSymbol(const char playing_symbol) {
  if ('X' == playing_symbol) return 'O';

  return 'X';
}

int EasyMode(char *board, const char playing_symbol) {
  srand(time(NULL));
  int board_place_number = rand() % 9 + 1;

  while (!IsPlaceEmpty(board, board_place_number)) {
    board_place_number = rand() % 9 + 1;
  }

  *(board + board_place_number - 1) = playing_symbol;

  return board_place_number;
}

void ComputerTurn(int game_mode, char *board, char playing_symbol,
                  int number_of_turns, bool *is_winning_algorithm_failed,
                  bool *is_center_and_corner_squares_empty,
                  bool *is_center_and_middle_squares_empty) {
  // puts("\n\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  // puts("|                  The Computer Turn                   |");
  // puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // sleep(1);

  int board_place_number = 0;

  if (game_mode == 1) {
    board_place_number = EasyMode(board, playing_symbol);
  }

  if (game_mode == 2) {
    board_place_number = NormalMode(board, playing_symbol, number_of_turns);
  }

  if (game_mode == 3) {
    board_place_number = UnbeatableMode(
        board, playing_symbol, number_of_turns, is_winning_algorithm_failed,
        is_center_and_corner_squares_empty, is_center_and_middle_squares_empty);
  }

  puts("\n++++++++++++++++++++ Computer Turn: ++++++++++++++++++++");
  printf(
      "|           The Computer Played in \033[31;1mPlace %d\033[0m            "
      " |\n",
      board_place_number);
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  sleep(1);
}