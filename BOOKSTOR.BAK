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
class Book
{
	int ID;
	char name[50];
	char author[30];
	char tag[3][20];
	int quantity;
	int price;
	public:
	void show();
	void add(int);
	void assign(long val)
	{
		ID=val;
	}
	void del()
	{
		quantity=-1;
	}
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
	char * rettag1()
	{
		return tag[0];
	}
	char * rettag2()
	{
		return tag[1];
	}
	char * rettag3()
	{
		return tag[2];
	}
};
void Book::add(int mode=1)
{
	int select=1; //mode=1 for add, 0 for modify
	char c=0;
	if(mode==1)
	{
		ID=0;
		strcpy(name,"");
		strcpy(author,"");
		strcpy(tag[0],"");
		strcpy(tag[1],"");
		strcpy(tag[2],"");
		quantity=0;
		price=0;
	}
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
		print(tag[0])<<endl;
		print(tag[1])<<endl;
		print(tag[2])<<"\n\n";
		print(" Quantity:")<<endl;
		prINT(quantity)<<"\n\n";
		print(" Price:")<<endl;
		prINT(price)<<"\n\n\n";
		print("Done");
		gotoxy(15,select<4?3*(select+1):select==4?13:select*3-1);
		cout<<(char)26;
		gotoxy(1,25);
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
					if(select<8)
						select++;
					else
					{
						if(!strcmp(name,""))
						{
							print("Enter a name");
							getch();
						}
						else if(!strcmp(author,""))
						{
							print("Enter an author");
							getch();
						}
						else if(price==0)
						{
							print("Enter a price");
							getch();
						}
						else
						{
							return;
						}
					}
					break;
				case 27:
					ID=-1;
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
							if(c=='\b')
							{
								if(tag[0][0]!='\0')
									tag[0][strlen(tag[0])-1]='\0';
							}
							else if(strlen(tag[0])<30)
							{
								tag[0][strlen(tag[0])+1]='\0';
								tag[0][strlen(tag[0])]=c;
							}
							break;
						case 4:
							if(c=='\b')
							{
								if(tag[1][0]!='\0')
									tag[1][strlen(tag[1])-1]='\0';
							}
							else if(strlen(tag[1])<30)
							{
								tag[1][strlen(tag[1])+1]='\0';
								tag[1][strlen(tag[1])]=c;
							}
							break;
						case 5:
							if(c=='\b')
							{
								if(tag[2][0]!='\0')
									tag[2][strlen(tag[2])-1]='\0';
							}
							else if(strlen(tag[2])<30)
							{
								tag[2][strlen(tag[2])+1]='\0';
								tag[2][strlen(tag[2])]=c;
							}
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
	cout<<"     #"<<ID<<"                                             Availibility: "<<quantity<<" items"<<endl;
	cout<<"     "<<name<<endl;
	cout<<"     by "<<author<<endl;
	cout<<"     Tags: ";
	cout<<tag[0];
	if(strcmp(tag[1],""))
		cout<<", "<<tag[1];
	if(strcmp(tag[2],""))
		cout<<", "<<tag[2];
	cout<<endl<<"     Price: "<<price;
}
/*int enterdata(char c, char * a="", char * b="")
{
	int j=0,select=0;
	char str[20]=" ";
	str[0]=c;
	Book search[10];
	for(int i=1;(i==0?1:str[i-1])!='\0';i<20?(i++):(i=20))
	{
		clrscr();
		cout<<endl;
		print(" Enter string:")<<endl;
		print(str)<<"\n\n";
		ifstream fin;
		fin.open("booklist.dat",ios::binary);
		while(fin.read((char *)&search[j],sizeof(search[j]))&&j<10)
		{
			if(strstr(search[j].rettag(),str)!=NULL)
			{
				for(int k=0,found=0;k<j;k++)
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
}*/
class Transaction
{
	long ID;
	long bookID[10];
	int quantity[10];
	int price[10];
	int total;
};
void passout(int len,int code=0)
{	 //code=0 for no error, 1 for incorrect pass, 2 for invalid char
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	if(code==1)
		print("Incorrect password, try again");
	else if(code==2)
		print("Invalid character");
	else if(code==3)
		print("This action cannot be undone. Confirm deletion?");
	cout<<endl<<setw((80+strlen("Enter password (Esc to cancel) : ")-len)/2)<<"Enter password (esc to quit) : ";
	for(int i=len;i>0;i--)
	{
		cout<<"*";
	}
}
int pass(int code=1)
{
	clrscr();
	char c,pass[20]="",corr[20];
	passout(0,code);
	code=0;
	for (int i=0;(i==0?1:pass[i-1])!='\0'&&i<20;i++)
	{
		c=getch();
		switch(c)
		{
			case 27:
				return -1;
			case '\b':
				pass[i-1]='\0';
				i-=2;
				passout(strlen(pass));
				break;
			case '\r':
				pass[i]='\0';
				break;
			case '\0':
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
	fin.getline(corr,20);
	fin.close();
	return strcmp(pass,corr)==0?0:1;
}
void bookmenu(Book b)
{
	clrscr();
	cout<<"\n\n\n";
	b.show();
	cout<<"\n\n";
	print("Perform an action")<<"\n\n";
	print("Press 1           to add to cart")<<"\n\n";
	print("Press 2                  to edit")<<"\n\n";
	print("Press 3                to delete")<<"\n\n";
	print("Press Esc             to go back")<<"\n\n";
	char c=getch();
	switch(c)
	{
		case 27:
			return;
		case 0:
			getch();
			break;
		case '1':
			break;
		case '2':
			b.add(0);
			if(b.retID()!=-1)
			{
				fstream fout;
				fout.open("booklist.dat",ios::binary|ios::out|ios::in);
				fout.seekp((b.retID()-1)*sizeof(b));
				fout.write((char *)&b,sizeof(b));
				fout.close();
			}
			break;
		case '3':
			clrscr();
			int x=pass(3);
			while(x!=-1)
			{
				if(!x)
				{
					b.del();
					fstream fout;
					fout.open("booklist.dat",ios::binary|ios::out|ios::in);
					fout.seekp((b.retID()-1)*sizeof(b));
					fout.write((char *)&b,sizeof(b));
					fout.close();
					break;
				}
				x=pass(1);
			}
			break;
	}
}
void searchscr(int type)
{
	clrscr();
	int start=0,range=0,select=0;
	char c,search[30]="";
	Book result[4];
	clrscr();
	cout<<'\n';
	print(" Search:")<<"\n\n";
	ifstream fin;
	fin.open("booklist.dat",ios::binary);
	int j=0;
	while(fin.read((char *)&result[j%4],sizeof(result[j]))&&j<4)
	{
		if(result[j%4].retquan()!=-1)
			j++;
	}
	fin.close();
	range=j;
	for(int i=0;i<range;i++)
		result[i].show();
	for(i=0;(i==0?1:search[i-1])!='\0'&&i<50;i<50?i++:(i=50))
	{
		c=getch();
		switch(c)
		{
			case 27:
				return;
			case '\r':
				if(select!=0)
					bookmenu(result[select-1]);
				break;
			case '\b':
				select=0;
				if(i!=0)
				{
					search[i-1]='\0';
					i-=2;
					ifstream fin;
					fin.open("booklist.dat",ios::binary);
					int j=0;
					while(fin.read((char *)&result[(j-start)%4],sizeof(result[j]))&&j<(start+4))
					{
						if(type==1||type==2)
							if(result[(j-start)%4].retquan()!=-1&&(strstr((type==1?result[(j-start)%4].retname():result[(j-start)%4].retauth()),search)!=NULL))
								j++;
						else
							if(result[(j-start)%4].retquan()!=-1&&((strstr(result[(j-start)%4].rettag1(),search)!=NULL)||(strstr(result[(j-start)%4].rettag2(),search)!=NULL)||(strstr(result[(j-start)%4].rettag3(),search)!=NULL)))
								j++;
					}
					fin.close();
					range=j-start;
				}
				break;
			case '\0':
				c=getch();
				i--;
				if(c==80)
				{
					if(select<range)
						select++;
				}
				else if(c==72)
				{
					if(select>1)
						select--;
				}
				break;
			default:
				select=0;
				search[i]=c;
				search[i+1]=0;
				ifstream fin;
				fin.open("booklist.dat",ios::binary);
				int j=0;
				while(fin.read((char *)&result[(j-start)%4],sizeof(result[j]))&&j<(start+4))
				{
					if(type==1||type==2)
							if(result[(j-start)%4].retquan()!=-1&&(strstr((type==1?result[(j-start)%4].retname():result[(j-start)%4].retauth()),search)!=NULL))
								j++;
						else
							if(result[(j-start)%4].retquan()!=-1&&((strstr(result[(j-start)%4].rettag1(),search)!=NULL)||(strstr(result[(j-start)%4].rettag2(),search)!=NULL)||(strstr(result[(j-start)%4].rettag3(),search)!=NULL)))
								j++;
				}
				fin.close();
				range=j-start;
		}
		clrscr();
		cout<<'\n';
		print(" Search:")<<'\n';
		print(search)<<"\n";
		for(int i=0;i<range;i++)
			result[i].show();
		if(select!=0)
		{
			gotoxy(4,select*5);
			cout<<(char)26;
		}
	}
}
void searchmenu()
{
	clrscr();
	cout<<"\n\n\n\n";
	print("Search")<<"\n\n\n\n\n";
	print("Press 0              to search by ID")<<"\n\n";
	print("Press 1            to search by name")<<"\n\n";
	print("Press 2          to search by author")<<"\n\n";
	print("Press 3             to search by tag")<<"\n\n";
	print("Press Esc          to return to home")<<"\n\n"<<setw(40);
	char ch=getch();
	switch(ch)
	{
		case '1':
		case '2':
		case '3':
			searchscr(ch-48);
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
			fout.open("booklist.dat",ios::binary|ios::app);
			Book b;
			b.add();
			if(b.retID()==0)
			{
				fout.seekp(0,ios::end);
				b.assign(fout.tellp()/sizeof(b)+1);
				fout.write((char *)&b,sizeof(b));
			}
			else if(b.retID()!=-1)
			{
				fout.seekp((b.retID()-1)*sizeof(b),ios::beg);
				fout.write((char *)&b,sizeof(b));
			}
			return 1;
		case '2':
			searchmenu();
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
	int x=pass(0);
	if(x==1)
		while(x)
		{
			x=pass();
			if(x==-1)
				exit(0);
		}
	else if(x==-1)
		exit(0);
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