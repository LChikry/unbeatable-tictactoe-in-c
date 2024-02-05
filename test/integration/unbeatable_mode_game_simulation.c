/*
  Compiler Process:

  cd src

  gcc -o ../bin/test/unbeatable_mode_game_simulation
  ../test/integration/unbeatable_mode_game_simulation.c game_checkers.c
  unfair_mode.c normal_mode.c computer_moves.c computer_turn.c
  non_interactive_messages.c

  ../bin/test/./unbeatable_mode_game_simulation
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/common.h"
#include "../../include/game_checkers.h"
#include "../../include/non_interactive_messages.h"
#include "../../include/unfair_mode.h"

unsigned long int d = 0;

// todo: check if the the place number we got from the file is taken or not, if
// taken, finish the game and start the next one. but don't forget to move the
// cursor.

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

void UnbeatableModeGameSimulation(FILE *instructions, FILE *results,
                                  bool should_user_play) {
  // setting the board
  char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
  const char computer_playing_symbol = 'X';
  const char user_playing_symbol = 'O';

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
        return;
      }

      MarkUserMove((char *)board, user_moves[i], user_playing_symbol);

      should_user_play = false;
      i++;

    } else {
      UnfairMode((char *)board, computer_playing_symbol, number_of_turns,
                 &is_winning_algorithm_failed,
                 &is_center_and_corner_squares_empty,
                 &is_center_and_middle_squares_empty);

      should_user_play = true;
    }

    number_of_turns++;

    if (number_of_turns >= 5) {
      game_result =
          WhoWon((char *)board, user_playing_symbol, computer_playing_symbol);
    }

    if (9 == number_of_turns) break;
  }  // end of the while loop

  if (game_result == USER_WON) {
    fprintf(results, "%s", user_moves);
  }
}

int main(void) {
  FILE *instructions =
      fopen("../data/test/user_first_random_board_place_numbers.txt", "r");
  FILE *results = fopen("../data/test/user_first_game_results.txt", "w");

  if (instructions == NULL) {
    printf("\nError opening first instructions file\n");
    return -1;
  } else {
    puts("\nFirst instructions file is successfully opened");
  }

  // user playing first
  for (d = 0; d < 15120; d++) {
    UnbeatableModeGameSimulation(instructions, results, true);
  }

  puts("The first test has successfully done");

  fclose(instructions);
  fclose(results);

  instructions =
      fopen("../data/test/user_second_random_board_place_numbers.txt", "r");
  results = fopen("../data/test/user_second_game_results.txt", "w");

  if (instructions == NULL) {
    printf("\nError opening second instructions file\n");
    return -1;
  } else {
    puts("\nSecond instructions file is successfully opened");
  }

  // user playing second
  for (d = 0; d < 1680; d++) {
    UnbeatableModeGameSimulation(instructions, results, false);
  }

  puts("The second test has successfully done\n");

  fclose(instructions);
  fclose(results);
  return 0;
}