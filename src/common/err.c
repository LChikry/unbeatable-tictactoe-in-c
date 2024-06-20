#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// cleans the stdin buffer
void BufferCleaner(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// Good input is an input that
// 1. its length equal to the expected length
// 2. it contains expected character type (alpha or digit)
// 3. if it is alpha, it should be UPPER_CASE
// 4. there is no buffer left in the stdin
int GetGoodInput(int expected_length, bool is_first_char_input_digit) {
  char user_input[expected_length + 8];  // 8 is the margin of error

  puts("\n========================================================");
  fputs("Your input is: ", stdout);
  fgets(user_input, expected_length + 8, stdin);
  puts("========================================================");

  int input_length = strlen(user_input);

  if (user_input[input_length - 1] != '\n') {
    BufferCleaner();
  }

  // shifting white-spaces to the back if there is any
  for (int d = 0; d < input_length - 1; d++) {
    for (int i = 0; i < input_length - 1; i++) {
      if (user_input[i] == ' ') {
        for (int j = i; j < input_length - 1; j++) {
          user_input[j] = user_input[j + 1];
        }
      }
    }
  }

  int character_counter = 0;
  for (int i = 0; i < input_length; i++) {
    if (user_input[i] != ' ' && user_input[i] != '\n') {
      character_counter++;
    }
  }

  if (expected_length != character_counter) return -1;
  if (character_counter == 0) return -1;

  // is input correct
  if (is_first_char_input_digit) {
    if (isalpha(user_input[0])) return -1;

  } else {
    if (isdigit(user_input[0])) return -1;
  }

  // make input good and return it
  if (!is_first_char_input_digit) {
    for (int i = 0; i < character_counter; i++) {
      user_input[i] = toupper(user_input[i]);
    }

    return user_input[0];
  }

  return user_input[0] - '0';
}