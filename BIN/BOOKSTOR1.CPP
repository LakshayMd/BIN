#include<fstream.h>
#include<time.h>
#include<ctype.h>
#include<process.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#define print(i) cout<<setw((80+strlen(i))/2)<<i
#define prINT(i) cout<<setw((80+intlen(i))/2)<<i
char setpass[20]; //temporarily stores new password when trying to change it
int N=0; //no of items in cart
struct transID
{
	long ID;
	transID * next;
};
class stack //stores IDs of books that satisfy search criteria so that data can be compiled accordingly
{
	transID * top;
	public:
	stack()
	{
		top=NULL;
	}
	void push(long ID)
	{
		transID * p=new transID;
		p->ID=ID;
		p->next=top;
		top=p;
	}
	transID * rettop()
	{
		return top;
	}
};
struct buy
{
	long ID;
	int quantity;
}cart[5];
char * space(int i,char c=' ')  //function to return a string of the character c repeated i times
{
	char * str=new char[i+1];
	str[i]='\0';
	for(i--;i>=0;i--)
		str[i]=c;
	return str;
}
int intlen(long n) //returns no of digits in a number
{
	for(int i=0;n!=0;i++,n/=10);
	return i?i:1;
}
void transinfo(stack);
char * partsearch(int,char);
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
	void sell(int r)
	{
		quantity-=r;
	}
	void assign(long val)
	{
		ID=val;
	}
	void setname(char * str)
	{
		strcpy(name,str);
	}
	void del()
	{
		quantity=-1; //instead of deleting the data of a book from the file
	}    //we decided to do this and not display any books with quantity -1
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
	int retprice()
	{
		return price;
	}
	int retquan()
	{
		return quantity;
	}
	char * rettag(int i)
	{
		return tag[i];
	}
};
void searchscr(int,int,Book *,char);
void Book::add(int mode=1)
{                 //mode=1 for add, 0 for modify
	int select=1; //text field selected (=8 for the done button)
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
	while(c!=27) //ascii for esc key
	{
		clrscr();
		cout<<"\n";
		if(mode)
			print("Add book")<<"\n\n\n";
		else
			print("Modify book")<<"\n\n\n";
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
		cout<<(char)26; //these 2 lines are to print the arrow that shows selection
		gotoxy(1,25);
			c=getch();
		if(c=='\0')
		{
			c=getch(); //keys which give '\0' on press return another character after '\0'
			switch(c)
			{
				case 72: //up arrow key
					if(select!=1)
						select--;
					else
						select=8;
					break;
				case 80: //down arrow key
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
							if(!strcmp(tag[1],"")&&strcmp(tag[2],""))
							{
								strcpy(tag[1],tag[2]);
								tag[2][0]=0;
							}
							if(!strcmp(tag[0],"")&&(strcmp(tag[1],"")))
							{
								strcpy(tag[0],tag[1]);
								tag[1][0]=0;
							}
							if(!strcmp(tag[1],"")&&strcmp(tag[2],""))
							{
								strcpy(tag[1],tag[2]);
								tag[2][0]=0;
							} //these 3 ifs make sure that the tags are filled in order
							return;
						}
					}
					break;
				case 27:
					ID=-1; //to mark that add book cancelled
					break;
				default:
					switch(select)
					{
						case 1:
							if(c=='\b')
								name[0]=0; //clears the name
							else
							{ //redirect to search function
								searchscr(1,2,this,c); //modify the book details
								if(ID) //ID=0 for unknown book name,+ve number for old book
									mode=0; //switches to modify mode
							}
							break;
						case 2:
							if(c=='\b')
								author[0]=0;
							else
							{
								char * temp=partsearch(1,c); //returns the string with author name
								if(temp!=NULL) //partsearch returns null pointer if user presses Esc
								{
									strcpy(author,temp);
								}
							}
							break;
						case 3:
						case 4:
						case 5:
							if(c=='\b')
							{
								if(tag[select-3][0]!='\0')
									tag[select-3][strlen(tag[select-3])-1]='\0';
							}
							else if(strlen(tag[select-3])<19)
							{
								tag[select-3][strlen(tag[select-3])+1]='\0';
								tag[select-3][strlen(tag[select-3])]=c;
							}
							break;
						case 6:
							if(isdigit(c)&&quantity<99)
								quantity=10*quantity+c-48;
							if(c=='\b')
								quantity/=10;
							break;
						case 7:
							if(isdigit(c)&&price<6500)
								price=10*price+c-48;
							if(c=='\b')
								price/=10;
					}
			}
	}
}
void Book::show() //shows the data in the object for search
{
	cout<<endl;
	cout<<"     #"<<ID<<space(49-intlen(ID)-intlen(quantity))<<"Availibility: "<<quantity<<" items"<<endl;
	cout<<"     "<<name<<endl;
	cout<<"     by "<<author<<endl;
	cout<<"     Tags: ";
	cout<<tag[0];
	if(strcmp(tag[1],""))
		cout<<", "<<tag[1];
	if(strcmp(tag[2],""))
		cout<<", "<<tag[2];
	cout<<space(60-strlen(tag[0])-(strlen(tag[1])==0?0:(strlen(tag[1])+2))-(strlen(tag[2])==0?0:strlen(tag[2])+2)-intlen(price))<<"Rs. "<<price<<endl;
}
class Transaction
{
	long ID;
	buy list[5]; //the cart gets copied here on transaction
	int price[5]; //stores price because that might be edited later
	double total;
	char date[9]; //picks from computer's date on transaction
	public:
	char * retdate()
	{
		return date;
	}
	void assign(long id)
	{
		ID=id;
	}
	void add();
	int retprice(int i)
	{
		return price[i];
	}
	double rettotal()
	{
		return total;
	}
	buy retlist(int i)
	{
		return list[i];
	}
	void show();
	void showpart();
};
void Transaction::showpart()
{
	int quan=0,total=0,i=0;
	while(list[i].quantity)
	{
		quan+=list[i].quantity;
		total+=price[i]*list[i].quantity;
		i++;
	}
	cout<<endl<<setw(9+intlen(ID)/2)<<ID<<setw(13-intlen(ID)/2+strlen(date))<<date<<setw(26-strlen(date)+intlen(quan)/2)<<quan<<setw(19-intlen(quan)/2+intlen(total)/2)<<total<<endl;
}
void Transaction::add()
{
	list[N].ID=0,total=0;
	Book b;
	ifstream fin;
	fin.open("booklist.dat",ios::binary);
	for(int i=0;i<N;i++)
	{
		list[i].ID=cart[i].ID;
		list[i].quantity=cart[i].quantity;
		fin.seekg((list[i].ID-1)*sizeof(b),ios::beg);
		fin.read((char *)&b,sizeof(b));
		price[i]=b.retprice();
		total+=list[i].quantity*price[i];
	}
	list[i].quantity=0;
	_strdate(date);
}
void Transaction::show()
{
	cout<<endl<<"  Transaction ID: "<<ID<<setw(52-intlen(ID))<<"Date: "<<date<<"\n\n";
	cout<<setw(9)<<"Book ID"<<setw(9)<<"Name"<<setw(51)<<"Price"<<setw(9)<<"Quantity"<<endl<<" "<<space(78,'-');
	ifstream fin;
	Book b;
	fin.open("booklist.dat",ios::binary);
	for(int i=0;list[i].quantity;i++)
	{
		fin.seekg((list[i].ID-1)*sizeof(b));
		fin.read((char *)&b,sizeof(b));
		cout<<endl<<"  #"<<list[i].ID<<space(11-intlen(list[i].ID))<<b.retname()<<space(50-strlen(b.retname()))<<price[i]<<space(6-intlen(price[i]))<<list[i].quantity<<endl;
	}
	fin.close();
	cout<<" "<<space(78,'-')<<endl<<space(64)<<total<<endl<<" "<<space(78,'-');
}
void transinfo(stack s)
{
	clrscr();
	Transaction t[8],t1;
	int j=0,select=0,start=0,total=0,quan=0,found;
	ifstream fin;
	fin.open("transact.dat",ios::binary);
	if(!fin)
	{
		clrscr();
		gotoxy(1,13);
		print("No transactions yet");
		if(!getch())
			getch();
		return;
	}
	while(fin.read((char *)&((j<start)?t[0]:(j-start<8?t[j-start]:t1)),sizeof(t1)))
	{
		found=0;
		for(int i=0;i<5&&((j<start)?t[0]:(j-start<8?t[j-start]:t1)).retlist(i).quantity;i++)
		{
			for(transID * p=s.rettop();p!=NULL;p=p->next)
			{
				if(p->ID==((j<start)?t[0]:(j-start<8?t[j-start]:t1)).retlist(i).ID)
				{
					quan+=(j<start?t[0]:(j-start<8?t[j-start]:t1)).retlist(i).quantity;
					total+=((j<start?t[0]:(j-start<8?t[j-start]:t1)).retlist(i).quantity)*(t[j<start?0:(j-start)].retprice(i));
					if(!found)
					{
						j++;
						found=1;
					}
				}
			}
		}
	}
	if(!quan)
	{
		clrscr();
		gotoxy(1,13);
		print("No matching transactions found");
		if(!getch())
			getch();
		fin.close();
		return;
	}
	while(1)
	{
		clrscr();
		cout<<endl;
		print("Matching transactions")<<"\n\n";
		cout<<"     Total items sold: "<<quan<<setw(52-intlen(quan)-intlen(total))<<"Amount transacted: "<<total<<"\n\n";
		cout<<setw(10)<<"ID"<<setw(23)<<"Date (MM/DD/YY)"<<setw(20)<<"Total items"<<setw(20)<<"Total amount"<<endl<<" "<<space(78,'-');
		for(int i=0;i<j-start;i++)
		{
			t[i].showpart();
		}
		cout<<' '<<space(78,'-');
		gotoxy(1,25);
		print("Arrow keys and enter key to navigate search results");
		if(select>j-start)
			select=j-start;
		if(select)
		{
			gotoxy(5,select*2+6);
			cout<<(char)26;
		}
		switch(getch())
		{
			case 27:
				fin.close();
				return;
			case 0:
				switch(getch())
				{
					case 72:
						if(select>1)
							select--;
						else if(start)
							start--;
						break;
					case 80:
						if(select<j-start)
							select++;
						else if(j-start==9)
							start++;
				}
				break;
			case '\r':
				if(select)
				{
					clrscr();
					t[select-1].show();
					if(!getch())
						getch();
				}
		}
	}
}
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
	else if(code==4)
		print("Confirm by entering old password");
	else if(code==5)
		print("Enter new password");
	else if(code==6)
		print("Re-enter new password");
	else if(code==7)
		print("Passwords do not match, please re-enter");
	cout<<endl<<setw((80+strlen("Enter password (Esc to cancel) : ")-len)/2)<<"Enter password (esc to quit) : ";
	for(int i=len;i>0;i--)
	{
		cout<<"*";
	}
}
int pass(int code=1,int mode=0)
{
	clrscr();
	char c,pass[20]="",corr[20];
	passout(0,code);
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
	if(!mode)
	{
		ifstream fin;
		fin.open("encryp.txt");
		fin.getline(corr,20);
		fin.close();
		return strcmp(pass,corr)==0?0:1;
	}
	else if(strcmp(pass,""))
	{
		if(code==5)
		{
			strcpy(setpass,pass);
			return 0;
		}
		else
			return (strcmp(setpass,pass)==0?0:1);
	}
	else
		return 1;
}
void bookmenu(Book b)
{
	while(1)
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
				for(int k=0,l=0;k<N&&l==0;k++)
					if(b.retID()==cart[k].ID)
						l=1;
				clrscr();
				gotoxy(1,13);
				if(!l&&N<5&&b.retquan())
				{
					cart[N].ID=b.retID();
					cart[N].quantity=1;
					N++;
					print("Book added to cart. To remove or change quantity, go to cart menu.");
					if(!getch())
						getch();
				}
				else
				{
					if(N==5)
					{
						print("Error: cart is already full");
					}
					else if(!b.retquan())
						print("Error: this book is out of stock");
					else
						print("Error: this book is already in the cart");
					if(!getch())
						getch();
				}
				return;
			case '2':
				b.add(0);
				if(b.retID()!=-1)
				{
					for(int k=0,l=0;k<N&&!l;k++)
						if(b.retID()==cart[k].ID)
							l=1;
					if(l==0||(l==1&&cart[k-1].quantity<=b.retquan()))
					{
						fstream fout;
						fout.open("booklist.dat",ios::binary|ios::out|ios::in);
						fout.seekp((b.retID()-1)*sizeof(b));
						fout.write((char *)&b,sizeof(b));
						fout.close();
						clrscr();
						gotoxy(1,13);
						print("Book modified successfully");
						if(!getch())
							getch();
					}
					else
					{
						clrscr();
						gotoxy(1,13);
						print("Error: Cannot edit quantity to lower than that in cart");
						if(!getch())
							getch();
					}
				}
				return;
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
				return;
		}
	}
}
void searchscr(int type,int mode=1,Book * b=NULL,char x=0)
{   //mode=1 for search book, 0 for search trans,2 for add book
	clrscr();
	int start=0,range=0,select=0;
	char c,search[30]=" ";
	search[0]=x;
	Book result[4];
	clrscr();
	cout<<'\n';
	print(" Search:")<<endl;
	print(search)<<endl;
	ifstream fin;
	fin.open("booklist.dat",ios::binary);
	int j=0;
	while(j<4&&fin.read((char *)&result[j],sizeof(result[j])))
	{
		if(mode==2)
		{
			if(result[j>start?(j-start):0].retquan()!=-1&&(strstr((type==1?result[j>start?(j-start):0].retname():result[j>start?(j-start):0].retauth()),search)!=NULL))
				j++;
		}
		else
		{
			if(result[j%4].retquan()!=-1)
				j++;
		}
	}
	fin.close();
	range=j;
	for(int i=0;i<range;i++)
		result[i].show();
	gotoxy(1,25);
	print("Arrow keys and enter key to navigate and select search results");
	for(i=(mode==2?1:0);;i<50?i++:(i=50))
	{
		c=getch();
		switch(c)
		{
			case 27:
				return;
			case '\r':
				if(select!=0)
				{
					if(mode==1)
						bookmenu(result[select-1]);
					else if(!mode)
					{
						stack s;
						s.push(result[select-1].retID());
						transinfo(s);
					}
					else
					{
						*b=result[select-1];
						return;
					}
				}
				else if(mode==2)
				{
					(*b).setname(search);
					return;
				}
				i--;
				break;
			case '\b':
				select=0;
				start=0;
				if(i!=0)
				{
					search[i-1]='\0';
					i--;
				}
				i--;
				break;
			case '\0':
				c=getch();
				i--;
				if(c==80)
				{
					if(select<range)
						select++;
					else if(range==4)
						start++;
				}
				else if(c==72)
				{
					if(select>1)
						select--;
					else if(start>0)
						start--;
				}
				break;
			default:
				select=0;
				start=0;
				search[i]=c;
				search[i+1]=0;
		}
		ifstream fin;
		fin.open("booklist.dat",ios::binary);
		int j=0;
		while(j<(start+4)&&fin.read((char *)&result[j>start?(j-start):0],sizeof(result[0])))
		{
			if(type==1||type==2)
			{
				if(result[j>start?(j-start):0].retquan()!=-1&&(strstr((type==1?result[j>start?(j-start):0].retname():result[j>start?(j-start):0].retauth()),search)!=NULL))
					j++;
			}
			else
				if(result[j>start?(j-start):0].retquan()!=-1&&((strstr(result[j>start?(j-start):0].rettag(0),search)!=NULL)||(strstr(result[j>start?(j-start):0].rettag(1),search)!=NULL)||(strstr(result[j>start?(j-start):0].rettag(2),search)!=NULL)))
					j++;
		}
		fin.close();
		range=j-start;
		clrscr();
		cout<<'\n';
		print(" Search:")<<'\n';
		print(search)<<"\n";
		for(int k=0;k<range;k++)
			result[k].show();
		gotoxy(1,25);
		print("Arrow keys and enter key to navigate and select search results");
		if(select>range)
			select=range;
		if(select!=0)
		{
			gotoxy(4,select*5);
			cout<<(char)26;
		}
	}
}
char * partsearch(int type,char x=0)
{
	char c,search[30]=" ";
	search[0]=x;
	Book b;
	ifstream fin("booklist.dat",ios::binary);
	fin.seekg(0,ios::end);
	int select=0,start=0,i=0,found;
	char * result=new char[30*fin.tellg()/sizeof(b)];
	while(i<sizeof(result))
	{
		result[i]=0;
		i+=30;
	}
	while(1)
	{
		clrscr();
		int j=0;
		cout<<endl;
		print("Search:")<<endl;
		print(search)<<"\n\n";
		fin.seekg(0,ios::beg);
		fin.clear();
		while(fin.read((char *)&b,sizeof(b))&&j-start<9)
		{
			if(type==1?(strstr(b.retauth(),search)!=NULL):(strstr(b.rettag(0),search)!=NULL||strstr(b.rettag(1),search)!=NULL||strstr(b.rettag(2),search)!=NULL))
			{
				for(i=0,found=0;!found&&i<j;i++)
					if(!strcmpi(&result[i*30],type==1?b.retauth():(strstr(b.rettag(0),search)!=NULL?b.rettag(0):(strstr(b.rettag(1),search)==NULL?b.rettag(2):b.rettag(1)))))
						found=1;
				if(!found)
				{
					strcpy(&result[30*j++],type==1?b.retauth():(strstr(b.rettag(0),search)!=NULL?b.rettag(0):(strstr(b.rettag(1),search)==NULL?b.rettag(2):b.rettag(1))));
				}
			}
		}
		for(i=start;i<j;i++)
			print(&result[i*30])<<"\n\n";
		if(select>j-start)
			select=j-start;
		if(select)
		{
			gotoxy(20,3+2*select);
			cout<<(char)26;
		}
		c=getch();
		switch(c)
		{
			case 27:
				delete result;
				fin.close();
				return NULL;
			case 0:
				switch(getch())
				{
					case 72:
						if(select>1)
							select--;
						else if(start)
							start--;
						break;
					case 80:
						if(select<j-start)
							select++;
						else if(j-start==9)
							start++;
				}
				break;
			case '\r':
				if(x)
				{
					if(select)
						strcpy(search,&result[(select+start-1)*30]);
					delete result;
					fin.close();
					return search;
				}
				else if(select)
				{
					fin.seekg(0,ios::beg);
					fin.clear();
					stack s;
					while(fin.read((char *)&b,sizeof(b)))
						if((type==1)?(!strcmpi(b.retauth(),&result[(select+start-1)*30])):(!strcmpi(b.rettag(0),&result[(start+select-1)*30])||!strcmpi(b.rettag(1),&result[(select+start-1)*30])||!strcmpi(b.rettag(2),&result[(select+start-1)*30])))
							s.push(b.retID());
					transinfo(s);
					break;
				}
				break;
			case '\b':
				select=0;
				start=0;
				search[strlen(search)-1]=0;
				break;
			default:
				select=0;
				start=0;
				if(strlen(search)<(type==1?30:20))
				{
					search[strlen(search)+1]=0;
					search[strlen(search)]=c;
				}
		}
	}
}
void searchmenu()
{
	while(1)
	{
		clrscr();
		cout<<"\n\n\n\n";
		print("Search")<<"\n\n\n\n\n";
	  //	print("Press 0              to search by ID")<<"\n\n";
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
				return;
			case '\0':
				getch();
		}
	}
}
void changepass()
{
	int x=1;
	while(x==1)
		x=pass(4);
	if(x==0)
	{
		x=1;
		while(x==1)
		{
			x=pass(5,1);
		}
		if(x==0)
		{
			x=pass(6,1);
			while(x==1)
			{
				x=pass(7,1);
			}
			if(x==0)
			{
				ofstream fout;
				fout.open("encryp.txt");
				fout<<setpass;
				fout.close();
			}
		}
	}
}
void cartmenu()
{
	if(N)
	{
		int k=0,select=0;
		while(1)
		{
			clrscr();
			cout<<endl;
			print("Cart")<<"\n\n";
			Book b;
			cout<<setw(9)<<"Book ID"<<setw(9)<<"Name"<<setw(51)<<"Price"<<setw(9)<<"Quantity"<<endl<<" "<<space(78,'-');
			for(int i=0;i<N;i++)
			{
				ifstream fin;
				fin.open("booklist.dat",ios::binary);
				fin.seekg((cart[i].ID-1)*sizeof(b));
				fin.read((char *)&b,sizeof(b));
				cout<<endl<<"  #"<<cart[i].ID<<space(11-intlen(cart[i].ID))<<b.retname()<<space(50-strlen(b.retname()))<<b.retprice()<<space(6-intlen(b.retprice()))<<cart[i].quantity<<endl;
				fin.close();
			}
			double total=0;
			for(i=0;i<N;i++)
			{
				ifstream fin;
				fin.open("booklist.dat",ios::binary);
				fin.seekg((cart[i].ID-1)*sizeof(b));
				fin.read((char *)&b,sizeof(b));
				total+=cart[i].quantity*b.retprice();
				fin.close();
			}
			cout<<" "<<space(78,'-')<<endl<<space(64)<<total<<endl<<" "<<space(78,'-');
			gotoxy(1,21);
			print("Arrow keys to select")<<endl;
			print("+ and - to increaase/decrease quantity of selected item")<<endl;
			print("Delete key to remove item from cart")<<endl;
			print("Press Enter twice to proceed with transaction");
			if(select)
			{
				gotoxy(2,4+select*2);
				cout<<(char)26;
			}
			else
				gotoxy(1,25);
			switch(getch())
			{
				case 0:
					switch(getch())
					{
						case 72:
							if(select>1)
								select--;
							break;
						case 80:
							if(select<N)
								select++;
							break;
						case 83://delete key
							if(select)
							{
								N--;
								cart[select-1].ID=cart[N].ID;
								cart[select-1].quantity=cart[N].quantity;
							}
					}
					k=0;
					break;
				case '\r':
					gotoxy(1,24);
					if(!k)
					{
						print("Press Enter again to confirm transaction");
						k++;
					}
					else
					{
						Transaction t;
						t.add();
						fstream f;
						f.open("transactions.dat",ios::binary|ios::out|ios::in);
						f.seekg(0,ios::end);
						t.assign(f.tellg()/sizeof(t)+1);
						f.write((char *)&t,sizeof(t));
						f.close();
						f.open("booklist.dat",ios::binary|ios::in|ios::out);
						for(int h=0;h<N;h++)
						{
							f.seekg((cart[h].ID-1)*sizeof(b));
							f.read((char *)&b,sizeof(b));
							b.sell(cart[h].quantity);
							f.seekg((cart[h].ID-1)*sizeof(b));
							f.write((char *)&b,sizeof(b));
						}
						f.close();
						clrscr();
						gotoxy(1,13);
						print("Transaction successful");
						if(!getch())
							getch();
						N=0;
						return;
					}
					break;
				case 27:
					return;
				case '=':
				case '+':
					k=0;
					if(select)
					{
						ifstream fin;
						fin.open("booklist.dat",ios::binary);
						fin.seekg((cart[select-1].ID-1)*sizeof(b));
						fin.read((char *)&b,sizeof(b));
						if(b.retquan()>cart[select-1].quantity)
							cart[select-1].quantity++;
						fin.close();
					}
					break;
				case '-':
					k=0;
					if(select&&cart[select-1].quantity>1)
						cart[select-1].quantity--;
					break;
				default:
					k=0;
			}
		}
	}
	else
	{
		clrscr();
		gotoxy(1,13);
		print("Cart is empty");
		if(!getch())
			getch();
	}
}
void datesearch()
{
	char c,date[]="--/--/--";
	for(int i=0;;i+=(i<6?1:0))
	{
		clrscr();
		gotoxy(1,12);
		print("Enter the date from which transactions are needed")<<endl;
		print(date)<<endl;
		print("(MM/DD/YY)");
		gotoxy(37+(i+i/2),13);
		c=getch();
		switch(c)
		{
			case 0:
				getch();
				break;
			case '\b':
				if(i>0)
					date[(--i)+i/2]='-';
				i--;
				break;
			case '\r':
				if(isdigit(date[0])&&isdigit(date[1])&&isdigit(date[3])&&isdigit(date[4])&&isdigit(date[6])&&isdigit(date[7]))
				{
					Transaction t;
					int found=0;
					long pos=0;
					char tdate[9];
					ifstream fin("transact.dat",ios::binary);
					while(!found&&fin.read((char *)&t,sizeof(t)))
					{
						strcpy(tdate,t.retdate());
						if(date[6]<tdate[6]
						||(date[6]==tdate[6]&&date[7]<tdate[7])
						||(date[6]==tdate[6]&&date[7]==tdate[7]&&date[0]<tdate[0])
						||(date[6]==tdate[6]&&date[7]==tdate[7]&&date[0]==tdate[0]&&date[1]<tdate[1])
						||(date[6]==tdate[6]&&date[7]==tdate[7]&&date[0]==tdate[0]&&date[1]==tdate[1]&&date[3]<tdate[3])
						||(date[6]==tdate[6]&&date[7]==tdate[7]&&date[0]==tdate[0]&&date[1]==tdate[1]&&date[3]==tdate[3]&&date[4]<=tdate[4]))
						{
							found=1;
							pos=fin.tellg()-sizeof(t);
						}
					}
					if(found)
					{
						int start=0,select=0,quan,total,j;
						while(1)
						{
							clrscr();
							cout<<endl;
							print("Matching transactions")<<"\n\n";
							cout<<"\n\n"<<setw(10)<<"ID"<<setw(23)<<"Date (MM/DD/YY)"<<setw(20)<<"Total items"<<setw(20)<<"Total amount"<<endl<<" "<<space(78,'-');
							total=0,quan=0,j=0;
							fin.seekg(pos);
							fin.clear();
							while(fin.read((char *)&t,sizeof(t)))
							{
								if(j>=start&&j<=start+7)
									t.showpart();
								total+=t.rettotal();
								for(int m=0;t.retlist(m).quantity;m++)
									quan+=t.retlist(m).quantity;
								j++;
							}
							cout<<' '<<space(78,'-');
							gotoxy(1,25);
							print("Arrow keys and enter key to navigate search results");
							gotoxy(1,4);
							cout<<"     Total items sold: "<<quan<<setw(52-intlen(quan)-intlen(total))<<"Amount transacted: "<<total<<"\n\n";
							if(select>j-start)
								select=j-start;
							if(select)
							{
								gotoxy(5,select*2+6);
								cout<<(char)26;
							}
							else
								gotoxy(25,80);
							switch(getch())
							{
								case 27:
									fin.close();
									return;
								case 0:
									switch(getch())
									{
										case 72:
											if(select>1)
												select--;
											else if(start)
												start--;
												break;
										case 80:
											if(select<j-start)
												select++;
											else if(j-start==9)
												start++;
									}
									break;
								case '\r':
									if(select)
									{
										clrscr();
										fin.seekg(pos+sizeof(t)*(select-1));
										fin.clear();
										fin.read((char *)&t,sizeof(t));
										t.show();
										if(!getch())
											getch();
									}
							}
						}
					}
					else
					{
						clrscr();
						gotoxy(1,13);
						print("No matching transactions found");
						if(!getch())
							getch();
					}
					fin.close();
				}
				else
				{
					cout<<"y tho ;-;";getch();
				}
				break;
			case 27:
				return;
			default:
				if(isdigit(c))
				{
					date[i+i/2]=c;
				}
				else
					i--;
		}
	}
}
void transmenu()
{
	while(1)
	{
		clrscr();
		cout<<"\n\n\n\n\n";
		print("View Transactions")<<"\n\n\n";
		print("Press 1         to see transactions by book")<<"\n\n";
		print("Press 2       to see transactions by author")<<"\n\n";
		print("Press 3          to see transactions by tag")<<"\n\n";
		print("Press 4      to see transactions since date")<<"\n\n";
		print("Press Esc                 to return to home")<<"\n\n";
		switch(getch())
		{
			case 27:
				return;
			case 0:
				getch();
				break;
			case '1':
				searchscr(1,0);
				break;
			case '2':
				partsearch(1);
				break;
			case '3':
				partsearch(2);
				break;
			case '4':
				datesearch();
		}
	}
}
int menu()
{
	clrscr();
	cout<<"\n\n\n\n\n";
	print("XD Book Shop")<<"\n\n\n";
	print("Press 1         to add book to stock")<<"\n\n";
	print("Press 2         to search for a book")<<"\n\n";
	print("Press 3               to manage cart")<<"\n\n";
	print("Press 4         to view transactions")<<"\n\n";
	print("Press 5           to change password")<<"\n\n";
	print("Press Esc        to log out and quit")<<"\n\n";
	char ch=getch();
	switch(ch)
	{
		case '\0':
			getch();
			return 1;
		case '1':
			fstream fout;
			fout.open("booklist.dat",ios::binary|ios::in|ios::out);
			Book b;
			b.add();
			if(b.retID()==0)
			{
				fout.seekp(0,ios::end);
				b.assign(fout.tellp()/sizeof(b)+1);
				fout.write((char *)&b,sizeof(b));
				clrscr();
				gotoxy(1,13);
				print("Book added successfully");
				if(!getch())
					getch();
			}
			else if(b.retID()!=-1)
			{
				fout.seekp((b.retID()-1)*sizeof(b),ios::beg);
				fout.write((char *)&b,sizeof(b));
				clrscr();
				gotoxy(1,13);
				print("Book modified successfully");
				if(!getch())
					getch();
			}
			return 1;
		case '2':
			searchmenu();
			return 1;
		case '3':
			cartmenu();
			return 1;
		case '4':
			clrscr();
			transmenu();
			return 1;
		case '5':
			changepass();
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