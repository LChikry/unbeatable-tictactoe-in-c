#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../include/common/common.h"
#include "../../include/game_play/game_checkers.h"

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

void BoardPrinter(char *board) {
  printf("\n");
  for (int i = 0; i < 3; i++) {
    puts("\t\t        |       |      ");
    printf("\t\t ");
    for (int j = 0; j < 3; j++) {
      if (j != 0) printf("|");

      if (!IsPlaceEmpty(board, j + i * 3 + 1)) {
        if (IsPlaceTakenByX(board, j + i * 3 + 1, COMPUTER_PLAYING_SYMBOL)) {
          printf("\033[34;1m   %c   \033[0m", *(board + j + i * 3));
        } else {
          printf("\033[33;1m   %c   \033[0m", *(board + j + i * 3));
        }
      } else {
        printf("   %c   ", *(board + j + i * 3));
      }
    }

    if (2 != i) puts("\n\t\t _______|_______|_______");
    if (2 == i) puts("\n\t\t        |       |      ");
  }
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
    }       // end of the switch
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
  }    // end of the else
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