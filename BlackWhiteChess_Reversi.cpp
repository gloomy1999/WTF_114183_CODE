// TestBlackWhite.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//C++�ڰ���
//δ���ԣ���һ����ȷ
//���±���д���룬δ������
//�����ش��Ź�2018��˼·�ο�ʹ��
//��Ϯ0�֣�����

//������һ��СAI�°��� 2018-12-13 00:00

#include <iostream>
#include <time.h>
using namespace std;

#define VALID 0 	//����������
#define WHITE 1	//����
#define BLACK -1	//����

#define GRID_SIZE 10	//���̴�С

int** pData = NULL; //����洢�ڶ�ά������ 8*8��0 - δ��������1 - ��������2 - ��������

void clearMemory(int**& ppD)
{
	if (ppD != NULL)
	{
		for (int i = 0; i < GRID_SIZE; i++)
			delete[] ppD[i];
		delete[] ppD;
		ppD = NULL;
	}
}

void createData(int**& ppD)
{
	clearMemory(ppD);
	ppD = new int*[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; i++)
		ppD[i] = new int[GRID_SIZE];
}

void display()	//���pData����ʾ
{
	//���pData����ʾ
	cout << "+\t";
	for (int i = 0; i < GRID_SIZE; i++)
		cout << i << "\t";
	cout << endl;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (pData[i][j] == BLACK)
				cout << "��" << "\t";
			if (pData[i][j] == WHITE)
				cout << "��" << "\t";
			if (pData[i][j] == VALID)
				cout << "+" << "\t";
		}

		cout << endl << endl;
	}
}

//�����㷨��pInputDataΪ��������
//����ά����ָ�����ã����޸Ķ�ά��������
bool play(int**& pInputData, int curX, int curY, int curColor = BLACK)
{
	if (curX < 0 || curY < 0 || curX >= GRID_SIZE || curY >= GRID_SIZE)
		return false;

	if (pInputData[curX][curY] != VALID)
		return false;

	pInputData[curX][curY] = curColor;

	//�������д�ڰ�����߼�������pInputData
	int searchX = curX, searchY = curY;
	int i, j;

	//������
	for (searchX = curX, searchY = curY; searchX < GRID_SIZE /*&& pInputData[searchX][searchY] != VALID*/; searchX++)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX; i < searchX; i++)
				pInputData[i][searchY] = curColor;

			//break;
		}
	}

	for (searchX = curX, searchY = curY; searchX >= 0 /*&& pInputData[searchX][searchY] != VALID*/; searchX--)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX; i >= searchX; i--)
				pInputData[i][searchY] = curColor;

			//break;
		}
	}

	//������
	for (searchX = curX, searchY = curY; searchY < GRID_SIZE /*&& pInputData[searchX][searchY] != VALID*/; searchY++)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curY; i < searchY; i++)
				pInputData[searchX][i] = curColor;

			//break;
		}
	}

	for (searchX = curX, searchY = curY; searchY >= 0 /*&& pInputData[searchX][searchY] != VALID*/; searchY--)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curY; i >= searchY; i--)
				pInputData[searchX][i] = curColor;

			//break;
		}
	}

	//б����
	for (searchX = curX, searchY = curY; searchX < GRID_SIZE && searchY < GRID_SIZE /*&& pInputData[searchX][searchY] != VALID*/; searchX++, searchY++)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX, j = curY; i < searchX && j < searchY; i++, j++)
				pInputData[i][j] = curColor;

			//break;
		}

	}

	for (searchX = curX, searchY = curY; searchX >= 0 && searchY >= 0 /*&& pInputData[searchX][searchY] != VALID*/; searchX--, searchY--)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX, j = curY; i >= searchX && j >= searchY; i--, j--)
				pInputData[i][j] = curColor;

			//break;
		}

	}

	for (searchX = curX, searchY = curY; searchX < GRID_SIZE && searchY >= 0 /*&& pInputData[searchX][searchY] != VALID*/; searchX++, searchY--)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX, j = curY; i < searchX && j >= searchY; i++, j--)
				pInputData[i][j] = curColor;

			//break;
		}

	}

	for (searchX = curX, searchY = curY; searchX >= 0 && searchY < GRID_SIZE /*&& pInputData[searchX][searchY] != VALID*/; searchX--, searchY++)
	{
		if (pInputData[searchX][searchY] == VALID)
			break;

		if (pInputData[searchX][searchY] == curColor)
		{
			for (i = curX, j = curY; i >= searchX && j < searchY; i--, j++)
				pInputData[i][j] = curColor;

			//break;
		}

	}


	return true;
}

bool isEndGame()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (pData[i][j] == VALID)
				return false;
		}
	}

	return true;
}

void replay()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			pData[i][j] = VALID;
		}
	}

	//���Ͻ����½Ƿֱ�Ϊ�ںͰ�
// 	pData[0][0] = BLACK;
// 	pData[GRID_SIZE - 1][GRID_SIZE - 1] = WHITE;

	srand((unsigned)time(NULL));
	//�����λ��
	pData[rand() % GRID_SIZE][rand() % GRID_SIZE] = BLACK;

	//�������������ͬλ��
	while (1)
	{
		int rnd_x = rand() % GRID_SIZE;
		int rnd_y = rand() % GRID_SIZE;
		if (pData[rnd_x][rnd_y] != VALID)
			continue;

		pData[rnd_x][rnd_y] = WHITE;
		break;
	}
	

	display();
}

//���㵱ǰ�׺ڱ�
double calCurrentWhitePerBlack(int** &pInputData)
{
	//���㵱ǰ�׺ڱ�
	int nWhiteCount = 0;
	int nBlackCount = 0;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (pInputData[i][j] == WHITE)
				nWhiteCount++;
			if (pInputData[i][j] == BLACK)
				nBlackCount++;
		}
	}

	if (nBlackCount == 0)
		return -1;

	double WhitePerBlack = (double)nWhiteCount / (double)nBlackCount;
	return WhitePerBlack;
}

void whoWinTheGame()
{
	double dWBRatio = calCurrentWhitePerBlack(pData);

	if (dWBRatio == 1)
		cout << "WHITE & BLACK ended in a draw." << endl;
	else if (dWBRatio > 1)
		cout << "WHITE WIN!" << endl;
	else
		cout << "BLACK WIN!" << endl;

}

void AI_findTheBestState(int curColor, int& selectX, int& selectY)
{
	int i, j;

	//�洢��ǰλ�õ����״̬
	double pState[GRID_SIZE][GRID_SIZE];

	//�������̣����ڼ������̨�����������λ��
	int** pBkupData = NULL;
	createData(pBkupData);


	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (pData[i][j] != VALID)
			{
				pState[i][j] = -2;
				continue;
			}

			//���Ƶ�ǰ����
			for (int m = 0; m < GRID_SIZE; m++)
				for (int n = 0; n < GRID_SIZE; n++)
					pBkupData[m][n] = pData[m][n];	//�����������̺ڰ׷ֲ�����

			//�ڱ���������ģ�����壬���ڵ�ǰ����İ׺ڱ�
			//�ɵõ������״̬�ֲ�����
			bool bResult = play(pBkupData, i, j, curColor);
			if (bResult)
				pState[i][j] = calCurrentWhitePerBlack(pBkupData);
			else
				pState[i][j] = -1;
		}
	}

	clearMemory(pBkupData);

	//�������״̬ȫ��<=0�������ѡ��λ��
	bool bflag = true;
	double sum_state = 0;
	int nValidStateCount = 0;
	double tmp_state = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (pState[i][j] > 1 && curColor == WHITE)
				bflag = false;
			if (1.0f / pState[i][j] > 1 && curColor == BLACK)
				bflag = false;

			if (pState[i][j] > 0)
			{
				tmp_state = pState[i][j];
				sum_state += pState[i][j];
				nValidStateCount++;
			}
		}
	}

	//���ȫ����һ����Ȩ�أ�Ҳ���ѡλ��
	if (abs(tmp_state - sum_state / (double)nValidStateCount) <= 10e-10 && nValidStateCount > 2)
		bflag = true;

	if (bflag)
	{
		srand((unsigned)time(NULL));
		while (1)
		{
			int rnd_x = rand() % GRID_SIZE;
			int rnd_y = rand() % GRID_SIZE;
			if (pData[rnd_x][rnd_y] != VALID)
				continue;

			selectX = rnd_x;
			selectY = rnd_y;
			return;
		}
	}


	//����ǰ��壬��׺ڱ�Խ��Խ��
	selectX = selectY = 0;
	double dCurState;
	if (curColor == WHITE)
	{
		dCurState = -2;
		for (i = 0; i < GRID_SIZE; i++)
		{
			for (j = 0; j < GRID_SIZE; j++)
			{
				if (pData[i][j] != VALID)
					continue;

				if (pState[i][j] >= dCurState)
				{
					dCurState = pState[i][j];
					selectX = i;
					selectY = j;
				}
			}
		}
	}

	//����Ǻ��壬��׺ڱ�Խ��Խ��
	if (curColor == BLACK)
	{
		dCurState = -2; // (double)GRID_SIZE*GRID_SIZE;
		for (i = 0; i < GRID_SIZE; i++)
		{
			for (j = 0; j < GRID_SIZE; j++)
			{
				if (pData[i][j] != VALID)
					continue;

				if (1.0f / pState[i][j] > dCurState /*&& 1.0f / pState[i][j] >= 0*/)
				{
					dCurState = 1.0f / pState[i][j];
					selectX = i;
					selectY = j;
				}
			}
		}
	}

	
}

int main()
{
	//����
	createData(pData);
	replay();

	// ��ǰ������ɫ
	int curColor = BLACK;
	int curX, curY;
	int nGameCount = 0;
	while (1)
	{		
		//�ж���Ϸ�Ƿ����
		if (isEndGame())
		{
			//���Ӯ��
			whoWinTheGame();

			//����
			//replay();
			//curColor = BLACK;
			break;
		}

		_sleep(500);
		system("cls");

		nGameCount++;
		cout << "Current Game is No. " << nGameCount << endl;

		if (curColor == WHITE)
			cout << "Input Location " << "WHITE" << " (X, Y): " << endl;
		else
			cout << "Input Location " << "BLACK" << " (X, Y): " << endl;

		//���ִ��ʱ����д���߼��ü�����Զ�Ѱ������λ�ã�СAI������ʵ�֣�
		if (curColor == WHITE)
		{
			cout << "AI-WHITE Running..." << endl;
			//RUN MY AI HERE!
			int AI_x, AI_y;
			AI_findTheBestState(curColor, AI_x, AI_y);

			cout << "AI-WHITE location is (" << AI_x << ", " << AI_y << ")" << endl;

			play(pData, AI_x, AI_y, curColor);

			//then display and continue the loop
			display();	//���
			curColor = BLACK;
			continue;
		}

		//���ִ��ʱ�������Ƽ�λ��
		if (curColor == BLACK)
		{
			cout << "AI-BLACK Running..." << endl;
			//RUN MY AI HERE!
			int AI_x, AI_y;
			AI_findTheBestState(curColor, AI_x, AI_y);

			cout << "Recommendation location is (" << AI_x << ", " << AI_y << ")" << endl;

			play(pData, AI_x, AI_y, curColor);

			//then display and continue the loop
			display();	//���
			curColor = WHITE;
			continue;
		}
		
		
		cin >> curX >> curY;

		//�޸�pData
		bool bResult = play(pData, curX, curY, curColor);

		if (bResult)
		{
			display();	//���

						// ������ǰ������ɫ
			if (curColor == BLACK) curColor = WHITE;
			else curColor = BLACK;
		}
		if (!bResult)
			cout << "Input X and Y Error!" << endl;

	}

	clearMemory(pData);

	return 0;
}

