#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word{
    char word[100];
    int count;
    int line[100];
} word;
word* w;
int NumOfTokens;

void strlwr(char* token)
{
    for (int i=0; i<strlen(token); i++)
    {
        if (token[i]>='A' && token[i]<='Z')
        token[i]+=32;
    }
}
void print()
{
    int j;
    for (int i=0; i<NumOfTokens; i++)
    {
        j=w[i].count;
        printf("%s %d", w[i].word, w[i].count);
        for (int k=0; k<j; k++)
        {
            printf(", %d",w[i].line[k]);
        }
        printf("\n");
    }
}
int check(int num, char* token)
{
    for (int i=0;i<num; i++)
    {
        if (strcmp(w[i].word,token) == 0) return 1;
    }
    return 0;
}

int check_stopw(word* stopw,int n, char* token)
{
    for (int i=0;i<n; i++)
    {
        if (strcmp(stopw[i].word,token) == 0) return 1;
    }
    return 0;
}
word* store(word* w, int num, char* token, int lineNo){
    word* tmp;
    tmp = (word*) malloc((num+1)*sizeof(word));
    if (num!=0)
    {
        for (int i=0; i<num; i++)
        {
            tmp[i] = w[i];
        }
        free(w);
    }
        strcpy(tmp[num].word,token);
        tmp[num].count=1;
        tmp[num].line[0]=lineNo;
    return tmp;
}

int doctu(FILE *f,word* stopw,int n, int num){
	int lineNo =1;
	char currentChar;
	char token[100];
	currentChar = fgetc(f);
	int i = 0;
    int j;
	while (currentChar != EOF) 
	{
		if ((currentChar >= 'a' && currentChar <= 'z')|| (currentChar >= 'A' && currentChar <= 'Z'))
		{
			token[i++]=currentChar;
		}
		else {
			token[i]='\0';
            strlwr(token);
			if (i!=0){
                if (!check_stopw(stopw,n, token))
                {
                    if (!check(num, token)) 
                    {
                        w = store(w, num, token, lineNo);
                        num++;
                    }
                    else
                    {
                        for(int i=0;i<num;i++)
                        {
                            if (strcmp(w[i].word, token) ==0)
                            {
                                j=w[i].count;
                                w[i].line[j]=lineNo;
                                w[i].count++;
                            }
                        }
                    }
                    
                }
            }
			i=0;
            if (currentChar == '\n') lineNo++;
		}
		currentChar = fgetc(f);
	}
    return num;
}



int main(){
    FILE *f1, *f2;
    NumOfTokens =0;
    if ((f1 = fopen("vanban.txt","r")) == NULL)
    {
        printf("khong mo dc file vanban.txt\n");
        exit(0);
    }
    if ((f2 = fopen("stopw.txt", "r"))== NULL)
    {
        printf("khong mo dc file stopw.txt\n");
        exit(0);
    }
    
    int n=0;
    char test[100];
    
    while (!feof(f2)){
	 fscanf(f2,"%s",test);
	 n++;
    }
    word* stopw = (word*)malloc(n*sizeof(word));
    rewind(f2);
    n=0;
    while (!feof(f2))
    {
        fscanf(f2, "%s", stopw[n].word);
        n++;
    }
    NumOfTokens= doctu(f1,stopw,n, NumOfTokens);
    
    print();
    fclose(f1);
    fclose(f2);
    return 0;
}