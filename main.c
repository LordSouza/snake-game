// imports
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
int altura = 30, largura = 30;
/*
declaracao das varias prncipais para funcionamento do jogo
-> fim_de_jogo = checa se o jogo terminou, seja por morte da snake, ou ao clicar
a tecla "x"
-> pontuacao = soma 10 cada vez q a snake encosta na fruta
-> flag = controla a direcao que a cobra se move
*/
int fim_de_jogo, pontuacao, flag;
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
  // coloca o valor do fim_de_jogo = 0, para "false", se fim_de jogo = 1, e
  // igual a "true"
  fim_de_jogo = 0;
  // x recebe o valor inicial para a posicao da snake
  x = largura / 2;
  // y receve o valor inicial para a posicao da snake
  y = altura / 2;
// GOTO da linguagem C, e utilizado para definir o valor de fruitx e fruity para
// definir a posicao da fruta
label1:
  // coloca um valor aleatorio para fruitx dentro do limite do campo(0:30), ou
  // seja, 1:29
  fruitx = rand() % ((28 - 1 + 1) + 1);
  fruity = rand() % ((28 - 1 + 1) + 1);
  // se fruitx == x, recomeca o GOTO label1 e tenta conseguir um valor valido
  // para nao aparecer em cima da snake
  if ((fruitx == x) && (fruity == y)) {
    // caso positivo, recomeca e tenta pegar outros valores
    goto label1;
  }
  // coloca a potuacao como 0 para inicio de um jogo novo
  pontuacao = 0;
}
/*
funcao para desenhar os objetos(snake e fruta) e o campo
type void
*/
void draw() {
  // limpar terminal sempre q a funcao for chamada para printar o jogo
  // atualizado
  system("clear");
  // loop para desenhar
  for (i = 0; i < largura; i++) {
    for (j = 0; j < altura; j++) {
      // checar se e borda e desenhar ! para indicar a beirada
      if (i == 0 || i == altura - 1 || j == 0 || j == largura - 1) {
        printf("!");
      } else {
        // checar se i == x e j == y, se sim, printar "o" que e a snake
        if (i == x && j == y)
          printf("o");
        // checar se i == fruitx e y == fruity, se sim, printar &, que e a fruta
        else if (i == fruitx && j == fruity)
          printf("&");
        // se nao, printar espaco vazio
        else
          printf(" ");
      }
    }
    // pular uma linha quando a funcao terminar
    printf("\n");
  }

  // printar o menu dentro do jogo, indicando a pontuacao e como sair do jogo
  printf("pontos = %d", pontuacao);
  printf("\n");
  printf(
      "para iniciar o jogo clique AWSD para mover a cobra na direcao desejada");
  printf("\n");
  printf("clique X para sair do jogo");
}

// funcao para receber inut sem ter que apertar ENTER
void input() {
  // kbhit e uma funcao importada que recebe valores pressionados no teclado se
  // for verdadeiro, quer dizer que recebeu valor
  if (kbhit()) {
    // utilizado switch para nao ter que utilizar varios operadores logicos
    // repetidos "if", "break" e para sair do local quando terminar sua funcao
    switch (getch()) {
    // caso o valor seja "a"
    case 'a':
      // mudar o valor da flag para 1
      flag = 1;
      break;
    // caso o valor seja "s"
    case 's':
      flag = 2;
      // mudar o valor da flag para 2
      break;
    // caso o valor seja "d"
    case 'd':
      flag = 3;
      // mudar o valor da flag para 3
      break;
    // caso o valor seja "w"
    case 'w':
      flag = 4;
      // mudar o valor da flag para 4
      break;
    // caso o valor seja "x"
    case 'x':
      // mudar o valor do fim_do_jogo para 1, para indicar o termino da rodada
      fim_de_jogo = 1;
      break;
    }
  }
}

/*
logic e a funcao que faz a snake se mover
type void
*/
void logic() {
  /*
  -> usleep e uma funcao semelhante a sleep(), mas como sao funcoes que utilizam
  INT, nao havia como colocar valores quebrados para segundos, essa funcao
  recebe um valor inteiro e o programa pausa pelo tempo recebido (microsegundos)
  */
  usleep(300000);
  // mais um caso de switch para determinacao de lado que a snake vai se mover
  switch (flag) {
  // se flag == 1, diminuir o valor de y por 1
  case 1:
    y--;
    break;
  // se flag == 2, aumentar o valor de x por 1
  case 2:
    x++;
    break;
  // se flag == 3, aumentar o valor de y por 1
  case 3:
    y++;
    break;
  // se flag == 4, diminuir o valor de x por 1
  case 4:
    x--;
    break;
  // caso o valor nao seja definido, nada acontece
  default:
    break;
  }

  // se o jogo terminou, pela snake tocando as bordas
  if (x < 1 || x > largura - 1 || y < 1 || y > altura - 1)
    // colocar fim_de_jogo para 1
    fim_de_jogo = 1;

  /*
  se a cobra tocar na fruta, a fruta e jogada para outro local
  */
  if (x == fruitx && y == fruity) {
  label3:
    fruitx = rand() % 20;
    if (fruitx == 0)
      goto label3;

  label4:
    fruity = rand() % 20;
    if (fruity == 0)
      goto label4;
    // aumento da pontuacao por 10 depois que a cobra encostar na fruta
    pontuacao += 10;
  }
}

///////////////////////////////////

// função principal
int main() {
  // gerar campo e os principais objetos
  setup();

  // enquanto o jogo nao terminar as funcoes continuam a ser chamadas
  while (!fim_de_jogo) {

    input();
    logic();
    draw();
  }

  return 0;
}