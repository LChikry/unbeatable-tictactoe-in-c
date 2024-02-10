#include "../../../include/computer_turn/unbeatable_mode.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../include/common/common.h"
#include "../../../include/game_play/game_checkers.h"
#include "../../../include/game_play/game_play.h"

unsigned long int d = 0;

void MarkUserMove(char *board, char place, const char user_playing_symbol) {
  switch (place) {
    case '1':
      *board = user_playing_symbol;
      break;

    case '2':
      *(board + 1) = user_playing_symbol;
      break;

    case '3':
      *(board + 2) = user_playing_symbol;
      break;

    case '4':
      *(board + 3) = user_playing_symbol;
      break;

    case '5':
      *(board + 4) = user_playing_symbol;
      break;

    case '6':
      *(board + 5) = user_playing_symbol;
      break;

    case '7':
      *(board + 6) = user_playing_symbol;
      break;

    case '8':
      *(board + 7) = user_playing_symbol;
      break;

    case '9':
      *(board + 8) = user_playing_symbol;
      break;

    default:
      puts("something went wrong when playing the user move");
      exit(1);
  }
}

bool UnbeatableModeGameSimulation(FILE *instructions, FILE *results,
                                  bool should_user_play) {
  // setting the board
  char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

  int game_result = DRAW_GAME, number_of_turns = 0;

  bool is_winning_algorithm_failed = false;
  bool is_center_and_corner_squares_empty = false;
  bool is_center_and_middle_squares_empty = false;

  char user_moves[7];
  fgets(user_moves, 7, instructions);

  // Game Started
  int i = 0;

  while (DRAW_GAME == game_result) {
    if (should_user_play) {
      if (!IsPlaceEmpty((char *)board, user_moves[i] - '0')) {
        return false;
      }

      MarkUserMove((char *)board, user_moves[i], USER_PLAYING_SYMBOL);

      should_user_play = false;
      i++;

    } else {
      UnbeatableMode((char *)board, number_of_turns,
                     &is_winning_algorithm_failed,
                     &is_center_and_corner_squares_empty,
                     &is_center_and_middle_squares_empty);

      should_user_play = true;
    }

    number_of_turns++;

    if (number_of_turns >= 5) {
      game_result = WhoWon((char *)board);
    }

    if (9 == number_of_turns) break;
  }  // end of the while loop

  bool is_unbeatable_mode_beaten = false;
  if (game_result == USER_WON) {
    is_unbeatable_mode_beaten = true;
    fprintf(results, "%s", user_moves);
  }

  return is_unbeatable_mode_beaten;
}

int UnbeatableModeTest(void) {
  FILE *instructions =
      fopen("data/test/user_first_random_board_place_numbers.txt", "r");
  FILE *results = fopen("data/test/user_first_game_results.txt", "w");

  if (instructions == NULL) {
    fputs("\033[36;1m", stdout);
    puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("FAILED EXECUTION: Unbeatable Mode with User Playing First");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    fputs("\033[0m", stdout);
    return -1;
  }

  bool is_unbeatable_mode_beaten = false;

  // user playing first
  for (d = 0; d < 15120; d++) {
    is_unbeatable_mode_beaten =
        UnbeatableModeGameSimulation(instructions, results, true);

    if (is_unbeatable_mode_beaten) {
      fputs("\033[31;1m", stdout);
      puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      puts("FAILED: Unbeatable Mode with User Playing First Simulator Test");
      puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      fputs("\033[0m", stdout);
      break;
    }
  }

  if (!is_unbeatable_mode_beaten) {
    fputs("\033[32;1m", stdout);
    puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("PASSED: Unbeatable Mode with User Playing First Simulator Test");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    fputs("\033[0m", stdout);
  }

  fclose(instructions);
  fclose(results);

  instructions =
      fopen("data/test/user_second_random_board_place_numbers.txt", "r");
  results = fopen("data/test/user_second_game_results.txt", "w");

  // todo: work on the aestitic of this message
  if (instructions == NULL) {
    fputs("\033[36;1m", stdout);
    puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("FAILED EXECUTION: Unbeatable Mode with User Playing Second");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    fputs("\033[0m", stdout);
    return -1;
  }

  is_unbeatable_mode_beaten = false;
  // user playing second
  for (d = 0; d < 1680; d++) {
    is_unbeatable_mode_beaten =
        UnbeatableModeGameSimulation(instructions, results, false);

    if (is_unbeatable_mode_beaten) {
      fputs("\033[31;1m", stdout);
      puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      puts("FAILED: Unbeatable Mode with User Playing Second Simulator Test");
      puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      fputs("\033[0m", stdout);
      break;
    }
  }

  if (!is_unbeatable_mode_beaten) {
    fputs("\033[32;1m", stdout);
    puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts("PASSED: Unbeatable Mode with User Playing Second Simulator Test");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    fputs("\033[0m", stdout);
  }

  fclose(instructions);
  fclose(results);

  return 0;
}

/****************************************************************/
/*                                                              */
/*                             MAIN                             */
/*                                                              */
/****************************************************************/
int main(void) {
  UnbeatableModeTest();

  return 0;
}