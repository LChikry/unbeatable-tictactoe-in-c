#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/common/common.h"
#include "../include/common/form.h"
#include "../include/common/graphic.h"
#include "../include/game_play/game_play.h"
#include "../include/game_play/saving_gameplays.h"

int main(void) {
  WelcomePage();
  int menu_choice = 1;

  while (menu_choice != 5) {
    menu_choice = MainMenuPage();

    if (1 == menu_choice) {
      GamePlayNode *top = NULL;  // top of the stack of the gameplay moves
      bool should_user_play = false;
      int game_mode_choice = ComputerModeMenuPage();

      do {
        if (2 == menu_choice) game_mode_choice = ComputerModeMenuPage();
        should_user_play = IsUserWillPlayFirst();

        char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
        int game_result =
            GamePlay((char *)board, game_mode_choice, should_user_play, &top);
        WinnerMessagePrinter(game_mode_choice, game_result);
        menu_choice = EndGameMenuPage((char *)board);

        if (3 != menu_choice) DeleteTheGamePlay(&top);
      } while (1 == menu_choice || 2 == menu_choice);

      // handling one of the choices of the EndGameMenuPage
      if (3 == menu_choice) {
        int game_title_choice = 0;
        TerminalCleaner();
        LogoPrinter();
        game_title_choice = GameTitleMenuPage();

        TerminalCleaner();
        LogoPrinter();
        char gameplay_title[26] = {0};

        if (1 == game_title_choice) {
          GetGameTitle(gameplay_title, 26);
          if (SaveTheGameplay(top, game_mode_choice, gameplay_title,
                              should_user_play)) {
            puts("\nerror in SaveTheGameplay");
            return 1;
          }
          SavedGameMessage(gameplay_title, true);
          continue;
        }

        // name the game automatically
        int save_number = PickGameplayName(game_mode_choice);
        snprintf(gameplay_title, 25, "Save %d", save_number);

        if (SaveTheGameplay(top, game_mode_choice, gameplay_title,
                            should_user_play)) {
          puts("\nerror in SaveTheGameplay");
          return 1;
        }
        SavedGameMessage(gameplay_title, true);
      }

      continue;
    }  // end of first choice

    if (menu_choice == 2) {
      // play with friends
      continue;
    }

  }  // end of the while loop

  TerminalCleaner();
  LogoPrinter();
  puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  puts("|   Thank you for playing the game, see you soon! :)   |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}  // end of the main