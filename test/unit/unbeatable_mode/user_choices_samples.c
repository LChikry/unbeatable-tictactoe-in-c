#include <stdio.h>

void CreateRandom4DigitsWithoutNumber5(void) {
  FILE *outfp =
      fopen("data/test/user_second_random_board_place_numbers.txt", "w");

  int count = 10;

  puts("File will started to be Generated");

  int cnt = 0;

  for (int a = 1; a < count; a++) {
    if (a == 5) continue;

    for (int b = 1; b < count; b++) {
      if (b == a || b == 5) continue;

      for (int c = 1; c < count; c++) {
        if (c == a || c == b || c == 5) continue;

        for (int d = 1; d < count; d++) {
          if (d == a || d == b || d == c || d == 5) continue;

          fprintf(outfp, "%d%d%d%d\n", a, b, c, d);
          cnt++;
        }
      }
    }
  }

  fclose(outfp);
  printf("File Created Successfully with %d numbers\n", cnt);
}

void CreateRandom5Digits(void) {
  FILE *outfp =
      fopen("data/test/user_first_random_board_place_numbers.txt", "w");

  int count = 10;

  puts("File will started to be Generated");

  int cnt = 0;

  for (int a = 1; a < count; a++) {
    for (int b = 1; b < count; b++) {
      if (b == a) continue;

      for (int c = 1; c < count; c++) {
        if (c == a || c == b) continue;

        for (int d = 1; d < count; d++) {
          if (d == a || d == b || d == c) continue;

          for (int e = 1; e < count; e++) {
            if (e == a || e == b || e == c || e == d) continue;

            fprintf(outfp, "%d%d%d%d%d\n", a, b, c, d, e);
            cnt++;
          }
        }
      }
    }
  }

  fclose(outfp);

  printf("File Created Successfully with %d numbers\n", cnt);
}

int main(void) {
  CreateRandom4DigitsWithoutNumber5();
  CreateRandom5Digits();

  return 1;
}