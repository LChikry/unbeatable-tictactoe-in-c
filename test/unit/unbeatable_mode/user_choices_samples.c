#include <stdio.h>

void CreateRandom4DigitsWithoutNumber5(void) {
  FILE *outfp =
      fopen("data/test/user_second_random_board_place_numbers.txt", "w");

  int numbers_list = 10;
  int cnt = 0;

  for (int a = 1; a < numbers_list; a++) {
    if (a == 5) continue;

    for (int b = 1; b < numbers_list; b++) {
      if (b == a || b == 5) continue;

      for (int c = 1; c < numbers_list; c++) {
        if (c == a || c == b || c == 5) continue;

        for (int d = 1; d < numbers_list; d++) {
          if (d == a || d == b || d == c || d == 5) continue;

          fprintf(outfp, "%d%d%d%d\n", a, b, c, d);
          cnt++;
        }
      }
    }
  }

  fclose(outfp);

  // fputs("\033[32;1m", stdout);
  // puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("PASSED EXECUTION: %d of 4 Digit Choices File Generated\n", cnt);
  // puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // fputs("\033[0m", stdout);
}

void CreateRandom5Digits(void) {
  FILE *outfp =
      fopen("data/test/user_first_random_board_place_numbers.txt", "w");

  int numbers_list = 10;
  int cnt = 0;

  for (int a = 1; a < numbers_list; a++) {
    for (int b = 1; b < numbers_list; b++) {
      if (b == a) continue;

      for (int c = 1; c < numbers_list; c++) {
        if (c == a || c == b) continue;

        for (int d = 1; d < numbers_list; d++) {
          if (d == a || d == b || d == c) continue;

          for (int e = 1; e < numbers_list; e++) {
            if (e == a || e == b || e == c || e == d) continue;

            fprintf(outfp, "%d%d%d%d%d\n", a, b, c, d, e);
            cnt++;
          }
        }
      }
    }
  }

  fclose(outfp);

  // fputs("\033[32;1m", stdout);
  // puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("PASSED EXECUTION: %d of 5 Digit Choices File Generated\n", cnt);
  // puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // fputs("\033[0m", stdout);
}

int main(void) {
  CreateRandom4DigitsWithoutNumber5();
  CreateRandom5Digits();

  return 1;
}