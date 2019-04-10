#include <stdio.h>

int Initmap(int map[8][8]);
void Initscreen();
void Gamescreen(int map[8][8]);
//int Inputscreen();

int main(){

      int x,y;
      int map[8][8];

      Initmap(map);
      Initscreen();

//      while(1){
            Gamescreen(map);
            //Inputscreen();
  //    }
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






