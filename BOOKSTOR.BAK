#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
void passout(int len,int retry)
{
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(55)<<(retry==1?"Incorrect password, try again\n":"\n")<<setw((80+strlen("Enter password: ")-len)/2)<<"Enter password: ";
	for(int i=len;i>0;i--)
	{
		cout<<"*";
	}
}
int pass(int retry=1)
{
	clrscr();
	char c,pass[20]="";
	int timer,i;
	passout(0,retry);
	for (i=0;pass[i-1]!='\0'&&i<20;i++)
	{
		c=getch();
		if(c=='\b')
		{
			pass[i-1]='\0';
			i-=2;
			passout(strlen(pass),retry);
		}
		else if(c=='\r')
			pass[i]='\0';
		else
		{
			pass[i]=c;
			passout(strlen(pass),retry);
		}
	}
	return strcmp(pass,"therealDoge");
}
void main()
{
	if(pass(0))
		while(pass());
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(51)<<"Successfully logged in";
	delay(1000);
	//printmenu();
	getch();
}