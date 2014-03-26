#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <md5.h>

#include "base64.h"

char *
sasl_plain(char *user, char *pass)
{
	char *auth = NULL;
	char *authstr = NULL;
	ssize_t authlen;
	size_t b64len;

	if ((authlen = asprintf(&auth, ".%s.%s", user, pass)) < 0)
		return NULL;

	auth[0] = '\0';
	auth[strlen(user) + 1] = '\0';

	authstr = base64_encode(auth, (size_t)authlen, &b64len);

	return authstr;
}

#if 0
char *
sasl_digest_md5(char *chellence, char *user, char *pass, char *realm)
{
	size_t size;
	char *chell = base64_decode(chellence, strlen(chellence), &size);
	char *authstr = NULL;

	asprintf(&authstr, "%s:%s:%s", user, realm, pass);

	return authstr;
}
#endif
