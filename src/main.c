// todo: add early prediction of draw and end the game automatically (when one
// spot left and is not winning one, when two spots are left and nether of them
// are the winning one)

// todo: add the choice of playing with friends

/* Mini Menu
todo: add a mini menu when finishing a game to give a choice to either return
to the main menu or to do another round
todo: add round score as long as the user enters play again in the mini
menu

todo: add later a feature of replay the last game using a double linked list.
Each node represents a turn

todo: add later a feature of saving a game play, which can be done by saving
a sequence of numbers and xo letters, which indicates the replay of the game,
 and each game play will be saved in one line in a file, and the menu will be
 showing numbering of games, so the user can choose like this:

  1. game 1
  2. game 2
  3. game 3
*/

// todo: use Corn mode all the time in the program

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
      char user_playing_symbol, computer_playing_symbol;
      AssignPlayingSymbols(&user_playing_symbol, &computer_playing_symbol);
      int game_mode_choice = ComputerModeMenuPage();

      while (1 == menu_choice) {
        bool should_user_play = !WhoWillPlayFirst();
        char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
        int game_result =
            GamePlay((char *)board, game_mode_choice, should_user_play,
                     user_playing_symbol, computer_playing_symbol);
        WinnerMessagePrinter(game_mode_choice, game_result);
        menu_choice = EndGameMenuPage((char *)board, computer_playing_symbol);
      }

      if (2 == menu_choice) {
        // save this game
      }

      continue;
    }  // end of first choice

    if (menu_choice == 2) {
      /* code */
    }

  }  // end of the while loop

  TerminalCleaner();
  LogoPrinter();
  puts("\n+++++++++++++++++++++++ MESSAGE: +++++++++++++++++++++++");
  puts("|   Thank you for playing the game, see you soon! :)   |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}  // end of the main