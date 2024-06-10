#include<iostream>
#include<easyx.h>
#include<vector>
using namespace std;
/* �˻ʺ����� */
#include<stdio.h>
int ack[10][10];
char que[10][10];
int cnt = 0;

IMAGE img_mm[8];
bool nextSolution = false;
bool terminateProgram = false;

void initmap(int n);//��ʼ��
void printMap(int n);//����Ĵ�ӡ
void copyMap(int a[10][10], int b[10][10], int n);//��a���鿽����b����
void backtrack(int k, int n);//���ĵݹ��㷨
void putQueen(int x, int y, int n);//����ack����


ExMessage msg = { 0 };

void drawShape(int n) {
	//����������ɫ
	setlinecolor(BLACK);
	//������С����ʽ
	setlinestyle(PS_SOLID, 1);
	//������
	int x1 = 0, y1 = 0;
	for (int i = 0; i < (n+1); i++) {

		line(x1, 0, x1, getheight());
		x1 += 100;
	}
	for (int i = 0; i < (n+1); i++) {

		line(0, y1, getwidth()-200, y1);
		y1 += 100;
	}
}

//void drawTest() {
//
//	printf("hello easyx");
//	//ʹ�ı����ڸ�
//	setbkmode(TRANSPARENT);
//	settextstyle(48, 0, _T("΢���ź�"));
//	//
//	outtextxy(
//		10, 10, _T("hello easyx")
//	);
//
//	//
//	settextstyle(30, 0, _T(("΢���ź�")));
//	int score = 66;
//	char str[50] = "";
//	sprintf(str, "Score:%d ", score);
//	outtextxy(getwidth() - 100, 0, str);
//}

//mx,my�Ƿ��ڰ�ť��Χ��
bool inArea(int mx, int my, int x, int y, int w, int h) {
	if (mx > x && mx < x + w && my > y && my < y + h) {
		return true;
	}
	return false;
}

bool button(int x, int y, int w, int h, const char* text) {

	if (inArea(msg.x, msg.y, x, y, w, h)) {
		setfillcolor(RGB(93, 107, 153));
	}
	else {
		//��ɫ����
		setfillcolor(RGB(230, 231, 233));
	}


	fillroundrect(x, y, x + w, y + h, 5, 5);
	//�����ı���ɫ
	settextcolor(BLACK);
	int hSpace = (w - textwidth(text)) / 2;
	int vSpace = (h - textheight(text)) / 2;
	outtextxy(x + hSpace, y + vSpace, text);

	//����������������ڷ�Χ��
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}

int main()
{
	int num;
	printf("������ʺ����: ");
	cin >> num;

	getchar();
	initgraph(num*100 + 200, num *100, EX_SHOWCONSOLE);

	setbkcolor((RGB(230, 231, 232)));
	cleardevice();
	setbkmode(TRANSPARENT);

	drawShape(num);


	for (int i = 0; i < 8; i++) {
		loadimage(&img_mm[i], "assets/queen.png", 100, 100);
	}
	
	initmap(8);
	while (!terminateProgram) {
		settextcolor(BLACK);


		backtrack(0, num);

		// ������Ϣ

		BeginBatchDraw();

		//// ��ť���ʹ���
		//if (button(820, 200, 170, 50, "��һ��")) {
		//	printf("��һ��\n");
		//	nextSolution = true;
		//}
		//if (button(820, 450, 170, 50, "����")) {
		//	printf("����\n");
		//	terminateProgram = true;
		//}

		EndBatchDraw();
		Sleep(10);

		msg.message = 0;
	}
	printf("cnt = %d\n", cnt);

	getchar();
	return 0;
}


/**
 *
 * @param n
 * ��ʼ�����飬ack���鱣���ܷ���ã�que�����ʾ�ʺ��λ��
 */
void initmap(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ack[i][j] = 0;
			que[i][j] = '.';
		}
	}
}
/**
 *
 * @param n
 * ��ӡ���飬�ʺ��λ��
 */
void printMap(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%c ", que[i][j]);
		printf("\n");
	}
	printf("\n");
}


void backtrack(int k, int n) {

	if (terminateProgram) {
		return;
	}
	if (n == 4 && cnt == 2) {
		//printf("cnt = %d", cnt);
		return;
	}
	if (n == 8 && cnt == 92) {
		//printf("cnt = %d", cnt);
		return;
	}
	//if (cnt == 92) {
	//	return;
	//}

	// k==n ��ʾ�ҵ�һ���  ��ӡ
	
	if (k == n) {
		cleardevice();

		drawShape(n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (que[i][j] == 'Q') {
					putimage(j * 100, i * 100, &img_mm[i]);
				}
			}
		}
		cnt++; //����Ľ������+1
		printf("��%d�ֽ������:\n", cnt);
		printMap(n);
		

		nextSolution = false;
		while (!nextSolution) {
			while (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN:
					if (button(n*100+20, (getheight()/2)/2, 170, 50, "��һ��")) {
						nextSolution = true;
					}
					if (button(n*100+20, (getheight() / 2), 170, 50, "����")) {
						terminateProgram = true;
						return;
					}
					break;
				}
			}
			Sleep(100);
		}
		return;
	}
	for (int i = 0; i < n; i++) {
		// ��һ��ѭ���ж��Ƿ���Է��ûʺ�������Խ������²��������У���
		if (ack[k][i] == 0) {//������λ��û�б���������ô���Է��ûʺ�
			// 1. ����attack���飨���ݺ����ָ���
			int tmp[10][10];
			copyMap(ack, tmp, n);
			// 2. ��Ǹ�λ��ΪQ��2. �洢λ�ã�`queen[k][i]='Q'` �����ı�һ���ط������ֱ�ӸĻ�����
			que[k][i] = 'Q';
			// 3. ��һ�������˻ʺ����Ը���attack����
			putQueen(k, i, n);
			// 4.  �ݹ���̽k+1�еĻʺ�λ�ã����У�
			backtrack(k + 1, n);
			// 5. �ݹ���ɺ󣬻ָ�attack����� `queen[k][i]='.' `
			copyMap(tmp, ack, n);
			que[k][i] = '.';
		}
	}
}
//���ڸ��ƣ�������
void copyMap(int a[10][10], int b[10][10], int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j] = a[i][j];
}
void putQueen(int x, int y, int n) {
	//���¸������� ack ��Ǵ�λ�� (x, y) ��ʼ�����а˸������ϵĹ���·����
	int dx[] = { -1,-1,-1,0, 1, 1, 1, 0 };
	int dy[] = { -1,0, 1, 1, 1, 0,-1,-1 };
	ack[x][y] = 1;

	for (int i = 1; i <= n - 1; i++)//��1���쵽n-1�ľ���
		for (int j = 0; j < 8; j++) {//�Ӱ˸���������
			int nx = x + i * dx[j];
			int ny = y + i * dy[j];

			if (nx >= 0 && nx < n && ny >= 0 && ny < n)
				ack[nx][ny] = 1;
		}
}
