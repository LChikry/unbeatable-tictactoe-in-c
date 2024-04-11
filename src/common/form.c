#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/common/err.h"
#include "../../include/common/graphic.h"
#include "../../include/computer_turn/computer_turn.h"

int MainMenuPage(void) {
  bool is_loop_run_once = false;
  int main_menu_choice;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n++++++++++++++++++++++ The Menu: +++++++++++++++++++++++");
    puts("|  1. Play Against the Computer                        |");
    puts("|  2. Play with Your Friends                           |");
    puts("|  3. Saved Gameplays                                  |");
    puts("|  4. Your Score                                       |");
    puts("|  5. Quit                                             |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    main_menu_choice = GetGoodInput(1, true);

  } while (main_menu_choice < 1 || main_menu_choice > 5);

  return main_menu_choice;
}

int ComputerModeMenuPage(void) {
  bool is_loop_run_once = false;
  int game_mode;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|          Now, Choose the mode of the game:           |");
    puts("|                                                      |");
    puts("|     1. Easy       2. Normal       3. Unbeatable      |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    game_mode = GetGoodInput(1, true);

  } while (game_mode < 1 || game_mode > 3);

  return game_mode;
}

int FriendsModeMenuPage(void) {
  bool is_loop_run_once = false;
  int number_of_friends;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|       How Many Friends You Want to Play With?        |");
    puts("|                       (Max. 5)                       |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    number_of_friends = GetGoodInput(1, true);

  } while (number_of_friends < 1 || number_of_friends > 5);

  return (number_of_friends + 1);
}

int ResetScoreMenuPage(void) {
  bool is_loop_run_once = false;
  int score_reset_choice;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|       Which Game Mode Score You Want to Reset?       |");
    puts("|                                                      |");
    puts("|    1. Easy    2. Normal    3. Unbeatable    4. All   |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    score_reset_choice = GetGoodInput(1, true);

  } while (score_reset_choice < 1 || score_reset_choice > 4);

  return score_reset_choice;
}

bool IsUserWillPlayFirst(void) {
  bool is_loop_run_once = false;
  int playing_order_choice;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|                Who Will Play First?                  |");
    puts("|                                                      |");
    puts("|     1. Random       2. You       3. The Computer     |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    playing_order_choice = GetGoodInput(1, true);

  } while (playing_order_choice < 1 || playing_order_choice > 3);

  switch (playing_order_choice) {
    case 1:
      return PickRandomlyWhoWillPlayFirst();
      break;

    case 2:
      return true;
      break;

    case 3:
      return false;
      break;

    default:
      return -1;
  }
}

int EndGameMenuPage(char *board) {
  bool is_loop_run_once = false;
  int end_game_menu_choice;

  do {
    if (is_loop_run_once) ErrorMessagePrinter();
    BoardPrinter(board);
    usleep(1300000);
    puts("\n++++++++++++++++++++++ Game Over: ++++++++++++++++++++++");
    puts("|                                                      |");
    puts("|         1. Play Again        2. Change Mode          |");
    puts("|         3. Save              4. Return               |");
    puts("|                                                      |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    end_game_menu_choice = GetGoodInput(1, true);
  } while (end_game_menu_choice <= 0 || end_game_menu_choice >= 5);

  return end_game_menu_choice;
}

int GameTitleMenuPage(void) {
  bool is_loop_run_once = false;
  int titling_the_game_choice;

  do {
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|       How Do You Want To Name This Gameplay?         |");
    puts("|                                                      |");
    puts("|        1. Manually          2. Automatically         |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    titling_the_game_choice = GetGoodInput(1, true);
  } while (titling_the_game_choice < 1 || titling_the_game_choice > 2);

  return titling_the_game_choice;
}

void GetGameTitle(char *gameplay_title, int max_size) {
  int confirming_game_title_choice = 1;

  do {
    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|       Please Enter the Title of This Gameplay        |");
    puts("|                                                      |");
    puts("|                 (Max. 25 Characters)                 |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    puts("\n========================================================");
    fputs("Title: ", stdout);
    fgets(gameplay_title, max_size, stdin);
    puts("========================================================");

    if (gameplay_title[strlen(gameplay_title) - 1] == '\n') {
      gameplay_title[strlen(gameplay_title) - 1] = 0;
    }

    do {
      if (confirming_game_title_choice < 1 ||
          confirming_game_title_choice > 2) {
        ErrorMessagePrinter();
      }
      puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
      puts("|               Do You Confirm This Title?             |");
      puts("|                                                      |");
      puts("|\t   |--------------------------------|          |");
      printf("\t      \"%s\"\n", gameplay_title);
      puts("|\t   |--------------------------------|          |");
      puts("|                                                      |");
      puts("|           1. Confirm          2. Rename              |");
      puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

      confirming_game_title_choice = GetGoodInput(1, true);
      TerminalCleaner();
      LogoPrinter();
    } while (confirming_game_title_choice < 1 ||
             confirming_game_title_choice > 2);
  } while (2 == confirming_game_title_choice);
}