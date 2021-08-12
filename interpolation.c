#include <stdio.h>
#include <string.h>
#include <float.h>

int main()
{
  char nome_arquivo[80];
  int leitura;
  int i = 0;
  float x, y, user_x;
  float menor_x = FLT_MAX, maior_x = FLT_MIN;

  printf("Arquivo para processar -> ");
  scanf("%s", nome_arquivo);

  FILE* arquivo = fopen(nome_arquivo, "rt");
  if(arquivo == NULL) {
      fprintf(stderr, "\nERRO - Erro ao abrir o arquivo.\n");
      return 1;
  }

  while(!feof(arquivo)){
    leitura = fscanf(arquivo, "%f %f", &x, &y);
    printf("X=%.1f Y=%.1f\n", x,y);
    if (leitura){
      if (x > maior_x){
          maior_x = x;
      }
      if (x < menor_x){
          menor_x = x;
      }
    }
    i++;
  }
  fclose(arquivo);

  printf("Coordenadas encontradas = %d\n", i-1);
  printf("Maior valor de X ==> %.2f\n", maior_x);
  printf("Menor valor de X ==> %.2f\n", menor_x);

  printf("\nDigite um valor de X -> ");
  scanf("%f", &user_x);

  if (user_x < menor_x || user_x > maior_x){
      printf("\nERRO: O valor digitado está fora do intervalo esperado.\n");
      return(0);
  }

  return(0);
}