#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN int(1<<23) // 8Mb

int f_case_1(FILE* f_ptr, char* buf, int len_buffer);
int f_case_2(FILE* f_ptr, char* buf, int len_buffer);
int f_case_3(FILE* f_ptr, char* buf, int len_buffer, int hex_mask);
void print_bits(void* ptr, int size);
bool prime_check(int c, char* prime_ar);

int main(int argc, char** argv)
{
    if((argc != 3) && (argc != 4)) /* 1: <prog_name> 2: <file> 3: <mod> */
    {
        printf("Program must has two or three arguments of command line:\n");
        printf("\t./fcpy <file> <mod>\n");
        return 0;
    }
    int mod = 0;
    bool continue_flag = true;
    if(continue_flag && (strcmp(argv[2], "-xor8") == 0))
    {
        if(argc == 4)
        {
            printf("Key -xor8 hasn't parametr\n");
            return 0;
        }
        mod = 1;
        continue_flag = false;
    }
    if(continue_flag && (strcmp(argv[2], "-xorodd") == 0))
    {
        if(argc == 4)
        {
            printf("Key -xorodd hasn't parametr\n");
            return 0;
        }
        mod = 2;
        continue_flag = false;
    }
    int hex_mask = 0;
    if(continue_flag && (strcmp(argv[2], "-mask") == 0))
    {
        if(argc == 3)
        {
            printf("Key -mask must has parametr\n");
            return 0;
        }
        char* endptr = NULL;
        hex_mask = strtol(argv[3], &endptr, 16);
        if(*endptr != '\0')
        {
            printf("Error in key -mask <par> : par isn't correct (!=hex_num)\n");
            printf("See %ld sybol \x1b[31m%c\x1b[0m\n", endptr - argv[3] + 1, *endptr);
            return 0;
        }
        mod = 3;
        continue_flag = false;
    }
    if(continue_flag) // is equal if(mod == 0)
    {
        printf("Program gets incorrect key\n");
        printf("keys:\n\t-xor8\t-xorodd\t-mask <0xhex_num(int)>\n");
        return 0;
    }

    /* open file */
    FILE* f_ptr = fopen(argv[1], "rb");
    if(f_ptr == NULL)
    {
        printf("Cant open \x1b[34m%s\x1b[0m file\n", argv[1]);
        return 0;
    }

    /* find out the file size */
    if(fseek(f_ptr, 0, SEEK_END) != 0)
    {
        printf("fseek error\n");
        fclose(f_ptr);
        return 0;
    }
    long int f_size = ftell(f_ptr); // sizeof(long int) = 8 bytes (on my pc)
    if(f_size == -1l)               // <number>l == long int(number) (I'm not sure about it)
    {
        printf("ftell error\n");
        fclose(f_ptr);
        return 0;
    }
    if(fseek(f_ptr, 0, SEEK_SET) != 0)
    {
        printf("fseek error\n");
        fclose(f_ptr);
        return 0;
    }
    /* Knowing size of file choce optimal length of buffer. */
    int len_buffer = 0;
    if(f_size > MAX_BUF_LEN)
    {
        len_buffer = MAX_BUF_LEN; // 8Mb 
    }
    else
    {
        len_buffer = f_size;
    }
    char* buf = (char*) malloc(len_buffer);

    switch(mod)
    {
        case 1:
            if(f_case_1(f_ptr, buf, len_buffer))
            {
                return 0;
            }
            break;

        case 2:
            if(f_size < 4)
            {
                printf("Size of file less then 4 bytes\n");
                break;
            }
            if(f_case_2(f_ptr, buf, len_buffer))
            {
                return 0;
            }
            break;

        case 3:
            if(f_case_3(f_ptr, buf, len_buffer, hex_mask))
            {
                return 0;
            }
            break;
    }

    free(buf);
    fclose(f_ptr);
    return 0;
}

/* ######################################################## */
/* FUNC INIT*/
/* ######################################################## */

/* print bits */
void print_bits(void* ptr, int size)
{
    for(int i = size - 1; i >= 0; --i) // start print from older byte
    {
        int c = *(((char*) ptr) + i);
        for(int j = 0; j < 8; ++j)
        {
            printf("%d", bool(c & (1 << 7)));
            c = c << 1;
        }
        printf(" ");
    }
    printf("\n");
}

/* Check bytes on prime */
bool prime_check(int c, char* prime_ar)
{
    char* ptr = (char*) &c;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 54; ++j)
        {
            if(ptr[i] == prime_ar[j])
            {
                return true;
            }
        }
    }
    return false;
}

/* case 1 */
int f_case_1(FILE* f_ptr, char* buf, int len_buffer)
{
    char c_xor = 0;
    for( ; ; )
    {
        int len_read = fread(buf, 1, len_buffer, f_ptr);
        if(len_read <= 0)
        {
            if(ferror(f_ptr) != 0)
            {
                printf("Error reading file\n");
                fclose(f_ptr);
                free(buf);
                return 1;
            }
            break;
        }

        char c = 0;
        for(int i = 0; i < len_read; ++i)
        {
            c = c ^ buf[i];
        }
        /* 
            c ^ 0 = c 
            therefore the first step is correct
        */
        c_xor = c_xor ^ c;
    }

    printf("char: \t\t%c\n", c_xor);
    printf("int o\\d\\x: \t%o\t%d\t%x\n", (int) c_xor, (int) c_xor, (int) c_xor);
    printf("bits: \t\t");
    print_bits(&c_xor, 1);

    return 0;
}

/* case 2 */
int f_case_2(FILE* f_ptr, char* buf, int len_buffer)
{
    /* Create array of prime numbers in interval 1...255 */
    char* prime_ar = (char*) malloc(54);
    prime_ar[0] = (char) 2;
    prime_ar[1] = (char) 3;
    prime_ar[2] = (char) 5;
    prime_ar[3] = (char) 7;
    prime_ar[4] = (char) 11;
    int len_prime_ar = 5;
    for(int i = 13; i < 253; i += 2)
    {
        bool prime_flag = true;
        for(int j = 3; j < i / 3; j += 2)
        {
            if(i % j == 0)
            {
                prime_flag = false;
                break;
            }
        }
        if(prime_flag)
        {
            prime_ar[len_prime_ar] = (char) i;
            ++len_prime_ar;
        }
    }
    /* OK we have array of prime number < 255 */

    int c_xor = 0;
    for( ; ; )
    {
        int len_read = fread(buf, 1, len_buffer, f_ptr);
        if(len_read <= 0)
        {
            if(ferror(f_ptr) != 0)
            {
                printf("Error reading file\n");
                fclose(f_ptr);
                free(prime_ar);
                free(buf);
                return 1;
            }
            break;
        }
        if(len_read < 4)
        {
            break;
        }

        int c = 0;
        for(int i = 0; i < len_read - 3; ++i)
        {
            int tmp_c = *((int*)(buf + i));
            if(prime_check(tmp_c, prime_ar))
            {
                c = c ^ tmp_c;
            }
        }
        c_xor = c_xor ^ c;

        if(fseek(f_ptr, -3, SEEK_CUR) != 0)
        {
            printf("Error in func fseek\n");
            fclose(f_ptr);
            free(prime_ar);
            free(buf);
            return 1;
        }
    }

    printf("int o\\d\\x: \t%o\t%d\t%x\n", c_xor, c_xor, c_xor);
    printf("bits: \t\t");
    print_bits(&c_xor, 4);

    free(prime_ar);
    return 0;
}

/* case 3 */
int f_case_3(FILE* f_ptr, char* buf, int len_buffer, int hex_mask)
{
    int num_mask_value = 0;
    for( ; ; )
    {
        int len_read = fread(buf, 1, len_buffer, f_ptr);
        if(len_read <= 0)
        {
            if(ferror(f_ptr) != 0)
            {
                printf("Error reading file\n");
                fclose(f_ptr);
                free(buf);
                return 1;
            }
            break;
        }
        if(len_read < 4)
        {
            break;
        }

        for(int i = 0; i < len_read - 3; ++i)
        {
            int c = *((int*)(buf + i));
            if((c & hex_mask) == hex_mask)
            {
                ++num_mask_value;
            }
        }

        if(fseek(f_ptr, -3, SEEK_CUR) != 0)
        {
            printf("Error in func fseek\n");
            fclose(f_ptr);
            free(buf);
            return 1;
        }
    }

    printf("Number of masks value = %d\n", num_mask_value);

    return 0;
}