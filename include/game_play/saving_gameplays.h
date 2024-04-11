#ifndef SAVING_GAMEPLAYS_H
#define SAVING_GAMEPLAYS_H

#include <stdbool.h>

typedef struct {
  void *next;
  char the_move[2];
} GameplayNode;

GameplayNode *SaveTheMove(GameplayNode **top, int new_move);

int GetNextGameplayTitleNumber(int game_mode_choice);

int SaveTheGameplay(GameplayNode *top, int game_mode, const char *game_title,
                    bool is_user_played_first);

void DeleteTheGameplay(GameplayNode **top);

#endif