#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
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
*/
struct cell{
      bool bomb;
      bool flag;
};
class ms{
      struct cell map[8][8];
public:
      void Initscreen();
      void bombset(int n);
      void Gamescreen();
      void checkbomb(int i,int j,int map[8][8]);
      void countbomb(int i,int j,int map[8][8]);
      //void Inputscreen(int **map);
      void GameoverScreen();
      void setflag(int x,int y,int map[][8]);
      void resetflag(int x,int y,int map[][8]);
};
//Display the game screen
void ms::Gamescreen(){
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

//Display the input screen
ms::ms(){
            printf("*** M Sweeper ***\n\
コマンドの入力:x y [asm]\n\
  x y … 座標[0-7]\n\
  a   … (x,y)の周囲の点を自動的にチェック\n\
  s   … (x,y)を安全な点としてチェック\n\
  m   … (x,y)にMマークをつける\n");

printf("\n");
}

//Initialize the array
ms::ms(){
      for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                  map[i][j].bomb = false;
                  map[i][j].flag = false;
            }
      }
}

void ms::bombset(int n){
      srand(time(NULL));
      int m = n;
     for(int i=0;i<n;i++){
            int x = ( rand() % 8);
            int y = ( rand() % 8);
            map[x][y] = 1;
     }
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
void ms::checkbomb(int i,int j){
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

int ms::countbomb(int x,int y){
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


ms::GameoverScreen(){
      printf("\n");
      printf("GameOver");
      printf("\n\n");
      exit(0);
}

void ms::setflag(int x,int y){
      map[x][y].flag = true;
}
void ms::resetflag(int x,int y){
      map[x][y].flag = false;
}


int main(){

      int x=0,y=0;
      ms Mine;
      Mine.bombset(10);

      Mine.
//      char command;
      printf("Please enter a command:");
  //    scanf("%d %d %c",&x,&y,&command);
      scanf("%d%d",&x, &y);
      checkbomb(x,y,map);
    }
}
