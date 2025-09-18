#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define AGUA 0
#define NAVIO 3
#define ACERTO 7
#define ERRO 1

void limpar(int t[N][N]){ for(int i=0;i<N;i++) for(int j=0;j<N;j++) t[i][j]=AGUA; }

void print_visivel(int t[N][N]){
    printf("  "); for(int c=0;c<N;c++) printf("%d ",c); printf("\n");
    for(int i=0;i<N;i++){ printf("%d ",i); for(int j=0;j<N;j++){
        int v=t[i][j]; char ch='.';
        if(v==ACERTO) ch='X'; else if(v==ERRO) ch='o';
        printf("%c ", ch);
    } printf("\n"); }
}

void print_completo(int t[N][N]){
    printf("  "); for(int c=0;c<N;c++) printf("%d ",c); printf("\n");
    for(int i=0;i<N;i++){ printf("%d ",i); for(int j=0;j<N;j++){
        int v=t[i][j]; char ch='.';
        if(v==NAVIO) ch='N'; else if(v==ACERTO) ch='X'; else if(v==ERRO) ch='o';
        printf("%c ", ch);
    } printf("\n"); }
}

void colocar_aleatorio(int t[N][N], int tam){
    int tent=0;
    while(tent++<1000){
        int dir=rand()%2; 
        int r=rand()%N, c=rand()%N;
        int ok=1;
        if(dir==0){
            if(c+tam>N) continue;
            for(int j=0;j<tam;j++) if(t[r][c+j]!=AGUA) {ok=0;break;}
            if(!ok) continue;
            for(int j=0;j<tam;j++) t[r][c+j]=NAVIO;
            return;
        } else {
            if(r+tam>N) continue;
            for(int i=0;i<tam;i++) if(t[r+i][c]!=AGUA) {ok=0;break;}
            if(!ok) continue;
            for(int i=0;i<tam;i++) t[r+i][c]=NAVIO;
            return;
        }
    }
}

int resta(int t[N][N]){
    int k=0; for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(t[i][j]==NAVIO) k++; return k;
}

int atacar(int t[N][N], int l,int c){
    if(l<0||l>=N||c<0||c>=N) return -1;
    if(t[l][c]==NAVIO){ t[l][c]=ACERTO; return 1; }
    if(t[l][c]==AGUA){ t[l][c]=ERRO; return 0; }
    return -1;
}

int main(){
    srand((unsigned)time(NULL));
    int J[N][N], C[N][N]; limpar(J); limpar(C);
    colocar_aleatorio(J,4); colocar_aleatorio(J,3); colocar_aleatorio(J,2);
    colocar_aleatorio(C,4); colocar_aleatorio(C,3); colocar_aleatorio(C,2);

    int turno=0;
    printf("=== Batalha Naval - Nivel Aventureiro ===\n");
    while(1){
        printf("\nSeu tabuleiro:\n"); print_completo(J);
        printf("\nInimigo (visao):\n"); print_visivel(C);
        if(resta(C)==0){ printf("Voce venceu!\n"); break; }
        if(resta(J)==0){ printf("CPU venceu!\n"); break; }

        if(turno==0){
            int l,c; printf("Ataque (l c): "); scanf("%d %d",&l,&c);
            int r=atacar(C,l,c);
            if(r==1) printf("Acertou!\n"); else if(r==0) printf("Agua!\n"); else printf("Ja atacado.\n");
            turno=1;
        } else {
            int l=rand()%N, c=rand()%N;
            int r=atacar(J,l,c);
            int tries=0;
            while(r==-1 && tries++<200){ l=rand()%N; c=rand()%N; r=atacar(J,l,c); }
            if(r==1) printf("CPU acertou (%d,%d)\n",l,c);
            else if(r==0) printf("CPU errou (%d,%d)\n",l,c);
            turno=0;
        }
    }
    return 0;
}
