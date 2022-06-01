#include "getch.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//////////////////////////////////////////////
int i, j, height = 30;
int width = 30, gameover, score;
int x, y, fruitx, fruity, flag, gameover, score;

void setup() {
  gameover = 0;
  x = height / 2;
  y = width / 2;
label1:
  fruitx = rand() % 20;
  if (fruitx == 0) {
    goto label1;
  }
label2:
  fruity = rand() % 20;
  if (fruity == 0) {
    goto label2;
  }
  score = 0;
}

void draw() {
  system("clear");
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
        printf("#");
      } else {
        if (i == x && j == y)
          printf("0");
        else if (i == fruitx && j == fruity)
          printf("*");
        else
          printf(" ");
      }
    }
    printf("\n");
  }

  // Print the score after the
  // game ends
  printf("pontos = %d", score);
  printf("\n");
  printf("press X to quit the game");
}

// Function to take the input
void input() {
  if (kbhit()) {
    switch (getch()) {
    case 'a':
      flag = 1;
      break;
    case 's':
      flag = 2;
      break;
    case 'd':
      flag = 3;
      break;
    case 'w':
      flag = 4;
      break;
    case 'x':
      gameover = 1;
      break;
    }
  }
}

// Function for the logic behind
// each movement
void logic() {
  usleep(100000);
  switch (flag) {
  case 1:
    y--;
    break;
  case 2:
    x++;
    break;
  case 3:
    y++;
    break;
  case 4:
    x--;
    break;
  default:
    break;
  }

  // If the game is over
  if (x < 0 || x > height || y < 0 || y > width)
    gameover = 1;

  // If snake reaches the fruit
  // then update the score
  if (x == fruitx && y == fruity) {
  label3:
    fruitx = rand() % 20;
    if (fruitx == 0)
      goto label3;

  // After eating the above fruit
  // generate new fruit
  label4:
    fruity = rand() % 20;
    if (fruity == 0)
      goto label4;
    score += 10;
  }
}

///////////////////////////////////

// função principal
int main() {
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
  // do {
  //   int m, n;

  //   // Generate boundary
  //   setup();

  //   // Until the game is over

  //   // Function Call
  //   draw();
  //   input();
  //   logic();
  // } while (!gameover);

  int m, n;

  // Generate boundary
  setup();

  // Until the game is over
  while (!gameover) {

    // Function Call
    draw();
    input();
    logic();
  }

  return 0;
}