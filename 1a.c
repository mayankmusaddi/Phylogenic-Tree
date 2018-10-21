#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char seq[1000][1000],nm[1000][1000];
int len;

float dist(char *s1,char *s2)
{
	int len1=strlen(s1),len2=strlen(s2),i,j;
	float mis,min=len2;
	for(i=0;i<=len2-len1;i++)
	{
		mis=0;
		for(j=0;j<len1;j++)
			if(s1[j]!=s2[i+j])
				mis++;
		min=(mis<min)?mis:min;
	}
	return (min/len1);
}
float Distance(char *s1,char *s2)
{
	return (strlen(s1)<=strlen(s2))?dist(s1,s2):dist(s2,s1);
}

int main()
{
	FILE * nucl=fopen("Nucleotide.txt","r");
	int i=-1,j;
	char s[1000],w1[1000],w2[1000],w0[1000];
	while(fscanf(nucl,"%[^\n\r]s",s)!=EOF)
	{
		fscanf(nucl,"\n");
		if(s[0]=='>')
		{
			sscanf(s+1,"%s %s %s",w0,w1,w2);
			strcat(w1," ");
			strcat(w1,w2);
			strcpy(nm[++i],w1);
		}
		else
			strcat(seq[i],s);
	}
	len=i+1;
	fclose(nucl);

	FILE * out=fopen("Ndistance.txt","w");
	fprintf(out,"                     *");
	for(i=0;i<len;i++)
		fprintf(out,",%22s",nm[i]);
	fprintf(out,"\n");
	for(i=0;i<len;i++)
	{
		fprintf(out,"%22s",nm[i]);
		for(j=0;j<len;j++)
			fprintf(out,",%22f",Distance(seq[i],seq[j]));
		fprintf(out,"\n");
	}
	fclose(out);
	return 0;
}