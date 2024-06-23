#ifndef COMMON_H
#define COMMON_H

typedef struct {
  void *next;
  char the_move[2];
} GameplayNode;

typedef struct {
  int *list;
  int list_length;
} GameplayNumbers;

#define false 0
#define true 1

#define HORIZONTAL_DIRECTION 1
#define VERTICAL_DIRECTION 2
#define X_SHAPE_DIRECTION 3

#define X_LINE_159 9
#define X_LINE_357 7

#define USER_WON 2
#define COMPUTER_WON 1
#define DRAW_GAME 0

#define USER_PLAYING_FIRST 1
#define COMPUTER_PLAYING_FIRST 0

#define USER_PLAYING_SYMBOL 'X'
#define COMPUTER_PLAYING_SYMBOL 'O'

#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define PLAYER_THREE 'V'
#define PLAYER_FOUR 'Q'
#define PLAYER_FIVE '@'

#define PLAYING_EASY_MODE 1
#define PLAYING_NORMAL_MODE 2
#define PLAYING_FIRST_ALGO 4
#define PLAYING_SECOND_MIDDLE 5
#define PLAYING_SECOND_CORNER 6
#define PLAYING_SECOND_CENTER 7

#define EASY_GAME_MODE 1
#define NORMAL_GAME_MODE 2
#define UNBEATABLE_GAME_MODE 3

#define MAX_GAMEPLAY_MODE_NAME_LENGTH 22
#define MAX_GAMEPLAY_TITLE_LENGTH 20
#define MAX_FILE_TITLE_LENGTH 57
#define MAX_MOVES_LENGTH 31

#define DEFAULT_SAVED_GAMEPLAY_NAME "Gameplay"
#define DEFAULT_SAVED_GAMEPLAY_LENGTH 8

#ifdef WIN32
#include <windows.h>
#endif

#endif