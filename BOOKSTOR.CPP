#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
void passout(int len)
{
	clrscr();
	cout<<setw((80+strlen("Enter password: ")-len)/2)<<"Enter password: ";
	for(int i=len;i>0;i--)
	{
		cout<<"*";
	}
}
int pass()
{
	clrscr();
	char c,pass[20]="";
	int timer,i;
	passout(0);
	for (i=0;pass[i-1]!='\0'&&i<20;i++)
	{
		c=getch();
		if(c=='\b')
		{
			pass[i-1]='\0';
			i-=2;
			passout(strlen(pass));
		}
		else if(c=='\r')
			pass[i]='\0';
		else
		{
			pass[i]=c;
			passout(strlen(pass));
		}
	}
	return strcmp(pass,"therealDoge");
}
void main()
{
	//int gd=DETECT,gm;
	//initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	//setbkcolor(15);
	//system("COLOR 08");
	while(pass());
	getch();
}