#include<stdio.h>
#include<ctype.h>
#include<string.h>
int keyword(char temp[])
{
    char key[32][10] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    int i, flag = 0;
    for(i = 0; i < 32; ++i)
    {
	if(strcmp(key[i], temp) == 0)
	{
	    flag = 1;
	    break;
	}
    }
    return flag;
}
int operator(char ch)
{
    char oper[]={'+','-','*','/','=','<','>','%',','};
    for(int i=0;i<9;i++)
    {
	if(ch==oper[i])
	    return 1;
    }
    return 0;
}
int symbols(char ch)
{
    char sym[]={'}','{',';','(',')','[',']'};
    for(int i=0;i<7;i++)
    {
	if(ch==sym[i])
	    return 1;
    }
    return 0;
}
int main(int argc, char **argv)
{
    int k, i, j=0;
    char op[10],lit[50],temp[10],ch;
    FILE *f1;
    f1=fopen(argv[1],"r");
    while((ch=fgetc(f1))!=EOF)
    {
	if(isalpha(ch) || isdigit(ch) || ch == '.')
	    temp[j++]=ch;
	else if((ch == ' ' || ch == '\n' || operator(ch)) && j!=0)
	{
	    temp[j]='\0';
	    j=0;
	    if(temp[strlen(temp)-2]=='.')
		printf("%s :		 header\n",temp);
	    else if(keyword(temp) == 1)
		printf("%s :		 keyword\n",temp);
	    else
		printf("%s :		 identifier\n",temp);
	}
	else if(ch == '"')
	{
	    ch=fgetc(f1);
	    for(i=0;ch!='"';i++)
	    {
		lit[i]=ch;
		ch=fgetc(f1);
	    }
	    lit[i]='\0';
	    printf("%s :		 literal\n",lit);
	}
	if(operator(ch))
/*	{
	  k=0;
	    while(operator(ch))
	    {
		op[k++]=ch;
		ch=fgetc(f1);
	    }
	    op[k]='\0';*/
	    printf("%c :		 operator\n",ch);
//	}
	else if(symbols(ch))
	    printf("%c :		 symbol\n",ch);
	else if(ch=='#')	
	    printf("%c :		 preprocessor directive\n",ch);
    }
    fclose(f1);
}
