#include <ctype.h>  //
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //
#include <time.h>
#include <unistd.h>

// Clean the terminal with any text, and changes the cursor to position (0,0)
void TerminalCleaner(void) {
  fflush(stdout);
  puts("\x1B[2J");              // erase anything in the terminal
  printf("\033[%d;%dH", 0, 0);  // move the cursor to the top
}

void LogoPrinter(void) {
  puts("\n\n\t   =================================");
  puts("\t   |     UNFAIR TICTACTOE GAME     |");
  puts("\t   =================================");
}

// cleans the stdin buffer
void BufferCleaner(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void EncryptionDecryption(char *data, char *key) {
  int data_length = strlen(data) - 1;
  int key_length = strlen(key);

  char same_data[data_length + 1];
  strcpy(same_data, data);

  for (int i = 0; i < data_length; i++) {
    same_data[i] = data[i] ^ key[i % key_length];
  }

  // printf("\n\nthe function data: %s\n\n", same_data);

  strcpy(data, same_data);
}

void SaveScoreGame(int game_mode, int user_score_to_add,
                   int computer_score_to_add) {
  FILE *infp = fopen("../../data/src/score.txt", "r");
  if (infp == NULL) {
    puts("file failed to Open");
    exit(1);
  }

  char key[] = "a$Thi54";
  char encrypted_data[10];

  // 1. Loading Data and Decrypt it
  fgets(encrypted_data, 9, infp);
  EncryptionDecryption(encrypted_data, key);
  char user_score[10];
  strcpy(user_score, encrypted_data);

  fgets(encrypted_data, 9, infp);
  EncryptionDecryption(encrypted_data, key);
  char computer_score[10];
  strcpy(computer_score, encrypted_data);

  fclose(infp);

  // 2. Adding the scores
  int user_score_length = strlen(user_score) - 1;
  int computer_score_length = strlen(computer_score) - 1;

  int user_num_score = 0, computer_num_score = 0;

  int j = user_score_length - 1;
  for (int i = 0; i < user_score_length; i++) {
    user_num_score = (user_score[i] - '0') * pow(10, j--);
  }
  user_num_score += user_score_to_add;

  j = computer_score_length - 1;
  for (int i = 0; i < user_score_length; i++) {
    computer_num_score = (computer_score[i] - '0') * pow(10, j--);
  }
  computer_num_score += computer_score_to_add;

  // 3. Encrypting the Data and Return it
  infp = fopen("../../data/src/score.txt", "w");

  fprintf(infp, "%d\n", user_num_score);
  fgets(user_score, 10, infp);
  EncryptionDecryption(user_score, key);

  fprintf(infp, "%d\n", computer_num_score);
  fgets(computer_score, 10, infp);
  EncryptionDecryption(computer_score, key);
}

void ShowScoreAndAskForReset(void) {
  FILE *infp = fopen("../../data/src/score.txt", "r");
  if (infp == NULL) {
    puts("file failed to Open");
    exit(1);
  }

  char key[] = "a$Thi54";
  char encrypted_data[10];

  // 1. Loading Data and Decrypt it
  fgets(encrypted_data, 10, infp);
  EncryptionDecryption(encrypted_data, key);
  char user_score[10];
  strcpy(user_score, encrypted_data);
  user_score[strlen(user_score) - 1] = '\0';

  fgets(encrypted_data, 10, infp);
  EncryptionDecryption(encrypted_data, key);
  char computer_score[10];
  strcpy(computer_score, encrypted_data);
  computer_score[strlen(computer_score) - 1] = '\0';

  fclose(infp);

  TerminalCleaner();
  LogoPrinter();
  //\033[60;H
  puts("\n+++++++++++++++++++++++ Score: +++++++++++++++++++++++");
  puts("|                                                      |");
  printf("|       You:  %s  -   %s  :Computer         |", user_score,
         computer_score);
  puts("|                                                      |");
  puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  printf("\n\n\n");

  printf("%s", user_score);
}

int main(void) {
  SaveScoreGame(0, 5, 1);

  ShowScoreAndAskForReset();

  return 0;
}
