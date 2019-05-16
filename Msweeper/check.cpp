#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 10 	//一辺の長さ

struct cell {
	bool isOpened;
	int arroundBomb;
	bool isBomb;
	bool flag;
};

class MineSweeper {
	int bombs;	//地雷の個数
	int opened;	//開かれた個数
	struct cell field[LENGTH][LENGTH];
public:
	MineSweeper();
	void bomb_set(int n);
	int count_arrount_bombs(int x, int y);
	void print();
	int open(int x, int y);
	void setFlag(int x, int y);
	void resetFlag(int x, int y);
	void debugprint(void);
};

//座標の初期化をして、とりあえず、全部爆弾が無いことにしておく。
//コンストラクタなので、自動で呼ばれます
MineSweeper::MineSweeper()
{
	opened = 0;
	for (int i = 0; i < LENGTH; i++) {
		for(int j = 0; j < LENGTH; j++) {
			field[i][j].arroundBomb = 0;
			field[i][j].isOpened = false;
			field[i][j].isBomb = false;
			field[i][j].flag = false;
		}
	}
}

//引数nに指定された個数だけ、爆弾を仕掛ける。
//爆弾を仕掛ける座標は乱数で決める。（辺の長さで割った余りを求めれば絶対大丈夫）
void MineSweeper::bomb_set(int n)
{
	srand(time(NULL));
	bombs = n;
	for(int i = 0; i < n; i++) {
		int x = ( rand()) % LENGTH;
		int y = ( rand()) % LENGTH;
		field[x][y].isBomb = true;
	}
}

//x,yで指定された座標の周りの爆弾の個数を求める。
//もし地雷がそこに会った場合は、-1を返して、ゲームオーバーであることを知らせる、
int MineSweeper::count_arrount_bombs(int x, int y)
{
	int count = 0;
	if (field[x][y].isBomb == true)
		return -1;
	if (x < 0 || LENGTH <= x || y < 0 || LENGTH <= y )
		return -2;
	if (0 < x) {
		if (field[x-1][y].isBomb == true) {
			count++;
		}
		if (0 < y) {
			if (field[x-1][y-1].isBomb == true) {
				count++;
			}
		}
		if (y < LENGTH - 1) {
			if (field[x-1][y+1].isBomb == true) {
				count++;
			}
		}
	}
	if (x < LENGTH - 1) {
		if (field[x+1][y].isBomb == true) {
			count++;
		}
		if (0 < y) {
			if (field[x+1][y-1].isBomb == true) {
				count++;
			}
		}
		if (y < LENGTH - 1) {
			if (field[x-1][y+1].isBomb == true) {
				count++;
			}
		}
	}
	if (0 < y) {
		if (field[x][y-1].isBomb == true) {
			count++;
		}
	}
	if (y < LENGTH - 1) {
		if (field[x][y+1].isBomb == true) {
			count++;
		}
	}
	return count;
}

//デバッグ用。爆弾があるところはあると表示されるので、ゲームには使えない。
void MineSweeper::debugprint()
{
	for(int i = 0; i < LENGTH; i++) {
		for(int j = 0; j < LENGTH; j++) {
			if (field[i][j].isBomb == false) {
				printf("%c ", 'o');
			} else if (field[i][j].isBomb == true){
				printf("%c ", 'x');
			}
		}
		putchar('\n');
	}
}
//地雷があると印をつける
void MineSweeper::setFlag(int x, int y)
{
	field[x][y].flag = true;
}

//地雷の印を解除
void MineSweeper::resetFlag(int x, int y)
{
	field[x][y].flag = false;
}

//x,yの座標を開く処理
int MineSweeper::open(int x, int y)
{
	if (field[x][y].isBomb == true) {
		return -1;
	}

	field[x][y].isOpened = true;
	opened++;
	if (opened == LENGTH * LENGTH - bombs)
		return 1;
	
	field[x][y].arroundBomb = count_arrount_bombs(x, y);
	return 0;
}

//まだ開かれていない座標はoを表示、開かれている場合は、周囲の地雷の個数を表示。
void MineSweeper::print()
{
	for(int i = 0; i < LENGTH; i++) {
		for(int j = 0; j < LENGTH; j++) {
			if (field[i][j].isOpened == false) {
				if (field[i][j].flag == true) {
					printf("%c ", 'l');
				} else {
					printf("%c ", 'o');
				}
			} else {
				printf("%1d ", field[i][j].arroundBomb);
			}
		}
		putchar('\n');
	}
}
			
					

int main(void)
{
	int x, y;
	MineSweeper ms;
	ms.bomb_set(20);
	
	ms.debugprint();
	for(;;) {
		printf("Input the value of x:");
		scanf("%1d", &x);
		printf("Input the value of y:");
		scanf("%1d", &y);
		int result = ms.open(x, y);
		if (result == -1) {
			printf("Game Over\n");
			return 0;
		} else if (result == 1) {
			printf("success!\n");
			return 0;
		} else {
			ms.print();
		}
	}
}
