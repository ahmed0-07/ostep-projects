#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for(int i = 1; i < argc; i++)
    {
        FILE* fp = fopen(argv[i], "r");
        if(fp == NULL)
        {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
    
    
        int c;
        char ch;
        while(fread(&c, sizeof(int), 1, fp) == 1 && fread(&ch, sizeof(char), 1, fp) == 1)
        {
            for(int j = 0; j < c; j++)
            {
                putc(ch, stdout);
            }
        }
        fclose(fp);
    }
    
    return 0;
}