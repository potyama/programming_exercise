#include <iostream>
#define END -1
#define GameOver -2
struct cell{
      bool check;//開けたかの判定　-1だと開いていない|0だと開いている
      int count = 0;//爆弾の数　countbombで数えている。
      bool bomb;//そのマスにbombがあるかどうか false ない|true ある
      bool flag;//旗　false 旗を置いていない |true 旗を置いている
};


class Mine{
      struct cell map[8][8];
public:
      Mine();
      void debugprint();
      void Initscreen();
      void bombset(int n);
      void Gamescreen();
      void checkbomb(int i,int j);
      int countbomb(int i,int j);
      void GameoverScreen(int i,int j);
      void setflag(int x,int y);
      void resetflag(int x,int y);
      int option(int x,int y,char a);
      void check();
};

//Display the input screen
Mine::Mine(){
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
                  map[i][j].check =false;
                  map[i][j].count = 0;
            }
      }
}

void Mine::bombset(int n){
      srand(time(NULL));
      int i,j,count=0,count2=0;
      bool tmp;

      for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                  if(count >= n)break;
                 map[i][j].bomb = true;
                 count++;
           }
      }
      for(i=0;i<8;i++){
           for(j=0;j<8;j++){
                 if(count2 >= n)break;
                  int x = (rand() % 8);
                  int y = (rand() % 8);
                  tmp = map[i][j].bomb;
                  map[i][j].bomb = map[x][y].bomb;
                  map[x][y].bomb = tmp;
                  printf("change map[%d][%d] = map[%d][%d] : %d = %d\n",i,j,x,y,map[i][j].bomb,map[x][y].bomb);
                  count2++;
           }
     }

      for(i=0;i<8;i++){
           for(j=0;j<8;j++){
                 printf("map[%d][%d].bomb=%di\n",i,j,map[i][j].bomb);
           }
      }
}


//Display the game screen
void Mine::Gamescreen(){
      printf("  0 1 2 3 4 5 6 7\n");
      for(int i=0;i<8;i++){
            printf("%d ",i);
            for(int j=0;j<8;j++){
                  if(map[i][j].check == false) {
                        if(map[i][j].flag == true){
                              printf("m ");
                        }else{
                              printf(". ");
                  }
            }else{
                  printf("%1d ",map[i][j].count);
            }
      }
      printf("\n");
      }
}
void Mine::debugprint()
{
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if (map[i][j].bomb == false) {
				printf("%c ", 'o');
			} else if (map[i][j].bomb == true){
				printf("%c ", 'x');
			}
		}
		putchar('\n');
	}
}
//Check bomb
void Mine::checkbomb(int i,int j){
      if(i < 0 || i >= 8 || j < 0 || j >= 8 || map[i][j].check == true)return;
      printf("map[%d][%d] = %d\n",i,j,map[i][j].bomb);
            map[i][j].count = countbomb(i,j);
            map[i][j].check = true;
            i++;
      
      if(map[i][j].bomb == 1){
            GameoverScreen(i,j);
      }

      if(map[i][j].count == 0){
  //          printf("左上\n");
            checkbomb(i-1,j-1);
    //        printf("上\n");
            checkbomb(i-1,j);
      //      printf("右上\n");
            checkbomb(i-1,j+1);
        //    printf("左\n");
            checkbomb(i,j-1);
          //  printf("右\n");
            checkbomb(i,j+1);
            //printf("左下\n");
            checkbomb(i+1,j-1);
            //printf("下\n");
            checkbomb(i+1,j);
            //printf("右上");
            checkbomb(i+1,j+1);
      }
      return;
}

int Mine::countbomb(int x,int y){
      int count=0;

      if(0 < x){
		if(map[x-1][y].bomb == true){
			count++;
		}
		if(0 < y){
			if(map[x-1][y-1].bomb == true){
				count++;
			}
		}
		if(y < 7){
			if(map[x-1][y+1].bomb == true){
				count++;
			}
		}
	}
	if(x < 7){
		if(map[x+1][y].bomb == true){
			count++;
            }
		if(0 < y){
			if (map[x+1][y-1].bomb == true){
				count++;
			}
		}
		if(y < 7){
			if(map[x+1][y+1].bomb == true){
				count++;
			}
		}
	}
	if (0 < y) {
		if (map[x][y-1].bomb == true) {
			count++;
		}
	}
	if (y < 7) {
		if (map[x][y+1].bomb == true) {
			count++;
		}
	}
	return count;
}


void Mine::GameoverScreen(int i,int j){
      if(map[i][j].bomb == false)return;
      printf("\n");
      printf("GameOver");
      printf("\n\n");
      exit(0);
}
int Mine::option(int x,int y,char a){
      if(a == 'm'){
            if(map[x][y].flag == false){
                  setflag(x,y);
                  return 0;
            }else{
                  resetflag(x,y);
                  return 0;
            }
      }
      return 1;
}

void Mine::setflag(int x,int y){
      map[x][y].flag = true;
}
void Mine::resetflag(int x,int y){
      map[x][y].flag = false;
}

void Mine::check(){
      int flag = 0;
      for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                  if(i == 8 * 8 - 1)flag = 1;
            }
      }
      if(flag == 0){
            return;
      }else{
            printf("Success!!!\n");
            exit(0);
      }
}


int main(){
      int x=0,y=0,flag = 0;
      char a;
      Mine ms;
      ms.bombset(20);
      while(1){
           // ms.Gamescreen();
            ms.debugprint();
            printf("Please enter a command:");
            scanf("%d %d %c",&x,&y,&a);
            flag = ms.option(x,y,a);
            printf("%d",flag);
            if(flag == 1){
                  ms.checkbomb(x,y);
                  ms.check();
            }
      }
}


