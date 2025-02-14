#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    
    char* search = argv[1];
    if(argc == 2)
    {
        char buffer[256]; 
        while(fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if(strstr(buffer, search) != NULL)
            {
                printf("%s", buffer);
            }
        }
        return 0;
    }

    for(int i = 2; i < argc; i++)
    {
        FILE* fp = fopen(argv[i], "r");
        if(fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        char* buffer = NULL; 
        size_t buffer_size = 0;
        __ssize_t read;

        while((read = getline(&buffer, &buffer_size, fp)) != -1)
        {
            // int j = 0;
            // int can = 0;
            // while(buffer[j] != '\0')
            // {
            //     int idx = 0;
            //     while(buffer[j] == search[idx])
            //     {
            //         idx++;
            //         j++;
            //     }

            //     if(search[idx] == '\0')
            //     {
            //         can = 1;
            //         break;
            //     }
            //     j++;
            // }

            if(strstr(buffer, search) != NULL)
                printf("%s", buffer);
        }
    }
    return 0;
}