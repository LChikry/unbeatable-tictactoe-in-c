#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/game_play/game_checkers.h"
#include "../../include/game_play/saving_gameplays.h"

// Clean the terminal with any text, and changes the cursor to position (0,0)
void TerminalCleaner(void) {
  fflush(stdout);
  puts("\x1B[2J");              // erase anything in the terminal
  printf("\033[%d;%dH", 0, 0);  // move the cursor to the top
}

void LogoPrinter(void) {
  puts("\n\n\t   ===================================");
  puts("\t   |    Unbeatable TicTacToe Game    |");
  puts("\t   ===================================");
}

// the first thing the user sees
void WelcomePage(void) {
  TerminalCleaner();
  puts("\n\n\n\n\n");
  fputs("\t\t      \033[41;1m Welcome to \033[0m", stdout);
  LogoPrinter();
  puts("\n\n\n\n\n");  // just to move the cursor for the design

  sleep(2);
}

void ErrorMessagePrinter(void) {
  TerminalCleaner();
  LogoPrinter();

  fputs("\033[31;1m", stdout);
  puts("\n++++++++++++++++++++++++ Error: ++++++++++++++++++++++++");
  puts("|         Please Choose a Valid Option Number          |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  fputs("\033[0m", stdout);
}

void SuccessfulMessagePrinter(void) {
  TerminalCleaner();
  LogoPrinter();
  puts("\n\n\n\n+++++++++++++++++++++++ Message: +++++++++++++++++++++++");
  puts("|                 Done Successfully :)                 |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  puts("\n\n\n\n");  // just to move the cursor for the design
  sleep(1);
}

static void print_the_move(char *board, int board_place_number) {
  bool is_place_empty = false;

  switch (*(board + board_place_number - 1)) {
    case PLAYER_ONE:
      printf("\033[33;1m");
      break;

    case PLAYER_TWO:
      printf("\033[34;1m");
      break;

    case PLAYER_THREE:
      printf("\033[35;1m");
      break;

    case PLAYER_FOUR:
      printf("\033[31;1m");
      break;

    case PLAYER_FIVE:
      printf("\033[32;1m");
      break;

    default:
      is_place_empty = true;
      break;
  }

  if (is_place_empty) {
    if (board_place_number < 10) printf(" ");
    printf("  %d   ", board_place_number);
  } else {
    printf("   %c   \033[0m", *(board + board_place_number - 1));
  }
}

void BoardPrinter(char *board) {
  printf("\n");
  for (int i = 0; i < 3; i++) {
    puts("\t\t        |       |      ");
    printf("\t\t ");
    for (int j = 0; j < 3; j++) {
      if (j != 0) printf("|");

      if (IsPlaceEmpty(board, j + i * 3 + 1)) {
        printf("   %c   ", *(board + j + i * 3));
        continue;
      }

      print_the_move(board, j + i * 3 + 1);
    }

    if (2 != i) puts("\n\t\t _______|_______|_______");
    if (2 == i) puts("\n\t\t        |       |      ");
  }
}

void MultiplePlayerBoardPrinter(char *board, int number_of_players) {
  printf("\n\n");
  for (int i = 0; i < number_of_players + 1; i++) {
    for (int d = 6; d > number_of_players; --d) printf("    ");
    for (int k = 0; k < number_of_players + 1; ++k) {
      printf("       ");
      if (k != number_of_players) printf("|");
    }
    printf("\n");

    for (int d = 6; d > number_of_players; --d) printf("    ");
    for (int j = 0; j < number_of_players + 1; j++) {
      if (j != 0) printf("|");
      print_the_move(board, j + i * (number_of_players + 1) + 1);
    }
    printf("\n");

    if (i == number_of_players) break;
    for (int d = 6; d > number_of_players; --d) printf("    ");
    for (int k = 0; k < number_of_players + 1; ++k) {
      printf("_______");
      if (k != number_of_players) printf("|");
    }
    printf("\n");
  }

  for (int d = 6; d > number_of_players; --d) printf("    ");
  for (int k = 0; k < number_of_players + 1; ++k) {
    printf("       ");
    if (k != number_of_players) printf("|");
  }
  printf("\n\n");
}

void GameIntro(void) {
  TerminalCleaner();
  LogoPrinter();
  puts("\n\n\n\n+++++++++++++++++++++++ BE READY: ++++++++++++++++++++++");
  puts("|                   The Game Begins                    |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  puts("\n\n\n\n");  // just to move the cursor for the design
  sleep(1);
}

void SavedGameMessage(char *gameplay_title,
                      bool is_gameplay_saved_successfully) {
  TerminalCleaner();
  LogoPrinter();

  puts("\n\n\n\n+++++++++++++++++++++++ Message: ++++++++++++++++++++++");
  puts("|                                                      |");

  if (is_gameplay_saved_successfully) {
    puts(
        "|     \033[32;1m The Gameplay Have Been Successfully Saved  \033[0m   "
        "  |");
    printf("                  Under \"%s\" \n", gameplay_title);
  } else {
    puts(
        "|           \033[31;1m The Gameplay Didn't Get Saved  \033[0m         "
        "  |");
  }

  puts("|                                                      |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  puts("\n\n\n\n");  // just to move the cursor for the design
  sleep(2);
}

void WinnerMessagePrinter(int game_mode, int game_result) {
  TerminalCleaner();
  LogoPrinter();

  if (game_mode == 1 || game_mode == 2)  // Normal Mode
  {
    switch (game_result) {
      case DRAW_GAME:
        puts("\n\n---------------------- Game Over: ----------------------");
        puts(
            "|            \033[36;1m Fair Game, Nether of Us "
            "Won. \033[0m            |");
        puts("--------------------------------------------------------");
        break;

      case COMPUTER_WON:
        puts("\n\n---------------------- Game Over: ----------------------");
        puts(
            "|              \033[31;1m Unfortunately, You Lost.  \033[0m       "
            "      |");
        puts("--------------------------------------------------------");
        break;

      case USER_WON:
        puts("\n\n+++++++++++++++++++ Congratulations: +++++++++++++++++++");
        puts(
            "|                      \033[32;1m You Won! \033[0m                "
            "      |");
        puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        break;

      default:
        break;
    }  // end of the switch
  } else {  // Unfair Mode
    switch (game_result) {
      case DRAW_GAME:
        puts("\n\n---------------------- Game Over: ----------------------");
        puts(
            "|           \033[36;1m As Expected, Nether of Us Won. \033[0m     "
            "      |");
        puts("--------------------------------------------------------");
        break;

      case COMPUTER_WON:
        puts("\n\n---------------------- Game Over: ----------------------");
        puts(
            "|                \033[31;1m As Expected, You Lost. \033[0m        "
            "      |");
        puts("--------------------------------------------------------");
        break;

      case USER_WON:
        puts("\n\n+++++++++++++++++++ Congratulations: +++++++++++++++++++");
        puts(
            "|          \033[32;1m You did the impossible, You Won! \033[0m    "
            "      |");
        puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        break;

      default:
        break;
    }  // end of the switch
  }  // end of the else
}

int PickRandomlyWhoWillPlayFirst(void) {
  TerminalCleaner();
  LogoPrinter();

  // this for nice graphical representation
  puts("\n\n++++++++++++++++++ Flipping the coin: ++++++++++++++++++");
  puts("|                                                      |");

  // showing graphically the coin is flipping
  bool turn = true;
  for (int i = 0; i < 3000; i++) {
    usleep(200);

    if (turn) {
      printf("|                         You                          |\r");
      turn = false;
    } else {
      printf("|                     The Computer                     |\r");
      turn = true;
    }
  }

  // flipping the coin
  int coin_value;
  srand(time(NULL));
  coin_value = rand() % 2;

  // show the result
  if (coin_value == USER_PLAYING_FIRST) {
    printf("|                         You                          |\r");
  } else {
    printf("|                     The Computer                     |\r");
  }

  puts("\n|                                                      |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  if (coin_value == USER_PLAYING_FIRST) {
    puts("\n\n+++++++++++++++++++ Congratulations: +++++++++++++++++++");
    puts("|                You Will Play First!                  |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  } else {
    puts("\n-------------------- Unfortunately: --------------------");
    puts("|                  I Will Play First!                  |");
    puts("--------------------------------------------------------");
  }

  usleep(1750000);
  return coin_value;
}

/// @brief
/// @param gameplay_mode
/// @returns -1 if it fails to open the file, or 0 if no gameplay found,
/// otherwise, it return the number of gameplays saved
int PrintSavedGameplayTitles(int gameplay_mode) {
  FILE *titles_file;
  {
    char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
    GetTitleFileName(titles_file_name, gameplay_mode);
    titles_file = fopen(titles_file_name, "r");
  }
  if (!titles_file) return -1;

  char buffer[MAX_GAMEPLAY_TITLE_LENGTH];
  if (!fgets(buffer, MAX_GAMEPLAY_TITLE_LENGTH, titles_file) ||
      strlen(buffer) == 1) {
    TerminalCleaner();
    LogoPrinter();

    puts("\n++++++++++++++++++++++ Message : +++++++++++++++++++++++");
    puts("|                                                      |");
    puts("|                     No Game Found!                   |");
    puts("|                                                      |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    sleep(2);
    fclose(titles_file);
    return 0;
  }

  puts("\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  puts("|                     Saved Games:                      |");
  puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  puts("---------------------------------------------------------");
  int title_length = 0;
  int titles_count = 0;
  rewind(titles_file);

  while (fgets(buffer, MAX_GAMEPLAY_TITLE_LENGTH, titles_file)) {
    title_length = strlen(buffer) - 1;
    buffer[title_length] = '\0';
    printf("|  %03d. %s", ++titles_count, buffer);
    for (int j = 0; j < MAX_GAMEPLAY_TITLE_LENGTH - title_length; ++j) {
      printf(" ");
    }

    if (!fgets(buffer, MAX_GAMEPLAY_TITLE_LENGTH, titles_file) ||
        strlen(buffer) == 1) {
      break;
    }

    title_length = strlen(buffer) - 1;
    buffer[title_length] = '\0';
    printf("|  %03d. %s", ++titles_count, buffer);

    for (int j = 0; j < MAX_GAMEPLAY_TITLE_LENGTH - title_length; ++j) {
      printf(" ");
    }

    printf("|\n");
    puts("---------------------------------------------------------");
  }

  if (1 == titles_count % 2) {
    for (int k = 0; k < MAX_GAMEPLAY_TITLE_LENGTH + 8; ++k) printf(" ");
    printf("|\n");
    puts("---------------------------------------------------------");
  }

  fclose(titles_file);
  return titles_count;
  return 0;
}  // end of printing saved gameplayTitles

static void ParseMovesIntoBoard(char *board, char *moves,
                                bool should_user_play) {
  char *cursor = moves + 3;
  int moves_length = strlen(moves);
  int board_place_number;

  while (cursor != moves + moves_length) {
    if (!isdigit(*cursor)) {
      ++cursor;
      continue;
    }

    if (-1 == (board_place_number = strtol(cursor, &cursor, 10))) {
      return;
    }

    if (should_user_play) {
      *(board + board_place_number - 1) = USER_PLAYING_SYMBOL;
      should_user_play = false;
      continue;
    }

    *(board + board_place_number - 1) = COMPUTER_PLAYING_SYMBOL;
    should_user_play = true;
  }
}

void PrintSavedGameplayBoards(GameplayNumbers gameplays_to_print,
                              int gameplay_mode, int titles_count) {
  TerminalCleaner();
  LogoPrinter();

  char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetTitleFileName(titles_file_name, gameplay_mode);
  FILE *titles_file = fopen(titles_file_name, "r");

  char moves_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  GetMovesFileName(moves_file_name, gameplay_mode);
  FILE *moves_file = fopen(moves_file_name, "r");

  if (!titles_file || !moves_file) {
    puts("error of Opening File in DeleteSavedGameplays");
    return;
  }

  puts("\n+++++++++++++++++++++++ Message: +++++++++++++++++++++++");
  printf("|     \033[34;1m  %c: Computer  \033[0m       ",
         COMPUTER_PLAYING_SYMBOL);
  printf("          \033[33;1m  %c: User  \033[0m      |\n",
         USER_PLAYING_SYMBOL);
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

  char title_buffer[MAX_GAMEPLAY_TITLE_LENGTH] = {0};
  char moves_buffer[MAX_MOVES_LENGTH] = {0};
  int count = 0;
  bool is_game_found = false;
  bool is_user_played_first = false;

  for (int i = 0; i < titles_count; ++i) {
    if (count >= gameplays_to_print.list_length) break;

    is_game_found = false;
    is_user_played_first = false;
    fgets(title_buffer, MAX_GAMEPLAY_TITLE_LENGTH, titles_file);
    fgets(moves_buffer, MAX_MOVES_LENGTH, moves_file);

    for (int j = 0; j < gameplays_to_print.list_length; ++j) {
      if (i + 1 == gameplays_to_print.list[j]) {
        is_game_found = true;
        ++count;
        break;
      }
    }

    if (!is_game_found) continue;
    int title_length = strlen(title_buffer) - 1;
    title_buffer[title_length] = '\0';
    puts("---------------------------------------------------------");
    printf("|            Title:  %s", title_buffer);
    for (int j = 0; j < 35 - title_length; ++j) printf(" ");
    puts("|");
    puts("---------------------------------------------------------");
    if (moves_buffer[0] == 'U') is_user_played_first = true;
    {
      char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
      ParseMovesIntoBoard(board, moves_buffer, is_user_played_first);
      BoardPrinter(board);
    }
    puts("\n");
  }

  fclose(titles_file);
  fclose(moves_file);

  char c[2];
  do {
    printf(" press enter to exist....");
    fgets(c, 2, stdin);
  } while (c[0] != '\n');
}

void DisplayMultiplePlayerRules(void) {
  TerminalCleaner();
  LogoPrinter();

  puts("\n++++++++++++++++++++++ The Rules: +++++++++++++++++++++++");
  puts("|                                                       |");
  puts("|  1. The First Person to Get 3 in a Row Wins.          |");
  puts("|  2. The Game Ends When One Player Left or It's Draw.  |");
  puts("|  3. Enjoy!!                                           |");
  puts("|                                                       |");
  puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");

  char c[2];
  do {
    printf(" press enter to exist....");
    fgets(c, 2, stdin);
  } while (c[0] != '\n');
}

void InGameMultiplePlayerWinningMessage(const char player_symbol,
                                        const int player_rank) {
  TerminalCleaner();
  LogoPrinter();

  puts("\n\n\n+++++++++++++++++++ Congratulations: +++++++++++++++++++");
  printf("|        ");
  printf("\033[32;1m");
  printf("Player %c, You Won!       You're the #%d", player_symbol,
         player_rank);
  printf("\033[0m");
  printf("        |\n");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
  usleep(2500000);
}