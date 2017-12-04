
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "estado.h"
#include <time.h>

/**
@file parser.c
Todas as funções necessárias para o nosso jogo: impressões, movimentos, inicializações, etc
*/


/**
\brief imprimir a vida - coraçoes pretos e vermelhos
@param e - recebe o estado do jogo
*/
void print_health (ESTADO e) {

	int x = 0, y = 505, z=e.jog.vida, a=5-e.jog.vida;

	while (z > 0) {
		printf ("<image x=%d y=%d width=50 height=50 xlink:href=\"%s\"/>\n",x,y, HEALTH);
		x += 50; /*espaço entre coraçoes*/
		z--;
	}

	while (a > 0) {
		printf ("<image x=%d y=%d width=50 height=50 xlink:href=\"%s\"/>\n",x,y, DEATH);
		x += 50;
		a--;
	}
}

/**
\brief função que imprime a informação actual do jogo, i.e., o score e o nivel;
@param e - estado actual do jogo
*/
void print_info (ESTADO e) {
    printf ("<image x=555 y=-65 width=150 height=250 xlink:href=\"%s\"/>\n",LEVEL);
    printf("<TEXT X=624 Y=105> %d </TEXT></A>\n",e.nivel + 1);
    printf ("<image x=555 y=55 width=150 height=250 xlink:href=\"%s\"/>\n",SCORE);
    printf("<TEXT X=624 Y=220> %d </TEXT></A>\n",e.score);
}


/**
\brief Função que verifica se a posição x y (valores dados como parametro) é válida.
@param e - estado do jogo onde queremos ver se a pos é válida;
@param x - coordenada x da posição que queremos verificar;
@param y - coordenada y da posição que queremos verificar;
@return int - A funçao retorna 1 caso a posição seja válida, 0 caso contrário;
*/
int pos_valida (ESTADO e, int x, int y){
	int i, j;
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE) return 0; /*ver se a pos está dentro do mapa*/
	if (x>=0 && y>=0 && x<SIZE && y<SIZE){
		/* Nao deixa colocar nada onde está a porta e a pos é invalida*/
		if(x == e.goal.x && y == e.goal.y) return 0;
		/* Se já lá estiver um inimigo a pos é invalida*/
		for (i = 0; i < e.num_inimigos; i++)
			if(x == e.inimigo[i].x && y == e.inimigo[i].y && e.inimigo[i].vida > 0) return 0;
		/* Se já lá estiver um obstaculo a pos é invalida: */
		for (j = 0; j < e.num_obstaculos; j++)
			if(x == e.obstaculo[j].x && y == e.obstaculo[j].y) return 0;
	}
	return 1;
}


/**
\brief Função que inicializa um estado
@param nivel - nivel do jogo onde estamos, normalmente inicializada a 0 e incrementada cada vez que passamos de nivel;
@param vida - quantidade de vidas do nosso jogador (corações vermelhos) com um máximo de 5;
@param score - score que o nosso jogador efectuou ao momento, inicializado a 0 e incrementado sempre que matamos um inimigo ou passamos de nivel;
@return ESTADO - A função retorna um estado inicializado
*/
ESTADO inicializar(int nivel, int vida, int score) {
	int i = 0, j = 0;
	int x, y;
	ESTADO e = {0};
	e.jog.vida = vida;
	e.nivel = nivel;
	e.score = score;
	e.num_inimigos = 10+nivel;
	while (i < e.num_inimigos){ /*ciclo para fazermos inimigos*/
		x=rand() % SIZE; /* coord x random entre 0 e 9*/
		y=rand() % SIZE; /* coord y random entre 0 e 9*/
		if (pos_valida(e,x,y)){ /*se a pos for valida coloca lá um inimigo*/
			e.inimigo[i].vida = 1;
			e.inimigo[i].x = x;
			e.inimigo[i].y = y;
			i++;
		}
	}
	e.num_obstaculos = 20+nivel;
	while(j < e.num_obstaculos){ /*ciclo para fazermos obstaculos*/
		x = rand() % SIZE; /*coord x entre 0 e 9*/
		y = rand() % SIZE; /*coord y*/
		if (pos_valida(e,x,y)){
			e.obstaculo[j].x = x; /*se a pos for valida, i.e., nao tiver la nada mete-se um obstaculo*/
			e.obstaculo[j].y = y;
			j++;
		}
	}
	x = rand() % SIZE; /*coord x entre 0 e 9*/
	y = rand() % SIZE; /*coord y*/
	while(!pos_valida(e,x,y)){
		x = rand() % SIZE; /*coord x entre 0 e 9*/
		y = rand() % SIZE;
		}
	e.goal.x = x;
	e.goal.y = y;
	while(!pos_valida(e,x,y)){
		x = rand() % SIZE; /*coord x entre 0 e 9*/
		y = rand() % SIZE;
		}
	e.jog.x = x;
	e.jog.y = y;
	return e;
}


/**
\brief Função que imprime um quadrado do tabuleiro;
@param x - coordenada x da posição onde queremos imprimir o quadrado
@param y - coord y da pos onde queremos imprimir o quadrado
@param tam - tamanho desejado do quadrado
*/
void print_square(int x, int y, int tam){
	char *color[] = {"#566600", "#777700"};
	int idx = (x + y) % 2;

	printf("<rect x=%d y=%d width=%d height=%d fill=\"%s\"/>\n", tam *x, tam *y, tam, tam, color[idx] );
}

/**
\brief Função que imprime o tabuleiro usando a função print_square para cada posição
*/
void print_board () {
	int x, y;
	for (y = 0; y < SIZE ; y++){ /*imprimir coluna*/
		for (x = 0; x < SIZE; x++) /* imprime a linha*/
			print_square(x,y,TAM);
	}
}


/**
\brief Função que imprime uma imagem
@param x - coordenada x da posição onde queremos imprimir a imagem
@param y - coordenada y da posição onde queremos imprimir a imagem
@param tam - tamanho da imagem que queremos imprimir
@param name - nome da imagem que queremos imprimir, vai buscar ao parser.h
*/
void print_image(int x, int y, int tam, char *name ){
	printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n", x*tam, y*tam, tam, tam, name);
}


/**
\brief Aqui verificamos se o inimigo i do ESTADO tem o jogador no seu campo de visão (2 casas)
@param e - Estado do jogo onde vamos verificar;
@param i - numero do inimigo que vamos verificar (inimigo[i]);
@return int - caso o jogador esteja no campo de visão do inimigo retorna 1, caso contrário retorna 0;
*/
int campovisao_inimigo(ESTADO e, int i){
	int z, h;
	z = (e.jog.x - e.inimigo[i].x); 
	h = (e.jog.y - e.inimigo[i].y);
	if (abs(z) < 3 && abs(h) < 3) return 1;
	return 0;
}


/**
\brief Função que move os inimigos do estado. Caso o jogador esteja no campo de visão do inimigo, este inimigo vai tentar matar o jogador
movendo-se para cima dele. Caso contrário o inimigo vai mover-se aleatoriamente
@param e - Estado onde vamos mover os inimigos
@return ESTADO - retorna o estado e, dado como parametro, depois dos inimigos se terem movido
*/
ESTADO move_enemies2(ESTADO e){
	int i = 0, m, n;
	while (i < e.num_inimigos && e.jog.vida > 0){
		if(e.inimigo[i].vida <= 0) i++; /* se o inimigo n tiver vida n é preciso fazer nada */
		else{
			if(campovisao_inimigo(e,i)){
            	if ((e.jog.x > e.inimigo[i].x && e.jog.y > e.inimigo[i].y) && (pos_valida(e, e.inimigo[i].x+1, e.inimigo[i].y+1))){
                		e.inimigo[i].x+=1;
                		e.inimigo[i].y+=1;
            			if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
						e.inimigo[i].x-=1;
						e.inimigo[i].y-=1;
						--e.jog.vida;
						}
            	}
            	else{ if ((e.jog.x < e.inimigo[i].x && e.jog.y < e.inimigo[i].y) && (pos_valida(e, e.inimigo[i].x-1, e.inimigo[i].y-1))){
              		  	e.inimigo[i].x-=1;
               		  	e.inimigo[i].y-=1;
            		  	if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
						e.inimigo[i].x+=1;
						e.inimigo[i].y+=1;
						--e.jog.vida;
						}
					  }
					  else{
					  	if ((e.jog.x < e.inimigo[i].x && e.jog.y > e.inimigo[i].y) && (pos_valida(e, e.inimigo[i].x-1, e.inimigo[i].y+1))){
              		  		e.inimigo[i].x-=1;
               		  		e.inimigo[i].y+=1;
            		  		if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
								e.inimigo[i].x+=1;
								e.inimigo[i].y-=1;
								--e.jog.vida;
							}
					  	}
					  	else{
					  		if ((e.jog.x > e.inimigo[i].x && e.jog.y < e.inimigo[i].y) && (pos_valida(e, e.inimigo[i].x+1, e.inimigo[i].y-1))){
              		  			e.inimigo[i].x+=1;
               		  			e.inimigo[i].y-=1;
            		  			if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
									e.inimigo[i].x-=1;
									e.inimigo[i].y+=1;
									--e.jog.vida;
								}
					  		}
		        			else{ if ((e.jog.x > e.inimigo[i].x) && pos_valida(e, e.inimigo[i].x+1, e.inimigo[i].y)){
		        					e.inimigo[i].x+=1;
		        					if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
										e.inimigo[i].x-=1;
										--e.jog.vida;
									}
		        		  		  }
		        				  else{
		        				  	if ((e.jog.x < e.inimigo[i].x) && pos_valida(e, e.inimigo[i].x-1, e.inimigo[i].y)){
		        						e.inimigo[i].x-=1;
		        						if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
											e.inimigo[i].x+=1;
											--e.jog.vida;
										}
		        			  		}
		        					else{ if ((e.jog.y > e.inimigo[i].y) && pos_valida(e, e.inimigo[i].x, e.inimigo[i].y+1)){
		        							e.inimigo[i].y+=1;
		        							if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
												e.inimigo[i].y-=1;
												--e.jog.vida;
											}
		        					      }
        							      else{ if ((e.jog.y < e.inimigo[i].y) && pos_valida(e, e.inimigo[i].x, e.inimigo[i].y-1)){
        											e.inimigo[i].y-=1;
        											if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
														e.inimigo[i].y+=1;
														--e.jog.vida;
													}
        							  			}
        									}
        								}
        							}
        			    		}
        					}
        				}
        			}
			}
			/* se tem vida mas o jog nao está no seu campo de visao: */
			else{
				m = rand() % 3 +(-1); /* numero random: -1, 0 ou 1 */
				n = rand() % 3 +(-1);
				if ((m == 0 && n == 0) || (pos_valida(e,e.inimigo[i].x+m,e.inimigo[i].y+n))){ 
					e.inimigo[i].x += m;
					e.inimigo[i].y += n;
				}
				if(e.inimigo[i].x == e.jog.x && e.inimigo[i].y == e.jog.y){
					e.inimigo[i].x -= m;
					e.inimigo[i].y -= n;
					--e.jog.vida;
				}
			}
			i++;
		}
	}
	return e;
}


/**
\brief Função que mata um inimigo, isto é, quando clicamos num inimigo: colocamos a vida a 0 e o jogador volta para a posição de onde atacou
@param x - coordenada x do inimigo que clicamos
@param y - coordenada y do inimigo que clicamos
@param e - Estado do jogo onde estamos a fazer a acção
@return ESTADO - retorna o estado depois de termos morto o inimigo
*/
ESTADO matar_inimigo(int x, int y, ESTADO e){
	int i = 0;
	while(i < e.num_inimigos){
		if(e.jog.x == e.inimigo[i].x && e.jog.y == e.inimigo[i].y && e.inimigo[i].vida > 0){
			e.inimigo[i].vida = 0;
			e.score = e.score + 5;
			e.jog.x = e.jog.x - x;
			e.jog.y = e.jog.y - y;
		}
		i++;
	}
	return e;
}


/**
\brief Função que imprime o link numa posição à volta do jogador para nos movermos
@param e - estado onde estamos a imprimir
@param dx - inteiro que vamos somar à posiçao x do jogador resultando na coordenada x onde vamos imprimir o link clicável
@param dy - inteiro que vamos somar à posiçao y do jogador resultando na coordenada y onde vamos imprimir o link
@param nomef - nome do nosso estado
@param acao - acao que estamos a efectuar
*/
void print_move(ESTADO e, int dx, int dy, char *nomef, int acao){
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;

	if(x < 0 || y < 0 || x >= SIZE || y >= SIZE) return; /*verifica se a pos para onde queremos ir é valida*/
	
	printf("<a xlink:href=\"http://127.0.01/cgi-bin/mec?%s,%d\">\n", nomef,acao); /*imprimir o link*/
	print_image(x,y,TAM, TRANS); /*meter o link num quadrado transparente*/
	printf("</a>\n");
}


/**
\brief Função que verifica se a posiçao do jogador coincide com a posiçao da porta e que passa/cria ao nivel seguinte caso se confirme
@param e - estado do jogo onde vamos verificar se passamos de nivel
@return ESTADO - retorna o estado com o nivel novo caso o jogador estivesse na porta
*/
ESTADO passar_de_nivel (ESTADO e){
	if(e.jog.x == e.goal.x && e.jog.y == e.goal.y && e.jog.vida < 5) e = inicializar(++e.nivel, ++e.jog.vida, e.score + 10);
	if(e.jog.x == e.goal.x && e.jog.y == e.goal.y && e.jog.vida == 5) e = inicializar(++e.nivel, 5, e.score + 10);
	return e;
}


/**
\brief Função que imprime a imagem do jogador no tabuleiro
@param e - estado onde vamos imprimir o jogador
@param nomef - nome do nosso estado/jogo, necessario para imprimir/actualizar o link quando nos movemos
*/
void print_player (ESTADO e, char nomef[]){
	print_image(e.jog.x, e.jog.y, TAM,PLAYER);
	print_move(e,-1,0,nomef,2);
	print_move(e,1,0,nomef,3);
	print_move(e,0,-1,nomef,4);
	print_move(e,0,1,nomef,5);
	/*andar nas diagonais:*/
	print_move(e,-1,-1,nomef,6);
	print_move(e,-1,1,nomef,7);
	print_move(e,1,-1,nomef,8);
	print_move(e,1,1,nomef,9);
}


/**
\brief Função que imprime a imagem de todos os obstáculos
@param e -  estado de onde retiramos a informaçao dos obstaculos para imprimir as imagens;
*/
void print_walls(ESTADO e){
	int i;
	for (i = 0; i < e.num_obstaculos; i++){
		print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM, WALL);
	}
}


/**
\brief Função que imprime as imagens dos inimigos
@param e - estado de onde retiramos a informaçao dos inimigos para imprimir as imagens;
*/
void print_enemies(ESTADO e){
	int i;
	for (i = 0; i < e.num_inimigos; i++){
		if(e.inimigo[i].vida > 0) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);
	}
}


/**
\brief Função que imprime a imagem do objectivo
@param e - estado de onde retiramos a informaçao da saída para imprimir a imagem;
*/
void print_goal(ESTADO e){
	print_image(e.goal.x, e.goal.y, TAM, GOAL);
}


/**
\brief Função que imprime a imagem de fundo
*/
void print_fundo(){
	printf("<image x=0 y=-280 height=1200 width=1200 xlink:href=\"%s\"/>\n", BACKGROUND);
}


/**
\brief Quando a vida do nosso jogador é 0, invocamos esta funçao que imprime a mensagem de gameover
*/
void print_gameover(){
	printf("<image x=0 y=0 height=800 width=800 xlink:href=\"%s\"/>\n", TRANS);
	printf("<image x=0 y=0 height=510 width=500 xlink:href=\"%s\"/>\n", END);
}


/**
\brief Função que imprime o botão de restart com link, é invocada quando a vida do jogador é 0.
@param nomef - nome do jogo/estado, útil para actualizarmos o jogo quando se clica no botao;
*/
void print_restart(char nomef[]){
	printf("<A xlink:href =\"http://127.0.0.1/cgi-bin/mec?%s,%d\"><image x=150 y=330 width=200 height=250 xlink:href=\"%s\"/>\n", nomef,0, RESTART);
	/* caso se clique no botao ele toma a acao 0 que é começar um jogo novo */
}


/**
\brief Função que lê o estado que está no ficheiro nomef
@param e - estado e para onde vamos
@param nomef - nome do ficheiro
@return ESTADO e - retorna o e com o estado que estava no ficheiro, ou um novo caso nao se encontrasse lá nada/fich nao existisse
*/
ESTADO ler_ficheiro(ESTADO e, char *nomef){
	FILE *fp;
	char path[1024] = "/var/www/html/saves/"; /* Caminho para o nosso ficheiro */
	strcat(path, nomef);
	fp = fopen(path, "rb");
	if(fp){
		if(!(fread (&e, sizeof(ESTADO),1,fp))) /* se n conseguir ler nada do ficheiro*/
			e = inicializar(0,4,0);			   /* cria-se um novo estado */
		fclose(fp);
	}
	else{e = inicializar(0,4,0);} /*se n houver ficheiro cria-se novo estado*/
	return e;
}

/* grava o estado e no ficheiro nomef*/

/**
\brief Função que grava o nosso estado num ficheiro
@param e - estado que vamos guardar no ficheiro
@param nomef - nome do ficheiro/estado que vamos gravar
*/
void grava_ficheiro(ESTADO e, char *nomef){
	FILE *fp;
	char path[1024] = "/var/www/html/saves/"; /* caminho para a pasta de saves*/
	strcat(path, nomef); /* "colamos" o caminho ao nome do ficheiro */
	fp = fopen(path, "wb"); /* wb para escrever em binario */
	fwrite(&e, sizeof(ESTADO), 1,fp);
	fclose(fp);
}


/**
\brief Função que processa as acçoes
@param e - estado onde estamos a actuar
@param nomef - nome do f
@param acao - numero da acao que queremos efectuar no estado e
@return ESTADO - retorna o estado depois de termos efectuado a acao
*/
ESTADO processa_acao(ESTADO e, char* nomef, int acao){
	if (acao == 0){
		e = inicializar(0,4,0);
	}
	if (acao == 1) e = ler_ficheiro(e, nomef);
	if (acao == 2){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x - 1;
		e = matar_inimigo(-1,0,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
		/* resto das acçoes que fazemos qd nos movemos */
	}
	if (acao == 3){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x + 1;
		e = matar_inimigo(1,0,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 4){
		e = ler_ficheiro(e,nomef);
		e.jog.y = e.jog.y - 1;
		e = matar_inimigo(0,-1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 5){
		e = ler_ficheiro(e, nomef);
		e.jog.y = e.jog.y + 1;
		e = matar_inimigo(0,1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 6){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x -1; e.jog.y = e.jog.y - 1;
		e = matar_inimigo(-1,-1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 7){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x -1; e.jog.y = e.jog.y + 1;
		e = matar_inimigo(-1,1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 8){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x + 1; e.jog.y = e.jog.y - 1;
		e = matar_inimigo(1,-1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	if (acao == 9){
		e = ler_ficheiro(e, nomef);
		e.jog.x = e.jog.x + 1; e.jog.y = e.jog.y + 1;
		e = matar_inimigo(1,1,e);
		e = move_enemies2(e);
		e = passar_de_nivel(e);
	}
	return e;
}


/**
\brief Funçao que guarda os melhores scores
@param top - estrutura onde estão guardados os 3 melhores scores;
*/
void guardar_highscore (SCORES top) {
	int i;    	
	FILE *fd;

	fd = fopen ("/var/www/html/scores.txt","wb");
   
	if (fd == NULL) {
	perror ("Not possible"), exit (1);
    }
    for(i = 0; i < 3; i++ ){
       		 fprintf (fd, "%d\n", top.score[i]);
    }

    fclose(fd);
}



/**
\brief Funçao que lê os highscores do ficheiro scores.txt
@return SCORES - retorna a estrutura com os scores do ficheiro
*/
SCORES ler_highscore() {
	int i; 
	char line[1024];
    SCORES top = {{0}};
	FILE *fd;
	fd = fopen("/var/www/html/scores.txt", "rb");
    
	if (fd == NULL) {
	perror ("Not possible"), exit (1);
    }

    for(i = 0; i < 3; i++ ){
        if(fgets(line, sizeof(line), fd) == NULL) {
            perror ("No scores left");
            break;
        }
        sscanf(line, "%d", &top.score[i]);
    }
    fclose(fd);
    return top;
}


/**
\brief Função que verifica se o nosso score está apto para ir para o top 3
@param e - estado do qual vamos ver o score
@param top - 3 melhores scores que fomos buscar ao scores.txt
@return top - retorna o top 3, com as alterações necessárias
*/
SCORES alteraSCORES (ESTADO e, SCORES top) {
	if (e.score  >= top.score[0]) {top.score[2] = top.score[1],top.score[1] = top.score[0], top.score[0] = e.score; return top; }
	if (e.score  >= top.score[1]) {top.score[2] = top.score[1],top.score[1] = e.score; return top; }
	if (e.score  >= top.score[2]) {top.score[2] = e.score; return top; }

	return top;	
}


/**
\brief Função que imprime os melhores scores ao lado do nosso jogo
@param top - melhores scores que vamos imprimir
*/
void print_highscores (SCORES top) {
	int i, x = 1016, y = 105;

	/* impressão de botões/imagens acima dos scores */
    printf ("<image x=955 y=-65 width=150 height=250 xlink:href=\"%s\"/>\n",HIGH);

	printf ("<image x=955 y=85 width=150 height=35 xlink:href=\"%s\"/>\n",FIRST);
	printf ("<image x=955 y=125 width=150 height=35 xlink:href=\"%s\"/>\n",SND);
	printf ("<image x=955 y=165 width=150 height=35 xlink:href=\"%s\"/>\n",TRD);

	printf ("<image x=985 y=87 width=30 height=30 xlink:href=\"%s\"/>\n",GOLD);	    
	printf ("<image x=985 y=127 width=30 height=30 xlink:href=\"%s\"/>\n",SILVER);
	printf ("<image x=985 y=167 width=30 height=30 xlink:href=\"%s\"/>\n",BRONZE);

	for (i = 0; i <= 2; i++) {
 		printf ("<TEXT X=%d Y=%d> %d </TEXT></A>\n",x, y, top.score[i]);
		y += 40;
	}
}


/**
\brief Função principal que "junta" todas as funções
*/
void parser () {
	int num, acao;
	char nomef[64];
	ESTADO e = {0};
	char *args = getenv("QUERY_STRING");
	SCORES top;
	top = ler_highscore();

	srand(time(NULL)); /*sem isto a funçao rand() nao funciona*/

	if (strlen(args) == 0){
		strcpy(nomef , "estadomec");
		acao = 0;
	}
	
	else{
		num = sscanf(args,"%[^,],%d", nomef, &acao);
		if (num == 1) acao = 1;
		}

	e = processa_acao(e, nomef, acao);

	print_fundo();
	print_board();
	print_goal(e);
	print_enemies(e);
	print_player(e, nomef);
	print_walls(e);
	print_health(e);
	print_info(e);
	print_highscores(top);

	if (e.jog.vida <= 0) {
	top = alteraSCORES(e,top);
	guardar_highscore(top);
	print_gameover();
	print_restart(nomef);
	}

	grava_ficheiro(e, nomef);
}
