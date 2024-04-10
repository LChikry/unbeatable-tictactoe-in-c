/*
  I implemented this saving feature using linked list only to implement this
  knowledge. I'm fully aware that the most efficient implementation of this
  feature in this case will be using an array.
*/

#include "../../include/game_play/saving_gameplays.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../include/common/common.h"

GamePlayNode *SaveTheMove(GamePlayNode **top, int new_move) {
  GamePlayNode *node = malloc(sizeof(node));
  if (node == NULL) return NULL;

  snprintf(node->the_move, 2, "%d", new_move);
  node->down = *top;

  *top = node;
  return node;
}

int GetFileName(char *moves_file_name, char *titles_file_name, int game_mode) {
  char game_mode_name[22];

  switch (game_mode) {
    case EASY_GAME_MODE:
      strncpy(game_mode_name, "easy_gameplays", 22);
      break;

    case NORMAL_GAME_MODE:
      strncpy(game_mode_name, "normal_gameplays", 22);
      break;

    case UNBEATABLE_GAME_MODE:
      strncpy(game_mode_name, "unbeatable_gameplays", 22);
      break;

    default:
      puts("error in GetFileName");
      return 1;
  }

  snprintf(moves_file_name, 65, "data/app/gameplays/%s_moves.txt",
           game_mode_name);
  snprintf(titles_file_name, 65, "data/app/gameplays/%s_titles.txt",
           game_mode_name);

  return 0;
}

int PickGameplayName(int game_mode_choice) {
  char titles_file_name[65] = {0};
  {
    char moves_file_name[65] = {0};
    GetFileName(moves_file_name, titles_file_name, game_mode_choice);
  }

  FILE *titles_file = fopen(titles_file_name, "r");
  if (titles_file == NULL) return 1;

  int title_count = 0;
  char title_match[30] = {0};
  while (!feof(titles_file)) {
    fgets(title_match, 30, titles_file);
    if (title_match[0] == 0) break;
    if (!strncmp(title_match, "Save ", 5)) title_count++;
  }

  fclose(titles_file);
  return title_count + 1;
}

int SaveTheGameplay(GamePlayNode *top, int game_mode, const char *game_title,
                    bool is_user_played_first) {
  char moves_file_name[65] = {0};
  char titles_file_name[65] = {0};
  GetFileName(moves_file_name, titles_file_name, game_mode);

  FILE *titles_file = fopen(titles_file_name, "a");
  if (titles_file == NULL) return 1;
  fprintf(titles_file, "%s\n", game_title);
  fclose(titles_file);

  FILE *moves_file = fopen(moves_file_name, "a");
  if (moves_file == NULL) return 1;
  if (is_user_played_first) {
    fputs("U: ", moves_file);
  } else {
    fputs("C: ", moves_file);
  }

  while (top != NULL) {
    fprintf(moves_file, "%c", top->the_move[0]);
    top = top->down;
    if (top != NULL) fputs(", ", moves_file);
  }
  fputs("\n", moves_file);
  fclose(moves_file);

  return 0;
}

void DeleteTheGamePlay(GamePlayNode **top) {
  GamePlayNode *temp = NULL;

  while ((*top) != NULL) {
    temp = *top;
    *top = (*top)->down;
    free(temp);
  }
}

void PrintStack(GamePlayNode *top) {
  int i = 0;
  while (top != NULL) {
    printf("\tstage %d: %c\n", i++, top->the_move[0]);
    top = top->down;
  }
}