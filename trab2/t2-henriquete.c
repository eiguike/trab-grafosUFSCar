// Segundo trabalho de Teoria dos Grafos
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  struct lista * prox;
  int rotulo;
  int dist;
}Lista;

int * vertices = NULL;
Lista * listaAdjacencia = NULL;

Lista * criarLista(int vertices){
  Lista * lista = malloc(sizeof(Lista)*vertices);
  int i;

  for(i=0;i<vertices;i++){
    lista[i].prox = NULL;
    lista[i].rotulo = i;
    lista[i].dist = 0;
  }

  return lista;
}

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

void printarLista(Lista * n){
  if(n->prox != NULL){
    printf("%d ",n->rotulo);
    printarLista(n->prox);
  }else{
    printf("%d\n",n->rotulo);
    return;
  }
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

int maiorCaminho(Lista * atual, int * loucuras, int dist){
  int distOriginal = dist;
  int auxMaior = 0;
  if(atual == NULL){
    return 0;
  }else{
    printf("passei pelo vertice %d HEUHEUHUE\n",atual->rotulo);
    if(loucuras[atual->rotulo] == 0){
      // quer dizer que não foi passado ainda
      loucuras[atual->rotulo] = 1;
    }else{
      return dist-1;
    }

    while(atual->prox != NULL){
      if(atual->rotulo == 0)
        dist = 0;
      dist = maiorCaminho(&listaAdjacencia[atual->prox->rotulo],loucuras, distOriginal+1);
      if(dist > auxMaior)
        auxMaior = dist;

      printf("auxMaior: %d\n",auxMaior);

      loucuras[atual->rotulo] = 2;
      atual = atual->prox;
    }
  }

  loucuras[atual->rotulo] = 2;

  return auxMaior > dist ? auxMaior : dist;
}

int main(){
  // primeira linha de entrada
  int n,m;
  int i;

  // segunda linhas de entrada
  int n1,m1;

  int maiorTamanho = 0;

  scanf("%d %d",&n,&m);
  vertices = calloc(n,sizeof(int));
  listaAdjacencia = criarLista(n);

  while(n!=0 && m!=0){
    for(i=0;i<m;i++){
      scanf("%d %d",&n1,&m1);
      inserirLista(&listaAdjacencia[n1],m1);
    }

    //função que descobre os roles
    maiorTamanho = maiorCaminho(&listaAdjacencia[0], vertices, 0);

    printf("LISTA de ADJACENCIA:\n");
    for(i=0;i<m;i++)
      printarLista(&listaAdjacencia[i]);

    printf("VETOR LOUCO:\n");
    for(i=0;i<n;i++){
      printf("%d:%d, ",i,vertices[i]);
      if(vertices[i] == 0)
        maiorTamanho = -1;
    }

    if(maiorTamanho == -1)
      printf("infinito\n");
    else
      printf("%d\n",maiorTamanho);


    // limpar memorias alocadas
    for(i=0;i<m;i++){
      limparLista(listaAdjacencia[i].prox);
    }
    free(vertices);
    free(listaAdjacencia);

    // começa tudo denovo
    scanf("%d %d",&n,&m);
    vertices = calloc(m,sizeof(int));
    listaAdjacencia = criarLista(m);
    maiorTamanho = 0;
  }


  return 0;
}
