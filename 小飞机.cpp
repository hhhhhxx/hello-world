#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
int main()
{
	int x=5,y=10;
	char input;
	int isFire=0;
	srand(time(0));
	int ny=rand()%20;;
	int isKilled=0;

	while(true)
	{
		system("cls");

		if(!isKilled)
		{
			for(int i=0; i<ny; i++)
				printf(" ");
			printf("+\n");
		}
		else 
		{
			printf("\n"); 
		}
		if(!isFire)
		{
			for(int i=0; i<x; i++)
				printf("\n");
		}
		else
		{
			for(int i=0; i<x; i++)
			{
				for(int i=0; i<y; i++)
					printf(" ");
				printf("|\n");
			}
			if(y==ny)
			{	
				//isKilled=1;
				ny=rand()%20;
			}
			isFire=0;
		}
		//飞机图案
		for(int i=0; i<y; i++)
			printf(" ");
		printf("*\n");
		for(int i=0; i<y; i++)
			printf(" ");
		printf("*\n");
		for(int i=0; i<y-2; i++)
			printf(" ");
		printf("*****\n");
		for(int i=0; i<y-1; i++)
			printf(" ");
		printf("* *\n");


		//控制按键
		if(kbhit())
		{
			input=getch();
			if(input=='a')
				y--;
			if(input=='d')
				y++;
			if(input=='w')
				x--;
			if(input=='s')
				x++;
			if(input==' ')
				isFire=1-isFire;
		}
	}
	return 0;
}
