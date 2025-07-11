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
        printf("K tem de ser entre 2 e 100.");
        return 0;
    }
}

void adicionar_nasequencia(int *seq, int *tamanho, int novo){
    if(*tamanho+1 < 100 && *tamanho >=0){
        *tamanho+=1;
        seq[*tamanho-1] = novo;
    }
}

void imprimir_sequencia(int seq[], int *tamanho, char *quemjoga){
    int i ;
    printf("\n Sequencia:");
    for(i = 0; i< *tamanho;i++){
        printf(" %d",seq[i]);
    }
    printf("%s\n", quemjoga);
}

void imprimir_sequenciafinal(int seq[], int *tamanho){
    int i ;
    printf("\n Sequencia:");
    for(i = 0; i< *tamanho;i++){
        printf(" %d",seq[i]);
    }
    printf("\n" );
}

void remover_nasequencia(int *seq, int *tamanho, int velho) {
    int i;
    for (i = velho; seq[i + 1] != '\0'; i++) {
        seq[i] = seq[i + 1];
    }
    seq[i] = 0;
    (*tamanho)--;
}

void alterar_nasequencia(int *seq, int *tamanho, int indice, int valor) {
    if (indice < 0 && indice < *tamanho) { 
        seq[0] = valor;  
    }
    if (indice >= 0 && indice < *tamanho) { 
        seq[indice] = valor;  
    }
}

void valor_negativo(int *seq, int *tamanho, int indice ,int valor){
     int i;
     if (indice<0){
        indice=0;
    }
    if (valor < 0) {
        for(i = *tamanho; i >= indice; i--) {
            if(indice<i){
                seq[i] = seq[i - 1];
            }
            if (indice>i){
                seq[i] = seq[i];
            }
        }
        seq[indice] = abs(valor);
        (*tamanho)++;
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
            while (m < *tamanho) {
                int j = m + 1; 
                while (j < *tamanho) {
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
    //Inicio do jogo
    int seq[100];
    int K,i;
    int jogadas=0;
    int jogadaspositivas=0;
    int jogadasnegativas=0;
    int mudavez=0; 
    char *quemjoga = " [Joga A]";
    int tamanho = 2;
    printf("Indique K:");
    scanf(" %d", &K);
    if (inicio(K,seq)){
        imprimir_sequencia(seq, &tamanho, quemjoga);
    }else{
        printf("K tem de ser entre 2 e 100. \n");
    }
    while (jogadas>=0 && jogadas<K){
        printf("Jogada (indice valor): ");
        int j=0;
        int indval;
        int jogada[2];
        char jogador;  
        while (j<2) {
            scanf("%d", &indval);
            jogada[j] = indval;
            j++;
        } 
        if (jogada[0]>=tamanho && jogada[1]!=0){
            adicionar_nasequencia(seq,&tamanho,jogada[1]);
            jogadaspositivas++;
        }
       if(jogada[0]<tamanho && jogada[1]!=0 && jogada[1]>0){
            alterar_nasequencia(seq, &tamanho,jogada[0], jogada[1]);
            jogadaspositivas++;
        }
       
        if (jogada[1]==0){
            if (jogada[0]<=tamanho-1){
               remover_nasequencia(seq,&tamanho,jogada[0]);
            }
              jogadasnegativas++;
        }
       if (jogada[1]<0) { 
           valor_negativo(seq, &tamanho, jogada[0] ,jogada[1]);
           jogadasnegativas++;
       }
        if (jogadaspositivas>=1 || jogadasnegativas==2){
            jogadasnegativas=0;
            jogadaspositivas=0;
            mudavez++;
        }
        jogadas++;
        if(resultado(K,&tamanho,seq)==2){
            imprimir_sequenciafinal(seq,&tamanho);
            printf("\nJogador %c ganhou.", jogador);
            return 0;
        }
        if(resultado(K,&tamanho,seq)==0){
            imprimir_sequenciafinal(seq,&tamanho);
            printf("\nJogador %c perdeu.", jogador);
            return 0;
        }
        if (resultado(K,&tamanho,seq)!=0 && resultado(K,&tamanho,seq)!=2 && K==jogadas){
            imprimir_sequenciafinal(seq,&tamanho);
            printf("Empate.");
            return 0;
        }
       if (mudavez%2==0){
            quemjoga = " [Joga A]";
            jogador= 'A';
        }else{
            quemjoga = " [Joga B]";
            jogador= 'B';
        }
        if(resultado(K, &tamanho, seq)==1){
            imprimir_sequencia(seq,&tamanho, quemjoga);
        }
    }
}