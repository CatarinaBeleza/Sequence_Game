#include <stdio.h>

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

int main () {
    
    int seq[2];
    int K;
    printf("Indique K:");
    scanf(" %d", &K);
   
    if (inicio(K, seq)==1){
        printf("Sequencia: %d %d", seq[0], seq[1]);
    }else{
         printf("\nK tem de ser entre 2 e 100.");
    }
}