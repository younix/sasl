/*
 * The following functions were bluntly stolen from
 * http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c.
 * Thanks ryyst!
 */

#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

char *base64_encode(const char *data, size_t input_length, size_t *output_length);
char *base64_decode(const char *data, size_t input_length, size_t *output_length);
void build_decoding_table(void);
void base64_cleanup(void);

#endif
