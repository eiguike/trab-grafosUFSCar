// Segundo trabalho de Teoria dos Grafos
// Henrique Teruo Eihara RA: 490016

#include <stdio.h>
#include <stdlib.h>

// estrutura de dados de lista ligada
typedef struct lista{
  struct lista * prox;
  int rotulo;
}Lista;

// vivendo perigosamente
int * vertices = NULL;
int * pred = NULL;
int * dist = NULL;
Lista * listaAdjacencia = NULL;
Lista * fila = NULL;

//typedef struct fila{
  //int * vetor;
  //int comeco;
  //int fim;
//}Fila;

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

// funções para fila
int entraFila(int n){

  // quando a fila esta vazia, ja é criado um
  // elemento e então retornado
  if(fila == NULL){
    fila = malloc(sizeof(Lista)*1);
    fila->rotulo = n;
    fila->prox = NULL;

    return 1;
  }

  // caso a fila não esteja vazia, é inserido
  // por último o elemento
  Lista * aux = fila;

  while(aux->prox != NULL){
    aux = aux->prox;
  }
  aux->prox = malloc(sizeof(Lista)*1);
  aux->prox->rotulo = n;
  aux->prox->prox = NULL;

  return 2;
}

int removeFila(){
  if(fila == NULL)
    return -1;

  Lista * aux = fila;
  int aux2;
  fila = fila->prox;
  aux2 = aux->rotulo;
  free(aux);

  return aux2;
}

int filaVazia(){
  if(fila == NULL)
    return 1;
  else
    return 0;
}

// Função que inicializa os vetores
// para a busca em largura
void inicializaVariaveis(int n){
  int i;

  dist = (int*)malloc(sizeof(int)*n);
  pred = (int*)malloc(sizeof(int)*n);
  vertices = (int*) malloc(sizeof(int)*n);

  for(i=0;i<n;i++){
    dist[i] = -1;
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
  aux->prox->prox = aux2;

  aux = &listaAdjacencia[rotulo2];
  aux2 = aux->prox;

  aux->prox = malloc(sizeof(Lista));
  aux->prox->rotulo = rotulo1;
  aux->prox->prox = aux2;
}

void inserirLista2(Lista * n, int rotulo){
  if(n->prox != NULL && (n->prox->rotulo > rotulo)){
    Lista * elemento = malloc(sizeof(Lista));
    elemento->rotulo = rotulo;
    elemento->prox = n->prox;
    n->prox = elemento;
  }else{
    if(n->prox != NULL){
      inserirLista2(n->prox, rotulo);
    }else{
      n->prox = malloc(sizeof(Lista));
      n->prox->prox = NULL;
      n->prox->rotulo = rotulo;
    }
  }

  return;
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

int buscaEmLargura(Lista * atual, int n){
  Lista * aux = NULL;
  int verticeAtual;
  int maior = 0;

  while(!filaVazia()){
    verticeAtual = removeFila();
    aux = atual[verticeAtual].prox;
    while(aux != NULL){
      if(vertices[aux->rotulo] == 0){
        entraFila(aux->rotulo);
        dist[aux->rotulo] = dist[verticeAtual] + 1;

        // condição ternária
        maior = maior < dist[aux->rotulo] ? dist[aux->rotulo] : maior;
        pred[aux->rotulo] = verticeAtual;
        vertices[aux->rotulo] = 1;
      }
      aux = aux->prox;
    }
    // pintando de preto
    vertices[verticeAtual] = 2;
  }
  return maior;
}

int main(){
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
    dist[0] = 0;
    pred[0] = -1;

    // maior tamanho é retornado da função buscaEmLargura
    maiorTamanho = buscaEmLargura(&listaAdjacencia[0], n);

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
    }
    free(dist);
    free(pred);
    free(vertices);
    free(listaAdjacencia);

    // começa tudo denovo
    scanf("%d %d",&n,&m);
    maiorTamanho = 0;
  }

  return 0;
}
