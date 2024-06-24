#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define PLAYER_THREE 'V'
#define PLAYER_FOUR 'Q'
#define PLAYER_FIVE '@'

// cleans the stdin buffer
void BufferCleaner(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int GetGoodIntegerInput(int min_boundary, int max_boundary) {
  char *buffer = NULL;
  size_t buffer_size_limit = 0;
  int read_chars = 0;

  puts("\n========================================================");
  fputs("Your input is: ", stdout);
  read_chars = getline(&buffer, &buffer_size_limit, stdin) - 1;
  buffer[read_chars] = '\0';
  puts("========================================================");

  printf("the line is:");
  printf("%s", buffer);
  printf("THINGSTOADD\n");

  printf("\n\nread chars are: %d\n", read_chars);

  int input;
  char *cursor = buffer;
  while (cursor != buffer + read_chars) {
    if (*cursor == ' ') {
      ++cursor;
      continue;
    }
    if (!isdigit(*cursor)) return min_boundary - 1;

    input = strtol(cursor, &cursor, 10);
    break;
  }

  if (input == 0 && errno == EINVAL) return min_boundary - 1;
  if (input < min_boundary || input > max_boundary) return min_boundary - 1;
  return input;
}

int main(void) {
  int input = GetGoodIntegerInput(1, 36);

  printf("the input was: %d", input);

  return 0;
}