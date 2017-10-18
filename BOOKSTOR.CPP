#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
void print(char pass[])
{
	cout<<setw((80+strlen("Enter password: "))/2)<<"Enter password: ";
	for(int i=strlen(pass);i>0;i--)
	{
		cout<<"*";
	}
}
int pass()
{
	clrscr();
	char c,pass[20]="";
	int timer,i;
	print(pass);
	for (i=0;pass[i-1]!='\0'&&i<20;i++)
	{
		c=getch();
	}
	//while(!strcmp(pass,"therealDoge"))
}
void main()
{
	pass();
	getch();
	//while(!pass());
}