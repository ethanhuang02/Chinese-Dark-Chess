#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

#define COLUMN 8
#define ROW 4
void uncoverboard(int chessBoard[][COLUMN], int boardstate[][COLUMN]);//�L�X���л\���L�� 
void firstBoard();//�L�X��l�ѽL�L�� 
void randomChess(int Board[][COLUMN]);//���ôѤl��function 
void printBoard(int chessBoard[][COLUMN], int boardstate[][COLUMN]);//�L�X�Ĥ@�^�X�᪺�ѽL�L����function 
void openchess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xo, int yo);//½�}�Ѥl��function 
void movechess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xs, int ys, int xe, int ye, int turn[1]);//���ʩΦY�Ѫ�function 

int main() {
	int chessBoard[ROW][COLUMN];//�ѽL��ơG�L�B��B�N...... 
	int boardstate[ROW][COLUMN] = { 0 };//�x�s�Ѥl���A���}�C�A0�O��½�}�B1�O½�}�B2�O�Ū� 
	int xo, yo;//½�}���Ѥl�y�� 
	int xs, ys;//���ʪ��Ѥl�_�I�y�� 
	int xe, ye;//���ʪ��Ѥl���I�y�� 
	int playercolor;//�������a���C��A1�����a�@�¡B���a�G�� �F2�����a�@���B���a�G�� 
	int victory = 0;//�����ӧQ�P�_�A1���O�B2���_ 
	int firstround = 1;//�����O�_���Ĥ@�^�X�A1���O�B2���_ 
	int turn[1] = { 0 };//�P�_�O���a�@�Ϊ��a�G 
	char command;
	randomChess(chessBoard);
	uncoverboard(chessBoard, boardstate);
	firstBoard();
	cout << "�C���}�l" << endl;
	//�Ĥ@�^�X
	do {
		cout << "���a1 ( a : ½�P �A b : ���ʩΦY�� �A c : �뭰 )" << endl;
		cin >> command;
		if (command == 'a') {
			cout << "��J��m�G" << endl;
			cin >> xo >> yo;
			if (xo<4 && xo >= 0 && yo<8 && yo >= 0) {//�P�_�y�Шҥ~ 
				boardstate[xo][yo] = 1;
				if (chessBoard[xo][yo] <= 16) {//�������a�C��
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
				cout << "�п�J���T���y��!" << endl;
			}
		}
		else if (command == 'b') {//�Ĥ@�^�X����
			system("CLS");
			firstBoard();
			cout << "�Х�½�P" << endl;
		}
		else if (command == 'c') {//�Ĥ@�^�X�뭰
			system("CLS");
			firstBoard();
			cout << "���a2 �ӧQ!" << endl;
			firstround = 0;
			victory = 1;
		}
		else {//���~���O
			system("CLS");
			firstBoard();
			cout << "�п�J���Ī����O!" << endl;
		}
	} while (firstround != 0);
	if(firstround == 0 && command == 'a') {
		system("CLS");
		printBoard(chessBoard, boardstate);//�L�X�Ĥ@�^�X�᪺�L��
	}	
	while (victory != 1) {
		if (turn[0] % 2 == 1) {//�P�_���a�C��H�Φ^�X
			if (playercolor == 1)		cout << "���a1(�´�)�^�X ( a : ½�P �A b : ���ʩΦY�� �A c : �뭰 )" << endl;
			else if (playercolor == 2)	cout << "���a1(����)�^�X ( a : ½�P �A b : ���ʩΦY�� �A c : �뭰 )" << endl;
		}
		if (turn[0] % 2 == 0) {
			if (playercolor == 1)		cout << "���a2(����)�^�X ( a : ½�P �A b : ���ʩΦY�� �A c : �뭰 )" << endl;
			else if (playercolor == 2)	cout << "���a2(�´�)�^�X ( a : ½�P �A b : ���ʩΦY�� �A c : �뭰 )" << endl;
		}
		cin >> command;
		if (command == 'a') {
			cout << "��J��m�G" << endl;
			cin >> xo >> yo;
			if (xo<4 && xo >= 0 && yo<8 && yo >= 0) {//�P�_�y�п��~�ҥ~
				system("CLS");
				if (boardstate[xo][yo] == 0)turn[0]++;
				openchess(boardstate, chessBoard, xo, yo);
			}
			else {
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�п�J���T���y��!" << endl;
			}
		}
		else if (command == 'b') {
			cout << "�Q���ʪ��Ѥl��m�G" << endl;
			cin >> xs >> ys;
			if (xs<4 && xs >= 0 && ys<8 && ys >= 0) {//�P�_�y�п��~�ҥ~ 
				if (boardstate[xs][ys] == 0) {//��½�}���Ѥl
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�Ѥl��½�}" << endl;
					continue;
				}
				else if (boardstate[xs][ys] == 2) {//�Ū���l
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�Ū���l" << endl;
					continue;
				}
				else if (boardstate[xs][ys] == 1) {
					//������~�C��ҥ~ 
					if (turn[0] % 2 == 1) {
						if (playercolor == 1 && chessBoard[xs][ys]>16) {//�´ѱ�����
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�б���ۤv���Ѥl" << endl; 
							continue;
						}
						else if (playercolor == 2 && chessBoard[xs][ys] <= 16) {//���ѱ��´� 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�б���ۤv���Ѥl" << endl;
							continue;
						}
					}
					if (turn[0] % 2 == 0) {
						if (playercolor == 1 && chessBoard[xs][ys] <= 16) {//���ѱ��´�
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�б���ۤv���Ѥl" << endl;
							continue;
						}
						else if (playercolor == 2 && chessBoard[xs][ys]>16) {//�´ѱ�����  
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�б���ۤv���Ѥl" << endl;
							continue;
						}
					}
					cout << "�Q���ʪ��ؼЦ�m�G" << endl;
					cin >> xe >> ye;
					if (xe<4 && xe >= 0 && ye<8 && ye >= 0) {//�y�п��~�ҥ~ 
						if (xs != xe&&ys != ye) {//�ר��ҥ~ 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�Фűר�" << endl;
							continue;
						}
						else if (xs == xe&&ys == ye) {//��J�ۦP�y�Шҥ~ 
							system("CLS");
							printBoard(chessBoard, boardstate);
							cout << "�y�Э���" << endl;
							continue;
						}
						else {
							if (boardstate[xe][ye] == 0) {//�ؼдѤl��½�}
								system("CLS");
								printBoard(chessBoard, boardstate);
								cout << "�ؼЦ�m���Ѥl��½�}" << endl;
								continue;
							}
							else if (boardstate[xe][ye] == 1) {//�ؼдѤl�w½�}
								movechess(boardstate, chessBoard, xs, ys, xe, ye, turn);
							}
							else if (boardstate[xe][ye] == 2) {//�ؼШS���Ѥl
								movechess(boardstate, chessBoard, xs, ys, xe, ye, turn);
							}
						}
					}
					else {
						system("CLS");
						printBoard(chessBoard, boardstate);
						cout << "�п�J���T���y��!" << endl;
						continue;
					}
				}
			}
			else {
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�п�J���T���y��!" << endl;
				continue;
			}
		}
		else if (command == 'c') {//�뭰
			if (turn[0] % 2 == 1)cout << "���a2 �ӧQ!" << endl;
			if (turn[0] % 2 == 0)cout << "���a1 �ӧQ!" << endl;
			victory = 1;//�����ӧQ
		}
		else {
			system("CLS");
			printBoard(chessBoard, boardstate);
			cout << "�п�J���Ī����O!" << endl;
		}
		//���g�L�뭰���ӧQ�P�w
		int blackcount = 0, redcount = 0;
		for (int i = 0; i<ROW; i++) {//�p��U�C��Ѿl���Ѥl
			for (int j = 0; j<COLUMN; j++) {
				if (chessBoard[i][j] <= 16 && chessBoard[i][j]>0)blackcount++;
				else if (chessBoard[i][j]>16 && chessBoard[i][j] <= 32)redcount++;
			}
		}
		if (blackcount == 0) {//�Ѿl�Ѥl��0�̸���
			if (playercolor == 1)cout << "���a2 �ӧQ!" << endl;
			else if (playercolor == 2)cout << "���a1 �ӧQ!" << endl;
			victory = 1;
		}
		else if (redcount == 0) {
			if (playercolor == 1)cout << "���a1 �ӧQ!" << endl;
			else if (playercolor == 2)cout << "���a2 �ӧQ!" << endl;
			victory = 1;
		}
	}
	//printBoard(chessBoard);
	return 0;
}
//���ʩΦY�Ѫ�function 
void movechess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xs, int ys, int xe, int ye, int turn[1]) {
	if (boardstate[xe][ye] == 1) {//�ؼдѤl�w�g½�}
		if (chessBoard[xs][ys] >= 1 && chessBoard[xs][ys] <= 5) {//�� 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y�ҥ~
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 21) {//��Y�L
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else if (chessBoard[xe][ye] == 32) {//��Y��
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 6 || chessBoard[xs][ys] == 7) {//�] 
			int middlechesscount = 0;//�����]�M�ؼдѤl�������Ѥl�Ӽ�
			if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�ФŦP�⤬�Y" << endl;
			}
			else if ((xs - xe)>1) {
				for (int i = xe + 1; i<xs; i++) {//�p��]�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((xe - xs)>1) {
				for (int i = xs + 1; i<xe; i++) {//�p��]�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((ys - ye)>1) {
				for (int i = ye + 1; i<ys; i++) {//�p��]�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {
					system("CLS");//�H�ϳW�h
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((ye - ys)>1) {
				for (int i = ys + 1; i<ye; i++) {//�p��]�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else {//�H�ϳW�h
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�H�ϥ]�����ʳW�h" << endl;
			}
		}
		if (chessBoard[xs][ys] == 8 || chessBoard[xs][ys] == 9) {//�� 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 25)) {//�Y�񰨤p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 10 || chessBoard[xs][ys] == 11) {//�� 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 27)) {//�Y�񨮤p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 12 || chessBoard[xs][ys] == 13) {//�H 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 29)) {//�Y��H�p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 14 || chessBoard[xs][ys] == 15) {//�h 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 31)) {//�Y��h�p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 16) {//�N 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] <= 16 && chessBoard[xe][ye] >= 1) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 22 && chessBoard[xe][ye] <= 32)) {//�Y��N�p���ѡA���F�L
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�N�Y�L
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] >= 17 && chessBoard[xs][ys] <= 21) {//�L 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				if (chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 5) {//�L�Y��
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else if (chessBoard[xe][ye] == 16) {//�L�Y�N
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 22 || chessBoard[xs][ys] == 23) {//�� 
			int middlechesscount = 0;//�������M�ؼдѤl�������Ѥl�Ӽ�
			if (chessBoard[xe][ye] <= 32 && chessBoard[xe][ye] >= 17) {//�P�⤬�Y
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�ФŦP�⤬�Y" << endl;
			}
			else if ((xs - xe)>1) {
				for (int i = xe + 1; i<xs; i++) {//�p�⬶�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((xe - xs)>1) {
				for (int i = xs + 1; i<xe; i++) {//�p�⬶�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[i][ys] == 0 || boardstate[i][ys] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((ys - ye)>1) {
				for (int i = ye + 1; i<ys; i++) {//�p�⬶�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else if ((ye - ys)>1) {
				for (int i = ys + 1; i<ye; i++) {//�p�⬶�M�ؼдѤl�������Ѥl�Ӽ�
					if (boardstate[xs][i] == 0 || boardstate[xs][i] == 1)middlechesscount++;
				}
				if (middlechesscount == 1) {//�X�G�W�h
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�H�ϳW�h
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�H�ϥ]�����ʳW�h" << endl;
				}
			}
			else {//�H�ϳW�h
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�H�ϥ]�����ʳW�h" << endl;
			}
		}
		if (chessBoard[xs][ys] == 24 || chessBoard[xs][ys] == 25) {//�X 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 9)) {//�X�Y��ۤv�p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 26 || chessBoard[xs][ys] == 27) {//�} 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 11)) {//�Y��}�p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 28 || chessBoard[xs][ys] == 29) {//�� 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 13)) {//�Y��ۤp����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 30 || chessBoard[xs][ys] == 31) {//�K 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 1 && chessBoard[xe][ye] <= 15)) {//�Y��K�p����
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�p�Y�j
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
		if (chessBoard[xs][ys] == 32) {//�� 
			if ((xs - 1 == xe&&ys == ye) || (xs + 1 == xe&&ys == ye) || (xs == xe&&ys - 1 == ye) || (xs == xe&&ys + 1 == ye)) {
				if (chessBoard[xe][ye] >= 17 && chessBoard[xe][ye] <= 32) {//�P�⤬�Y
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФŦP�⤬�Y" << endl;
				}
				else if ((chessBoard[xe][ye] >= 6 && chessBoard[xe][ye] <= 16)) {//�Y��Ӥp���ѡA���F��
					chessBoard[xe][ye] = chessBoard[xs][ys];
					chessBoard[xs][ys] = 0;
					boardstate[xe][ye] = 1;
					boardstate[xs][ys] = 2;
					system("CLS");
					printBoard(chessBoard, boardstate);
					turn[0]++;
				}
				else {//�ӦY��
					system("CLS");
					printBoard(chessBoard, boardstate);
					cout << "�ФťH�p�Y�j" << endl;
				}
			}
			else {//���ʶW�L�@��
				system("CLS");
				printBoard(chessBoard, boardstate);
				cout << "�Ф@�����ʤ@��" << endl;
			}
		}
	}
	else if (boardstate[xe][ye] == 2) {//�ؼЬO�Ū�
		chessBoard[xe][ye] = chessBoard[xs][ys];
		chessBoard[xs][ys] = 0;
		boardstate[xe][ye] = 1;
		boardstate[xs][ys] = 2;
		system("CLS");
		printBoard(chessBoard, boardstate);
		turn[0]++;
	}
}

void openchess(int boardstate[][COLUMN], int chessBoard[][COLUMN], int xo, int yo) {//½�}�Ѥl��function
	if (boardstate[xo][yo] == 0) {//�ؼХ�½�}
		boardstate[xo][yo] = 1;
		system("CLS");
		printBoard(chessBoard, boardstate);
	}
	else if (boardstate[xo][yo] == 1) {//�ؼФw½�}
		system("CLS");
		printBoard(chessBoard, boardstate);
		cout << "�w�g½�}�F" << endl;
	}
	else if (boardstate[xo][yo] == 2) {//�ؼЬO�Ū�
		system("CLS");
		printBoard(chessBoard, boardstate);
		cout << "�O�Ū���l" << endl;
	}
}

void printBoard(int chessBoard[][COLUMN], int boardstate[][COLUMN]) {//�L�X�Ĥ@�^�X�᪺�ѽL��function
	cout << "    0   1   2   3   4   5   6   7 " << endl;
	for (int i = 0; i < 4; i++) {
		cout << i;
		for (int j = 0; j < 8; j++) {
			if (boardstate[i][j] == 0)cout << "  ��";
			if (boardstate[i][j] == 1) {
				if (chessBoard[i][j] >= 1 && chessBoard[i][j] <= 5)		cout << setw(4) << "��";
				if (chessBoard[i][j] == 6 || chessBoard[i][j] == 7)		cout << setw(4) << "�]";
				if (chessBoard[i][j] == 8 || chessBoard[i][j] == 9)		cout << setw(4) << "��";
				if (chessBoard[i][j] == 10 || chessBoard[i][j] == 11)	cout << setw(4) << "��";
				if (chessBoard[i][j] == 12 || chessBoard[i][j] == 13)	cout << setw(4) << "�H";
				if (chessBoard[i][j] == 14 || chessBoard[i][j] == 15)	cout << setw(4) << "�h";
				if (chessBoard[i][j] == 16)								cout << setw(4) << "�N";
				if (chessBoard[i][j] >= 17 && chessBoard[i][j] <= 21)	cout << setw(4) << "�L";
				if (chessBoard[i][j] == 22 || chessBoard[i][j] == 23)	cout << setw(4) << "��";
				if (chessBoard[i][j] == 24 || chessBoard[i][j] == 25)	cout << setw(4) << "�X";
				if (chessBoard[i][j] == 26 || chessBoard[i][j] == 27)	cout << setw(4) << "�}";
				if (chessBoard[i][j] == 28 || chessBoard[i][j] == 29)	cout << setw(4) << "��";
				if (chessBoard[i][j] == 30 || chessBoard[i][j] == 31)	cout << setw(4) << "�K";
				if (chessBoard[i][j] == 32)								cout << setw(4) << "��";
			}
			if (boardstate[i][j] == 2) {
				cout << "    ";
			}
		}
		cout << endl;
	}
}

void randomChess(int Board[][COLUMN]) {//���Ѥl�H���\��function
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
			randcolumn = rand() % COLUMN;//�ؼдѤl�P�H���Ѥl�洫��m
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
			if (chessBoard[i][j] >= 1 && chessBoard[i][j] <= 5)		cout << setw(4) << "��";
			if (chessBoard[i][j] == 6 || chessBoard[i][j] == 7)		cout << setw(4) << "�]";
			if (chessBoard[i][j] == 8 || chessBoard[i][j] == 9)		cout << setw(4) << "��";
			if (chessBoard[i][j] == 10 || chessBoard[i][j] == 11)	cout << setw(4) << "��";
			if (chessBoard[i][j] == 12 || chessBoard[i][j] == 13)	cout << setw(4) << "�H";
			if (chessBoard[i][j] == 14 || chessBoard[i][j] == 15)	cout << setw(4) << "�h";
			if (chessBoard[i][j] == 16)								cout << setw(4) << "�N";
			if (chessBoard[i][j] >= 17 && chessBoard[i][j] <= 21)	cout << setw(4) << "�L";
			if (chessBoard[i][j] == 22 || chessBoard[i][j] == 23)	cout << setw(4) << "��";
			if (chessBoard[i][j] == 24 || chessBoard[i][j] == 25)	cout << setw(4) << "�X";
			if (chessBoard[i][j] == 26 || chessBoard[i][j] == 27)	cout << setw(4) << "�}";
			if (chessBoard[i][j] == 28 || chessBoard[i][j] == 29)	cout << setw(4) << "��";
			if (chessBoard[i][j] == 30 || chessBoard[i][j] == 31)	cout << setw(4) << "�K";
			if (chessBoard[i][j] == 32)								cout << setw(4) << "��";
		}
		cout << endl; 
	}
}

void firstBoard() {//�L�X�Ĥ@�^�X���L��
	cout << "    0   1   2   3   4   5   6   7 " << endl;
	for (int i = 0; i < 4; i++) {
		cout << i;
		for (int j = 0; j < 8; j++) {
			cout << "  ��";
		}
		cout << endl;
	}
}
