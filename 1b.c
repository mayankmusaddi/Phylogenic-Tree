#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *inp=fopen("Ndistance.txt","r");
	float mat[1000][1000],num;
	int i,j,l,c=0,k=0;
	char s[1000],nmt[1000],nm[1000][1000],s1[1000],s2[1000];
	fscanf(inp,"%[^\n\r]s",nmt);
	for(i=23;i<strlen(nmt);i++)
	{
		if(nmt[i]!=',')
			nm[c][k++]=nmt[i];
		else
		{
			sscanf(nm[c],"%s %s",s1,s2);
			strcpy(nm[c],"");
			strcat(nm[c],s1);
			strcat(nm[c]," ");
			strcat(nm[c],s2);
			if(k>0)
				c++;
			k=0;
		}
	}
	sscanf(nm[c],"%s %s",s1,s2);
	strcpy(nm[c],"");
	strcat(nm[c],s1);
	strcat(nm[c]," ");
	strcat(nm[c],s2);
	fscanf(inp,"\n");
	l=c+1;i=0;
	while(fscanf(inp,"%s",s)!=EOF)
	{
		int lnw=strlen(s);
		if(s[lnw-1]==',')
			s[lnw-1]='\0';
		if(sscanf(s,"%f",&num)==1)
			mat[i][j++]=num;
		if(j==l)
		{
			i++;
			j=0;
		}
	}
	float min=1.5;
	int x,y,end=0;

	for(i=0;i<l;i++)
		mat[i][i]=1.5;
	while(1)
	{
		min=1.5;end=0;
		char upgma[1000];
		for(i=0;i<l;i++)
		{
			for(j=0;j<l;j++)
			{
				if(mat[i][j]==1.5)
					end++;
				if(mat[i][j]<min)
				{
					min=mat[i][j];
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
			mat[x][i]=mat[i][x]=(mat[i][x]+mat[i][y])/2;
			mat[y][i]=1.5;
			mat[i][y]=1.5;
			mat[i][i]=1.5;
		}
	}
	printf("%s\n",nm[x]);
	return 0;
}