#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv)
{
    // create file
    if(argc == 1)
    {
        printf("You don't enter name of file\n");
        exit(-1);
    }
    ++argv;
    FILE* f_ptr = fopen(*argv, "w");
    if(f_ptr == NULL)
    {
        printf("Can't create file %s\n", *argv);
        exit(-1);
    }

    int len = 11;
    char* data = (char*) malloc(len);
    double pi = M_PI;
    for(int i = 0; i < len; ++i)
    {
        data[i] = char(int(pi));
        pi = (pi -  int(pi)) * 10;
    }
    fwrite(data, 1, len, f_ptr);
    fclose(f_ptr);

    
    // open rb
    f_ptr = fopen(*argv, "rb");
    if(f_ptr == NULL)
    {
        printf("Can't open file %s\n", *argv);
        exit(-1);
    }

    for(int i = 1 ; ; ++i)
    {
        int c = fgetc(f_ptr);
        if(c == EOF) break;
        printf("char %d: %c\n", i, char(c));
        printf("int _flags = \t\t\t%d\n", f_ptr->_flags);
        printf("char *_IO_read_ptr = \t\t%p\n", (void*) f_ptr->_IO_read_ptr);
        printf("char *_IO_read_end = \t\t%p\n", (void*) f_ptr->_IO_read_end);
        printf("char *_IO_read_base = \t\t%p\n", (void*) f_ptr->_IO_read_base);
        printf("char *_IO_rwrite_base = \t%p\n", (void*) f_ptr->_IO_write_base);
        printf("char *_IO_rwrite_ptr = \t\t%p\n", (void*) f_ptr->_IO_write_ptr);
        printf("char *_IO_rwrite_end = \t\t%p\n", (void*) f_ptr->_IO_write_end);
        printf("char *_IO_buf_base = \t\t%p\n", (void*) f_ptr->_IO_buf_base);
        printf("char *_IO_buf_end = \t\t%p\n", (void*) f_ptr->_IO_buf_end);
        printf("char *_IO_save_base = \t\t%p\n", (void*) f_ptr->_IO_save_base);
        printf("char *_IO_backup_base = \t%p\n", (void*) f_ptr->_IO_backup_base);
        printf("char *_IO_save_end = \t\t%p\n", (void*) f_ptr->_IO_save_end);
        printf("struct _IO_marker *_markers = \t%p\n", (void*) f_ptr->_markers);
        printf("struct _IO_FILE *_chain = \t%p\n", (void*) f_ptr->_chain);
        printf("int _fileno = \t\t\t%d\n", f_ptr->_fileno);
        printf("int _flags2 = \t\t\t%d\n", f_ptr->_flags2);
        printf("sizeof(__off_t) = \t\t%ld\n", sizeof(__off_t));
        printf("__off_t _old_offset = \t\t%ld\n", f_ptr->_old_offset);
        printf("unsigned short _cur_column = \t%hu\n", f_ptr->_cur_column);
        printf("signed char _vtable_offset = \t%d\n", f_ptr->_vtable_offset);
        printf("char _shortbuf[1] = %c\n", f_ptr->_shortbuf[1]);
        printf("_IO_lock_t *_lock = \t\t%p\n", (void*) f_ptr->_lock);
        printf("\n#########################################################\n");
    }
    fclose(f_ptr);
    printf("\n");

    
    // open rb
    f_ptr = fopen(*argv, "rb");
    if(f_ptr == NULL)
    {
        printf("Can't open file %s\n", *argv);
        exit(-1);
    }
    if(fseek(f_ptr, 3, SEEK_SET) != 0)
    {
        printf("fseek error\n");
        exit(-1);
    }

    char* buf = (char*) malloc(4);
    if(fread(buf, 1, 4, f_ptr) != 4)
    {
        printf("fread error\n");
        exit(-1);
    }
    printf("4 byte of buf *(int*( char* )): %d\n", *((int*) buf));
    fclose(f_ptr);

    return 0;
}