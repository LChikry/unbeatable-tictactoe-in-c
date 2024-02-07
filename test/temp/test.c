#include <stdio.h>

int main(void) {
  // code here
  fputs("\033[36;1m", stdout);
  puts("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  puts(
      " EXECUTION FAILURE: Unbeatable Mode with User Playing First Simulator "
      "Test");
  puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  fputs("\033[0m", stdout);
  return 0;
}