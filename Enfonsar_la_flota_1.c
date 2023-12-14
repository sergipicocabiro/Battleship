#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

void Get_Coord(char C[], int D, int *r, int *c){
    char *Rows[]={"A","B","C","D","E","F","G","H"};
    char *Columns[]={"1","2","3","4","5","6","7","8"};
    *r = -1;
    *c = -1;
    for(int i=0; i<D; i++){
        if(C[0]==*Rows[i]){
            *r = i;
        }
        if(C[1]==*Columns[i]){
            *c = i;
        }
    }
}

void Print_malla(int D,int grid[D][D], int hidden){
    char letters[8] = {'A','B','C','D','E','F','G','H'};
    printf("\t1\t2\t3\t4\t5\t6\t7\t8\n");
    printf("------------------------------------------------------------------\n");
    for(int i=0;i<D;i++){
        printf("%c|\t",letters[i]);
        for(int j=0;j<D;j++){
            if(hidden == 1){
                if(grid[i][j]==-2){
                    printf("~\t");
                }
                else if(grid[i][j]==-1){
                    printf("#\t");
                }
                else{
                    printf("\t");
                }
            }
            else if(hidden == 0){
                printf("%i\t", grid[i][j]);
            }
        }
        printf("\n");
    }
}

void Random_Ship(int N, int D, int Len[],int grid[D][D]){
    for(int i=0; i<N;i++){
        while(1){
            srand(time(NULL));
            int rndmRow_index;
            int rndmCol_index;
            while(1){
                rndmRow_index = rand() % D;
                rndmCol_index = rand() % D;
                if (grid[rndmRow_index][rndmCol_index]==0){
                    grid[rndmRow_index][rndmCol_index]=i+1;
                    break;
                }
            }
            int rndmDir = rand() % 4;
            if(rndmDir ==0 && rndmRow_index-Len[i]>=-1){
                int count = 0;
                for(int k=1;k<Len[i];k++){
                    if(grid[rndmRow_index-k][rndmCol_index]>0){
                        count=1;
                    }
                }
                if(count == 0){
                    for(int k=1;k<Len[i];k++){
                        grid[rndmRow_index-k][rndmCol_index]=i+1;
                    }
                    break;
                }
            }
            if(rndmDir ==1 && rndmRow_index+Len[i]<=D){
                int count = 0;
                for(int k=1;k<Len[i];k++){
                    if(grid[rndmRow_index+k][rndmCol_index]>0){
                        count=1;
                    }
                }
                if(count == 0){
                    for(int k=1;k<Len[i];k++){
                    grid[rndmRow_index+k][rndmCol_index]=i+1;
                    }
                    break;
                }
            }
            if(rndmDir ==2 && rndmCol_index-Len[i]>=-1){
                int count = 0;
                for(int k=1;k<Len[i];k++){
                    if(grid[rndmRow_index][rndmCol_index-k]>0){
                        count=1;
                    }
                }
                if(count == 0){
                    for(int k=1;k<Len[i];k++){
                    grid[rndmRow_index][rndmCol_index-k]=i+1;
                    }
                    break;
                }
            }
            if(rndmDir == 3 && rndmCol_index+Len[i]<=D){
                int count = 0;
                for(int k=1;k<Len[i];k++){
                    if(grid[rndmRow_index][rndmCol_index+k]>0){
                        count=1;
                        }
                }
                if(count == 0){
                    for(int k=1;k<Len[i];k++){
                    grid[rndmRow_index][rndmCol_index+k]=i+1;
                    }
                    break;
                }
            }
            else{
                grid[rndmRow_index][rndmCol_index]=0;
            }
        }
    }
}

void Allocate_Ships(int N,int D, int Len[], int grid[D][D]){
    int k = 0;
    while(k<N){
        Print_malla(D,grid,0);
        printf("A quina posicio vols que comenci el vaixell %i?\n", k+1);
        char C[3];
        scanf("%s", C);
        int r,c;
        Get_Coord(C,D,&r,&c);
        printf("Cap a quina direccio vols colocar el vaixell %i de llargada %i? (Adalt, Abaix, Dreta, Esquerra)\n", k+1, Len[k]);
        while(1){
            char Direction[100];
            scanf("%s", Direction);
            if(strcmp(Direction, "Adalt")==0){
                int count = 0;
                for(int i=0;i<Len[k];i++){
                    if(grid[r-i][c]>0){
                        count=1;
                    }
                }
                if(count == 0 && r-Len[k]>=0){
                    for(int i=0;i<Len[k];i++){
                        grid[r-i][c]=k+1;
                    }
                    k++;
                    break;
                }
                else{
                    printf("Aquesta direccio no es possible. Prem 0 per escollir un altre punt inicial, qualsevol altre numero per reescollir una nova direccio:\n");
                    int kfer;
                    scanf("%i",&kfer);
                    if(kfer==0){
                        break;
                    }
                    else{
                        printf("\nIntrodueix una nova direccio:\n");
                    }
                }
            }
            else if(strcmp(Direction, "Abaix")==0){
                int count = 0;
                for(int i=0;i<Len[k];i++){
                    if(grid[r+i][c]>0){
                        count=1;
                    }
                }
                if(count == 0 && r+Len[k]<=8){
                    for(int i=0;i<Len[k];i++){
                        grid[r+i][c]=k+1;
                    }
                    k++;
                    break;
                }
                else{
                    printf("Aquesta direccio no es possible. Prem 0 per escollir un altre punt inicial, qualsevol altre numero per reescollir una nova direccio:\n");
                    int kfer;
                    scanf("%i",&kfer);
                    if(kfer==0){
                        break;
                    }
                    else{
                        printf("\nIntrodueix una nova direccio:\n");
                    }                 }
            }
            else if(strcmp(Direction, "Dreta")==0){
                int count = 0;
                for(int i=0;i<Len[k];i++){
                    if(grid[r][c+i]>0){
                        count=1;
                    }
                }
                if(count == 0 && c+Len[k]<=8){
                    for(int i=0;i<Len[k];i++){
                        grid[r][c+i]=k+1;
                    }
                    k++;
                    break;
                }
                else{
                    printf("Aquesta direccio no es possible. Prem 0 per escollir un altre punt inicial, qualsevol altre numero per reescollir una nova direccio:\n");
                    int kfer;
                    scanf("%i",&kfer);
                    if(kfer==0){
                        break;
                    }
                    else{
                        printf("\nIntrodueix una nova direccio:\n");
                    }
                }
            }
            else if(strcmp(Direction, "Esquerra")==0){
                int count = 0;
                for(int i=0;i<Len[k];i++){
                    if(grid[r][c-i]>0){
                        count=1;
                    }
                }
                if(count == 0 && c-Len[k]>=0){
                    for(int i=0;i<Len[k];i++){
                        grid[r][c-i]=k+1;
                    }
                    k++;
                    break;
                }
                else{
                    printf("Aquesta direccio no es possible. Prem 0 per escollir un altre punt inicial, qualsevol altre numero per reescollir una nova direccio:\n");
                    int kfer;
                    scanf("%i",&kfer);
                    if(kfer==0){
                        break;
                    }
                    else{
                        printf("\nIntrodueix una nova direccio:\n");
                    }
                }
            }
            else{
                printf("Aquesta direccio no existeix. Introdueix una d'entre: Adalt, Abaix, Dreta o Esquerra\n");
            }
        }
    }
}

void Dispar(int N, int D, int Len[], int grid[D][D], int *aigua_count, int *finish, int mod){
    while(1){
        printf("Dispara\n");
        char C[3];
        scanf("%s", C);
        int r,c;
        Get_Coord(C,D,&r,&c);
        if(r!=-1 && c!=-1){
            if(grid[r][c]==0){
                printf("Aigua\n");
                (*aigua_count)++;
                grid[r][c]=-2;
            }
            else if(grid[r][c]>0){
                printf("Tocat");
                int Vaixell = grid[r][c];
                Len[Vaixell-1]--;
                grid[r][c] = -1;
                for(int k=0;k<N;k++){
                    if(Len[k]==0){
                        printf(" i enfonsat");
                        Len[k]--;
                    }
                (*finish) += Len[k];
                }
                printf("\n");
            }
            else{
                printf("Ja has disparat a aquesta posicio\n");
            }
            Print_malla(D,grid,1);
            break;
        }
        else{
            printf("Introdueix una coordenada valida\n");
        }
    }
}

int main(){
    //TÍTOL
    printf("\n\t\t\t\t\tBenvolgut a enfonsar la flota!\n\n\n");
    // DIMENSIONS
    int D;
    while(1){
        printf("Amb quantes dimensions vols jugar?\n");
        scanf("%d", &D);
        if(D>8 || D<1){
            printf("Les dimensions del joc no poden ser superiors a 8 o inferiors a 1. Torne'm-hi.\n");
        }
        else{
            break;
        }
    }
    //MODALITAT DE JOC
    printf("\nA quina modalitat de joc vols jugar?\n");
    printf("1. J1 vs ordinador\n");
    printf("2. J1 vs J2\n");
    int mod;
    while(1){
        scanf("%i", &mod);
        if(mod ==1 || mod==2){
            break;
        }
        else{
            printf("Escull un valor entre 1 i 2\n");
        }
    }
    //VAIXELLS I LLARGADA
    printf("\nAmb quants vaixells vols jugar?\n");
    int N;
    scanf("%d", &N);
    printf("\n");
    int Len[N];
    int k=0;
    while(k<N){
        while(1){
            printf("Quina es la llargada del vaixell %i?\n",k+1);
            scanf("%d", &Len[k]);
            if(Len[k]>8 || Len[k]<1){
                printf("La llargada dels vaixells ha de ser un numero entre 1 i 8. Torne'm-hi.\n");
            }
            else{
                k++;
                break;
            }
        }
    }
    int Len1[N];
    int Len2[N];
    for(int i=0;i<N;i++){
        Len1[i] = Len[i];
        Len2[i] = Len[i];
    }
    //MALLES
    unsigned int grid[D][D];
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            grid[i][j] = 0;
        }
    }

    unsigned int grid1[D][D];
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            grid1[i][j] = 0;
        }
    }
    unsigned int grid2[D][D];
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            grid2[i][j] = 0;
        }
    }
    //INICIALITZACIÓ DELS VAIXELLS I MALLA I JOC
    if(mod==1){
        Print_malla(D,grid,1);
        Random_Ship(N,D, Len, grid);
        printf("Aquest sera el camp de batalla. L'algoritme ha disposat els vaixells de manera aleatoria.\n");
        int N_tir = 32;
        int aigua_count = 0;
        int finish = 0;
        while(aigua_count<N_tir && finish>-N){
            Dispar(N,D,Len,grid,&aigua_count,&finish,1);
        }
        //VEREDICTE
        if(aigua_count!=N_tir){
            printf("Enhorabona, has enfonsat tota la flota :)\n");
        }
        else{
            printf("Ho sento, has superat el limit d'intents :(\n");
        }
    }
    else if(mod == 2){
        printf("\nJugador 1, escull la disposicio dels teus vaixells (Jugador 2, no miris):\n\n");
        Allocate_Ships(N,D,Len,grid1);
        Print_malla(D,grid1,0);
        printf("Jugador 1, aquesta es la teva disposicio de vaixells. Prem el boto que sigui perque el Jugador 2 en faci la seva\n");
        _getch();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Jugador 2, escull la disposicio dels teus vaixells (Jugador 1, no miris):\n\n");
        Allocate_Ships(N,D,Len,grid2);
        Print_malla(D,grid2,0);
        printf("Jugador 2, aquesta es la teva disposicio de vaixells. Prem el boto que sigui per jugar\n");
        _getch();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        int finish1 = 0;
        int finish2 = 0;
        int aigua_count1 = 0;
        int aigua_count2 = 0;
        while(1){
            Print_malla(D,grid2,1);
            printf("Jugador 1, aquest es el camp de batalla del Jugador 2.\n");
            Dispar(N,D,Len2,grid2,&aigua_count2,&finish2,2);
            if(finish2==-N){
                printf("Enhorabona Jugador 1, has enfonsat tota la flota del jugador 2\n");
                break;
            }
            printf("Camp de batalla enemic\n");
            Print_malla(D,grid1,0);
            printf("El teu camp de batalla (-2 representa el tir fallit del teu contrincant, -1 el tir encertat).\nPrem qualsevol boto per donar pas al torn del Jugador 2:\n");
            _getch();
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            Print_malla(D,grid1,1);
            printf("Jugador 2, aquest es el camp de batalla del Jugador 1.\n");
            Dispar(N,D,Len1,grid1,&aigua_count1,&finish1,2);
            if(finish1==-N){
                printf("Enhorabona Jugador 2, has enfonsat tota la flota del jugador 1\n");
                break;
            }
            printf("Camp de batalla enemic\n");
            Print_malla(D,grid2,0);
            printf("El teu camp de batalla (-2 representa el tir fallit del teu contrincant, -1 el tir encertat).\nPrem qualsevol boto per donar pas al torn del Jugador 1:\n");
            _getch();
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
    return 0;
}
