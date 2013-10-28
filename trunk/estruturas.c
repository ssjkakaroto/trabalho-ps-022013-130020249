#define ESTRUTURAS_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


/**
 * RFC 822 defines the syntax for email addresses. Unfortunately, the syntax is
 * complex, and it supports several address formats that are no longer relevant.
 * The fortunate thing is that if anyone attempts to use one of these
 * no-longer-relevant address formats, you can be reasonably certain they are
 * attempting to do something they are not supposed to do.
 *
 * You can use the following spc_email_isvalid( ) function to check the format
 * of an email address. It will perform only a syntactical check and will not
 * actually attempt to verify the authenticity of the address by attempting to
 * deliver mail to it or by performing any DNS lookups on the domain name
 * portion of the address.
 *
 * The function only validates the actual email address and will not accept any
 * associated data. For example, it will fail to validate
 * "Bob Bobson <bob@bobson.com>", but it will successfully validate
 * "bob@bobson.com".
 * If the supplied email address is syntactically valid, spc_email_isvalid( )
 * will return 1; otherwise, it will return 0.
 *
 * http://www.oreillynet.com/network/excerpt/spcookbook_chap03/index3.html
 *
int spc_email_isvalid(const char *address)
{
	int count = 0; /*!< Descrição da variável para o Doxygen *
	const char *c, *domain;
	static char *rfc822_specials = "()<>@,;:\\\"[]";

	/* first we validate the name portion (name@domain) *
	for (c = address;  *c;  c++) {
		if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == '\"')) {
			while (*++c) {
				if (*c == '\"') break;
				if (*c == '\\' && (*++c == ' ')) continue;
				if (*c <= ' ' || *c >= 127) return 0;
			}
			if (!*c++) return 0;
			if (*c == '@') break;
			if (*c != '.') return 0;
			continue;
		}
		if (*c == '@') break;
		if (*c <= ' ' || *c >= 127) return 0;
		if (strchr(rfc822_specials, *c)) return 0;
	}

	if (c == address || *(c - 1) == '.') return 0;

	/* next we validate the domain portion (name@domain) *
	if (!*(domain = ++c)) return 0;
	do {
		if (*c == '.') {
			if (c == domain || *(c - 1) == '.') return 0;
			count++;
		}
		if (*c <= ' ' || *c >= 127) return 0;
		if (strchr(rfc822_specials, *c)) return 0;
	} while (*++c);

	return (count >= 1);
}
*/

int verificar_email(const char *email)
{
	size_t count = 0;
	const char *c;
	static char *rfc822_specials = "()<>@,;:\\\"[]";
	
	for (c = email;  *c;  c++) {
		//if (email[i] == '@')
			//break;
		printf("%c", *c);
	}
	
	return count;
}
