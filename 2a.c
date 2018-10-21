#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

char seq[1000][1000],nm[1000][1000];
int len;

int dist(char *s1,char *s2)
{
	FILE *inp=fopen("BLOSUM62.txt","r");
	int mat[1000][1000],num;
	int i=-1,j=0,l,b,c=0,k=0;
	char s[1000],nmt[1000],nm[1000];

	fscanf(inp,"%[^\n\r]s",nmt);
	for(i=1;i<strlen(nmt);i++)
	{
		if(nmt[i]!=' ')
			nm[k++]=nmt[i];
	}
	fscanf(inp,"\n");
	i=-1;
	while(fscanf(inp,"%s",s)!=EOF)
	{
		if(sscanf(s,"%d",&num)==1)
			mat[i][j++]=num;
		else
		{
			b=j;
			i++;
			j=0;
		}
	}
	l=i+1;
	fclose(inp);

	int len1=strlen(s1),len2=strlen(s2);
	int dis,max=INT_MIN,li,lj;
	for(i=0;i<=len2-len1;i++)
	{
		dis=0;
		for(j=0;j<len1;j++)
		{
			char *e;
			e = strchr(nm, s1[j]);
			li = (int)(e - nm);
			e = strchr(nm, s2[i+j]);
			lj = (int)(e - nm);
			dis=dis+mat[li][lj];
		}
		max=(dis>max)?dis:max;
	}
	return max;
}
int Distance(char *s1,char *s2)
{
	return (strlen(s1)<=strlen(s2))?dist(s1,s2):dist(s2,s1);
}

int main()
{
	FILE * nucl=fopen("Protein.txt","r");
	int i=-1,j,k,fl;
	char s[1000];
	while(fscanf(nucl,"%[^\n\r]s",s)!=EOF)
	{
		fscanf(nucl,"\n");
		if(s[0]=='>')
		{
			int lnw=strlen(s);
			i++;
			k=0;
			fl=0;
			for(j=0;j<lnw-2;j++)
			{
				if(s[j]=='[')
					fl=1;
				if(fl==1)
					nm[i][k++]=s[j+1];
			}
		}
		else
			strcat(seq[i],s);
	}
	len=i+1;
	fclose(nucl);

	FILE * out=fopen("Pdistance.txt","w");
	fprintf(out,"                        *");
	for(i=0;i<len;i++)
		fprintf(out,",%25s",nm[i]);
	fprintf(out,"\n");
	for(i=0;i<len;i++)
	{
		fprintf(out,"%25s",nm[i]);
		for(j=0;j<len;j++)
			fprintf(out,",%25d",Distance(seq[i],seq[j]));
		fprintf(out,"\n");
	}
	fclose(out);
	return 0;
}