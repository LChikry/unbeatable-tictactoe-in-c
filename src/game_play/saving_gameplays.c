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
    if (!strncmp(title_match, DEFAULT_SAVED_GAMEPLAY_NAME, 4)) title_count++;
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

GameplayTitles GetSavedGameplaysTitleAndNumber(int game_mode) {
  FILE *titles_file;
  {
    char titles_file_name[65] = {0};
    get_title_file_name(titles_file_name, game_mode);
    titles_file = fopen(titles_file_name, "r");
  }
  if (titles_file == NULL) {
    puts("error of Opening File in GetSavedGameplaysTitleAndNumber");
    return (GameplayTitles){.saved_titles = NULL, .number_of_saved_games = -1};
  }

  GameplayTitles saved_games;
  saved_games.saved_titles = malloc(sizeof(char *));
  saved_games.number_of_saved_games = 0;
  char *buffer = NULL;
  size_t buffer_size = 0;
  int read_chars = 0;

  while ((read_chars = getline(&buffer, &buffer_size, titles_file)) != -1) {
    if (read_chars < 1) return saved_games;

    buffer[read_chars - 1] = '\0';
    ++saved_games.number_of_saved_games;

    saved_games.saved_titles =
        realloc(saved_games.saved_titles,
                sizeof(char *) * saved_games.number_of_saved_games);

    saved_games.saved_titles[saved_games.number_of_saved_games - 1] = buffer;

    buffer = NULL;
    buffer_size = 0;
  }

  fclose(titles_file);
  return saved_games;
}