#include<fstream.h>
#include<process.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
class Book
{
	long ID;
	char name[70];
	char author[30];
	char tag1[15];
	char tag2[15];
	char tag3[15];
	int quantity;
	float price;
	public:
	void show();
	char * retauth()
	{
		return author;
	}
	long retid()
	{
		return ID;
	}
	char * retname()
	{
		return name;
	}
};
void passout(int len,int errcode=0)
{	 //errcode=0 for no error, 1 for incorrect pass, 2 for invalid char
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	if(errcode==1)
		cout<<setw(55)<<"\aIncorrect password, try again";
	else if(errcode==2)
		cout<<setw(49)<<"\aInvalid character";
	cout<<endl<<setw((80+strlen("Enter password (esc to quit) : ")-len)/2)<<"Enter password (esc to quit) : ";
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
	retry=0;
	for (i=0;pass[i-1]!='\0'&&i<20;i++)
	{
		c=getch();
		switch(c)
		{
			case 27:
				exit(0);
				break;
			case '\b':
				pass[i-1]='\0';
				i-=2;
				passout(strlen(pass));
				break;
			case '\r':
				pass[i]='\0';
				break;
			case'\0'://so that arrow keys etc dont create glitches
				getch();
				passout(strlen(pass),2);
				i--;
				break;
			default:
				pass[i]=c;
				passout(strlen(pass));
		}
	}
	return strcmp(pass,"therealDoge"); //password to be entered to proceed
}
int menu()
{
	clrscr();
	return 0;
}
Book findauth(char * str,int sno)
{
	ifstream fin;
	fin.open("booklist.dat",ios::binary);
	Book b;
	int i=0;
	while(fin.read((char *)&b,sizeof(b))&&i<sno)
	{
		if(strstr(b.retauth(),str)!=NULL)
			i++;
	}
	fin.close();
	if(i==sno)
		return b;
}
void main()
{
	if(pass(0))
		while(pass());
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(51)<<"Successfully logged in";
	delay(1000);
	while(menu());
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(51)<<"Successfully logged out";
	getch();
}