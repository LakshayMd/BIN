#include<fstream.h>
#include<ctype.h>
#include<process.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
#define print(i) cout<<setw((80+strlen(i))/2)<<i
#define prINT(i) cout<<setw((80+intlen(i))/2)<<i
int intlen(long n)
{
	for(int i=0;n!=0;i++,n/=10);
	return i;
}
struct tag
{
	int ID;
	char name[20];
};
int entag(char c, int a, int b)
{
	int j=0,select=0;
	char str[20]=" ";
	str[0]=c;
	tag t[10];
	for(int i=1;(i==0?1:str[i-1])!='\0';i<20?(i++):(i=20))
	{
		clrscr();
		cout<<endl;
		print(" Enter tag:")<<endl;
		print(str)<<"\n\n";
		ifstream fin;
		fin.open("tags.dat",ios::binary);
		while(fin.read((char *)&t[j],sizeof(t[j]))&&j<10)
		{
			if(strstr(t[j].name,str)!=NULL&&t[j].ID!=a&&t[j].ID!=b)
			{
				cout<<endl;
				print(t[j].name)<<endl;
				j++;
			}
		}
		fin.close();
		c=getch();
		switch(c)
		{
			case 27:
				return 0;
			case '\b':
				if(i!=0)
				{
					str[i-1]='\0';
					i--;
				}
				i--;
				break;
			case '\r':
				str[i]='\0';
				break;
			case '\0':
				c=getch();
				i--;
				if(c==72)
					if(select>0)
						select--;
					else
						select=j;
				else
					if(c==80)
						if(select<j)
							select++;
						else
							select=0;
				break;
			default:
				select=0;
				str[i]=c;
		}
	}
	if(select==0)
	{
		fstream f;
		f.open("tags.dat",ios::binary|ios::in|ios::out);
		i=0;
		while(f.read((char *)&t[0],sizeof(t[0])))
		{
			if(!strcmpi(t[0].name,str))
			{
				f.close();
				return t[0].ID;
			}
		}
		t[0].ID=(f.tellg()/sizeof(t[0])+1);
		strcpy(t[0].name,str);
		f.write((char *)&t[0],sizeof(t[0]));
		f.close();
		return t[0].ID;
	}
	else
		return t[select-1].ID;
}
class Book
{
	int ID;
	char name[50];
	char author[30];
	int tag[3];
	int quantity;
	int price;
	public:
	void show();
	void add();
	char * retauth()
	{
		return author;
	}
	int retID()
	{
		return ID;
	}
	char * retname()
	{
		return name;
	}
	int retquan()
	{
		return quantity;
	}
};
char * taglookup(int intag)
{
	ifstream fin;
	tag t;
	fin.open("tags.dat",ios::binary);
	char strtag[60]="";
	while(fin.read((char *)&t,sizeof(t))&&intag!=0)
		if(intag==t.ID)
		{
			strcpy(strtag,t.name);
			break;
		}
	return strtag;
}
void Book::add()
{
	int select=1,mode=1; //mode=1 for add, 0 for modify
	char c=0,tag1[20],tag2[20],tag3[20];
	ID=NULL;
	strcpy(name,"");
	strcpy(author,"");
	tag[0]=0;
	tag[1]=0;
	tag[2]=0;
	quantity=0;
	price=0;
	while(c!=27)
	{
		clrscr();
		cout<<"\n";
		print("Add book")<<"\n\n\n";
		print(" Book name:")<<endl;
		print(name)<<"\n\n";
		print(" Author:")<<endl;
		print(author)<<"\n\n";
		print(" Tags:")<<endl;
		print(taglookup(tag[0]))<<endl;
		print(taglookup(tag[1]))<<endl;
		print(taglookup(tag[2]))<<"\n\n";
		print(" Quantity:")<<endl;
		prINT(quantity)<<"\n\n";
		print(" Price:")<<endl;
		prINT(price)<<"\n\n\n";
		print("Done");
		gotoxy(15,select<4?3*(select+1):select==4?13:select*3-1);
		cout<<(char)26;
		gotoxy(80,25);
			c=getch();
		if(c=='\0')
		{
			c=getch();
			switch(c)
			{
				case 72:
					if(select!=1)
						select--;
					else
						select=8;
					break;
				case 80:
					if(select!=8)
						select++;
					else
						select=1;
			}
		}
		else
			switch(c)
			{
				case '\r':
					select++;
					break;
				case 27:
					break;
				default:
					switch(select)
					{
						case 1:
							if(c=='\b')
							{
								if(name[0]!='\0')
									name[strlen(name)-1]='\0';
							}
							else if(strlen(name)<50)
							{
								name[strlen(name)+1]='\0';
								name[strlen(name)]=c;
							}
							break;
						case 2:
							if(c=='\b')
							{
								if(author[0]!='\0')
									author[strlen(author)-1]='\0';
							}
							else if(strlen(author)<30)
							{
								author[strlen(author)+1]='\0';
								author[strlen(author)]=c;
							}
							break;
						case 3:
							if(c!='\b')
							tag[0]=entag(c,tag[1],tag[2]);
							break;
						case 4:
							tag[1]=entag(c,tag[0],tag[2]);
							break;
						case 5:
							tag[2]=entag(c,tag[0],tag[1]);
							break;
						case 6:
							if(isdigit(c))
								quantity=10*quantity+c-48;
							if(c==8)
								quantity/=10;
							break;
						case 7:
							if(isdigit(c))
								price=10*price+c-48;
							if(c==8)
								price/=10;
					}
			}
	}
}
void Book::show()
{
	cout<<endl;
	char strID[10],strquan[2];
	int temp=ID,quan=quantity;
	for(int i=9;i>=0;i--,temp/=10)
		strID[i]=temp%10;
	for(i=1;i>=0;i--,quan/=10)
		strquan[i]=quan%10;
	print(strcat(strcat("#",strID),(quantity==0?"                                 Availibility: out of stock":strcat(strcat("                                 Availibility:     ",strquan)," items"))));
}
class Transaction
{
	long ID;
	long bookID[10];
	int quantity[10];
	int price[10];
	int total;
};
void passout(int len,int errcode=0)
{	 //errcode=0 for no error, 1 for incorrect pass, 2 for invalid char
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	if(errcode==1)
		print("Incorrect password, try again");
	else if(errcode==2)
		print("Invalid character");
	cout<<endl<<setw((80+strlen("Enter password (esc to quit) : ")-len)/2)<<"Enter password (esc to quit) : ";
	for(int i=len;i>0;i--)
	{
		cout<<"*";
	}
}
int pass(int retry=1)
{
	clrscr();
	char c,pass[20]="",code[20];
	passout(0,retry);
	retry=0;
	for (int i=0;(i==0?1:pass[i-1])!='\0'&&i<20;i++)
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
			case '\0'://so that arrow keys etc dont create glitches
				getch();
				passout(strlen(pass),2);
				i--;
				break;
			default:
				pass[i]=c;
				passout(strlen(pass));
		}
	}
	ifstream fin;
	fin.open("encryp.txt");
	fin.getline(code,20);
	fin.close();
	return strcmp(pass,code); //password to be entered to proceed
}
int findauth(Book b[],char * str,int start=0)
{
	ifstream fin;
	fin.open("booklist.dat",ios::binary);
	int i=0;
	while(fin.read((char *)&b[(i-start)%10],sizeof(b[i]))&&i<(start+10))
	{
		if(b[i].retquan()!=-1&&strstr(b[i].retauth(),str)!=NULL)
			i++;
	}
	fin.close();
	return i-start;
}
void searchauth(int type=0)
{
	clrscr();
	int start=0,range=0,select=-1;
	char c,search[30]="";
	Book result[10];
	if(type==1)
	{
		clrscr();
		cout<<'\n';
		print(" Search:");
	}
	for (int i=0;(i==0?1:search[i-1])!='\0'&&i<20;i++)
	{
		c=getch();
		switch(c)
		{
			case 27:
				break;
			case '\b':
				if(i!=0)
				{
					search[i-1]='\0';
					i-=2;
					range=findauth(result,search,start);
				}
				if(type==1)
				{
					clrscr();
					cout<<'\n';
					print(" Search:")<<'\n';
					print(search)<<"\n\n";
					for(int i=0;i<6&&i<range;i++)
						result[i].show();
				}
				else {}
					//specsearch(3,search,result);
				break;
			case '\r':
				search[i]='\0';
				break;
			case '\0':
				getch();
				i--;
				break;
			default:
				search[i]=c;
				if(!strcmp(search,""))
					range=findauth(result,search,start);
				if(type==1)
				{
					clrscr();
					cout<<'\n';
					print(" Search:")<<'\n';
					print(search)<<"\n\n";
					for(int i=0;i<6&&i<range;i++)
						result[i].show();
				}
				else {}
					//specsearch(3,search,result);
		}
	}
}
void search()
{
	clrscr();
	cout<<"\n\n\n\n";
	print("Search")<<"\n\n\n\n";
	print("Press 1              to search by ID")<<"\n\n";
	print("Press 2            to search by name")<<"\n\n";
	print("Press 3          to search by author")<<"\n\n";
	print("Press 4             to search by tag")<<"\n\n";
	print("Press 5           to search by price")<<"\n\n";
	print("Press Esc          to return to home")<<"\n\n"<<setw(40);
	char ch=getch();
	switch(ch)
	{
		case '1':
			break;
		case '2':
			break;
		case '3':
			searchauth(1);
			break;
		case '4':
			break;
		case '5':
			break;
		case 27:
			break;
		case '\0':
			getch();
	}
}
int menu()
{
	clrscr();
	cout<<"\n\n\n\n";
	print("XD Book Shop")<<"\n\n\n";
	print("Press 1         to add book to stock")<<"\n\n";
	print("Press 2         to search for a book")<<"\n\n";
	print("Press 3               to manage cart")<<"\n\n";
	print("Press 4                  to checkout")<<"\n\n";
	print("Press 5         to view transactions")<<"\n\n";
	print("Press 6           to change password")<<"\n\n";
	print("Press Esc        to log out and quit")<<"\n\n"<<setw(40);
	char ch=getch();
	switch(ch)
	{
		case '\0':
			getch();
			return 1;
		case '1':
			ofstream fout;
			fout.open("booklist.dat",ios::binary);
			Book b;
			b.add();
			if(b.retID()==0)
				fout.write((char *)&b,sizeof(b));
			return 1;
		case '2':
			search();
			return 1;
		case '3':
			return 1;
		case '4':
			return 1;
		case '5':
			return 1;
		case '6':
			return 1;
		case 27:
			return 0;
		default:
			return 1;
	}
}
void main()
{
	if(pass(0))
		while(pass());
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
	print("Successfully logged in");
	delay(700);
	while(menu());
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
	print("Successfully logged out");
	delay(700);
}