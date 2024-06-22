#ifndef COMMON_H
#define COMMON_H

typedef struct {
  void *next;
  char the_move[2];
} GameplayNode;

typedef struct {
  char **titles;
  int titles_count;
} GameplayTitles;

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

#define PLAYING_EASY_MODE 1
#define PLAYING_NORMAL_MODE 2
#define PLAYING_FIRST_ALGO 4
#define PLAYING_SECOND_MIDDLE 5
#define PLAYING_SECOND_CORNER 6
#define PLAYING_SECOND_CENTER 7

#define EASY_GAME_MODE 1
#define NORMAL_GAME_MODE 2
#define UNBEATABLE_GAME_MODE 3

#define MAXIMUM_GAMEPLAY_TITLE_SIZE 20

#define DEFAULT_SAVED_GAMEPLAY_NAME "Gameplay"
#define DEFAULT_SAVED_GAMEPLAY_LENGTH 8

#ifdef WIN32
#include <windows.h>
#endif

#endif