#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "getch.h"

//////////////////////////////////////////////
int i, j, height = 30;
int width = 30, gameover, score;
int x, y, fruitx, fruity, flag, gameover, score;

void draw()
{
    system("clear");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1 || j == 0
                || j == height - 1) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void setup() {
  gameover=0;
  x= height/2;
  y= width/2;
  label1:
    fruitx=rand()%20;
    if (fruitx==0) {
      goto label1;
    }
  label2:
    fruity=rand()%20;
    if (fruity==0) {
      goto label2;
    }
  score=0;
}

///////////////////////////////////


// função principal
int main()
{
	char c;
  int play = 1;

  draw();
  // fruta aparece em lugar aleatorio, dentro do campo
  // // aparecer fruta em lugar vazio
  // // se cobra comer fruta
  // // // fruta some
  // cobra q se mexe
  // // cobra move
  // // // mudar direcao quando a tecla for clicada
  // // // aumentar tamanho e velocidade ao comer fruta
  // // cobra cresce(se comer fruta)
  // // cobra morre com contato alem da fruta
  // check gameover
  // // se gameover acaba o jogo
  // // vai para o menu de recomeco
  // recomecar o jogo caso a pessoa queira
  // // sim ou nao
	do{
        
		c = getch();
		putchar(c); 

    draw();
    setup();
	}while(c != '\n');
  
	return 0;
}