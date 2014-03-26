/*
 * The following functions were bluntly stolen from
 * http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c.
 * Thanks ryyst, I hope that's okay! <3 \o/
 */

#include <math.h>
#include "base64.h"

static char *encoding_table =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

char *
base64_encode(const char *data, size_t input_length, size_t *output_length)
{
	*output_length = (size_t) (4.0 * ceil((double) input_length / 3.0));

	char *encoded_data = calloc(*output_length + 1, sizeof *encoded_data);
	if (encoded_data == NULL) return NULL;

	int i, j;
	for (i = 0, j = 0; i < input_length;) {
		uint32_t octet_a = i < input_length ? data[i++] : 0;
		uint32_t octet_b = i < input_length ? data[i++] : 0;
		uint32_t octet_c = i < input_length ? data[i++] : 0;

		uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
		encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
	}

	for (i = 0; i < mod_table[input_length % 3]; i++)
		encoded_data[*output_length - 1 - i] = '=';

	encoded_data[*output_length] = '\0';

	return encoded_data;
}

char *
base64_decode(const char *data, size_t input_length, size_t *output_length)
{
	if (decoding_table == NULL)
		build_decoding_table();

	if (input_length % 4 != 0)
		return NULL;

	*output_length = input_length / 4 * 3;
	if (data[input_length - 1] == '=') (*output_length)--;
	if (data[input_length - 2] == '=') (*output_length)--;

	char *decoded_data = malloc(*output_length);
	if (decoded_data == NULL)
		return NULL;

	int i, j;
	for (i = 0, j = 0; i < input_length;) {
		uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];
		uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[(int)data[i++]];

		uint32_t triple = (sextet_a << 3 * 6)
			+ (sextet_b << 2 * 6)
			+ (sextet_c << 1 * 6)
			+ (sextet_d << 0 * 6);

		if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
	}

	return decoded_data;
}

void
build_decoding_table(void)
{
	decoding_table = malloc(256);
	int i;

	for (i = 0; i < 0x40; i++)
		decoding_table[(int)encoding_table[i]] = i;
}

void
base64_cleanup(void)
{
	free(decoding_table);
}
