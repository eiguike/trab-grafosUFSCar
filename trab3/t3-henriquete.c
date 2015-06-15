// Terceiro trabalho de Teoria dos Grafos
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>

// estrutura de dados de lista ligada
typedef struct lista{
  struct lista * prox;
  int rotulo;
  int peso;
}Lista;

// vivendo perigosamente
int * cor = NULL;
int * pred = NULL;
int * encontro = NULL;
int * final = NULL;
int tempo = 0;
Lista * listaAdjacencia = NULL;
Lista * fila = NULL;
int * principaisPesos = NULL;

// função que inicializa lista
Lista * criarLista(int vertices){
  Lista * lista = malloc(sizeof(Lista)*vertices);
  int i;

  for(i=0;i<vertices;i++){
    lista[i].prox = NULL;
    lista[i].rotulo = i;
  }

  return lista;
}

// Função que inicializa os vetores
// para a busca em largura
void inicializaVariaveis(int n){
  int i;

  cor = (int*)malloc(sizeof(int)*n);
  pred = (int*)malloc(sizeof(int)*n);
  encontro = (int*) malloc(sizeof(int)*n);
  final = (int*) malloc(sizeof(int)*n);

  tempo = 0;

  for(i=0;i<n;i++){
    cor[i] = 0;
    pred[i] = -1;
    encontro[i] = -1;
    final[i] = -1;
  }
}

// Função que realiza a inserção de elementos
// na lista
void inserirLista(int rotulo1, int rotulo2){
  Lista * aux = &listaAdjacencia[rotulo1];
  Lista * aux2 = aux->prox;

  aux->prox = malloc(sizeof(Lista));
  aux->prox->rotulo = rotulo2;
  aux->prox->peso = principaisPesos[rotulo2];
  aux->prox->prox = aux2;

//  aux = &listaAdjacencia[rotulo2];
//  aux2 = aux->prox;

//  aux->prox = malloc(sizeof(Lista));
//  aux->prox->rotulo = rotulo1;
//  aux->prox->prox = aux2;
}

// função de debug para imprimir
// o que está contido na lista
void printarLista(Lista * n){
  if(n->prox != NULL){
    printf("%d ",n->rotulo);
    printarLista(n->prox);
  }else{
    printf("%d\n",n->rotulo);
    return;
  }
}

// limpa a lista, recebendo o primeiro
// elemento da lista
void limparLista(Lista * n){
  if(n == NULL)
    return;

  if(n->prox != NULL){
    limparLista(n->prox);
  }
  free(n);
  return;
}

int DFS (int vertice){
  cor[vertice] = 1;
  encontro[vertice] = tempo;
  tempo+=1;

  Lista * aux = &listaAdjacencia[vertice];

  while(aux->prox != NULL){
    if(cor[aux->prox->rotulo] == 0){
      pred[vertice] = aux->prox->rotulo;
      DFS(aux->prox->rotulo);
    }
  }

  cor[vertice] = 2;
  final[vertice] = tempo;
  tempo+=1;
}

int main(){
  int iteracao;
  // primeira linha de entrada
  int n,m;
  int i;

  // segunda linhas de entrada
  int n1,m1;

  int maiorTamanho;

  // recebe o númeor de vertices e número de arestas
  scanf("%d %d",&n,&m);

  // loop principal
  while(n!=0 || m!=0){
    // inicializa as listas de adjacências
    // para cada vertice
    listaAdjacencia = criarLista(n);
    //principaisPesos = malloc(sizeof(int)*n);
    iteracao = 0;

    for(i=0;i<n;i++)
    	scanf("%d",listaAdjacencia[i].peso);

    // define-se uma aresta entre dois vertices
    // e insere na lista de adjacência
    for(i=0;i<m;i++){
      scanf("%d %d",&n1,&m1);
      inserirLista(n1,m1);
    }
    // prepara vetores necessários para busca em largura
    inicializaVariaveis(n);

    // passos iniciais da busca em Largura

    // maior tamanho é retornado da função buscaEmProfundidade 
    for(i=0;i<n;i++){
      maiorTamanho = DFS(i);
    }

    printf("cor\n");
    for(i=0;i<n;i++){
      printf("%d %d, ",i, cor[i]);
    }

    printf("pred\n");
    for(i=0;i<n;i++){
      printf("%d %d, ",i, pred[i]);
    }

    printf("encontro\n");
    for(i=0;i<n;i++){
      printf("%d %d, ",i, encontro[i]);
    }

    printf("final\n");
    for(i=0;i<n;i++){
      printf("%d %d, ",i, final[i]);
    }

    // desaloca variáveis
    for(i=0;i<n;i++){
      limparLista(listaAdjacencia[i].prox);
    }
    free(cor);
    free(pred);
    free(listaAdjacencia);
    free(principaisPesos);
    free(encontro);

    // começa tudo denovo
    scanf("%d %d",&n,&m);
    maiorTamanho = 0;
  }

  return 0;
}
