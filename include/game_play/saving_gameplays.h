#ifndef SAVING_GAMEPLAYS_H
#define SAVING_GAMEPLAYS_H

#include <stdbool.h>

typedef struct {
  void *next;
  char the_move[2];
} GameplayNode;

typedef struct {
  char **saved_titles;
  int number_of_saved_games;
} GameplayTitles;

GameplayNode *SaveTheMove(GameplayNode **top, int new_move);

int GetNextGameplayTitleNumber(int game_mode_choice);

int SaveTheGameplay(GameplayNode *top, int game_mode, const char *game_title,
                    bool is_user_played_first);

void DeleteTheGameplay(GameplayNode **top);

GameplayTitles GetSavedGameplaysTitleAndNumber(int game_mode);

#endif