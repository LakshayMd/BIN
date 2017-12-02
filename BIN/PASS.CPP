int pass()
{
	clrscr();
	char c,pass[20]="";
	cout<<"Enter password: ";
	for (int i=0;(i==0?1:pass[i-1])!='\0'&&i<20;i++)
	{
		c=getch();
		switch(c)
		{
			case '\b':
				pass[i-1]='\0';
				i-=2;
				break;
			case '\r':
				pass[i]='\0';
				break;
			default:
				pass[i]=c;
		}
		cout<<"Enter password: ";
		for(int j=0;j<=i;j++)
			cout<<'*';
	}
	return strcmp(pass,"correct pass")==0?1:0;
}