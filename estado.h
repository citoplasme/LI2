#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100

/**
\brief Estrutura que armazena uma posição do objectivo e dos obstáculos, isto é, nao possuem vida
*/
typedef struct posicao {
	/** coordenada x da posiçao */
	char x;
	/** coordenada x da posiçao */
	char y;
} POSICAO;


/**
\brief Estrutura que armazena uma posição do jogador e dos inimigos, isto é, possuem vida
*/
typedef struct posicao2 {
	/** coordenada x da posiçao */
	char x;
	/** coordenada y da posiçao */
	char y;
	/** vida que o jogador/inimigo tem*/
	char vida;
} POSICAO2;


/**
\brief Estrutura que armazena os tres melhores scores
*/
typedef struct {
	/** array com os 3 maiores scores efetuados */
    int score[3];
} SCORES;


/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	/** o nivel em que nos encontramos */
	char nivel;
	/** A posição do jogador */
	POSICAO2 jog;
	/** A posição da porta de saída objectivo */
	POSICAO goal;
	/** O nº de inimigos */
	char num_inimigos;
	/** O nº de obstáculos */
	char num_obstaculos;
	/** Array com a posição dos inimigos */
	POSICAO2 inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** score do jogador */
	int score;
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/

char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif