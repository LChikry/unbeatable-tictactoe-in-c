#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    puts("|  3. Saved Game Plays                                 |");
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

int WhoWillPlayFirst(void) {
  bool is_loop_run_once = false;
  int playing_order_choice;

  do {
    TerminalCleaner();
    LogoPrinter();
    if (is_loop_run_once) ErrorMessagePrinter();

    puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
    puts("|                Who Will Play First?                  |");
    puts("|                                                      |");
    puts("|     1. You       2. The Computer       3. Random     |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    playing_order_choice = GetGoodInput(1, true);

  } while (playing_order_choice < 1 || playing_order_choice > 3);

  if (3 == playing_order_choice) return PickRandomlyWhoWillPlayFirst();

  return (playing_order_choice - 1);
}

void AssignPlayingSymbols(char *user_playing_symbol,
                          char *computer_playing_symbol) {
  bool is_loop_run_once = false;
  *user_playing_symbol = 'n';

  do {
    TerminalCleaner();
    LogoPrinter();

    if (is_loop_run_once) {
      fputs("\033[31;1m", stdout);
      puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
      puts("|    Please Choose Either:        X     or     O       |");
      puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      fputs("\033[0m", stdout);

    } else {
      puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
      puts("|          What Symbol You Want to Play With?          |");
      puts("|                                                      |");
      puts("|                  X      or      O                    |");
      puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }

    is_loop_run_once = true;
    *user_playing_symbol = GetGoodInput(1, false);
  } while (*user_playing_symbol != 'X' && *user_playing_symbol != 'O');

  *computer_playing_symbol = CounterPlayingSymbol(*user_playing_symbol);
}

int EndGameMenuPage(char *board, const char computer_playing_symbol) {
  bool is_loop_run_once = false;
  int end_game_menu_choice;

  do {
    if (is_loop_run_once) ErrorMessagePrinter();
    BoardPrinter(board, computer_playing_symbol);
    usleep(1300000);
    puts("\n++++++++++++++++++++++ Game Over: ++++++++++++++++++++++");
    puts("|                                                      |");
    puts("|  1. Play Again    2. Save This Game     3. Return    |");
    puts("|                                                      |");
    puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

    is_loop_run_once = true;
    end_game_menu_choice = GetGoodInput(1, true);
  } while (end_game_menu_choice < 1 || end_game_menu_choice > 4);

  return end_game_menu_choice;
}