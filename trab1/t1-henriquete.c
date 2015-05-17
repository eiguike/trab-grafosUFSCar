// Trabalho 1 - Teoria dos Grafos

// Nome: Henrique Teruo Eihara    RA: 490016

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  struct lista * prox;
  int rotulo;
}Lista;

void inserirLista(Lista * n, int rotulo){
  if(n->prox != NULL && (n->prox->rotulo > rotulo)){
    Lista * elemento = malloc(sizeof(Lista));
    elemento->rotulo = rotulo;
    elemento->prox = n->prox;
    n->prox = elemento;
  }else{
    if(n->prox != NULL){
      inserirLista(n->prox, rotulo);
    }else{
      n->prox = malloc(sizeof(Lista));
      n->prox->prox = NULL;
      n->prox->rotulo = rotulo;
    }
  }

  return;
}

Lista * criarLista(int vertices){
  Lista * lista = malloc(sizeof(Lista)*vertices);
  int i;
  for(i=0;i<vertices;i++){
    lista[i].prox = NULL;
    lista[i].rotulo = i;
  }

  return lista;
}

void limparLista(Lista * n){
  if(n == NULL)
    return;

  if(n->prox != NULL){
    limparLista(n->prox);
  }else{
    return;
  }
  free(n);
  return;
}

void printarLista(Lista * n){
  if(n->prox != NULL){
    printf("%d ",n->rotulo);
    printarLista(n->prox);
  }else{
    printf("%d\n",n->rotulo);
    return;
  }

}

int main(){

  Lista * listaAdjacencia = NULL;
  Lista * aux = NULL;
  int ** matriz = NULL;

  int n;
  int i;
  int i2;
  int arestas = 0;

  scanf("%d",&n);

  // loop principal, sairá somente quando é entrado n = 0
  while(n>0){
    // arestas é reinicializado para cada iteração
    arestas = 0;
    matriz = malloc(sizeof(int**)*(n));
    for(i=0;i<n;i++)
      matriz[i] = malloc(sizeof(int*)*n);

    // loops utilizado para preencher
    // a matriz de forma já transposta
    for(i=0;i<n;i++){
      for(i2=0;i2<n;i2++){
        scanf("%d",&matriz[i2][i]);
      }
    }

    // inicializa a lista de adjacência
    listaAdjacencia = criarLista(n);

    // cada arco detectado é inserido
    // na lista de adjacência, e adicionado
    // tambem no acmuluador de arestas
    for(i=0;i<n;i++){
      for(i2=0;i2<n;i2++){
        if(matriz[i][i2] == 1){
          inserirLista(&listaAdjacencia[i],i2);
          arestas++;
        }
      }
    }

    // saída padrão, número de vertíces
    // e número de arestas
    printf("%d %d\n",n,arestas);

    // loop para printar a lista
    // de adjacência
    for(i=0;i<n;i++){
        aux = &listaAdjacencia[i];
        while(aux->prox != NULL){
          aux = aux->prox;
            printf("%d ", aux->rotulo);
        }
        printf("\n");
    }

    // moral e bons constumes do programador
    for(i=0;i<n;i++){
      free(matriz[i]);
      limparLista(listaAdjacencia[i].prox);
    }
    free(matriz);
    scanf("%d",&n);
  }

  return 0;

}
