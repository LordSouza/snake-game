#include "getch.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//////////////////////////////////////////////
// declaracao das variaveis dos loops
int i, j;
/*
declaracao das variaveis que desenham o mapa
-> altura = tamanho da altura do campo
-> largura = tamanho da largura do campo
OBS: tem q ser do mesmo tamanho
*/
int altura = 30, largura = 30 ;
/*
declaracao das varias prncipais para funcionamento do jogo
-> fim_de_jogo = checa se o jogo terminou, seja por morte da snake, ou ao clicar a tecla "x"
-> pontuacao = soma 10 cada vez q a snake encosta na fruta
-> flag = controla a direcao que a cobra se move
*/
int fim_de_jogo, pontuacao,flag;
/*
declaracao de variaveis para posicao dos objetos
-> x = valor do eixo x da snake inicial
-> y = valor do eixo y da snake inicial
-> fruitx = valor do eixo x da fruta inicial
-> fruity = valor do eixo y da fruta inicial
*/
int x, y, fruitx, fruity;
/*
funcao do type void(nao retorna valor)
coloca valor inicial para a snake e a fruta ao comecar o jogo
*/
void setup() {
  // coloca o valor do fim_de_jogo = 0, para "false", se fim_de jogo = 1, e igual a "true"
  fim_de_jogo = 0;
  // x recebe o valor inicial para a posicao da snake
  x = largura / 2;
  // y receve o valor inicial para a posicao da snake
  y = altura / 2;
// GOTO da linguagem C, e utilizado para definir o valor de fruitx e fruity para definir a posicao da fruta
label1:
  // coloca um valor aleatorio para fruitx
  fruitx = rand() % 20;
  // se fruitx == 0, recomeca o GOTO label1 e tenta conseguir um valor valido
  if (fruitx == 0) {
    goto label1;
  }
// definicao da posicao fruity
label2:
  // coloca um valor aleatorio da fruity
  fruity = rand() % 20;
  // se fruity == 0, recomeca o GOTO e tenta conseguir um valor valido
  if (fruity == 0) {
    goto label2;
  }
  // coloca a potuacao como 0 para inicio de um jogo novo
  pontuacao = 0;
}

void draw() {
  system("clear");
  for (i = 0; i < largura; i++) {
    for (j = 0; j < altura; j++) {
      if (i == 0 || i == altura - 1 || j == 0 || j == largura - 1) {
        printf("!");
      } else {
        if (i == x && j == y)
          printf("o");
        else if (i == fruitx && j == fruity)
          printf("&");
        else
          printf(" ");
      }
    }
    printf("\n");
  }

  // Print the pontuacao after the
  // game ends
  printf("pontos = %d", pontuacao);
  printf("\n");
  printf("clique X para sair do jogo");
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
      fim_de_jogo = 1;
      break;
    }
  }
}

// Function for the logic behind
// each movement
void logic() {
  usleep(300000);
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
  if (x < 0 || x > largura || y < 0 || y > altura)
    fim_de_jogo = 1;

  // If snake reaches the fruit
  // then update the pontuacao
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
    pontuacao += 10;
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
  // check fim_de_jogo
  // // se fim_de_jogo acaba o jogo
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
  // } while (!fim_de_jogo);

  int m, n;

  // Generate boundary
  setup();

  // Until the game is over
  while (!fim_de_jogo) {

    // Function Call
    input();
    logic();
    draw();
  }

  return 0;
}