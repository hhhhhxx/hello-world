#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <list>
using namespace std;

struct point
{
	int x,y;
};

const int High=15;
const int Width=20;
int canvas[High][Width]= {0};
int food_x,food_y;
char moveWay;
bool isInput=false;
list<point> Snake;
point head,tail;

//Ë¢ÐÂÓÅ»¯
void gotoxy(int x,int y)
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info= {1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void startup()
{
	head.x=High/2;
	head.y=Width/2;
	tail.x=head.x+1;
	tail.y=head.y;
	canvas[head.x][head.y]=1;
	Snake.push_back(head);
	moveWay='w';
	food_x=rand()%High;
	food_y=rand()%Width;
	canvas[food_x][food_y]=2;
}

void show()
{
	gotoxy(0,0);
	for(int i=0; i<High; i++)
	{
		for(int j=0; j<Width; j++)
		{
			if(canvas[i][j]==0)
				printf(" ");
			else if(canvas[i][j]==1)
				printf("*");
			else if(canvas[i][j]==2)
				printf("O");
		}
		printf("|\n");
	}
	for(int i=0; i<Width; i++)
		printf("-");
	printf("+\n");

}

void updateWithInput()
{
	isInput=false;
	static int speed=0;
	char input;
	if(speed<40)
		speed++;
	if(speed==40)
		if(kbhit())
		{
			input=getch();
			if(input=='w'&&moveWay!='w'&&moveWay!='s')
			{
				head=Snake.front();
				tail=Snake.back();
				Snake.pop_back();
				canvas[tail.x][tail.y]=0;
				head.x=(head.x-1+High)%High;
				canvas[head.x][head.y]=1;
				Snake.push_front(head);
				moveWay=input;
				isInput=true;
			}
			if(input=='s'&&moveWay!='s'&&moveWay!='w')
			{
				tail=Snake.back();
				Snake.pop_back();
				canvas[tail.x][tail.y]=0;
				head.x=(head.x+1+High)%High;
				canvas[head.x][head.y]=1;
				Snake.push_front(head);
				moveWay=input;
				isInput=true;
			}
			if(input=='a'&&moveWay!='a'&&moveWay!='d')
			{
				tail=Snake.back();
				Snake.pop_back();
				canvas[tail.x][tail.y]=0;
				head.y=(head.y-1+Width)%Width;
				canvas[head.x][head.y]=1;
				Snake.push_front(head);
				moveWay=input;
				isInput=true;
			}
			if(input=='d'&&moveWay!='d'&&moveWay!='a')
			{
				tail=Snake.back();
				Snake.pop_back();
				canvas[tail.x][tail.y]=0;
				head.y=(head.y+1+Width)%Width;
				canvas[head.x][head.y]=1;
				Snake.push_front(head);
				moveWay=input;
				isInput=true;
			}
		}
}

void updateWithoutInput()
{
	static int speed=0;
	if(isInput)
		speed=0;
	if(speed<40)
		speed++;
	if(speed==40)
	{
		speed=0;
		if(moveWay=='w')
		{
			head=Snake.front();
			tail=Snake.back();
			Snake.pop_back();
			canvas[tail.x][tail.y]=0;
			head.x=(head.x-1+High)%High;
			canvas[head.x][head.y]=1;
			Snake.push_front(head);
		}
		if(moveWay=='s')
		{
			tail=Snake.back();
			Snake.pop_back();
			canvas[tail.x][tail.y]=0;
			head.x=(head.x+1+High)%High;
			canvas[head.x][head.y]=1;
			Snake.push_front(head);
		}
		if(moveWay=='a')
		{
			tail=Snake.back();
			Snake.pop_back();
			canvas[tail.x][tail.y]=0;
			head.y=(head.y-1+Width)%Width;
			canvas[head.x][head.y]=1;
			Snake.push_front(head);
		}
		if(moveWay=='d')
		{
			tail=Snake.back();
			Snake.pop_back();
			canvas[tail.x][tail.y]=0;
			head.y=(head.y+1+Width)%Width;
			canvas[head.x][head.y]=1;
			Snake.push_front(head);
		}

		if(canvas[food_x][food_y]!=2)
		{
			food_x=rand()%High;
			food_y=rand()%Width;
			canvas[food_x][food_y]=2;
			canvas[tail.x][tail.y]=1;
			Snake.push_back(tail);
		}
	}
}

int main()
{
	srand(time(0));
	HideCursor();
	startup();
	while(true)
	{
		show();
		updateWithInput();
		updateWithoutInput();
	}
	return 0;
}
