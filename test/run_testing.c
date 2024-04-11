#include "run_testing.h"

#include <stdio.h>

void UnitTests(void);
void IntegrationTests(void);

int main(void) {
  UnitTests();
  IntegrationTests();

  return 0;
}

void UnitTests(void) {
  // Un beatable Mode Test
  // CreateRandom4DigitsWithoutNumber5();
  // CreateRandom5Digits();
  UnbeatableModeTest();
}

void IntegrationTests(void) {}