#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "com_str.h"

/*
COLOR_KODE:
               0   to restore default color
               1   for brighter colors
               4   for underlined text
               5   for flashing text
              30   for black foreground
              31   for red foreground
              32   for green foreground
              33   for yellow (or brown) foreground
              34   for blue foreground
              35   for purple foreground
              36   for cyan foreground
              37   for white (or gray) foreground
              40   for black background
              41   for red background
              42   for green background
              43   for yellow (or brown) background
              44   for blue background
              45   for purple background
              46   for cyan background
              47   for white (or gray) background
*/

void hello()
{
    printf("\x1b[33m### ## # \x1b[1mHello ! \x1b[0m\x1b[33m# ## ###\x1b[0m\n");

    /*
    printf("%s\n", c_Time.n_com);
    printf("%s\n", (*(c_Time.key_com)).n_key);
    printf("%s\n", (*(c_Howmuch.key_com + 4)).n_key);
    */
}

bool check_c(char c)
{
    if(((c >= '0') && (c <= '9')) || 
       ((c >= 'a') && (c <= 'z')) || 
       ((c >= 'A') && (c <= 'Z')))
        return false;
    else return true;
}

void enter(const char* user_f, const char* user_ban)
{
    for( ; ; )
    {
        printf("# Login or crete new account\n");

        char* i_login = (char*) malloc(7);
        bool flag_end_str = false;
        printf("# Log: ");
        for( ; !check_log(i_login, flag_end_str); )
        {
            if(!flag_end_str)
            {
                clean_stdin_buf();
            }
            flag_end_str = false;
            printf("# Log: ");
        }

        // printf("\n%s\n", i_login);
        char* u_pas = (char*) malloc(7);
        int mod = search_log(i_login, user_f, u_pas);
        if(mod == 3) // q
        {
            free(u_pas);
            free(i_login);
            return;
        }
        if(mod == 4) // help
        {
            printf("# login must have length <= 6 and consist of latin letters and numbers\n");
            printf("# password must be a decimal namber betwin 0 and 1e5\n");
            printf("# enter q for exit\n");
            printf("# enter help for get help\n");
            free(u_pas);
            free(i_login);
            continue;
        }

        if((mod == 1) || (mod == 2)) // 1 - new account 2 - first account
        {
            free(u_pas);

            printf("# There is no user with that name \x1b[32m%s\x1b[0m yet\n", i_login);
            printf("# Woul you like to create a new account?\n# print yes/no\n# ");
            if(user_answer())
            {
                char* i_pas = (char*) malloc(7);
                reg(i_pas, i_login);

                add_account(user_f, i_login, i_pas);
                int exit_mod = u_session(user_f, i_login, i_pas, user_ban);

                free(i_login);
                free(i_pas);

                if(exit_mod == 1)
                {
                    return;
                }
                if(exit_mod == 2)
                {
                    continue;
                }
                break;
            }
            else
            {
                free(i_login);
                continue;
            }
        }

        if(mod == 0) // such the user exists
        {
            aut(i_login, u_pas);
            int exit_mod = u_session(user_f, i_login, u_pas, user_ban);

            free(u_pas);
            free(i_login);
            if(exit_mod == 1)
            {
                return;
            }
            if(exit_mod == 2)
            {
                continue;
            }
            break;
        }
    }
}

bool user_answer()
{
    int c = 0;
    int ans_mod = 0;
    int len = 0;
    for( ; c != '\n'; )
    {
        c = getchar();
        ++len;

        if((len == 1) && ((c == 'y') || (c == 'Y'))) ++ans_mod;
        if((len == 2) && ((c == 'e') || (c == 'E')) && (ans_mod == 1)) ++ans_mod;
        if((len == 3) && ((c == 's') || (c == 'S')) && (ans_mod == 2)) ++ans_mod;
    }

    if((ans_mod == 1) && (len == 2)) return true;
    if((ans_mod == 2) && (len == 3)) return true;
    if((ans_mod == 3) && (len == 4)) return true;

    return false;
}

bool check_log(char* i_login, bool &flag_end_str)
{
    bool good_log = false;

    for(int i = 0; ; ++i)
    {
        int c = getchar();
        if(c == '\n')
        {
            if(i > 0) good_log = true;
            else
            {
                flag_end_str = true;
                printf("# \x1b[31mlogin is empty\x1b[0m\n");
            }
            i_login[i] = '\0';
            break;
        }

        if(c == EOF)
        {
            printf("# \x1b[31mEOF error\x1b[0m\n");
            break;
        }


        if(check_c(c))
        {
            printf("# \x1b[31mOnly latin letters and numbers are allowed\x1b[0m\n");
            printf("# sybol \x1b[32m%c\x1b[0m is'n correct\n", char(c));
            break;
        }

        if( i == 6)
        {
            printf("# \x1b[31mThe login length can't exceed 6 characters\x1b[0m\n");
            break;
        }

        i_login[i] = char(c);
    }

    return good_log;
}

void clean_stdin_buf()
{
    int c = 0;
    for( ; c != '\n'; )
    {
        c = getchar();
    }
}

int search_log(char* log, const char* user_f, char* u_pas)
{
    if(strcmp(log, "q") == 0) return 3; // exit
    if(strcmp(log, "help") == 0) return 4; // show help

    FILE* u_log_ptr = fopen(user_f, "r");
    if(u_log_ptr == NULL)
    {
        printf("# \x1b[31merror: file\x1b[0m \x1b[32m%s\x1b[0m \x1b[31doesn't found\x1b[0m\n", user_f);
        free(u_pas);
        free(log);
        exit(-1);
    }

    char* u_log = (char*) malloc(15);
    for(int i = 0; ; ++i)
    {
        if(fgets(u_log, 15, u_log_ptr) == NULL)
        {
            if(i == 0)
            {
                free(u_log);
                return 2; // it is the first user
            }
            else
            {
                free(u_log);
                return 1; // need add user to data file
            }
        }

        char* u_hash = strstr(u_log, " ");
        *u_hash = '\0';

        if(strcmp(log, u_log) == 0)
        {
            ++u_hash;
            for( ; *u_hash == ' '; ++u_hash){}
            for(int i = 0 ; ; ++i)
            {
                if(u_hash[i] == '\n')
                {
                    u_hash[i] = '\0';
                    break;
                }
            }
            strcpy(u_pas, u_hash);
            free(u_log);
            return 0; // such user is exist already
        }
    }
}

void check_data_f(const char* user_f, const char* user_ban)
{
    FILE* u_log_ptr = fopen(user_f, "r");
    if(u_log_ptr == NULL)
    {
        u_log_ptr = fopen(user_f, "w");
        if(u_log_ptr == NULL)
        {
            printf("# \x1b[31merror: cant crete file\x1b[0m \x1b[32m%s\x1b[0m\n", user_f);
            exit(-1);
        }
        fclose(u_log_ptr);
    }
    else fclose(u_log_ptr);

    FILE* u_ban_ptr = fopen(user_ban, "r");
    if(u_ban_ptr == NULL)
    {
        u_ban_ptr = fopen(user_ban, "w");
        if(u_ban_ptr == NULL)
        {
            printf("# \x1b[31merror: cant crete file\x1b[0m \x1b[32m%s\x1b[0m\n", user_ban);
            exit(-1);
        }
        fclose(u_ban_ptr);
    }
    else fclose(u_ban_ptr);

    char* _u_ban = (char*) malloc(strlen(user_ban) + 2);
    _u_ban[0] = '.';
    ++_u_ban;
    strcpy(_u_ban, user_ban);
    --_u_ban;
    u_ban_ptr = fopen(_u_ban, "r");
    if(u_ban_ptr == NULL)
    {
        u_ban_ptr = fopen(_u_ban, "w");
        if(u_ban_ptr == NULL)
        {
            printf("# \x1b[31merror: cant crete file\x1b[0m \x1b[32m%s\x1b[0m\n", _u_ban);
            exit(-1);
        }
        fclose(u_ban_ptr);
    }
    else fclose(u_ban_ptr);

    free(_u_ban);
}

bool check_pas(char* i_pas, bool &flag_end_str, char* i_login, char* u_pas)
{
    bool good_pas = false;

    for(int i = 0; ; ++i)
    {
        int cp = getchar();
        if(cp == '\n')
        {
            if(i > 0) good_pas = true;
            else
            {
                flag_end_str = true;
                printf("\x1b[0m# \x1b[31mpassword is empty\x1b[0m\n");
            }
            i_pas[i] = '\0';

            if((i == 6) && (strcmp(i_pas, "100000") > 0))
            {
                good_pas = false;
                flag_end_str = true;
                printf("\x1b[0m# \x1b[31mThis decimal numbers > 1e5\x1b[0m\n");
            }
            break;
        }

        if(cp == EOF)
        {
            printf("\x1b[0m# \x1b[31mEOF error\x1b[0m\n");
            break;
        }


        if(check_cp(cp))
        {
            if((i == 0) && (cp == 'q'))
            {
                if(getchar() == '\n')
                {
                    free(i_login);
                    free(i_pas);
                    free(u_pas);
                    exit(0);
                }
            }
            printf("\x1b[0m# \x1b[31mOnly  decimal numbers >= 0 and <= 1e5 are allowed\x1b[0m\n");
            printf("# sybol \x1b[32m%c\x1b[0m is'n correct\n", char(cp));
            break;
        }

        if( i == 6)
        {
            printf("\x1b[0m# \x1b[31mThe password length can't exceed 6 characters\x1b[0m\n");
            break;
        }

        i_pas[i] = char(cp);
    }

    return good_pas;
}

bool check_cp(char cp)
{
    if((cp >= '0') && (cp <= '9'))
        return false;
    else return true;
}

void reg(char* i_pas, char* i_login)
{
    for( ; ; )
    {
        bool flag_end_str = false;
        printf("# Pas: \x1b[30m");
        for( ; !check_pas(i_pas, flag_end_str, i_login); )
        {
            if(!flag_end_str)
            {
                clean_stdin_buf();
            }
            flag_end_str = false;
            printf("\x1b[0m# Pas: \x1b[30m");
        }

        int pas_1 = int(strtol(i_pas, NULL, 10));
        flag_end_str = false;

        printf("\x1b[0m# Repeat password\n");
        printf("# Pas: \x1b[30m");
        for( ; !check_pas(i_pas, flag_end_str, i_login); )
        {
            if(!flag_end_str)
            {
                clean_stdin_buf();
            }
            flag_end_str = false;
            printf("\x1b[0m# Pas: \x1b[30m");
        }

        int pas_2 = int(strtol(i_pas, NULL, 10));
        if(pas_1 == pas_2)
        {
            printf("\x1b[0m# Saving data\n");
            break;
        }
        else printf("\x1b[0m# Passwords are different. Enter new password\n");
    }
}

void add_account(const char* user_f, char* i_login, char* i_pas)
{
    FILE* ac_ptr = fopen(user_f, "a");
    fprintf(ac_ptr, "%-6s %6s\n", i_login, i_pas);
    fclose(ac_ptr);
}

int u_session(const char* user_f, char* u_log, char* u_pas, const char* user_ban)
{
    /* Check user on ban */
    bool u_ban_flag = check_u_ban(u_log, user_ban);

    printf("\x1b[0m# Hello \x1b[32m%s\x1b[0m!\n", u_log);
    if(u_ban_flag)
    {
        printf("\x1b[0m# You have been banned.\n");
        printf("\x1b[0m# In this session you can use only two commands:\n\tq\tLoguot\n");

        remov_ban(u_log, user_ban);
    }

    /* Get command */
    char* input_com = NULL;
    for( ; ; )
    {
        printf("\x1b[0m# \x1b[32m%s\x1b[0m: ", u_log);

        int len = get_com(&input_com);
        char* start_w = input_com;
        char* end_w = NULL;
        bool end_flag = false;
        next_word(start_w, end_w, end_flag);
        if(start_w == end_w)
        {
            free(input_com);
            continue;
        }
        
        bool mod_flag = true;
        int mod = 0;

        if(mod_flag && (strcmp(start_w, name_c_q) == 0))
        {
            mod_flag = false;
            mod = 1; // q
        }

        if(mod_flag && (strcmp(start_w, name_c_help) == 0))
        {
            mod_flag = false;
            mod = 2; // help
        }

        if(mod_flag && (strcmp(start_w, name_c_Time) == 0))
        {
            mod_flag = false;
            mod = 3; // Time
        }

        if(mod_flag && (strcmp(start_w, name_c_Date) == 0))
        {
            mod_flag = false;
            mod = 4; // Date
        }

        if(mod_flag && (strcmp(start_w, name_c_Howmuch) == 0))
        {
            mod_flag = false;
            mod = 5; // Howmuch
        }

        if(mod_flag && (strcmp(start_w, name_c_Logout) == 0))
        {
            mod_flag = false;
            mod = 6; // Logout
        }

        if(mod_flag && (strcmp(start_w, name_c_Sanctions) == 0))
        {
            mod_flag = false;
            mod = 7; // Sanctions
        }

        int proc_ret = 0; // process return
        switch(mod)
        {
            case 0: // incorrect command
                printf("\x1b[0m# \x1b[32m%s\x1b[0m: Command \x1b[31m%s\x1b[0m don't found\n", u_log, start_w);
                free(input_com);
                break;

            case 1: // q
                proc_ret = process_c_q(start_w, end_w, end_flag, u_log);
                free(input_com);
                if(proc_ret == 1) return 1; // exit from program
                break;

            case 2: // help
                if(u_ban_flag)
                {
                    printf("\x1b[0m# The command is unavailable\n");
                    free(input_com);
                    break;
                }
                process_c_help(start_w, end_w, end_flag, u_log);
                free(input_com);
                break;

            case 3: // Time
                if(u_ban_flag)
                {
                    printf("\x1b[0m# The command is unavailable\n");
                    free(input_com);
                    break;
                }
                process_c_Time(start_w, end_w, end_flag, u_log);
                free(input_com);
                break;
            
            case 4: // Date
                if(u_ban_flag)
                {
                    printf("\x1b[0m# The command is unavailable\n");
                    free(input_com);
                    break;
                }
                process_c_Date(start_w, end_w, end_flag, u_log);
                free(input_com);
                break;
            
            case 5: // Howmach
                if(u_ban_flag)
                {
                    printf("\x1b[0m# The command is unavailable\n");
                    free(input_com);
                    break;
                }
                process_c_Howmuch(start_w, end_w, end_flag, u_log);
                free(input_com);
                break;

            case 6: // Logout
                proc_ret = process_c_Logout(start_w, end_w, end_flag, u_log);
                free(input_com);
                if(proc_ret == 2) return 2;
                break;

            case 7: // Sanctions
                if(u_ban_flag)
                {
                    printf("\x1b[0m# The command is unavailable\n");
                    free(input_com);
                    break;
                }
                process_c_Sanctions(start_w, end_w, end_flag, u_log, user_f, user_ban);
                free(input_com);
                break;
        }
    }

    return 0;
}

void aut(char* i_login, char* u_pas)
{
    for( ; ; )
    {
        bool flag_end_str = false;
        char* i_pas = (char*) malloc(7);
        printf("\x1b[0m# Pas: \x1b[30m");
        for( ; !check_pas(i_pas, flag_end_str, i_login); )
        {
            if(!flag_end_str)
            {
                clean_stdin_buf();
            }
            flag_end_str = false;
            printf("\x1b[0m# Pas: \x1b[30m");
        }

        int pas_1 = int(strtol(i_pas, NULL, 10));
        int pas_2 = int(strtol(u_pas, NULL, 10));
        if(pas_1 == pas_2)
        {
            free(i_pas);
            break;
        }
        else
        {
            printf("\x1b[0m# Incorrect password\n# Please try again\n");
            free(i_pas);
            continue;
        }
    }
}

int get_com(char** input_com)
{
    int len = 16;
    *input_com = (char*) malloc(len);
    int n_ch = 0;

    for( ; ; )
    {
        int c = getchar();
        
        if(n_ch == len)
        {
            inc_mas(input_com, len);
        }

        if((c == '\n') || (c == EOF))
        {
            (*input_com)[n_ch] = '\0';
            ++n_ch;
            return n_ch;
        }

        (*input_com)[n_ch] = (char) c;
        ++n_ch;
    }

    return 0;
}

void inc_mas(char** input_com, int& len)
{
    char* tmp_mas =(char*) malloc(len);
    for(int i = 0; i < len; ++i)
    {
        tmp_mas[i] = (*input_com)[i];
    }
    free(*input_com);
    len = int(len * 2.718);
    *input_com = (char*) malloc(len);
    for(int i = 0; i < len; ++i)
    {
        (*input_com)[i] = tmp_mas[i];
    }
    free(tmp_mas);
}

void next_word(char*& s_w, char*& e_w, bool& end_flag)
{
    for( ; ;)
    {
        if(*s_w == ' ')
        {
            ++s_w;
            continue;
        }
        else
        {
            e_w = s_w;
            break;
        }
    }
    if(*e_w == '\0') return;
    ++e_w;

    for( ; ;)
    {
        if((*e_w == ' ') || (*e_w == '\0'))
        {
            if(*e_w == '\0') end_flag = true;
            else *e_w = '\0';
            break;
        }
        else
        {
            ++e_w;
            continue;
        }
    }
}

bool check_u_ban(char* u_log, const char* user_ban)
{
    FILE* f_ptr = fopen(user_ban, "r");
    if(f_ptr == NULL)
    {
        printf("\x1b[0m# File %s don't found\n", user_ban);
        exit(-1);
    }
    char* u_log_ban = (char*) malloc(8); // 6 + \n + \0
    for( ; fgets(u_log_ban, 8, f_ptr) != NULL; )
    {
        u_log_ban[strlen(u_log_ban) - 1] = '\0';
        if(strcmp(u_log_ban, u_log) == 0)
        {
            free(u_log_ban);
            fclose(f_ptr);
            return true;
        }
    }

    free(u_log_ban);
    fclose(f_ptr);
    return false;
}

void remov_ban(char* u_log, const char* user_ban)
{
    FILE* out_ptr = fopen(user_ban, "r");
    if(out_ptr == NULL)
    {
        printf("\x1b[0m# File %s don't found\n", user_ban);
        exit(-1);
    }

    char* _user_ban = (char*) malloc(strlen(user_ban) + 2); // len + '.' + '\0'
    _user_ban[0] = '.';
    ++_user_ban;
    strcpy(_user_ban, user_ban);
    --_user_ban;
    FILE* in_ptr = fopen(_user_ban, "w");
    if(in_ptr == NULL)
    {
        printf("\x1b[0m# File %s can't create\n", _user_ban);
        exit(-1);
    }
    /* At this stage we open two file. */

    char* u_log_ban = (char*) malloc(8); // 6 + \n + \0
    for( ; fgets(u_log_ban, 8, out_ptr) != NULL; )
    {
        u_log_ban[strlen(u_log_ban) - 1] = '\0';
        if(strcmp(u_log_ban, u_log) == 0)
        {
            break;
        }

        fprintf(in_ptr, "%s\n", u_log_ban);
    }
    for( ; fgets(u_log_ban, 8, out_ptr) != NULL; )
    {
        fprintf(in_ptr, "%s", u_log_ban);
    }
    fclose(out_ptr);
    fclose(in_ptr);

    /* Now we need to swap the names of these files. */
    const char* tmp_fname = ".tmp_file.txt";
    rename(_user_ban, tmp_fname);
    rename(user_ban, _user_ban);
    rename(tmp_fname, user_ban);
    
    free(_user_ban);
    free(u_log_ban);
}