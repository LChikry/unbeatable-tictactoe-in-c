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
#include "../../include/common/form.h"

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
  FILE *titles_file;
  {
    char titles_file_name[65] = {0};
    get_title_file_name(titles_file_name, game_mode_choice);
    titles_file = fopen(titles_file_name, "r");
  }
  if (titles_file == NULL) return 1;

  int next_title_number = 0;
  char title_match[MAXIMUM_GAMEPLAY_TITLE_SIZE + 2] = {0};

  while (fgets(title_match, MAXIMUM_GAMEPLAY_TITLE_SIZE + 1, titles_file)) {
    if (!strncmp(title_match, DEFAULT_SAVED_GAMEPLAY_NAME,
                 DEFAULT_SAVED_GAMEPLAY_LENGTH)) {
      next_title_number =
          strtol(title_match + DEFAULT_SAVED_GAMEPLAY_LENGTH, NULL, 10) + 1;
    }
  }

  fclose(titles_file);
  return next_title_number;
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

GameplayTitles GetSavedGameplaysTitle(int game_mode) {
  FILE *titles_file;
  {
    char titles_file_name[65] = {0};
    get_title_file_name(titles_file_name, game_mode);
    titles_file = fopen(titles_file_name, "r");
  }
  if (titles_file == NULL) {
    puts("error of Opening File in GetSavedGameplaysTitleAndNumber");
    return (GameplayTitles){.saved_titles = NULL, .titles_count = -1};
  }

  GameplayTitles saved_games = {.saved_titles = NULL, .titles_count = 0};
  char *buffer = NULL;
  size_t buffer_size_limit = 0;
  int read_chars = 0;

  while ((read_chars = getline(&buffer, &buffer_size_limit, titles_file)) > 1) {
    ++saved_games.titles_count;
    saved_games.saved_titles = realloc(
        saved_games.saved_titles, sizeof(char *) * saved_games.titles_count);
    buffer[read_chars - 1] = '\0';
    saved_games.saved_titles[saved_games.titles_count - 1] = buffer;

    buffer = NULL;
    buffer_size_limit = 0;
  }

  fclose(titles_file);
  return saved_games;
}

void DeleteSavedGameplays(GameplayTitles saved_games,
                          GameplayNumbers games_to_delete, int game_mode) {
  FILE *titles_file;
  {
    char titles_file_name[65] = {0};
    get_title_file_name(titles_file_name, game_mode);
    titles_file = fopen(titles_file_name, "w");
  }
  if (titles_file == NULL) {
    puts("error of Opening File in GetSavedGameplaysTitleAndNumber");
    return;
  }

  if (saved_games.titles_count == games_to_delete.list_length) {
    fclose(titles_file);
    return;
  }

  int count = 0;
  bool is_game_found = false;
  for (int i = 0; i < saved_games.titles_count; ++i) {
    is_game_found = false;

    if (count < games_to_delete.list_length) {
      for (int j = 0; j < games_to_delete.list_length; ++j) {
        if (i + 1 == games_to_delete.list[j]) {
          is_game_found = true;
          ++count;
          break;
        }
      }
    }

    if (is_game_found) continue;
    fputs(saved_games.saved_titles[i], titles_file);
    fputs("\n", titles_file);
  }

  fclose(titles_file);
}