#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#define WIDTH 8
#define HEIGHT 8

using namespace std;


struct cell{
      bool open;//開けたかの判定用
      bool bomb;//爆弾の有無
      bool flag;//フラグの有無
      int count;//周りに爆弾が何個あるか
};

class Mine{
      int map[WIDTH][HEIGHT];
public:
      Mine();
      void Initialize_map();
      int set_bomb(int bomb);
      int open_amp(int x,int y);
      int count_bomb(int x,int y){
      void print_map();
      void setflag();
      void resetflag();
};

Mine::Mine(){
            printf("*** M Sweeper ***\n\
コマンドの入力:x y [m]\n\
x y … 座標[0-7]\n\\n\
m   … (x,y)にMマークをつける\n");
      printf("\n");
}

void Mine::Initialize_map(){
      for(int i=0;i<WIDTH;i++){
            for(int j=0;j<HEIGTH;j++){
                  map[i][j].open =false;
                  map[i][j].bomb = false;
                  map[i][j].flag = false;
                  map[i][j].count = -1;
            }
      }
      set_bomb(20);
}

Mine::set_bomb(int bomb){
      int count=0;
      for(int i = 0;i < WIDTH;i++){
            for(int j=0;j < HEIGHT;j++){
                 if(count > bomb)break;
                 map[i][j].bomb = true;
                 count++;
            }
      }
      for(int i = 0;i < WIDTH;i++){
            for(int j = 0;j < HEIGHT;j++){
                  if(count  < 0)break;
                  int x = (rand() % x);
                  int y = (rand() % y);
                  map[x][y].bomb=map[i][j].bomb;
                  count--;
            }
      }            
}

void Mine::open_map(int x,int y){
      if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || map[x][y].open == true)return;
      
      map[x][y].open = true;
      open_count++;

      if(map[x][y].bomb == true){
            GameOverScreen();
      }

      map[x][y].count = count_bomb(x,y);
      
      if(map[x][y].count == 0){
            open_map(x-1,y-1);
            open_map(x-1,y);
            open_map(x-1,y+1);
            open_map(x,y-1);
            open_map(x,y+1);
            open_map(x+1,y-1);
            open_map(x+1,y);
            open_map(x+1,y+1);
      }
      return;
}

//枠出ないように
int Mine::count_bomb(int x,int y){
      int count = 0;
      if(0 < x){
            if(map[x-1][y].bomb == true){
                  count++;
            }
            if(0 < y){
                  if(map[x-1][y-1].bomb == true){
                        count++;
                  }
            }
            if(y < HEIGTH-1){
                  if(map[x-1][y+1].bomb == true){
                        count++;
                  }
            }
      }
      if(x < WIDTH-1){
            if(map[x+1][y].bomb == true){
                  count++;
            }
            if(y < HEIGHT-1){
                  if(map[x+1][y+1].bomb == true){
                        count++;
                  }
            }
            if(0 < y){
                  if(map[x][y-1].bomb == true){
                        count++;
                  }
            }
            if(y < HEIGHT-1){
                  if(map[x][y+1].bomb == true){
                        count++;
                  }
            }
      }
      return count;
}

void Mine::print_map(){
      for(int x = 0; x < WIDTH;x++){
            printf("%d   ",x);
            for(int y = 0;y < HEIGTH;y++){
                  prinf("%d ",y);
                  if(map[x][y].open == false){
                        if(map[x][y].flag == true){
                              printf("m ");
                        }
                  }else if(map[x][y].open == true){
                        if(map[x][y].count >= 0){
                              printf("%d ",map[x][y].count);
                        }else{
                              printf("＊ ");
                        }
                  }
            }
            printf("\n");
      }
}

                        

void Mine::set_flag(int x,int y){
      map[x][y].flag = true;
}
void Mine::reset_flag(int x,int y){
      map[x][y].flag = false;
}

int main(){


}
