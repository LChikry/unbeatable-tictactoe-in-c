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

int EasyMode(char *board) {
  srand(time(NULL));
  int board_place_number = rand() % 9 + 1;

  while (!IsPlaceEmpty(board, board_place_number)) {
    board_place_number = rand() % 9 + 1;
  }

  *(board + board_place_number - 1) = COMPUTER_PLAYING_SYMBOL;

  return board_place_number;
}

void ComputerTurn(char *board, int number_of_turns,
                  int *playing_algorithm_used) {
  int board_place_number = 0;

  if (PLAYING_EASY_MODE == *playing_algorithm_used) {
    board_place_number = EasyMode(board);
  }

  // Normal Mode used also when the unbeatable algorithm can't win
  if (PLAYING_NORMAL_MODE == *playing_algorithm_used) {
    board_place_number = NormalMode(board, number_of_turns);
  }

  // Finding The Most Optimal and Unbeatable Algorithm
  if (3 == *playing_algorithm_used) {
    *playing_algorithm_used = GetUnbeatableAlgorithm(board, number_of_turns);
  }

  if (PLAYING_FIRST_ALGO == *playing_algorithm_used) {
    board_place_number = StartingFirstWinningAlgorithm(board, number_of_turns,
                                                       playing_algorithm_used);
  }

  if (PLAYING_SECOND_CORNER == *playing_algorithm_used) {
    board_place_number = StartingSecondWithEmptyCenterAndCornerSquares(
        board, number_of_turns, playing_algorithm_used);
  }

  if (PLAYING_SECOND_MIDDLE == *playing_algorithm_used) {
    board_place_number =
        StartingSecondWithEmptyCenterAndMiddleSquares(board, number_of_turns);
  }

  if (PLAYING_SECOND_CENTER == *playing_algorithm_used) {
    board_place_number =
        StartingSecondWithMarkedCenterSquare(board, number_of_turns);
  }

  if (0 != board_place_number) {
    puts("\n++++++++++++++++++++ Computer Turn: ++++++++++++++++++++");
    printf(
        "|           The Computer Played in \033[31;1mPlace %d\033[0m          "
        "  "
        " |\n",
        board_place_number);
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    sleep(1);
    return;
  }

  puts("Something went Wrong in ComputerTurn function");
  exit(1);
}