#include<iostream>
#include<easyx.h>
#include<vector>
using namespace std;
/* 八皇后问题 */
#include<stdio.h>
int ack[10][10];
char que[10][10];
int cnt = 0;

IMAGE img_mm[8];
bool nextSolution = false;
bool terminateProgram = false;

void initmap(int n);//初始化
void printMap(int n);//数组的打印
void copyMap(int a[10][10], int b[10][10], int n);//把a数组拷贝到b数组
void backtrack(int k, int n);//核心递归算法
void putQueen(int x, int y, int n);//更新ack数组


ExMessage msg = { 0 };

void drawShape(int n) {
	//设置线条颜色
	setlinecolor(BLACK);
	//线条大小和样式
	setlinestyle(PS_SOLID, 1);
	//画线条
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
//	//使文本不遮盖
//	setbkmode(TRANSPARENT);
//	settextstyle(48, 0, _T("微软雅黑"));
//	//
//	outtextxy(
//		10, 10, _T("hello easyx")
//	);
//
//	//
//	settextstyle(30, 0, _T(("微软雅黑")));
//	int score = 66;
//	char str[50] = "";
//	sprintf(str, "Score:%d ", score);
//	outtextxy(getwidth() - 100, 0, str);
//}

//mx,my是否在按钮范围内
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
		//变色操作
		setfillcolor(RGB(230, 231, 233));
	}


	fillroundrect(x, y, x + w, y + h, 5, 5);
	//设置文本颜色
	settextcolor(BLACK);
	int hSpace = (w - textwidth(text)) / 2;
	int vSpace = (h - textheight(text)) / 2;
	outtextxy(x + hSpace, y + vSpace, text);

	//如果左键点击，并且在范围内
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}

int main()
{
	int num;
	printf("请输入皇后个数: ");
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

		// 处理消息

		BeginBatchDraw();

		//// 按钮检测和处理
		//if (button(820, 200, 170, 50, "下一次")) {
		//	printf("下一次\n");
		//	nextSolution = true;
		//}
		//if (button(820, 450, 170, 50, "结束")) {
		//	printf("结束\n");
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
 * 初始化数组，ack数组保存能否放置，que数组表示皇后的位置
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
 * 打印数组，皇后的位置
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

	// k==n 表示找到一组解  打印
	
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
		cnt++; //问题的解决方法+1
		printf("第%d种解决方法:\n", cnt);
		printMap(n);
		

		nextSolution = false;
		while (!nextSolution) {
			while (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
				switch (msg.message) {
				case WM_LBUTTONDOWN:
					if (button(n*100+20, (getheight()/2)/2, 170, 50, "下一次")) {
						nextSolution = true;
					}
					if (button(n*100+20, (getheight() / 2), 170, 50, "结束")) {
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
		// 在一层循环判断是否可以放置皇后，如果可以进行以下操作（按列）：
		if (ack[k][i] == 0) {//如果这个位置没有被攻击，那么可以放置皇后
			// 1. 备份attack数组（备份后，最后恢复）
			int tmp[10][10];
			copyMap(ack, tmp, n);
			// 2. 标记该位置为Q（2. 存储位置）`queen[k][i]='Q'` （仅改变一个地方，最后直接改回来）
			que[k][i] = 'Q';
			// 3. 上一步放置了皇后，所以更新attack数组
			putQueen(k, i, n);
			// 4.  递归试探k+1行的皇后位置（按行）
			backtrack(k + 1, n);
			// 5. 递归完成后，恢复attack数组和 `queen[k][i]='.' `
			copyMap(tmp, ack, n);
			que[k][i] = '.';
		}
	}
}
//用于复制，来保存
void copyMap(int a[10][10], int b[10][10], int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j] = a[i][j];
}
void putQueen(int x, int y, int n) {
	//更新辅助数组 ack 标记从位置 (x, y) 开始，所有八个方向上的攻击路径。
	int dx[] = { -1,-1,-1,0, 1, 1, 1, 0 };
	int dy[] = { -1,0, 1, 1, 1, 0,-1,-1 };
	ack[x][y] = 1;

	for (int i = 1; i <= n - 1; i++)//从1延伸到n-1的距离
		for (int j = 0; j < 8; j++) {//从八个方向延伸
			int nx = x + i * dx[j];
			int ny = y + i * dy[j];

			if (nx >= 0 && nx < n && ny >= 0 && ny < n)
				ack[nx][ny] = 1;
		}
}
