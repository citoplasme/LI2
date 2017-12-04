#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

/**
@file mec.c
Função main e funções que terminam e inicializam a area grafica.
*/


/**
\brief Função que começa a cgi
*/
void print_header(){
	printf("content-Type: text/html; charset=utf-8\n\n");
	printf("<body>\n");
	printf("<svg width=1400 height=1000>\n"); /*cria uma area grafica*/
}

/**
\brief Função que termina a cgi
*/
void print_footer(){
	printf("</svg>\n");
	printf("</body>\n");
}


/**
\brief Executar o programa
*/
int main(){
	print_header(); /*começa cgi*/
	parser();
	print_footer(); /*termina cgi*/
	return 0;
}
