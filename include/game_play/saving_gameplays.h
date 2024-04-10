#ifndef SAVING_GAMEPLAYS_H
#define SAVING_GAMEPLAYS_H

#include <stdbool.h>

typedef struct {
  void *down;
  char the_move[2];
} GamePlayNode;

GamePlayNode *SaveTheMove(GamePlayNode **top, int new_move);

int GetFileName(char *moves_file_name, char *titles_file_name, int game_mode);

int PickGameplayName(int game_mode_choice);

int SaveTheGameplay(GamePlayNode *top, int game_mode, const char *game_title,
                    bool is_user_played_first);

void DeleteTheGamePlay(GamePlayNode **top);

void PrintStack(GamePlayNode *top);

#endif