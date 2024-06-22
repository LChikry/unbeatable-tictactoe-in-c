#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_file_name(char *moves_file_name, char *titles_file_name,
                         int game_mode) {
  char game_mode_name[22];

  switch (game_mode) {
    case 1:
      strncpy(game_mode_name, "easy_gameplays", 22);
      break;

    case 2:
      strncpy(game_mode_name, "normal_gameplays", 22);
      break;

    case 3:
      strncpy(game_mode_name, "unbeatable_gameplays", 22);
      break;

    default:
      puts("error in get_file_name");
      return 1;
  }

  if (moves_file_name != NULL) {
    snprintf(moves_file_name, 65, "../../data/app/gameplays/%s_moves.txt",
             game_mode_name);
  }

  if (titles_file_name != NULL) {
    snprintf(titles_file_name, 65, "../../data/app/gameplays/%s_titles.txt",
             game_mode_name);
  }

  return 0;
}

int main(void) {
  char titles_file_name[MAX_FILE_TITLE_LENGTH] = {0};
  get_file_name(NULL, titles_file_name, 1);

  FILE *input_titles_file = fopen(titles_file_name, "r");
  if (input_titles_file == NULL) return 1;

  int title_count = 0;
  char title_match1[30] = {0};
  char title_match2[30] = {0};
  char title_match3[30] = {0};
  char title_match4[30] = {0};
  char title_match5[30] = {0};

  // while (!feof(input_titles_file)) {
  //   fgets(title_match, 30, input_titles_file);
  //   if (title_match[0] == 0) break;
  //   if (!strncmp(title_match, "Save", 4)) title_count++;
  // }

  fgets(title_match1, 30, input_titles_file);
  fgets(title_match2, 30, input_titles_file);
  fgets(title_match3, 30, input_titles_file);
  fgets(title_match4, 30, input_titles_file);
  fgets(title_match5, 30, input_titles_file);

  if (title_match4[0] == 0) {
    puts("it the null as we saw 4");
  }

  if (strlen(title_match4) == 0) {
    puts("it there is no length 4");
  }

  if (title_match5[0] == 0) {
    puts("it the null as we saw 5");
  }

  if (strlen(title_match5) == 0) {
    puts("it there is no length 5");
  }

  fclose(input_titles_file);

  return 0;
}