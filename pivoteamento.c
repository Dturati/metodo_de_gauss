/*  David Turati
    davidturati@gmail.com
    Metodos computacionais
    Implementação do metodo de solução de equaçoes lineares de Gauss com pivoteamento
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//protótipos de função
void aloca(float ***mt, int m, int n);
void imprime(float **mt, int m, int n);
void preenche(float **mt, int m, int n);
void fatora(float **mt, int m, int n);
void solucao(float **mt, int m, int n);
int inicio();

int main(){
    inicio();
    return 0;
}

//Funções
int inicio(){
  float **mt;  //matriz, ponteiro para ponteiro
  int m,n;
  printf("Digite o numero de linhas:");
  scanf("%d",&m);
  __fpurge(stdin);
  while(m < 0){
      printf("Não existe matriz com tamanho negativo\n");
      printf("Digite o numero de linhas:");
      scanf("%d",&m);
      __fpurge(stdin);
  }

  printf("Digite o numeto de colunas:");
  scanf("%d",&n);
  __fpurge(stdin);
  while(n < 0 ){
      printf("Não existe matriz com tamanho negativo\n");
      printf("Digite o numeto de colunas:");
      scanf("%d",&n);
      __fpurge(stdin);
  }

    if(n ==0 || m== 0){
      printf("Matriz nula\n");
      return 0;
    }
  aloca(&mt,m,n);
  preenche(mt,m,n);
  printf("\nMatriz original");
  imprime(mt,m,n);
  fatora(mt,m,n);
  printf("\nMatriz fatorada");
  imprime(mt,m,n);
  solucao(mt,m,n);
}

void aloca(float ***mt, int m, int n){
  register int i,j;

  *mt = malloc(m * sizeof(double *));
  for (i=0;i<m;i++){
    (*mt)[i]= malloc(n * sizeof(double));
  }


}

void imprime(float **mt, int m, int n){
  register int i,j;
  printf("\n");
  for (i=0;i<m;i++){
    for (j=0;j<n;j++){
      printf("%f ",mt[i][j]);
    }
    printf("\n");
  }
}

void preenche(float **mt, int m, int n){
  register int i,j;
  float aux;
  aux=1.0;
  for (i=0;i<m;i++){
    for (j=0;j<n;j++){
      printf("elemento[%d%d]:",i,j);
      scanf("%f",&mt[i][j]);
    }
  }
}

void fatora(float **mt, int m, int n){
  register int i,j,k,l;
  int v,p;
  float aux,maior;
  float pv;
  aux=0;

  //percore todas as linhas da matriz
  for (i=0; i<m; i++){
    k=i+1;
    v=0; //serve como variável "lógica"
    aux=0;

    //encontra o maior elemento que servirá de pivo
    maior=mt[i][i];
    p=i;
    while(k<m){
      if((fabs(maior)) < (fabs(mt[k][i]))){
          maior=mt[k][i];
          v=1;
          p=k;
        }
        k++;
    }

    //realiza a permutação de linhas se ouver um maior elemento
    if(v==1){
      for(j=0;j<n;j++){
        aux=mt[i][j];
        mt[i][j]=mt[p][j];
        mt[p][j]=aux;
        }
    }//fim da permutação

    //Aplica o método de gauss
      for (j=i+1;j<m;j++){
        if(mt[i][i]!=0){
          pv = mt[j][i]/mt[i][i];
          for (l=0;l<n;l++){
            mt[j][l]=mt[j][l] - pv*mt[i][l];
          }
        }
        }
    }

}

//funão que encontra a soluçoes na matriz já fatorada
void solucao(float **mt, int m, int n){
  /*uma matriz mxn tera m coeficiêntes e n-1 soluções*/
  register int i,j;
  float *sl,*vi,soma;
  m=m-1;      //estou reduzindo m em -1 pois em c o primeiro elemento de um vetor começa em zero e isso iria alocar um vetor maior do deveria
  n=n-1;
  soma = 0;
  printf("\n");

  sl = (float *)calloc(n, sizeof(float));  //aloca vetor das soluções
  vi =(float *)calloc(m, sizeof(float));   //aloca vetor das coeficiêntes


  //armazena em um vetor os coeficiêntes
  for(i=0;i<m+1;i++){
    vi[i]=mt[i][n];
  }

  if(mt[m][m] != 9){
    sl[n] = vi[n]/mt[m][m]; //encontra a primeira solução da matriz, ou seja o ultimo coeficiênte
  }
  
  //for que percorre a matriz de traz para frente, ou seja do ultimo elemento até o primeiro
  for (i=n-1;i>=0;i--){
    soma = 0;
    for(j=i+1;j<=n-1;j++){
      soma = soma + mt[i][j]*sl[j]; //multiplica cada elemento pelo vetor das soluçoes anteriores em sua devida posição
    }
      if(mt[i][i] != 0){
        sl[i]=(vi[i]-soma)/mt[i][i];  //divide a soma pelo elemento so vetor dos coeficiêntes em sua respectiva posição
      }                               //e guade na sua posicão correspondente
  }                                 

  //imprime vetor dos coeficiêntes
  printf("Vetor dos coeficiêntes\n");
  for(i=0;i<m+1;i++){
    printf("%f\n",vi[i]);
  }

  //imprime vetor com as soluções
  printf("\nVetor solução\n");
  for(i=0;i<n;i++){
    printf("%f ",sl[i]);
  }
  printf("\n");
  free(sl);
}
