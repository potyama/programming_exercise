#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Initmap(int map[8][8]);
void Initscreen();
void bombset(int n,int map[][8]);
void Gamescreen(int map[8][8]);
void checkbomb(int i,int j,int map[8][8]);
void countbomb(int i,int j,int map[8][8]);
//void Inputscreen(int **map);
void GameoverScreen();
void setflag(int x,int y,int map[][8]);
void resetflag(int x,int y,int map[][8]);

struct cell{
      bool bomb;
      bool flag;
}

int main(){

      int x=0,y=0;
      int map[8][8];
//      char command;

      Initmap(map);
      Initscreen();
      scanf("%d",int n);
      bombset(n,map);
      while(1){
      Gamescreen(map);
      printf("Please enter a command:");
  //    scanf("%d %d %c",&x,&y,&command);
      scanf("%d%d",&x, &y);
      checkbomb(x,y,map);
    }
}

//Display the game screen
void Gamescreen(int map[][8]){
      printf("  0 1 2 3 4 5 6 7\n");
      for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                  if(map[i][j] == -1 ){
                        if(map[i][j].flag == true){
                              printf("m ");
                        }else if(map[i][j].flag == false){
                              printf(". ");
                        }else{
                        printf(" ");
                  }
            }else{
                  printf("%1d ",map[i][j]);
            }
      }
      printf("\n");
      }
}
//Initialize the array
void Initmap(int map[][8]){
      int i,j;

      for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                  map[i][j] = -1;
            }
      }
}


void bombset(int n,int map[][8]){
      srand(time(NULL));
      int m = n;
     for(int i=0;i<n;i++){
            int x = ( rand() % 8);
            int y = ( rand() % 8);
            map[x][y] = 1;
     }
}


//Display the input screen
void Initscreen(){
            printf("*** M Sweeper ***\n\
コマンドの入力:x y [asm]\n\
  x y … 座標[0-7]\n\
  a   … (x,y)の周囲の点を自動的にチェック\n\
  s   … (x,y)を安全な点としてチェック\n\
  m   … (x,y)にMマークをつける\n");

printf("\n");
}

// Input
/*
void Inputscreen(){
      int x,y;
      char command;
      printf("Please enter a command:");
      scanf("%d %d %c",&x,&y,&command);
      return x,y;
}
*/
//Check bomb
void checkbomb(int i,int j,int map[][8]){
      printf("%d/%d\n",i,j);
      if(i < 0 || j < 0 || i > 8 || j > 8)return;

      if(map[i][j] == 1){
            GameoverScreen();
      }
      if(map[i][j] == -1 ){
//      printf("%d->%d\n",i,j);
            map[i][j] = countbomb(i,j,map);
      }
      if(map[i][j] >= 0){
            checkbomb(i-1,j-1,map);
            checkbomb(i-1,j,map);
            checkbomb(i-1,j+1,map);
            checkbomb(i,j-1,map);
            checkbomb(i,j+1,map);
            checkbomb(i+1,j-1,map);
            checkbomb(i+1,j,map);
            checkbomb(i+1,j+1,map);
      }
      return;
}

int countbomb(int x,int y,int map[][8]){
      int count=0;
      if(0 < x){
            if(map[i-1][j] == 1)count++;
            if(0 < y){
                  if(map[i-1][j-1] == 1)count++;
            }
            if(y < 8){
                  if(map[i-1][j+1] == 1)count++;
            }
      }
      if(x < 8){
            if(map[i+1][j] == 1)count++;
            if(0 < y){
                  if(map[i+1][j-1] == 1)count++;
            }
            if(y < 8){
                  if(map[i-1][j+1] == 1)count++;
            }
      }
      if(0 < y){
            if(map[i][j-1] == 1)count++;
      }
      if(y < 8){
            if(map[i+1][j+1] == 1)count++;
      }
      return count;
}


void GameoverScreen(){
      printf("\n");
      printf("GameOver");
      printf("\n\n");
      exit(0);
}

void setflag(int x,int y){
      map[x][y].flag = true;
}
void resetflag(int x,int y){
      map[x][y],flag = false;
}
