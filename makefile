CFLAGS = -Wall -Wextra -pedantic -O2
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
EXEC = mec
# CFLAGS = -Wall -Wextra é a pedir os warnings todos
# -pedantic -O2 é por causa da optimizaçao
# EXEC = nome do prog executavel que vai ser criado

instalar: $(OBJS)
	gcc $(CFLAGS) -o $(EXEC) $(OBJS)
	sudo cp $(EXEC) /usr/lib/cgi-bin/

	sudo cp imagens/link.png /var/www/html/
	sudo cp imagens/monster.png /var/www/html
	sudo cp imagens/porta.png /var/www/html
	sudo cp imagens/brick.jpg /var/www/html
	sudo cp imagens/trans.png /var/www/html
	sudo cp imagens/zelda.jpg /var/www/html
	sudo cp imagens/health.png /var/www/html
	sudo cp imagens/black_heart.png /var/www/html
	sudo cp imagens/over.png /var/www/html
	sudo cp imagens/level.png /var/www/html
	sudo cp imagens/restart.png /var/www/html
	sudo cp imagens/score.png /var/www/html
	sudo cp imagens/start.png /var/www/html
	sudo cp imagens/high.png /var/www/html
	sudo cp imagens/gold.png /var/www/html
	sudo cp imagens/silver.png /var/www/html
	sudo cp imagens/bronze.png /var/www/html
	sudo cp imagens/first.png /var/www/html
	sudo cp imagens/snd.png /var/www/html
	sudo cp imagens/trd.png /var/www/html

	sudo touch /var/www/html/scores.txt
	sudo chmod 666 /var/www/html/scores.txt
	sudo mkdir -p /var/www/html/saves
	sudo chmod -R ugo+rw /var/www/html/saves

# quando fazemos make ele executa estas instruçoes

doc:
	doxygen -g
	doxygen

limpar:
	rm -f $(EXEC) *.o
# quando fazemos make limpar ele executa isto
# remove o prog e todos os .o
