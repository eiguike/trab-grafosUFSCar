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
int * vertices = NULL;
int * pred = NULL;
int * cor = NULL;
int * tempo = NULL;
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
  vertices = (int*) malloc(sizeof(int)*n);
  tempo = (int*) malloc(sizeof(int)*n);

  for(i=0;i<n;i++){
    cor[i] = -1;
    pred[i] = -1;
    vertices[i] = 0;
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

int buscaEmProfundidade(int n, int * iteracao){
  cor[n] = 1;
  tempo[n] = iteracao;

  Lista * aux = listaAdjacencia[n];
  while(aux->prox != NULL){
    if(cor[aux->rotulo] == 0){
      pred[aux->rotulo] = n;
      buscaEmProfundidade(aux->rotulo)
    }
  }







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
    principaisPesos = malloc(sizeof(int)*n);
    iteracao = 0;

    for(i=0;i<n;i++)
    	scanf("%d",&principaisPesos[i]);

    // define-se uma aresta entre dois vertices
    // e insere na lista de adjacência
    for(i=0;i<m;i++){
      scanf("%d %d",&n1,&m1);
      inserirLista(n1,m1);
    }
    // prepara vetores necessários para busca em largura
    inicializaVariaveis(n);

    // passos iniciais da busca em Largura
    entraFila(0);
    vertices[0] = 1;
    cor[0] = 0;
    pred[0] = -1;

    // maior tamanho é retornado da função buscaEmProfundidade 
    for(i=0;i<n;i++){
      maiorTamanho = buscaEmProfundidade(n, &iteracao);
    }

    // verifica se o grafo é conexo
    // se não for printa infinito
    // caso contrario printa o maior caminho
    for(i=0;i<n;i++){
      if(vertices[i] == 0)
        maiorTamanho = -1;
    }

    if(maiorTamanho == -1)
      printf("infinito\n");
    else
      printf("%d\n",maiorTamanho);

    // desaloca variáveis
    for(i=0;i<n;i++){
      limparLista(listaAdjacencia[i].prox);
iteracao
    free(cor);
    free(pred);
    free(vertices);
    free(listaAdjacencia);
    free(principaisPesos);
    free(tempo);

    // começa tudo denovo
    scanf("%d %d",&n,&m);
    maiorTamanho = 0;
  }

  return 0;
}
