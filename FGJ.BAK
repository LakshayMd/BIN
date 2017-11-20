#include<iostream.h>
#include<conio.h>
void median()
{
	long kek[101][101],pleb[101],ha[101];
	long num,i,j,temp,d,e;
	cin>>num;
	cout<<"\n";
	for(i=0;i<num;i++)
	{
		   for(j=0;j<num;j++)
	       cin>>kek[i][j];
	      
	}
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
		      ha[j]=kek[i][j];
		}
		for(d=0;d<num;d++)
		{
			for(e=d+1;e<num;e++)
			{
			if(ha[d]>ha[e])
			{
				temp=ha[d];
				ha[d]=ha[e];
				ha[e]=temp;
			}
			}
		}
		pleb[i]=ha[e/2];
		}



	for(d=0;d<num;d++)
	{
		for(e=d+1;e<num;e++)
		{
			if(pleb[d]>pleb[e])
			{
				temp=pleb[d];
				pleb[e]=pleb[d];
				pleb[d]=temp;
			}
		}
	}
	cout<<"\n"<<pleb[d/2-1];
	}
void main()
{
	clrscr();
	int t;
	cin>>t;
	for(int i=0;i<=t-1;i++)
	median();

	getch();
}