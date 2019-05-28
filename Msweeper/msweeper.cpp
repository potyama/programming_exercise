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
      struct cell map[WIDTH][HEIGHT];
      int x,y,bomb=1;
      int open_count=0;
public:
      Mine();//コンストラクタ
      void Input_val();//値入力
      void Set_bomb();//爆弾設置
      void Open_map(int x,int y);//マスを開ける
      int Count_bomb(int x,int y);//周りに爆弾が何個あるかカウント
      void GameOverScreen();//ゲームオーバー
      void GameClearScreen();//ゲームクリア
      void Print_map();//現在のマップ表示
      void Judgment();//ゲームクリアしたかどうか
      void Set_flag(int x,int y);//フラグを立てる
      void Reset_flag(int x,int y);//フラグを下ろす

};
Mine::Mine(){
            printf("*** M Sweeper ***\n\
コマンドの入力:x y\n\
1を選択(mapを開ける)\n\
2を選択(flagを置く)\n\
x y … 座標[0-7]\n");

      printf("\n");

      for(int i=0;i<WIDTH;i++){
            for(int j=0;j<HEIGHT;j++){
                  map[i][j].open = false;
                  map[i][j].bomb = false;
                  map[i][j].flag = false;
                  map[i][j].count = -1;
            }
      }
      map[0][0].bomb = true;
}


void Mine::Input_val(){
      int tmp;
      printf("1:open 2:flag\n");
      scanf("%d",&tmp);
      
      if(tmp == 1){
            printf("Where to open?[x y]:");
            scanf("%d %d",&x,&y);
            Open_map(x,y);
      }else if(tmp == 2){
            printf("Where to put the flag?[x y]:");
            scanf("%d %d",&x,&y);
            if(map[x][y].flag == true){
                  Reset_flag(x,y);
            }else{
                  Set_flag(x,y);
            }
      }else{
            printf("Please select 1 or 2\n");
            printf("↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\n\n");
            Input_val();
      }
}

void Mine::Set_bomb(){
      srand((unsigned int) time(NULL));
      printf("How many bombs do you prepare?:");
      scanf("%d",&bomb);
      printf("%d\n",bomb);
      for(int i = 0;i < bomb;i++){
                 int x = (rand()) % 8;
                 int y = (rand()) % 8;
                 if(map[x][y].bomb == false){
                       map[x][y].bomb = true;
                 }else{
                       i--;
                 }
      }
}

void Mine::Open_map(int x,int y){
      if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || map[x][y].open == true)return;//枠でてたらreturn
      
      map[x][y].open = true;
      open_count++;

      if(map[x][y].bomb == true){
            GameOverScreen();
      }
      map[x][y].count = Count_bomb(x,y);
      
      if(map[x][y].count == 0){//深さ優先探索
            Open_map(x-1,y-1);
            Open_map(x-1,y);
            Open_map(x-1,y+1);
            Open_map(x,y-1);
            Open_map(x,y+1);
            Open_map(x+1,y-1);
            Open_map(x+1,y);
            Open_map(x+1,y+1);
      }
      return;
}

//枠出ないように
int Mine::Count_bomb(int x,int y){
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
            if(y < HEIGHT-1){
                  if(map[x-1][y+1].bomb == true){
                        count++;
                  }
            }
      }
      if(x < WIDTH-1){
            if(map[x+1][y].bomb == true){
                  count++;
            }
            if(0 < y){
                  if(map[x+1][y-1].bomb == true){
                        count++;
                  }
            }
            if(y < HEIGHT-1){
                  if(map[x+1][y+1].bomb == true){
                        count++;
                  }
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
      return count;
}

void Mine::Print_map(){
      printf("  0 1 2 3 4 5 6 7\n");
      for(int x = 0; x < WIDTH;x++){
            printf("%d ",x);
            for(int y = 0;y < HEIGHT;y++){
                  if(map[x][y].open == false){
                        if(map[x][y].flag == true){
                              printf("m ");
                        }else{
                              printf(". ");
                        }
                  }else{
                        printf("%1d ",map[x][y].count);
                  }
            }
            printf("\n");
      }
}

void Mine::Judgment(){
      if((WIDTH * HEIGHT) - bomb == open_count){
            GameClearScreen();
      }else{
            return;
      }
}

void Mine::GameClearScreen(){
      printf("GameClear!\n");
      Print_map();
      exit(0);
}

void Mine::GameOverScreen(){
      printf("GameOver\n");
      exit(0);
}

void Mine::Set_flag(int x,int y){
      map[x][y].flag = true;
}

void Mine::Reset_flag(int x,int y){
      map[x][y].flag = false;
}

int main(){
      Mine ms;
      ms.Set_bomb();
      for(;;){
      ms.Print_map();
      ms.Input_val();
      ms.Judgment();
      }            
}
