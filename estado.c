#include <stdio.h>
#include "estado.h"


/**
@file estado.c
Funções que passam o estado para uma string e vice versa
*/

/** tamanho max do nosso buffer */
#define MAX_BUFFER		10240

char *estado2str(ESTADO e) {
	static char buffer[MAX_BUFFER];
	unsigned char *p = (unsigned char *) &e;
	size_t i;

	buffer[0] = 0;

	for(i = 0; i < sizeof(ESTADO); i++)
		sprintf(buffer, "%s%02x", buffer, p[i]);
	
	return buffer;
}

ESTADO str2estado(char *argumentos) {
	ESTADO e;
	unsigned char *p = (unsigned char *) &e;
	size_t i;

	for(i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
		unsigned int d;
		sscanf(argumentos, "%2x", &d);
		p[i] = (unsigned char) d;
	}
	
	return e;
}