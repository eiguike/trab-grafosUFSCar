#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  struct lista * prox;
}Lista;

int main(){
  int n,m;
  int i;

  int * vertices = NULL;
  Lista * listaAdjacencia = NULL;

  scanf("%d %d",&n,&m);
  vertices = calloc(m,sizeof(int));

  while(n==0 && m==0){
    for(i=0;i<m;i++){
      
    }

    scanf("%d %d",&n,&m);
  }


  return 0;
}
