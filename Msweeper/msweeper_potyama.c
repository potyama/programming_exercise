#include <stdio.h>
#include <stdlib.h>

int Initmap(int map[8][8]);
void Initscreen();
void Gamescreen(int map[8][8]);
void checkbomb(int i,int j,int map[8][8]);
void countbomb(int i,int j,int map[8][8]);
//void Inputscreen(int **map);
void GameoverScreen();

int main(){

      int x,y;
      int map[8][8];
      int *b[8];
      char command;

      Initmap(map);
      Initscreen();
      for(x = 0; x < 8;x++){
            for(y = 0; y < 8;y++) b[x] = map[x];
      }
      while(1){
      Gamescreen(map);
      printf("Please enter a command:");
      scanf("%d %d %c",&x,&y,&command);
      checkbomb(x,y,map);
      }
}

//Display the game screen
void Gamescreen(int map[][8]){
      int i,j;
      printf("  0 1 2 3 4 5 6 7\n");
      for(i=0;i<8;i++){
            printf("%d ",i);
            for(j=0;j<8;j++){
                  if(map[i][j] == -1){ 
                        printf(". ");
                  }else if(map[i][j] == 0){
                        printf(" ");

                  }else{
                        printf("%d",map[i][j]);
                       
                  }
            }
            printf("\n");
            
      }
}
//Initialize the array
int Initmap(int map[][8]){
      int i,j;

      for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                  map[i][j] = -1;
            }
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
      if(i < 0 || j < 0 || i >= 9 || j >= 9)return;
      if(map[i][j] == 1){
            GameoverScreen();
      }
      if(map[i][j] == -1){
            countbomb(i,j,map);
      }

      if(map[i][j] == 0){
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

void countbomb(int i,int j,int map[][8]){
      int count=0;
      
            if(map[i-1][j-1] == 1)count++;
            if(map[i-1][j] == 1)count++;
            if(map[i-1][j+1] == 1)count++;
            if(map[i][j-1] == 1)count++;
            if(map[i][j+1] == 1)count++;
            if(map[i+1][j-1] == 1)count++;
            if(map[i+1][j] == 1)count++;
            if(map[i+1][j+1] == 1)count++;
            
            map[i][j] = count;
}


void GameoverScreen(){
      printf("\n");
      printf("GameOver");
      printf("\n\n");
      exit(0);
}
