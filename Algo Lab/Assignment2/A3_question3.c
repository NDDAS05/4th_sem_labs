#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int* subString(char s[], char P[], int strSize, int pSize, int* resultSize)
{
    static int res[1000];
    bool wildCard = (P[pSize-1] == '*');

    for(int i=0;i<=strSize-pSize;i++)
    {
        int match = 1;

        for(int j=0;j<pSize;j++)
        {
            if(j==pSize-1 && wildCard) continue;
            if(s[i+j] != P[j])
            {
                match=0;
                break;
            }
        }
        if(match) res[(*resultSize)++] = i;
    }

    return res;
}

int main()
{
    char str[50];
    char pattern[50];
    int resultSize=0;

    printf("Enter string of c and d: ");
    scanf("%s", str);

    printf("Enter pattern to detect: ");
    scanf("%s", pattern);

    int strSize=strlen(str);
    int pSize=strlen(pattern);

    int* indices=subString(str, pattern, strSize, pSize, &resultSize);

    if(resultSize==0) printf("No matches found.\n");
    else{

        printf("Pattern found at: ");
        for(int i=0;i<resultSize;i++)
        {
            printf("%d  ",indices[i]);
        }

        printf("\n");

    }

    return 0;
}