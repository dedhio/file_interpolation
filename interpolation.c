#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

typedef struct lista{
    float x;
    float y;
    struct lista *prox;
}coordenada;

void insere (float x, float y, coordenada *c){
   coordenada *nova_coordenada;
   nova_coordenada = malloc (sizeof (coordenada));
   nova_coordenada->x = x;
   nova_coordenada->y = y;
   nova_coordenada->prox = c->prox;
   c->prox = nova_coordenada;
}

float calcula_interpolacao(float xp, coordenada *le){
    coordenada *c, *aux;
    float x0,y0,x1,y1,yp;
    for (c = le->prox; c != NULL; c = c->prox){
        if (c->prox != NULL){
            aux = c->prox;
            if (xp == c->x){
                yp = c->y;
                return yp;
            } else if (xp < c->x && xp > aux->x){
                printf ("\nIntervalo considerado\nx0=%.1f y0=%.1f \nx1=%.1f y1=%.1f\n", aux->x, aux->y, c->x, c->y);
                x0 = c->x;
                y0 = c->y;
                x1 = aux->x;
                y1 = aux->y;
                yp = y0 + ((y1-y0)/(x1-x0)) * (xp - x0);
                return yp;
            } else {
                continue;
            }
        }
    }
    return yp;
}

int main()
{
  char nome_arquivo[80];
  int leitura;
  int i = 0;
  float x, y, user_x, user_y;
  float menor_x = FLT_MAX, maior_x = FLT_MIN;
  coordenada *lista_intervalos;

  lista_intervalos = malloc (sizeof (coordenada));
  lista_intervalos->prox = NULL;
    
  printf("Arquivo para processar -> ");
  scanf("%s", nome_arquivo);

  FILE* arquivo = fopen(nome_arquivo, "rt");
  if(arquivo == NULL) {
      fprintf(stderr, "\nERRO - Erro ao abrir o arquivo.\n");
      return 1;
  }

  while(!feof(arquivo)){
    leitura = fscanf(arquivo, "%f %f", &x, &y);
    printf("X=%.1f Y=%.1f\n", x, y);
    insere(x, y, lista_intervalos);
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

  printf("\nCoordenadas encontradas = %d\n", i-1);
  printf("Menor valor de X ==> %.1f\n", menor_x);
  printf("Maior valor de X ==> %.1f\n", maior_x);

  printf("\nDigite um valor de X -> ");
  scanf("%f", &user_x);

  if (user_x < menor_x || user_x > maior_x){
      printf("\nERRO: O valor digitado está fora do intervalo esperado.\n");
      return(0);
  } else {
    user_y = calcula_interpolacao(user_x, lista_intervalos);
  }

  printf("\nPara X=%.1f, Y=%.1f\n", user_x, user_y);

  return(0);
}