#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;

enum P
{
	null_,ground_,left_,right_,up_,down_,start_,end_
};

class Point
{
public:
	int state;
	int x;
	int y;

	void outPoint(int y, int x);
	int getXY(int x_, int y_);
};

int Point::getXY(int x_, int y_)
{
	if ((x_ > x * 50) && (x_ < (x * 50 + 50)) && (y_ > y * 50) && (y_ < (y * 50 + 50)))
	{
		return 1;
	}
	return 0;
}

void Point::outPoint(int y_, int x_)
{
	x = x_;
	y = y_;
	setfillcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	switch (state)
	{
	case ground_:
	{
		solidrectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50);
	}
	break;
	case left_:
	{
		solidrectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50);
		setfillcolor(BLUE);
		solidcircle(x * 50 + 25, y * 50 + 25, 20);
		outtextxy(x * 50, y * 50, L"←");
	}
	break;
	case right_:
	{
		solidrectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50);
		setfillcolor(BLUE);
		solidcircle(x * 50 + 25, y * 50 + 25, 20);
		outtextxy(x * 50, y * 50, L"→");
	}
	break;
	case up_:
	{
		solidrectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50);
		setfillcolor(BLUE);
		solidcircle(x * 50 + 25, y * 50 + 25, 20);
		outtextxy(x * 50, y * 50, L"↑");
	}
	break;
	case down_:
	{
		solidrectangle(x * 50, y * 50, x * 50 + 50, y * 50 + 50);
		setfillcolor(BLUE);
		solidcircle(x * 50 + 25, y * 50 + 25, 20);
		outtextxy(x * 50, y * 50, L"↓");
	}
	break;
	case start_:
	{
		solidcircle(x * 50 + 25, y * 50 + 25, 43);
		outtextxy(x * 50, y * 50, L"START");
	}
	break;
	case end_:
	{
		solidcircle(x * 50 + 25, y * 50 + 25, 43);
		outtextxy(x * 50, y * 50, L"END");
	}
	break;
	}
}


class BackGround
{
public:
	Point point[60][30];

	BackGround();
	void set();


};

BackGround::BackGround()
{
	for (int i = 0;i < 60;i++)
	{
		for (int j = 0;j < 30;j++)
		{
			point[i][j].state = null_;
		}
	}
	setfillcolor(GREEN);
	solidrectangle(0, 0, 6 * 50 * 5, 12 * 50 * 5);
	set();
	for (int i = 0;i < 60;i++)
	{
		for (int j = 0;j < 30;j++)
		{
			point[i][j].outPoint(i, j);
		}
	}
}

void BackGround::set()
{
	point[32][15].state = end_;
	point[33][15].state = ground_;
	point[34][15].state = ground_;
	point[35][15].state = ground_;
	point[36][15].state = up_;
	for (int i = 14;i > 6;i--)
	{
		point[36][i].state = ground_;
	}
	point[36][6].state = right_;
	for (int i = 37;i <40;i++)
	{
		point[i][6].state = ground_;
	}
	point[40][6].state = up_;
	for (int i = 7;i <11;i++)
	{
		point[40][i].state = ground_;
	}
	point[40][12].state = left_;
	point[41][12].state = up_;
	for (int i = 13;i <16;i++)
	{
		point[41][i].state = ground_;
	}
	point[41][17].state = left_;
	point[41][18].state = left_;
	point[43][18].state = up_;
	point[45][18].state = up_;
	point[47][18].state = up_;
	for (int i = 12;i <18;i++)
	{
		point[47][i].state = ground_;
	}
	point[47][11].state = right_;
	point[48][11].state = up_;
	point[48][12].state = ground_;
	point[48][13].state = ground_;
	point[48][15].state = left_;
	point[48][16].state = left_;
	point[50][16].state = up_;
	point[51][16].state = ground_;
	point[52][16].state = ground_;
	point[53][16].state = ground_;
	point[54][16].state = start_;

}


class Gamer
{
public:
	IMAGE *lman;
	IMAGE *bman;
	int x, y;

	Gamer()
	{
		lman = new IMAGE;
		bman = new IMAGE;
		loadimage(lman, L"littleman.jpg");
		loadimage(bman, L"bigman.jpg");
	}
};

class Game
{
public:
	int state;
	int startI, startJ;
	Gamer gamer;
	BackGround *bk;

	int LR[15] = { up_,left_,left_,up_,right_,up_,up_,up_,left_,left_,up_,left_,up_,right_,up_ };
	void startGame(IMAGE *img);
	void failGame();
	void endGame();
	Game()
	{
		bk = new BackGround;
	}
};

void Game::startGame(IMAGE *img)
{
	state = up_;
	startI = 54;
	startJ = 16;
	gamer.x = -675;
	gamer.y = -2425;
	int jump = 0;//是否跳
	int jumpNum = 0;//是否跳完
	int i = 0;
	while (true)
	{
		putimage(gamer.x, gamer.y, img);
		setfillcolor(RED);
		if (jumpNum)
			putimage(120, 270, gamer.bman);
		else
			putimage(125, 275, gamer.lman);

		for (int i = 0;i < 60;i++)
		{
			for (int j = 0;j < 30;j++)
			{
				if (bk->point[i][j].getXY(150 - gamer.x, 300 - gamer.y) && (jumpNum == 0))
				{
					if (bk->point[i][j].state == null_)
					{
						failGame();
						return;
					}
					if (bk->point[i][j].state == end_)
					{
						endGame();
						return;
					}

				}
			}
		}

		switch (state)
		{
		case up_:
		{
			gamer.y++;	
		}
		break;
		case down_:
		{
			gamer.y--;
		}
		break;
		case left_:
		{
			gamer.x++;
		}
		break;
		case right_:
		{
			gamer.x--;
		}
		break;
		default:
			break;
		}

		if (kbhit())
		{
			getch();
			jump = 1;
			jumpNum = 1;
			state = LR[i];
			i++;
		}
		if (jumpNum)
		{
			jumpNum++;
		}
		if (jumpNum == 100)
		{
			jumpNum = 0;
			
		}
		if (jumpNum ==  120)
		{
			jump = 0;
		}
		Sleep(10);
	}

}

void Game::failGame()
{
	outtextxy(0, 0, L"失败");
	Sleep(3000);
}
void Game::endGame()
{
	outtextxy(0, 0, L"成功");
	Sleep(3000);
}

int main()
{
	initgraph(300*5, 600*5);
	setbkmode(TRANSPARENT);
	
	Game game;
	IMAGE *img = new IMAGE;
	getimage(img, 0,0, 50 * 6 * 5, 50 * 12 * 5);
	initgraph(300 , 600 );
	saveimage(L"IMG.jpg", img);
	while (true)
	{
		game.startGame(img);
	}
	system("pause");
	closegraph();
	return 0;
}