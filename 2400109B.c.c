#include <stdio.h>
#include <stdlib.h>

int inicio(int K, int* seq){
    if (K>=2 && K<=100){
        if(K%2!=0){
            K=K-1;
        }
        seq[0]=K/2;
        seq[1]=K/2;
        return 1;
    }else{
        return 0;
    }
}
int resultado(int K,int *tamanho, int seq[]){
    int i;
    int produto=1;
    int soma=0;
    int somadiferencas=0;
    int h;
    i=0;
    while ( seq[i]!=0){
        i++;
    }
    int m=0;
    for (h=0;h<i;h++){
        if (seq[h]!=0){
            produto*=seq[h];
            soma+=seq[h];
            while (m < *tamanho-1) {
                int j = m + 1; 
                while (j < *tamanho-1) {
                    somadiferencas += abs(seq[m] - seq[j]);
                    j++;
                }
                m++;
            }
        }
    }
    if (produto>=K  && soma<=K ){
        if (somadiferencas==K){
            return 2;
        }
        return 1;
    }
    return 0;
}

int main () {
    int seq[100];
    int K,i;
    printf("Indique K: ");
    scanf(" %d", &K);
     if (inicio(K, seq)==1){
    }else{
         printf("\nK tem de ser entre 2 e 100.");
         return -1;
    }
    printf("Indique uma sequencia de numeros inteiros positivos, terminando com 0: ");
    int j=1;
    while (j!=0) {
        scanf("%d", &j);
        seq[i] = j;
        i++;
    }
    int tamanho=i;
    if(resultado(K,&tamanho,seq)==2){   
            printf("Sequencia vitoria");
        } 
    if(resultado(K,&tamanho,seq)==1){ 
            printf("Sequencia valida");
        }
    if(resultado(K,&tamanho,seq)==0){ 
        printf("Sequencia invalida");
}
}