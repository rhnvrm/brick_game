#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#include <ctype.h>
#include <string.h>
#include <iomanip.h>
#include <graphics.h>
#include <dos.h>

class Velocity;
class Brick;
class Ball;
class PowerUp;
class Board;
class Panel;
class TextBox;

class Velocity
{
	public:
	int sp, di;
};
class Panel
{
	public:
	int width,change;
	int points; char* pts;
	void score(int);
	void draw();

	Panel()
	{
		change = 1;
		width = 100;
		points = 0;
		pts = "";
	}
};
class Board
{
	public:
	int xC, yC, len, di,sp,height;
	void draw(void);
	void draw1(void);
	void brd(void);
	void clear();
	void pCatch(PowerUp& p, int index);
	void launch(Ball& b,int tedi);
	//int change;
	Board()
	{	
		height = 7;
		xC=getmaxx()/2;
		sp = 15;
		yC = getmaxy()-height;
		//change = 1;
	}


}/*b1,b2*/;
class Ball
{
	public:
	int radius, xC, yC;
	int type,tcat;
	int alive;
	int m,n;
	int index;

	Velocity vC;
	void draw();
	void clear();
	void move(int,int);
	int  checkCollision(int,int,int,int);
	void collision();

	Ball()
	{

		vC.di = 2;
		vC.sp = 1;
		radius = 4;
		type = 0;
		alive = 0;
		tcat=0;
	}


};
class PowerUp
{
	public:
	int xC, yC, type;
	int height, width;
	int flag;
	int color;
	int alive;

	int fall(void);
	int clear(void);
	int draw(void);

	PowerUp()
	{
		height=10;
		width=50;
		flag = 0;
		alive = 0;
	}

};
class Brick
{
	public:
	int xC, yC;
	int alive, type;
	int height, width;
	int powerUp;
	PowerUp p;
	int f1,f2;

	int brickInit(void);
	void brickDesignInit(void);
	int aliveInit(void);
	Brick()
	{
		alive  =  1;
		height = 10;
		width  = 50;
		//powerUp=  0;
		f1=0;
		f2=0;
		xC =0;yC =0;
		powerUp= brickInit();
	    //	brickDesignInit();
	}

	int drawAlive(void);
	int drawDead(void);
	int brickCheck(Ball&);


};