#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

#define COLUMN 8
#define ROW 4
void uncoverboard(int chessBoard[][COLUMN], int boardstate[][COLUMN]);//印出未覆蓋的盤面 
void firstBoard();//印出初始棋盤盤面 
void randomChess(int Board[][COLUMN]);//打亂棋子的function 
void printBoard(int chessBoard[][COLUMN], int boardstate[][COLUMN]);//印出第一回合後的棋盤盤面的function 
void openchess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xo, int yo);//翻開棋子的function 
void movechess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xs, int ys, int xe, int ye, int turn[1]);//移動或吃棋的function 

int main() {
	int chessBoard[ROW][COLUMN];//棋盤資料：兵、卒、將...... 
	int boardstate[ROW][COLUMN] = { 0 };//儲存棋子狀態的陣列，0是未翻開、1是翻開、2是空的 
	int xo, yo;//翻開的棋子座標 
	int xs, ys;//移動的棋子起點座標 
	int xe, ye;//移動的棋子終點座標 
	int playercolor;//紀錄玩家的顏色，1為玩家一黑、玩家二紅 ；2為玩家一紅、玩家二黑 
	int victory = 0;//紀錄勝利與否，1為是、2為否 
	int firstround = 1;//紀錄是否為第一回合，1為是、2為否 
	int turn[1] = { 0 };//判斷是玩家一或玩家二 
	char command;
	randomChess(chessBoard);
	uncoverboard(chessBoard, boardstate);
	firstBoard();
	cout << "遊戲開始" << endl;
	//第一回合
	do {
		cout << "玩家1 ( a : 翻牌 ， b : 移動或吃棋 ， c : 投降 )" << endl;
		cin >> command;
		if (command == 'a') {
			cout << "輸入位置：" << endl;
			cin >> xo >> yo;
			if (xo<4 && xo >= 0 && yo<8 && yo >= 0) {//判斷座標例外 
				boardstate[xo][yo] = 1;
				if (chessBoard[xo][yo] <= 16) {//紀錄玩家顏色
					playercolor = 1;
				}
				else if (chessBoard[xo][yo]>16) {
					playercolor = 2;
				}
				firstround = 0;
			}
			else {
				system("CLS");
				firstBoard();
				cout << "請輸入正確的座標!" << endl;
			}
		}
		else if (command == 'b') {//第一回合移動
			system("CLS");
			firstBoard();
			cout << "請先翻牌" << endl;
		}
		else if (command == 'c') {//第一回合投降
			system("CLS");
			firstBoard();
			cout << "玩家2 勝利!" << endl;
			firstround = 0;
			victory = 1;
		}
		else {//錯誤指令
			system("CLS");
			firstBoard();
			cout << "請輸入有效的指令!" << endl;
		}
	} while (firstround != 0);
	if(firstround == 0 && command == 'a') {
		system("CLS");
		printBoard(chessBoard, boardstate);//印出第一回合後的盤面
	}	
	while (victory != 1) {
		if (turn[0] % 2 == 1) {//判斷玩家顏色以及回合
			if (playercolor == 1)		cout << "玩家1(黑棋)回合 ( a : 翻牌 ， b : 移動或吃棋 ， c : 投降 )" << endl;
			else if (playercolor == 2)	cout << "玩家1(紅棋)回合 ( a : 翻牌 ， b : 移動或吃棋 ， c : 投降 )" << endl;
		}
		if (turn[0] % 2 == 0) {
			if (playercolor == 1)		cout << "玩家2(紅棋)回合 ( a : 翻牌 ， b : 移動或吃棋 ， c : 投降 )" << endl;
			else if (playercolor == 2)	cout << "玩家2(黑棋)回合 ( a : 翻牌 ， b : 移動或吃棋 ， c : 投降 )" << endl;
		}
		cin >> command;
		if (command == 'a') {
			cout << "輸入位置：" << endl;
			cin >> xo >> yo;
			if (xo<4 && xo >= 0 && yo<8 && yo >= 0) {//判斷座標錯誤例外
				system("CLS");
				if (boardstate[xo][yo] == 0)turn[0]++;
				openchess(boardstate, chessBoard, xo, yo);
			}
			else {
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請輸入正確的座標!" << endl;
			}
		}
		else if (command == 'b') {
			cout << "想移動的棋子位置：" << endl;
			cin >> xs >> ys;
			if (xs<4 && xs >= 0 && ys<8 && ys >= 0) {//判斷座標錯誤例外 
				if (boardstate[xs][ys] == 0) {//未翻開的棋子
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "棋子未翻開" << endl;
					continue;
				}
				else if (boardstate[xs][ys] == 2) {//空的格子
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "空的格子" << endl;
					continue;
				}
				else if (boardstate[xs][ys] == 1) {
					//控制錯誤顏色例外 
					if (turn[0] % 2 == 1) {
						if (playercolor == 1 && chessBoard[xs][ys]>16) {//黑棋控紅棋
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "請控制自己的棋子" << endl; 
							continue;
						}
						else if (playercolor == 2 && chessBoard[xs][ys] <= 16) {//紅棋控黑棋 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "請控制自己的棋子" << endl;
							continue;
						}
					}
					if (turn[0] % 2 == 0) {
						if (playercolor == 1 && chessBoard[xs][ys] <= 16) {//紅棋控黑棋
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "請控制自己的棋子" << endl;
							continue;
						}
						else if (playercolor == 2 && chessBoard[xs][ys]>16) {//黑棋控紅棋  
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "請控制自己的棋子" << endl;
							continue;
						}
					}
					cout << "想移動的目標位置：" << endl;
					cin >> xe >> ye;
					if (xe<4 && xe >= 0 && ye<8 && ye >= 0) {//座標錯誤例外 
						if (xs != xe&&ys != ye) {//斜走例外 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "請勿斜走" << endl;
							continue;
						}
						else if (xs == xe&&ys == ye) {//輸入相同座標例外 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "座標重複" << endl;
							continue;
						}
						else {
							if (boardstate[xe][ye] == 0) {//目標棋子未翻開
								system("CLS");
								printBoard(chessBoard, boardstate);
								cout << "目標位置的棋子未翻開" << endl;
								continue;
							}
							else if (boardstate[xe][ye] == 1) {//目標棋子已翻開
								movechess(boardstate, chessBoard, xs, ys, xe, ye, turn);
							}
							else if (boardstate[xe][ye] == 2) {//目標沒有棋子
								movechess(boardstate, chessBoard, xs, ys, xe, ye, turn);
							}
						}
					}
					else {
						system("CLS");
						printBoard(chessBoard, boardstate);
						cout << "請輸入正確的座標!" << endl;
						continue;
					}
				}
			}
			else {
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請輸入正確的座標!" << endl;
				continue;
			}
		}
		else if (command == 'c') {//投降
			if (turn[0] % 2 == 1)cout << "玩家2 勝利!" << endl;
			if (turn[0] % 2 == 0)cout << "玩家1 勝利!" << endl;
			victory = 1;//紀錄勝利
		}
		else {
			system("CLS");
			printBoard(chessBoard, boardstate);
			cout << "請輸入有效的指令!" << endl;
		}
		//未經過投降的勝利判定
		int blackcount = 0, redcount = 0;
		for (int i = 0; i<ROW; i++) {//計算各顏色剩餘的棋子
			for (int j = 0; j<COLUMN; j++) {
				if (chessBoard[i][j] <= 16 && chessBoard[i][j]>0)blackcount++;
				else if (chessBoard[i][j]>16 && chessBoard[i][j] <= 32)redcount++;
			}
		}
		if (blackcount == 0) {//剩餘棋子為0者落敗
			if (playercolor == 1)cout << "玩家2 勝利!" << endl;
			else if (playercolor == 2)cout << "玩家1 勝利!" << endl;
			victory = 1;
		}
		else if (redcount == 0) {
			if (playercolor == 1)cout << "玩家1 勝利!" << endl;
			else if (playercolor == 2)cout << "玩家2 勝利!" << endl;
			victory = 1;
		}
	}
	//printBoard(chessBoard);
	return 0;
}
//移動或吃棋的function 
void movechess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xs, int ys, int xe, int ye, int turn[1]) {
	if (boardstate[xe][ye] == 1) {//目標棋子已經翻開
		if (chessBoard[xs][ys] >= 1 && chessBoard[xs][ys] <= 5) {//卒 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃例外
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 21) {//卒吃兵
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else if (chessBoard[xe][ye] == 32) {//卒吃帥
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 6 || chessBoard[xs][ys] == 7) {//包 
			int middlechesscount = 0;//紀錄包和目標棋子之間的棋子個數
			if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請勿同色互吃" << endl;
			}
			else if ((xs - xe)>1) {
				for (int i = xe + 1; i<xs; i++) {//計算包和目標棋子之間的棋子個數
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((xe - xs)>1) {
				for (int i = xs + 1; i<xe; i++) {//計算包和目標棋子之間的棋子個數
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((ys - ye)>1) {
				for (int i = ye + 1; i<ys; i++) {//計算包和目標棋子之間的棋子個數
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {
					system("CLS");//違反規則
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((ye - ys)>1) {
				for (int i = ys + 1; i<ye; i++) {//計算包和目標棋子之間的棋子個數
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else {//違反規則
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "違反包的移動規則" << endl;
			}
		}
		if (chessBoard[xs][ys] == 8 || chessBoard[xs][ys] == 9) {//馬 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 25)) {//吃比馬小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 10 || chessBoard[xs][ys] == 11) {//車 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 27)) {//吃比車小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 12 || chessBoard[xs][ys] == 13) {//象 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 29)) {//吃比象小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 14 || chessBoard[xs][ys] == 15) {//士 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 31)) {//吃比士小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 16) {//將 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 22 && chessBoard[xe][ye] <= 32)) {//吃比將小的棋，除了兵
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//將吃兵
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] >= 17 && chessBoard[xs][ys] <= 21) {//兵 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				if (chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 5) {//兵吃卒
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else if (chessBoard[xe][ye] == 16) {//兵吃將
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 22 || chessBoard[xs][ys] == 23) {//炮 
			int middlechesscount = 0;//紀錄炮和目標棋子之間的棋子個數
			if (chessBoard[xe][ye] <= 32 && chessBoard[xe][ye] >= 17) {//同色互吃
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請勿同色互吃" << endl;
			}
			else if ((xs - xe)>1) {
				for (int i = xe + 1; i<xs; i++) {//計算炮和目標棋子之間的棋子個數
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((xe - xs)>1) {
				for (int i = xs + 1; i<xe; i++) {//計算炮和目標棋子之間的棋子個數
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((ys - ye)>1) {
				for (int i = ye + 1; i<ys; i++) {//計算炮和目標棋子之間的棋子個數
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else if ((ye - ys)>1) {
				for (int i = ys + 1; i<ye; i++) {//計算炮和目標棋子之間的棋子個數
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//合乎規則
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//違反規則
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "違反包的移動規則" << endl;
				}
			}
			else {//違反規則
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "違反包的移動規則" << endl;
			}
		}
		if (chessBoard[xs][ys] == 24 || chessBoard[xs][ys] == 25) {//傌 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 9)) {//傌吃比自己小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 26 || chessBoard[xs][ys] == 27) {//陣 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 11)) {//吃比陣小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 28 || chessBoard[xs][ys] == 29) {//相 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 13)) {//吃比相小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 30 || chessBoard[xs][ys] == 31) {//仕 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 15)) {//吃比仕小的棋
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//小吃大
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
		if (chessBoard[xs][ys] == 32) {//帥 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//同色互吃
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿同色互吃" << endl;
				}
				else if ((chessBoard[xe][ye] >= 6 && chessBoard[xe][ye] <= 16)) {//吃比帥小的棋，除了卒
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//帥吃卒
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "請勿以小吃大" << endl;
				}
			}
			else {//移動超過一格
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "請一次移動一格" << endl;
			}
		}
	}
	else if (boardstate[xe][ye] == 2) {//目標是空的
		chessBoard[xe][ye] = chessBoard[xs][ys];
		chessBoard[xs][ys] = 0;
		boardstate[xe][ye] = 1;
		boardstate[xs][ys] = 2;
		system("CLS");
		printBoard(chessBoard, boardstate);
		turn[0]++;
	}
}

void openchess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xo, int yo) {//翻開棋子的function
	if (boardstate[xo][yo] == 0) {//目標未翻開
		boardstate[xo][yo] = 1;
		system("CLS");
		printBoard(chessBoard, boardstate);
	}
	else if (boardstate[xo][yo] == 1) {//目標已翻開
		system("CLS");
		printBoard(chessBoard, boardstate);
		cout << "已經翻開了" << endl;
	}
	else if (boardstate[xo][yo] == 2) {//目標是空的
		system("CLS");
		printBoard(chessBoard, boardstate);
		cout << "是空的格子" << endl;
	}
}

void printBoard(int chessBoard[][COLUMN], int boardstate[][COLUMN]) {//印出第一回合後的棋盤的function
	cout << "    0   1   2   3   4   5   6   7 " << endl;
	for (int i = 0; i < 4; i++) {
		cout << i;
		for (int j = 0; j < 8; j++) {
			if (boardstate[i][j] == 0)cout << "  ◎";
			if (boardstate[i][j] == 1) {
				if (chessBoard[i][j] >= 1 && chessBoard[i][j] <= 5)		cout << setw(4) << "卒";
				if (chessBoard[i][j] == 6 || chessBoard[i][j] == 7)		cout << setw(4) << "包";
				if (chessBoard[i][j] == 8 || chessBoard[i][j] == 9)		cout << setw(4) << "馬";
				if (chessBoard[i][j] == 10 || chessBoard[i][j] == 11)	cout << setw(4) << "車";
				if (chessBoard[i][j] == 12 || chessBoard[i][j] == 13)	cout << setw(4) << "象";
				if (chessBoard[i][j] == 14 || chessBoard[i][j] == 15)	cout << setw(4) << "士";
				if (chessBoard[i][j] == 16)								cout << setw(4) << "將";
				if (chessBoard[i][j] >= 17 && chessBoard[i][j] <= 21)	cout << setw(4) << "兵";
				if (chessBoard[i][j] == 22 || chessBoard[i][j] == 23)	cout << setw(4) << "炮";
				if (chessBoard[i][j] == 24 || chessBoard[i][j] == 25)	cout << setw(4) << "傌";
				if (chessBoard[i][j] == 26 || chessBoard[i][j] == 27)	cout << setw(4) << "陣";
				if (chessBoard[i][j] == 28 || chessBoard[i][j] == 29)	cout << setw(4) << "相";
				if (chessBoard[i][j] == 30 || chessBoard[i][j] == 31)	cout << setw(4) << "仕";
				if (chessBoard[i][j] == 32)								cout << setw(4) << "帥";
			}
			if (boardstate[i][j] == 2) {
				cout << "    ";
			}
		}
		cout << endl;
	}
}

void randomChess(int Board[][COLUMN]) {//讓棋子隨機擺放的function
	int chessnumber[32];
	for (int i = 0; i < 32; i++) {
		chessnumber[i] = i + 1;
	}
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			Board[i][j] = chessnumber[i * 8 + j];
		}
	}
	srand(time(NULL));
	int randcolumn, randrow;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			randcolumn = rand() % COLUMN;//目標棋子與隨機棋子交換位置
			randrow = rand() % ROW;
			int temp = Board[i][j];
			Board[i][j] = Board[randrow][randcolumn];
			Board[randrow][randcolumn] = temp;
		}
	}
}

void uncoverboard(int chessBoard[][COLUMN], int boardstate[][COLUMN]){
	cout << "    0   1   2   3   4   5   6   7 " << endl;
	for (int i = 0; i < 4; i++) {
		cout << i;
		for (int j = 0; j < 8; j++) {
			if (chessBoard[i][j] >= 1 && chessBoard[i][j] <= 5)		cout << setw(4) << "卒";
			if (chessBoard[i][j] == 6 || chessBoard[i][j] == 7)		cout << setw(4) << "包";
			if (chessBoard[i][j] == 8 || chessBoard[i][j] == 9)		cout << setw(4) << "馬";
			if (chessBoard[i][j] == 10 || chessBoard[i][j] == 11)	cout << setw(4) << "車";
			if (chessBoard[i][j] == 12 || chessBoard[i][j] == 13)	cout << setw(4) << "象";
			if (chessBoard[i][j] == 14 || chessBoard[i][j] == 15)	cout << setw(4) << "士";
			if (chessBoard[i][j] == 16)								cout << setw(4) << "將";
			if (chessBoard[i][j] >= 17 && chessBoard[i][j] <= 21)	cout << setw(4) << "兵";
			if (chessBoard[i][j] == 22 || chessBoard[i][j] == 23)	cout << setw(4) << "炮";
			if (chessBoard[i][j] == 24 || chessBoard[i][j] == 25)	cout << setw(4) << "傌";
			if (chessBoard[i][j] == 26 || chessBoard[i][j] == 27)	cout << setw(4) << "陣";
			if (chessBoard[i][j] == 28 || chessBoard[i][j] == 29)	cout << setw(4) << "相";
			if (chessBoard[i][j] == 30 || chessBoard[i][j] == 31)	cout << setw(4) << "仕";
			if (chessBoard[i][j] == 32)								cout << setw(4) << "帥";
		}
		cout << endl; 
	}
}

void firstBoard() {//印出第一回合的盤面
	cout << "    0   1   2   3   4   5   6   7 " << endl;
	for (int i = 0; i < 4; i++) {
		cout << i;
		for (int j = 0; j < 8; j++) {
			cout << "  ◎";
		}
		cout << endl;
	}
}
