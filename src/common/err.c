#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/common/common.h"

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
  if (read_chars < 1) return min_boundary - 1;

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