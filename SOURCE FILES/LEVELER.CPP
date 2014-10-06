 /*THE LEVEL CREATOR*/
//-------------------
#include <lib.h>
#include <fstream.h>
//-------------------
Brick b[10][5] ;
Panel panel;
char* levf;
int Brick::brickInit(void)
{
	int r = random(2);
	int a=random(2);
	if(!r&&!a)
		return random(4);
	else
		return 0;
}
void levelini()
{
	int ixC = 200, iyC = 100;
	for (int i = 0; i < 10; i++)
	{
		ixC=200;
		for (int j = 0; j < 5; j++)
		{
			b[i][j].xC=ixC;
			ixC+=50;
			b[i][j].yC =iyC;
		}
		iyC+=10;
	}
}

Brick::drawDead(void)
{
	if (!alive)
	{
		if (f2)
		{
			setcolor(0);
			setfillstyle(0,0);
			bar(xC,yC,xC+width,yC+height);
			rectangle(xC, yC, xC+ width, yC + height);
			setcolor(15);
			f2=1;
		}
	}
	return 0;
}
Brick::drawAlive(void)
{
	if (alive)
	{
		if (!f1)
		{
			setcolor(12);
			if(powerUp == 1)
				setfillstyle(5,14);
			else 
				if (powerUp == 2)
					setfillstyle(5,11);
			else 
				if (powerUp == 3)
					setfillstyle(5,13);
			else
				setfillstyle(5,12);
			bar(xC,yC,xC+width,yC+height);
			rectangle(xC, yC, xC+ width, yC + height);
			setcolor(15);
			f1=1;
		}
	}
	return 0;
}
//-------------------

void Panel::draw()
{
	//Base
	setfillstyle(1, 7);
	bar(getmaxx()-width, 0,getmaxx(),getmaxy());
	setfillstyle(0, 0);
	//Score
	char* strScore=itoa(points,strScore,10);
	setfillstyle(0, 7);
	bar(getmaxx()-panel.width/2-textwidth(strScore)/2,0-textheight(strScore),getmaxx()/2+textwidth(strScore),textheight(strScore));
	settextstyle(0,0,1);
	outtextxy(getmaxx()-panel.width/2-(textwidth(strScore)/2),getmaxy()/2-textheight(strScore),strScore);
	change = 0;
}
void Panel::score(int amount)
{
	points += amount;
	change = 1;
}

//-------------------

void gameStart()
{
	setcolor(5);
	settextstyle(4,0,12);
	outtextxy(getmaxx()/2-(textwidth("BRICKZ")/2),getmaxy()/2-textheight("BRICKZ"),"BRICKZ");
	settextstyle(4,0,2);
	outtextxy(getmaxx()/2-(textwidth("Press any key to start...")/2),getmaxy()/2-textheight("Press any key to start...")+200,"Press any key to start...");
	getch();
	cleardevice();
	settextstyle(0,0,1);
	outtextxy(getmaxx()/2-(textwidth("Loading...")/2),getmaxy()/2-textheight("Loading..."),"Loading...");
	delay(1000);
	cleardevice();
}

void fileHandle()
{
	ofstream f;
	f.open(levf);
	f.write((char*)&b,sizeof(Brick)*50);
	f.close();
}

void fileHandler()
{
	ifstream f;
	f.open(levf);
	f.read((char*)&b,sizeof(Brick )* 50);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			f.read((char*)&b[i][j],sizeof(b[i][j]));
		}
	}
	f.close();
	for(i=0;i<10;i++)
	{
		for(int j=0;j<5;j++)
		{
			b[i][j].f1=0;
		}
	}
}

//-------------------
int briche(int i1,int j1)
{
	for(int r=0;r<10;r++)
	{	
		for(int u=0;u<5;u++)
		{
			if(r!=i1 || u!=j1)
			{
				if((b[i1][j1].xC==b[r][u].xC) && (b[i1][j1].yC==b[r][u].yC))
				goto q;
			}
		}
	}
	return 1;
q:	return 0;
}

//main:
int main()
{	//GRAPHICS INITIALIZATION:
	/* request auto detection */int gdriver = DETECT, gmode, errorcode;/* initialize graphics and local variables */initgraph(&gdriver, &gmode, "");/* read result of initialization */errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{printf("Graphics error: %s\n", grapherrormsg(errorcode));printf("Press any key to halt:");getch();exit(1); /* terminate with an error code */}
	/* start code */

	levf="LEVEL1.LVL\0";
	//Welcome Screen:
	gameStart();
	char lev;
	int a=0,bricksAlive = 10 * 5, bricnum=1,brchan=0;
	unsigned int i1=0,j1=0;
	//-------------------
	//GAME LOOP:-
	//-------------
	levelini();
	cout<<"enter level to draw/edit? ";
	cin>>lev;
	levf[5]=lev;
    fileHandler();
	cleardevice();
	setcolor(10);
	settextstyle(3,0,2);
	outtextxy(getmaxx()-textwidth("CHANGE"),100,"CHANGE");
	do
	{ 
		setcolor(12);
		rectangle(b[i1][j1].xC,b[i1][j1].yC,b[i1][j1].xC+b[i1][j1].width,b[i1][j1].yC+b[i1][j1].height);
		if (panel.change)
		{
			panel.draw();
		}
		j1=(bricnum%5);
	    i1=(bricnum/5);
		setcolor(15);
		rectangle(b[i1][j1].xC,b[i1][j1].yC,b[i1][j1].xC+b[i1][j1].width,b[i1][j1].yC+b[i1][j1].height);
		setcolor(9);
		//Check the keyboard buffer:-
		if(kbhit())
		{
			a = getche();
			if(a==113)
			{	
				if(!brchan)
					brchan=1;
				else
				brchan=0;
			}
			if (a==50 )
			{
				if(!brchan)
					bricnum+=5;
				else
				{
					b[i1][j1].f2=1;
					b[i1][j1].alive=0;
					b[i1][j1].drawDead();
					b[i1][j1].f1=0;
					b[i1][j1].alive=1;
					b[i1][j1].yC+=b[i1][j1].height;
				
					if(!briche(i1,j1))
						b[i1][j1].yC-=b[i1][j1].height;
					b[i1][j1].drawAlive();
				}
			}
			if(a==56)
			{
				if(!brchan)
					bricnum-=5;
				else
				{
					b[i1][j1].f2=1;
					b[i1][j1].alive=0;
					b[i1][j1].drawDead();
					b[i1][j1].f1=0;
					b[i1][j1].alive=1;
					b[i1][j1].yC-=b[i1][j1].height;
					if(!briche(i1,j1))
						b[i1][j1].yC+=b[i1][j1].height;
					b[i1][j1].drawAlive(); 
				}
			}
			if(a==52)
			{
				if(!brchan)
					bricnum-=1;
				else
				{
					b[i1][j1].f2=1;
					b[i1][j1].alive=0;
					b[i1][j1].drawDead();
					b[i1][j1].f1=0;
					b[i1][j1].alive=1;
					b[i1][j1].xC-=b[i1][j1].width;
					if(!briche(i1,j1))
						b[i1][j1].xC+=b[i1][j1].width;
					b[i1][j1].drawAlive(); 
				}
			}
			if(a==54)
			{
				if(!brchan)
					bricnum+=1;
				else
				{
					b[i1][j1].f2=1;
					b[i1][j1].alive=0;
					b[i1][j1].drawDead();
					b[i1][j1].f1=0;
					b[i1][j1].alive=1;
					b[i1][j1].xC+=b[i1][j1].width;
					if(!briche(i1,j1))
						b[i1][j1].xC-=b[i1][j1].width;
					b[i1][j1].drawAlive(); 
				}
			}
			if(a==27)
			{
				fileHandle();
				bricksAlive = 0;   
			}
			a=0;
		}
		for (i = 0; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				b[i][j].drawDead();
			}
		}
		for (i = 0; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				b[i][j].drawAlive();
			}
		}
		
	} while(bricksAlive != 0);
	closegraph();
	return 0;
}
