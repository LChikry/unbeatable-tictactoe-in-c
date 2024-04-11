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
      GameplayNode *head = NULL;  // head of the linked list
      bool should_user_play = false;
      int game_mode_choice = ComputerModeMenuPage();

      do {
        DeleteTheGameplay(&head);  // sets also head to NULL at the end
        if (2 == menu_choice) game_mode_choice = ComputerModeMenuPage();
        should_user_play = IsUserWillPlayFirst();

        char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
        int game_result =
            GamePlay((char *)board, game_mode_choice, should_user_play, &head);
        WinnerMessagePrinter(game_mode_choice, game_result);
        menu_choice = EndGameMenuPage((char *)board);
      } while (1 == menu_choice || 2 == menu_choice);

      // Saving The Gameplay
      if (3 == menu_choice) {
        int game_title_choice = 0;
        TerminalCleaner();
        LogoPrinter();
        game_title_choice = GameTitleMenuPage();

        TerminalCleaner();
        LogoPrinter();
        char gameplay_title[26] = {0};

        // Manually Adding the Title of the Save
        if (1 == game_title_choice) {
          GetGameTitle(gameplay_title, 26);

          if (SaveTheGameplay(head, game_mode_choice, gameplay_title,
                              should_user_play)) {
            SavedGameMessage(gameplay_title, false);
            // puts("\nerror in SaveTheGameplay");
            // return 1;
          }
          SavedGameMessage(gameplay_title, true);
          DeleteTheGameplay(&head);
          continue;
        }

        // Automatically Adding the Title of the Save
        int save_number = GetNextGameplayTitleNumber(game_mode_choice);
        snprintf(gameplay_title, 25, "Save %0.d", save_number);

        if (SaveTheGameplay(head, game_mode_choice, gameplay_title,
                            should_user_play)) {
          SavedGameMessage(gameplay_title, false);
          // puts("\nerror in SaveTheGameplay");
          // return 1;
        }
        SavedGameMessage(gameplay_title, true);
        DeleteTheGameplay(&head);
        continue;
      }  // end of saving choice in EndGameMenuPage

      DeleteTheGameplay(&head);
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