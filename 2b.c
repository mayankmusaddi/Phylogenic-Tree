#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main()
{
	FILE *inp=fopen("Pdistance.txt","r");
	int mat[1000][1000],num;
	int i=-1,j,l,c=0,k=0,p;
	char s[1000],nmt[1000],nm[1000][1000],tmp[1000];
	fscanf(inp,"%[^\n\r]s",nmt);
	for(i=26;i<strlen(nmt);i++)
	{
		if(nmt[i]!=',')
			nm[c][k++]=nmt[i];
		else
		{
			p=0;
			while(nm[c][p]==' ')
				p++;
			strcpy(tmp,nm[c]+p);
			strcpy(nm[c],tmp);
			if(k>0)
				c++;
			k=0;
		}
	}
	p=0;
	while(nm[c][p]==' ')
		p++;
	strcpy(nm[c],nm[c]+p);
	fscanf(inp,"\n");
	l=c+1;i=0;
	while(fscanf(inp,"%s",s)!=EOF)
	{
		int lnw=strlen(s);
		if(s[lnw-1]==',')
			s[lnw-1]='\0';
		if(sscanf(s,"%d",&num)==1)
			mat[i][j++]=num;
		if(j==l)
		{
			i++;
			j=0;
		}
	}
	int max=INT_MIN;
	int x,y,end=0;

	for(i=0;i<l;i++)
		mat[i][i]=INT_MIN;
	while(1)
	{
		max=INT_MIN;end=0;
		char upgma[1000];
		for(i=0;i<l;i++)
		{
			for(j=0;j<l;j++)
			{
				if(mat[i][j]==INT_MIN)
					end++;
				if(mat[i][j]>max)
				{
					max=mat[i][j];
					x=i;
					y=j;
				}
			}
		}
		if(end==(l*l))
			break;
		strcpy(upgma,"");
		strcat(upgma,"(");
		strcat(upgma,nm[x]);
		strcat(upgma,",");
		strcat(upgma,nm[y]);
		strcat(upgma,")");
		strcpy(nm[x],upgma);
		for(i=0;i<l;i++)
		{
			if(mat[x][i]!=INT_MIN)
				mat[x][i]=mat[i][x]=(mat[i][x]+mat[i][y])/2;
			mat[y][i]=INT_MIN;
			mat[i][y]=INT_MIN;
			mat[i][i]=INT_MIN;
		}
	}
	printf("%s\n",nm[x]);
	return 0;
}