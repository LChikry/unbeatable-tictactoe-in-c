/*
  I implemented this saving feature using linked list only to implement this
  knowledge. I'm fully aware that the most efficient implementation of this
  feature in this case will be using an array.
*/

#include "../../include/game_play/saving_gameplays.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../include/common/common.h"

GameplayNode *SaveTheMove(GameplayNode **head, int new_move) {
  GameplayNode *node = malloc(sizeof(node));
  if (node == NULL) return NULL;

  snprintf(node->the_move, 2, "%d", new_move);
  node->next = *head;

  *head = node;
  return node;
}

static int get_game_mode_name(int game_mode, char *game_mode_name) {
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
      puts("error in get_file_name");
      return 1;
  }

  return 0;
}

static int get_title_file_name(char *titles_file_name, int game_mode) {
  if (titles_file_name == NULL) return 1;

  char game_mode_name[22];
  if (get_game_mode_name(game_mode, game_mode_name)) return 1;

  snprintf(titles_file_name, 65, "data/app/gameplays/%s_titles.txt",
           game_mode_name);

  return 0;
}

static int get_moves_file_name(char *moves_file_name, int game_mode) {
  if (moves_file_name == NULL) return 1;

  char game_mode_name[22];
  if (get_game_mode_name(game_mode, game_mode_name)) return 1;

  snprintf(moves_file_name, 65, "data/app/gameplays/%s_moves.txt",
           game_mode_name);

  return 0;
}

int GetNextGameplayTitleNumber(int game_mode_choice) {
  char titles_file_name[65] = {0};
  get_title_file_name(titles_file_name, game_mode_choice);

  FILE *input_titles_file = fopen(titles_file_name, "r");
  if (input_titles_file == NULL) return 1;

  int title_count = 0;
  char title_match[30] = {0};

  while (fgets(title_match, 30, input_titles_file) != NULL) {
    if (!strncmp(title_match, "Save", 4)) title_count++;
  }

  fclose(input_titles_file);
  return title_count + 1;
}

static void saving_moves(FILE *moves_file, GameplayNode *head,
                         bool is_it_first_call) {
  if (head == NULL) return;

  saving_moves(moves_file, head->next, false);
  fprintf(moves_file, "%c", head->the_move[0]);
  if (!is_it_first_call) fputs(", ", moves_file);
}

int SaveTheGameplay(GameplayNode *head, int game_mode, const char *game_title,
                    bool is_user_played_first) {
  char moves_file_name[65] = {0};
  char titles_file_name[65] = {0};
  get_moves_file_name(moves_file_name, game_mode);
  get_title_file_name(titles_file_name, game_mode);

  // First file
  FILE *titles_file = fopen(titles_file_name, "a");
  if (titles_file == NULL) return 1;
  fprintf(titles_file, "%s\n", game_title);
  fclose(titles_file);

  // Second file
  FILE *moves_file = fopen(moves_file_name, "a");
  if (moves_file == NULL) return 1;

  if (is_user_played_first) {
    fputs("U: ", moves_file);
  } else {
    fputs("C: ", moves_file);
  }

  saving_moves(moves_file, head, true);
  fputs("\n", moves_file);
  fclose(moves_file);

  return 0;
}

void DeleteTheGameplay(GameplayNode **head) {
  if (*head == NULL) return;
  GameplayNode *temp = NULL;

  while ((*head) != NULL) {
    temp = *head;
    *head = (*head)->next;
    free(temp);
  }
}

char **GetSavedGameplaysTitleAndNumber(int game_mode,
                                       int *number_of_gameplays) {
  char titles_file_name[65] = {0};
  get_title_file_name(titles_file_name, game_mode);

  FILE *titles_file = fopen(titles_file_name, "a");
  if (titles_file == NULL) return NULL;

  int number_of_titles = 0;
  char **saved_titles = malloc(sizeof(char *) * ++number_of_titles);
  char title_buffer[MAXIMUM_GAMEPLAY_TITLE_SIZE + 2];

  while (fgets(title_buffer, MAXIMUM_GAMEPLAY_TITLE_SIZE + 1, titles_file) !=
         NULL) {
    int title_size = strlen(title_buffer) - 1;
    if (title_size < 1) return NULL;
    title_buffer[title_size] = '\0';
    saved_titles[number_of_titles] = malloc(sizeof(char) * title_size);
    strncpy(saved_titles[number_of_titles], title_buffer, title_size);
    saved_titles = realloc(saved_titles, sizeof(char *) * ++number_of_titles);
  }
  fclose(titles_file);

  *number_of_gameplays = number_of_titles - 1;
  return saved_titles;
}