#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    char cur = '\0';
    int c = 1;

    for(int i = 1; i < argc; i++)
    {
        FILE* fp = fopen(argv[i], "r");
        if(fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        char* buffer = NULL;
        size_t buffer_size = 0;
        ssize_t read;

        while((read = getline(&buffer, &buffer_size, fp)) != -1)
        {
            int j = 0;
            while(buffer[j] != '\0')
            {
                if(buffer[j] != cur)
                {
                    if(cur != '\0')
                    {
                        fwrite(&c, sizeof(int), 1, stdout);
                        putc(cur, stdout);
                    }
                    cur = buffer[j];
                    c = 1;
                    j++;
                }
                
                while(buffer[j] == cur && buffer[j] != '\0')
                {
                    c++;
                    j++;
                }
            }
        }
        fclose(fp);
    }

    if(cur != '\0')
    {
        fwrite(&c, sizeof(int), 1, stdout);
        putc(cur, stdout);
    }
    return 0;
}