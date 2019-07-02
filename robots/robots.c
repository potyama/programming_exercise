#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 20
#define Y 60
#define NONE 0
#define PLAYER 1
#define ENEMY 2

typedef struct robots{
  int x;
  int y;
} robots;

//extern char getChar(void);

void Map_init(int map[X][Y]);
void Enemy(int map[X][Y],int level);
void State(int map[X][Y],int level,robots player);
void Display(int map[X][Y],int level,robots player);
void Player(int map[X][Y],robots *player,int input);
int Input_direction(void);

int main(void){
      robots player;

      int map[X][Y];
      int input;
      int level;
      char dummy;

      player.x = player.y = 0;
      level = 1;
      Map_init(map);
      Enemy(map,level);

  while(1){
    State(map,level,player);
    Display(map,level,player);
    //input = Input_direction();
    printf("Input Direction : ");
    scanf("%d%c",&input,&dummy);
    Player(map,&player,input);
  }

  return 0;
}

void Map_init(int map[X][Y]){

      for(int x = 0; x <= X; x++){
            for(int y = 0; y <= Y; y++){
                  map[x][y] = NONE;
            }
      }
}

void Enemy(int map[X][Y],int level){
      int i,x=0,y=0;
      int tmp;
      srand((unsigned)time(NULL));

      for(i = 0;i < 5*level;i++){
            map[0][i+1] =  ENEMY;
      }
      for(i=0;i<5*level;i++){
            x = (rand()) % X;
            y = (rand()) % Y;
            tmp = map[0][i+1];
            map[0][i+1] = map[x][y];
            map[x][y] = tmp;
      }
}

void State(int map[X][Y],int level,robots player){
      int i,j,x,y;
      int flag = 0;
      int tmp;

      for(i=0; i<X; i++){
            for(j=0; j<Y; j++){

            if(i == player.x && j == player.y){
	            map[i][j] = PLAYER;
                  x = i;
                  y = j;
                  flag = 1;
            }
            if((i != player.x || j != player.y )&& map[i][j] != ENEMY){
                  map[i][j] = NONE;
            }
            if(map[i][j] == ENEMY){
                  if(x > i){

                  flag = 1;
      /*for(k=0; k<5*level; k++){
	      if(i==enemy[k].x && j==enemy[k].y){
	            map[i][j] = ENEMY;
	            flag = 1;
            }
	}*/
            if(flag == 0) map[i][j] = NONE;
            flag = 0;
    }
  }

}

void Display(int map[X][Y],int level,robots player){

      printf("+");
      for(int i = 0; i <= Y; i++)printf("-");
      
      printf("+\n");

      for(int i = 0; i <= X; i++){
            printf("|");
            for(int j = 0; j <= Y; j++){
                  if(map[i][j] == NONE){
	                  printf(" ");
                  }else if(map[i][j] == PLAYER){
                  //      printf("map[%d][%d]==%d\n",i,j,map[i][j]);
	                  printf("@");
                  }else if(map[i][j] == ENEMY){
	                  printf("+");
                  }else{
                        printf("?");
                  }
            }
            printf("|\n");
      }

      printf("+");
      for(int i = 0; i <= Y; i++) printf("-");
      printf("+");

      printf("\n");
}

/*int Input_direction(void)
{
  int gets;

  printf("Input Direction : ?
  gets = getChar()-'0';
  printf("Your Input %d

  return gets;
}*/

void Player(int map[X][Y],robots *player,int input){
      srand((unsigned)time(NULL));
      switch(input){
            case 0:
                  player -> x = rand()%X;
                  player -> y = rand()%Y;
                  while(map[player -> x][player -> y] == ENEMY || map[player -> x][player -> y] == PLAYER){
                        player -> x = rand()%X;
                        player -> y = rand()%Y;
                  }
                  break;
            case 1: 
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  if(player -> y > 0){
                        player -> y -= 1;
                  }
                  break;
            case 2:
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  break;
            case 3:
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  if(player -> y < 60){
                      player -> y += 1;
                  }
                  break; 
            case 4:
                  if(player -> y > 0){
                        player -> y -= 1;
                  }
                  break;
            case 6:
                  if(player -> y < 60){
                        player -> y += 1;
                  }
                  break;
            case 7:
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  if(player -> y > 0){
                        player -> y -= 1;
                  }
                  break;
            case 8:
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  break;
            case 9:
                  if(player -> y < 60){
                        player -> y += 1;
                  }
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  break;
            default:
                  break;
      
      }
}
