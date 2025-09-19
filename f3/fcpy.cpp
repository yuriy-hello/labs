/* Copy file argv[1] -> file argv[2] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN int(1<<23) // 8Mb

int main(int argc, char** argv)
{
    if(argc != 3) /* 1: <prog_name> 2: <copy_file> 3: <new_file> */
    {
        printf("Program must has two arguments of command line:\n");
        printf("\t./fcpy <copy_file> <new_file>\n");
        return 0;
    }
    if(strcmp(argv[1], argv[2]) == 0)
    {
        printf("File names are equal.\n");
        return 0;   
    }

    FILE* cpyf_ptr = fopen(argv[1], "rb");
    if(cpyf_ptr == NULL)
    {
        printf("Cant open \x1b[34m%s\x1b[0m file\n", argv[1]);
        return 0;
    }
    FILE* newf_ptr = fopen(argv[2], "wb");
    if(newf_ptr == NULL)
    {
        printf("Cant create or open \x1b[34m%s\x1b[0m file\n",  argv[2]);
        fclose(cpyf_ptr);
        return 0;
    }

    if(fseek(cpyf_ptr, 0, SEEK_END) != 0)
    {
        printf("fseek error\n");
        fclose(cpyf_ptr);
        fclose(newf_ptr);
        return 0;
    }
    long int cpyf_size = ftell(cpyf_ptr); // sizeof(long int) = 8 bytes (on my pc)
    if(cpyf_size == -1l)                  // <number>l == long int(number) (I'm not sure about it)
    {
        printf("ftell error\n");
        fclose(cpyf_ptr);
        fclose(newf_ptr);
        return 0;
    }
    if(fseek(cpyf_ptr, 0, SEEK_SET) != 0)
    {
        printf("fseek error\n");
        fclose(cpyf_ptr);
        fclose(newf_ptr);
        return 0;
    }

    /* Knowing size of copy_file choce optimal length of buffer. */
    long int len_buffer = 0;
    if(cpyf_size > MAX_BUF_LEN)
    {
        len_buffer = MAX_BUF_LEN; // 8Mb 
    }
    else
    {
        len_buffer = cpyf_size;
    }
    char* buf = (char*) malloc(len_buffer);

    /* Let's copying file */
    for( ; ; )
    {
        int len_read = fread(buf, 1, len_buffer, cpyf_ptr);
        if(len_read <= 0)
        {
            if(ferror(cpyf_ptr) != 0)
            {
                printf("Error reading copy_file\n");
                fclose(cpyf_ptr);
                fclose(newf_ptr);
                free(buf);
                return 0;
            }
            break;
        }
        fwrite(buf, 1, len_read, newf_ptr);
        if(ferror(newf_ptr) != 0)
        {
            printf("Error writing new_file\n");
            fclose(cpyf_ptr);
            fclose(newf_ptr);
            free(buf);
            return 0;
        }
    }

    fclose(cpyf_ptr);
    fclose(newf_ptr);
    free(buf);
    return 0;
}