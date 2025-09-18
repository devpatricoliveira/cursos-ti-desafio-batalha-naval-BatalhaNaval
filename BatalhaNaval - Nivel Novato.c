#include <stdio.h>
#define N 5
#define AGUA 0
#define NAVIO 3
#define ACERTO 7
#define ERRO 1

void print(int t[N][N]){
    printf("  "); for(int c=0;c<N;c++) printf("%d ",c); printf("\n");
    for(int i=0;i<N;i++){ printf("%d ",i); for(int j=0;j<N;j++){
        int v=t[i][j]; char ch='.';
        if(v==NAVIO) ch='N'; else if(v==ACERTO) ch='X'; else if(v==ERRO) ch='o';
        printf("%c ", ch);
    } printf("\n"); }
}

int main(){
    int tab[N][N]={0};
    
    tab[1][1]=NAVIO; tab[1][2]=NAVIO;
    tab[3][3]=NAVIO;

    int tentativas=5;
    printf("=== Batalha Naval - Nivel Novato ===\n");
    while(tentativas--){
        print(tab);
        int l,c; printf("Ataque (linha coluna): "); scanf("%d %d",&l,&c);
        if(l<0||l>=N||c<0||c>=N){ printf("Fora do tabuleiro.\n"); continue; }
        if(tab[l][c]==NAVIO){ tab[l][c]=ACERTO; printf("Acertou!\n"); }
        else if(tab[l][c]==AGUA){ tab[l][c]=ERRO; printf("Agua!\n"); }
       
    }
    printf("Fim de jogo.\n");
    return 0;
}
