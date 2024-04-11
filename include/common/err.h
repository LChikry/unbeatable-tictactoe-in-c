#ifndef ERR_H
#define ERR_H

#include <stdbool.h>

void BufferCleaner(void);
int GetGoodInput(int expected_length, bool is_first_char_input_digit);

#endif