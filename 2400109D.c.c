#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

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
    printf("\nSequencia:");
    for(i = 0; i< *tamanho;i++){
        printf(" %d",seq[i]);
    }
    printf("%s\n", quemjoga);
}

void imprimir_sequenciafinal(int seq[], int *tamanho){
    int i ;
    printf("\nSequencia:");
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
    if (valor < 0){
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
    int i=0;
    int produto=1;
    int soma=0;
    int diferenca=0;
    int somadiferenca=0;
    int h; 
    int w = 0;
    for (h=0;h<*tamanho;h++){
        if (seq[h]!=0){
            produto*=seq[h];
            soma+=seq[h];
            while (i < *tamanho) {
                w = i + 1; 
                while (w < *tamanho) {
                    diferenca += abs(seq[i] - seq[w]);
                    w++;
                }
                i++;
            }
        }
    }
    if (produto>=K  && soma<=K ){
        if (diferenca==K){
            return 2;
        }
        return 1;
    }
    return 0;
}

bool verificar_seq_iguais(int *seq_1, int *seq_2, int tamanho_1, int tamanho_2){
    if (tamanho_1 != tamanho_2) {
        return false;
    }
    for (int i = 0; i < tamanho_1; i++) {
        if (seq_1[i] != seq_2[i]) {
            return false; 
        }
    }
    return true; 
}

int analisar_vitoria_jogada_artificial(int K, int*tamanho, int *seq_art, int *seq, int *tamanho_original, int i, int indice, int valor_art){
    bool seq_invalida=true;
   if (resultado(K, tamanho_original,seq_art) ==2 && !verificar_seq_iguais(seq, seq_art, *tamanho_original, i)){
        seq_invalida=false;
        for (int i = 0; i < *tamanho; i++) {
            seq[i] = 0;
        }
        for (int i = 0; i < *tamanho_original; i++) {
            seq[i] = seq_art[i];
        }
        *tamanho=*tamanho_original;
        printf("\nJogada artificial : %d %d", indice, valor_art);
        return 1;
    } else{
        for (int z = 0; z < *tamanho_original; z++) {
            seq_art[z] = 0;
        }
        *tamanho_original=i;
        for (int z = 0; z < *tamanho_original; z++) {
            seq_art[z] = seq[z];
        }
    }
    return 0;
}

void jogada_artifical(int *seq, int *tamanho, int K, int *jogada){
    int indice=0;
    int tamanho_original=0;
    int seq_art[100];
    int m;
    int i;
     while ( seq[tamanho_original]!=0){
        tamanho_original++;
    }
    int tamanho_art=tamanho_original;
    for (int m = 0; m < tamanho_art; m++) {
        seq_art[m] = seq[m];
    }
    for(i=1; i<tamanho_art;i++){
        if (seq[i]>seq[indice]){
            indice=i;
        }
    }
    bool seq_invalida=true;
    int valor_art=0;
    int f;
    int contador=0;
    while(seq_invalida){
        jogada[0]=indice;
        jogada[1]=valor_art;
        if (contador==0) {
            if (jogada[1]==0 && jogada[0]<=tamanho_art-1){
                remover_nasequencia(seq_art, &tamanho_art,jogada[0]);
                analisar_vitoria_jogada_artificial(K,&tamanho_art,seq_art, seq, &tamanho_art, *tamanho, indice, valor_art);
            }  
        }
        if (contador==1 && jogada[0]<tamanho_art) {
            for(int l=1;l<=K;l++){
                jogada[1]=l;
                alterar_nasequencia(seq_art, &tamanho_art,jogada[0], jogada[1]);
                if (resultado(K,&tamanho_art,seq_art) == 2 && !verificar_seq_iguais(seq, seq_art, tamanho_art, *tamanho)) {
                    seq_invalida=false;
                    int o;
                    for (int o = 0; o < tamanho_art; o++) {
                        seq[o] = seq_art[o];
                    }
                    printf("\nJogada artificial: %d %d", jogada[0], jogada[1]);
                    break;
                } else{
                    for (int z = 0; z < tamanho_original; z++) {
                        seq_art[z] = seq[z];
                    }
                }
            }
        }
        if (contador==2){
            for(f=-1;f>-K;f--){
                jogada[1]=f;
                valor_negativo(seq_art, &tamanho_art, jogada[0] ,jogada[1]);
                if (resultado(K,&tamanho_art,seq_art) ==2 && !verificar_seq_iguais(seq, seq_art, tamanho_art, *tamanho)){
                    seq_invalida=false;
                    int n;
                    for (int n = 0; n < tamanho_art; n++) {
                        seq[n] = seq_art[n];
                    }
                    *tamanho=tamanho_art;
                    printf("\nJogada artificial: %d %d", jogada[0], jogada[1]);
                    break;
                } else{
                    for (int z = 0; z < tamanho_original; z++) {
                        seq_art[z] = seq[z];
                    }
                    tamanho_art=tamanho_original;
                    jogada[1]=valor_art;
                }
            }
        }
        if (contador==3) {
            if (jogada[1]==0 && jogada[0]<=tamanho_art-1){
                remover_nasequencia(seq_art, &tamanho_art,jogada[0]);
                if (resultado(K, &tamanho_art,seq_art) ==1 && !verificar_seq_iguais(seq, seq_art, tamanho_art, tamanho_original)){
                    seq_invalida=false;
                    for (int n = 0; n < *tamanho; n++) {
                        seq[n] = 0;
                    }
                    for (int n = 0; n < tamanho_art; n++) {
                        seq[n] = seq_art[n];
                    }
                    *tamanho=tamanho_art;
                    printf("\nJogada artificial : %d %d", jogada[0], jogada[1]);
                } else{
                     for (int z = 0; z < tamanho_art; z++) {
                        seq_art[z] = 0;
                    }
                    tamanho_art=tamanho_original;
                    for (int z = 0; z < tamanho_art; z++) {
                        seq_art[z] = seq[z];
                    }
                }
            }
        } 
        if (contador==4 && jogada[0]<tamanho_art) {
            for(int l=1;l<=K;l++){
                jogada[1]=l;
                alterar_nasequencia(seq_art, &tamanho_art,jogada[0], jogada[1]);
                if (resultado(K,&tamanho_art,seq_art) == 1 && !verificar_seq_iguais(seq, seq_art, tamanho_art, *tamanho)) {
                    seq_invalida=false;
                    int o;
                    for (int o = 0; o < tamanho_art; o++) {
                        seq[o] = seq_art[o];
                    }
                    printf("\nJogada artificial: %d %d", jogada[0], jogada[1]);
                    break;
                } else{
                    for (int z = 0; z < tamanho_original; z++) {
                        seq_art[z] = seq[z];
                    }
                    jogada[1]=valor_art;
                }
            }
        }
        if (contador==5){
            if (jogada[0]==tamanho_art && jogada[1]!=0){
                adicionar_nasequencia(seq_art,&tamanho_art,jogada[1]);
                if (resultado(K, &tamanho_art,seq_art) >0 && !verificar_seq_iguais(seq, seq_art, tamanho_art, tamanho_original)){
                    seq_invalida=false;
                    int n;
                    for (int n = 0; n < tamanho_original; n++) {
                        seq[n] = seq_art[n];
                    }
                    *tamanho=tamanho_art;
                    printf("\nJogada artificial : %d %d", jogada[0], jogada[1]);
                } else{
                    tamanho_art=i;
                    for (int z = 0; z < tamanho_art; z++) {
                        seq_art[z] = seq[z];
                    }
                    valor_art++;
                }
            }
        }
        contador++;
   }
}
int main () {
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
        int indice;
        int valor;
        while (j<2) {
            scanf("%d", &indval);
            jogada[j] = indval;
            indice= jogada[0] ;
            valor= jogada[1];
            j++;
        } 
        if(indice==-2 && valor==-2){
            jogada_artifical(seq, &tamanho, K, jogada);
            if ((jogada[1]==0 && jogada[0]<=tamanho-1) || jogada[1]<0){
                jogadasnegativas++;
            } else {
                jogadaspositivas++;
            }
        } else{
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
        }
        if (jogadaspositivas>=1 || jogadasnegativas==2){
            jogadasnegativas=0;
            jogadaspositivas=0;
            mudavez++;
        }
        jogadas++;
        if(resultado(K,&tamanho,seq)==2){
            imprimir_sequenciafinal(seq,&tamanho);
            printf("Jogador %c ganhou.", jogador);
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