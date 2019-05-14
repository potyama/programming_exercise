#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define END -1
#define GameOver -2


struct cell{
      int check = -1;
      int count = 0;
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

//Display the input screen
ms::ms(){
      printf("*** M Sweeper ***\n\
      コマンドの入力:x y [asm]\n\
        x y … 座標[0-7]\n\
        a   … (x,y)の周囲の点を自動的にチェック\n\
        s   … (x,y)を安全な点としてチェック\n\
        m   … (x,y)にMマークをつける\n");
      printf("\n");
      for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                  map[i][j].bomb = false;
                  map[i][j].flag = false;
                  map[i][j].check = -1;
                  map[i][j].count = 0;
            }
      }
}

void ms::bombset(int n){
      srand(time(NULL));
      int m = n;
     for(int i=0;i<n;i++){
            int x = (rand() % 8);
            int y = (rand() % 8);
            map[x][y] = 1;
     }
}


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
//WTNBさんにきく
//関数内から関数に渡す時(=再帰)につけるクラス名 ms.で良いのかmainで宣言した.Mineで良いのか
void ms::checkbomb(int i,int j){
      if(i < 0 || i >= 8 || j < 0 || j >= 8 || map[i][j].check == 0)return;
      if(map[i][j].bomb == true){
            GameoverScreen();
            return;
      }
            map[i][j].count = countbomb(i,j);
            map[i][j].check = 0;
      if(map[i][j]. == -1){
            checkbomb(i-1,j);
            checkbomb(i-1,j-1);
            checkbomb(i-1,j+1);
            checkbomb(i+1,j);
            checkbomb(i+1,j-1);
            checkbomb(i-1,j+1);
            checkbomb(i,j-1);
            checkbomb(i+1,j+1);
      }
      return;
}

int ms::countbomb(int x,int y){
      int count=0;
      if(0 < x){
            if(map[i-1][j].bomb == true)count++;
            if(0 < y){
                  if(map[i-1][j-1].bomb == true)count++;
            }
            if(y < 8){
                  if(map[i-1][j+1].bomb == true)count++;
            }
      }
      if(x < 8){
            if(map[i+1][j].bomb == true)count++;
            if(0 < y){
                  if(map[i+1][j-1].bomb == true)count++;
            }
            if(y < 8){
                  if(map[i-1][j+1].bomb == true)count++;
            }
      }
      if(0 < y){
            if(map[i][j-1].bomb == true)count++;
      }
      if(y < 8){
            if(map[i+1][j+1].bomb == true)count++;
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
