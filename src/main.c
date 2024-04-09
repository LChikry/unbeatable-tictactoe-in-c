#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common/form.h"
#include "../include/common/graphic.h"
#include "../include/game_play/game_play.h"

int main(void) {
  WelcomePage();
  int menu_choice = 1;

  while (menu_choice != 5) {
    menu_choice = MainMenuPage();

    if (1 == menu_choice) {
      int game_mode_choice = ComputerModeMenuPage();

      do {
        if (2 == menu_choice) {
          game_mode_choice = ComputerModeMenuPage();
        }
        bool should_user_play = IsUserWillPlayFirst();
        char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
        int game_result =
            GamePlay((char *)board, game_mode_choice, should_user_play);
        WinnerMessagePrinter(game_mode_choice, game_result);
        menu_choice = EndGameMenuPage((char *)board);
      } while (1 == menu_choice || 2 == menu_choice);

      if (3 == menu_choice) {
        // save this game
      }

      continue;
    }  // end of first choice

    if (menu_choice == 2) {
      // play with friends
    }

  }  // end of the while loop

  TerminalCleaner();
  LogoPrinter();
  puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  puts("|   Thank you for playing the game, see you soon! :)   |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}  // end of the main