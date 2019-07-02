#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 20
#define Y 60
#define NONE 0
#define PLAYER 1
#define ENEMY 2
#define OUT 3
#define SCRAP 4
#define WARP 5

typedef struct robots{
  int x;
  int y;
} robots;

extern char getChar(void);

void Map_init(int map[X][Y]);
void Enemy_make(int map[X][Y],int level);
int State(int map[X][Y],int level,int score,robots player);
void Display(int map[X][Y],int level,int score,robots player);
void Enemy(int map[X][Y],int x,int y,int level,robots player);
void GameOver(int map[X][Y],int level,int score,robots player);
int check(int map[X][Y],int level,int score);
int Player(int map[X][Y],robots *player,int input,int level);

int main(void){
      robots player;

      int map[X][Y];
      char input;
      int level;
      int score;
      int flag;
      int up;

      player.x = player.y = 0;
      level = 1;
      Map_init(map);
      Enemy_make(map,level);
      map[0][0] = PLAYER;
  
      while(1){
            up = State(map,level,score,player); 
            if(up == 1){
                  if(level <= 8){
                        score = (5*level) +(level * 10);
                  }else{
                        score = 40 + (level * 10);
                  }
                  level++;
            }else{
                  score = up;
            }
            Display(map,level,score,player);
            printf("Input Direction :\n ");
            input = getChar();
            printf("%c\n",input);
            flag = Player(map,&player,input,level);
            if(flag == OUT)GameOver(map,level,score,player);
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

void Enemy_make(int map[X][Y],int level){
      int i,j,k=0,x=0,y=0;
      int tmp;
      srand((unsigned)time(NULL));
      
      for(j = 0;j < level;j++){
            if(k*level > 40)break; 
            k+=5;
      }
      for(i = 0;i < k;i++){
            map[0][i+1] = ENEMY;
      }
      for(i=0;i<5*level;i++){
            x = (rand()) % X;
            y = (rand()) % Y;
            tmp = map[0][i+1];
            map[0][i+1] = map[x][y];
            map[x][y] = tmp;
      }
}

int State(int map[X][Y],int level,int score,robots player){
      int i,j,m,l,x,y;
      int levelup = 0;
      int flag = 0;

      for(i=0; i<X; i++){
            for(j=0; j<Y; j++){
            if(i == player.x && j == player.y){
                  x = i;
                  y = j;
                  map[x][y] = PLAYER;
                  flag = 1;
            }
            if(i != player.x || j != player.y){
                  if(map[i][j] != ENEMY && map[i][j] != SCRAP){
                        map[i][j] = NONE;
                  }
            }
            
            if(map[i][j] == ENEMY || map[i][j] == SCRAP)flag = 1;
            
            if(flag == 0) map[i][j] = NONE;
            
            flag = 0;
            }
      }
      Enemy(map,x,y,level,player);
      for(i = 0;i < X; i++){
            for(j = 0;j < Y; j++){
                 if(map[i][j] == OUT)GameOver(map,level,score,player);
            }
      } 
      flag = check(map,level,score);
      if(flag == 0){
            level++;
            Map_init(map);
            map[0][0] = PLAYER;
            Enemy_make(map,level);
            levelup = 1;
      }else{
            return score;
      }
      return levelup;
}

void Display(int map[X][Y],int level,int score,robots player){

      printf("+");
      for(int i = 0; i <= Y; i++)printf("-");
      
      printf("+\n");

      for(int i = 0; i <= X; i++){
            printf("|");
            for(int j = 0; j <= Y; j++){
                  if(map[i][j] == NONE){
	                  printf(" ");
                  }else if(map[i][j] == PLAYER){
	                  printf("@");
                  }else if(map[i][j] == ENEMY){
	                  printf("+");
                  }else if(map[i][j] == SCRAP){
                        printf("*");
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
      printf("(level:%d score:%d):?",level,score);
}

int Player(int map[X][Y],robots *player,int input,int level){
      int i=0;
      int flag = 0;
      srand((unsigned)time(NULL));
      switch(input - '0'){
            case 0:
                  map[player -> x][player -> y] = NONE;
                  player -> x = rand()%X;
                  player -> y = rand()%Y;
                  while(map[player -> x][player -> y] == SCRAP || map[player -> x][player -> y] == ENEMY){
                        player -> x = rand()%X;
                        player -> y = rand()%Y;
                  }
                  map[player -> x][player -> y] = PLAYER ;
                  break;
            case 1: 
                  map[player -> x][player -> y] = NONE;
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  if(player -> y > 0){
                        player -> y -= 1;
                  }if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 2:
                  map[player -> x][player -> y] = NONE;
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 3:
                  map[player -> x][player -> y] = NONE;
                  if(player -> x < 20){
                        player -> x += 1;
                  }
                  if(player -> y < 60){
                      player -> y += 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break; 
            case 4:
                  map[player -> x][player -> y] = NONE;
                  if(player -> y > 0){
                        player -> y -= 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 6:
                  map[player -> x][player -> y] = NONE;
                  if(player -> y < 60){
                        player -> y += 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 7:
                  map[player -> x][player -> y] = NONE;
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  if(player -> y > 0){
                        player -> y -= 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 8:
                  map[player -> x][player -> y] = NONE;
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            case 9:
                  map[player -> x][player -> y] = NONE;
                  if(player -> y < 60){
                        player -> y += 1;
                  }
                  if(player -> x > 0){
                        player -> x -= 1;
                  }
                  if(map[player -> x][player -> y] == ENEMY){
                        map[player -> x][player -> y] == OUT;
                  }else{
                        map[player -> x][player -> y] == PLAYER;
                  }
                  break;
            default:
                  break;
      }
      if(map[player -> x][player -> y] == OUT)return OUT;
}

void Enemy(int map[X][Y],int x,int y,int level,robots player){
      int i,j;
      for(i = 0; i < X; i++){
            for(j = 0; j < Y; j++){
                  if(map[i][j] == ENEMY){
                        if(x > i){
                              if(y > j){
                                    if(map[i+1][j+1] == ENEMY || map[i+1][j+1] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i+1][j+1] = SCRAP;
                                    }else{
                                          map[i+1][j+1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                               }else if(y == j){
                                    if(map[i+1][j] == ENEMY || map[i+1][j] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i+1][j] = SCRAP;
                                    }else{
                                          map[i+1][j] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }else{
                                    if(map[i+1][j-1] == ENEMY || map[i+1][j-1] == SCRAP){
                                          map[i][j] = SCRAP;
                                          map[i+1][j-1] = SCRAP;
                                    }else{
                                          map[i+1][j-1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }
                        }else if(x == i){
                              if(y > j){
                                    if(map[i][j+1] == ENEMY || map[i][j+1] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i][j+1] = SCRAP;
                                    }else{
                                          map[i][j+1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }else if(y < j){
                                    if(map[i][j-1] == ENEMY || map[i][j-1] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i][j-1] = SCRAP;
                                    }else{
                                          map[i][j-1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }
                        }else{
                              if(y > j){
                                    if(map[i-1][j+1] == ENEMY || map[i-1][j+1] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i-1][j+1] = SCRAP;
                                    }else{
                                          map[i-1][j+1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }else if(y == j){
                                    if(map[i-1][j] == ENEMY || map[i-1][j] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i-1][j] = SCRAP;
                                    }else{
                                          map[i-1][j] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }else{
                                    if(map[i-1][j-1] == ENEMY || map[i-1][j-1] == SCRAP){
                                          map[i][j] = NONE;
                                          map[i-1][j-1] = SCRAP;
                                    }else{
                                          map[i-1][j-1] += map[i][j];
                                          map[i][j] = NONE;
                                    }
                              }
                        }
                  }
            }
      } 
}
                 
int check(int map[X][Y],int level,int score){
      int i,j;
      int flag = 0;

      for(i = 0;i < X;i++){
            for(j = 0; j < Y;j++){
                  if(map[i][j] == ENEMY){
                        flag = 1;
                        score++;
                  }
                  if(map[i][j] == SCRAP)score++;
            }
      }
      if(flag == 0){
            level++;
            printf("GameClear!!\n");
            printf("Next Level is %d\n",level);
      }else{
            return score;
      }           
      return flag;
}      

void GameOver(int map[X][Y],int level,int score,robots player){
      printf("result -----------------------------------------\n\n\n\n\n");
      Display(map,level,score,player);
      printf("GameOver......");
      exit(0);
}
