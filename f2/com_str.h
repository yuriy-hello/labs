#ifndef COMMAND_STRUCT
#define COMMAND_STRUCT

#include <time.h>

#include "func.h"

struct c_key
{
    const char* n_key = NULL; // name of key
    bool exist_par = false;   // does this key have parametr
    char* par_key = NULL;     // parametr of the key
    bool key_on = false;      // is there the key in the command
};

struct com
{
    const char* n_com = NULL; // name of command

    int num_of_par = 0;       // number of parametrs
    char** par_com = NULL;    // array of strings, one str = one par

    int num_of_keys = 0;      // number of keys
    c_key* key_com = NULL;    // array of structs c_key
};

const char* name_c_Time = "Time";
const char* name_c_Date = "Date";
const char* name_c_Howmuch = "Howmuch";
const char* name_c_Logout = "Logout";
const char* name_c_Sanctions = "Sanctions";
const char* name_c_help = "help";
const char* name_c_q = "q";

const c_key k_help{"--help", false, NULL, false};
const c_key k_Howmuch_s{"-s", false, NULL, false};
const c_key k_Howmuch_m{"-m", false, NULL, false};
const c_key k_Howmuch_h{"-h", false, NULL, false};
const c_key k_Howmuch_y{"-y", false, NULL, false};

/* FUNCTIONS PROTOTIPES START */

void init_c_q(com& c_q);
void inf_com(com& command);
void clean_com(com& command);
void init_c_help(com& c_help);
void init_c_Logout(com& c_Logout);
void init_c_Time(com& c_Time);
void cur_time();
void init_c_Date(com& c_Date);
void cur_date();
void init_c_Howmuch(com& c_Howmuch);
int fill_cstruct(com& c, char*& s_w, char*& e_w, bool& end_flag);
void fill_par_com(com& c, char* input_array, int len, int number_of_par);
int count_key_on(com& c);
void inf_key_com(com& c);
int check_c_Howmuch_com_par(com& c);
int check_value_dmy_hms(com& c, int* dmy_hms);
void cou_elap_time(com& c, int* dmy_hms);
bool get_onkey_c_Howmuch(com& c, int& int_key);
void init_c_Sanctions(com& c_Sanctions);
bool search_log_for_ban(const char* user_f, char* u_log);
bool check_pas_for_ban(char* u_log);
bool is_already_ban(const char* user_ban, char* u_log);

int process_c_q(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_help(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_Logout(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_Time(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_Date(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_Howmuch(char*& s_w, char*& e_w, bool& end_flag, char* u_log);
int process_c_Sanctions(char*& s_w, char*& e_w, bool& end_flag, char* u_log, const char* user_f, const char* user_ban);

/* FUNCTIONS PROTOTIPES   END */

void init_c_q(com& c_q)
{
    c_q.n_com = name_c_q;
    c_q.num_of_par = 0;
    c_q.par_com = NULL;
    c_q.num_of_keys = 1;
    c_q.key_com = (c_key*) malloc(sizeof(c_key) * c_q.num_of_keys);
    c_q.key_com[0] = k_help;
}

void init_c_help(com& c_help)
{
    c_help.n_com = name_c_help;
    c_help.num_of_par = 0;
    c_help.par_com = NULL;
    c_help.num_of_keys = 0;
    c_help.key_com = NULL;
}

void init_c_Logout(com& c_Logout)
{
    c_Logout.n_com = name_c_Logout;
    c_Logout.num_of_par = 0;
    c_Logout.par_com = NULL;
    c_Logout.num_of_keys = 1;
    c_Logout.key_com = (c_key*) malloc(sizeof(c_key) * c_Logout.num_of_keys);
    c_Logout.key_com[0] = k_help;
}

void init_c_Time(com& c_Time)
{
    c_Time.n_com = name_c_Time;
    c_Time.num_of_par = 0;
    c_Time.par_com = NULL;
    c_Time.num_of_keys = 1;
    c_Time.key_com = (c_key*) malloc(sizeof(c_key) * c_Time.num_of_keys);
    c_Time.key_com[0] = k_help;
}

void init_c_Date(com& c_Date)
{
    c_Date.n_com = name_c_Date;
    c_Date.num_of_par = 0;
    c_Date.par_com = NULL;
    c_Date.num_of_keys = 1;
    c_Date.key_com = (c_key*) malloc(sizeof(c_key) * c_Date.num_of_keys);
    c_Date.key_com[0] = k_help;
}

void init_c_Howmuch(com& c_Howmuch)
{
    c_Howmuch.n_com = name_c_Howmuch;
    c_Howmuch.num_of_par = 0;
    c_Howmuch.par_com = NULL;
    c_Howmuch.num_of_keys = 5;
    c_Howmuch.key_com = (c_key*) malloc(sizeof(c_key) * c_Howmuch.num_of_keys);
    c_Howmuch.key_com[0] = k_help;
    c_Howmuch.key_com[1] = k_Howmuch_s;
    c_Howmuch.key_com[2] = k_Howmuch_m;
    c_Howmuch.key_com[3] = k_Howmuch_h;
    c_Howmuch.key_com[4] = k_Howmuch_y;
}

void init_c_Sanctions(com& c_Sanctions)
{
    c_Sanctions.n_com = name_c_Sanctions;
    c_Sanctions.num_of_par = 0;
    c_Sanctions.par_com = NULL;
    c_Sanctions.num_of_keys = 1;
    c_Sanctions.key_com = (c_key*) malloc(sizeof(c_key) * c_Sanctions.num_of_keys);
    c_Sanctions.key_com[0] = k_help;
}

void cur_time()
{
    time_t cur_time = time(NULL);
    tm* hms_cur_time = localtime(&cur_time);
    /* struct tm
            tm_sec
            tm_min
            tm_hour
            tm_mday
            tm_mon
            tm_year
            tm_wday
            tm_yday
            tm_isdst
    */
    printf("\x1b[0m# %02d:%02d:%02d\n", 
            hms_cur_time->tm_hour, 
            hms_cur_time->tm_min, 
            hms_cur_time->tm_sec);
    /*
        for convert time to str use strftime()
    */
}

void cur_date()
{
    time_t cur_date = time(NULL);
    tm* dmy_cur_date = localtime(&cur_date);
    /* struct tm
            tm_sec: 0...60
            tm_min: 0...59
            tm_hour: 0...23
            tm_mday: 1...31
            tm_mon: 0...11
            tm_year: 1900... ,need data + 1900
            tm_wday: 0...6 sunday = 0
            tm_yday: 0...365
            tm_isdst: switching to daylight saving time, if > 0 swith on if = 0 swith off
    */
    printf("\x1b[0m# %02d:%02d:%d\n", 
            dmy_cur_date->tm_mday, 
            dmy_cur_date->tm_mon + 1, 
            dmy_cur_date->tm_year + 1900);
    /*
        for convert time to str use strftime()
    */
}

void inf_com(com& command)
{
    if(command.n_com == NULL)
    {
        printf("\x1b[1m\nNAME\n\x1b[0m\tNULL\n");
    }
    else
    {
        printf("\x1b[1m\nNAME\n\x1b[0m\t%s\n", command.n_com);
    }

    printf("\x1b[1mKEY\x1b[0m : %d\n", command.num_of_keys);
    for(int i = 0; i < command.num_of_keys; ++i)
    {
        printf("\x1b[0m\t%s", command.key_com[i].n_key);
        if(command.key_com[i].par_key == NULL)
        {
            printf("\tNULL");
        }
        else
        {
            printf("\t%s", command.key_com[i].par_key);
        }
        if(command.key_com[i].key_on)
        {
            printf("\ton\n");
        }
        else
        {
            printf("\toff\n");
        }
    }

    printf("\x1b[1mPARAMETR\x1b[0m : %d\n", command.num_of_par);
    for(int i = 0; i < command.num_of_par; ++i)
    {
        printf("\x1b[0m\t%s\n", command.par_com[i]);
    }
}

void clean_com(com& command)
{
    command.n_com = NULL;

    if(command.num_of_par > 0)
    {
        for(int i = 0; i < command.num_of_par; ++i)
        {
            free(command.par_com[i]);
        }
        free(command.par_com);
    }
    command.par_com = NULL;
    command.num_of_par = 0;

    for(int i = 0; i < command.num_of_keys; ++i)
    {
        command.key_com[i].n_key = NULL;
        if(command.key_com[i].exist_par)
        {
            free(command.key_com[i].par_key);
        }
        command.key_com[i].key_on = false;
    }

    free(command.key_com);
    command.key_com = NULL;
    command.num_of_keys = 0;
}

void fill_par_com(com& c, char* input_array, int len, int number_of_par)
{
    c.num_of_par = number_of_par;
    c.par_com = (char**) malloc(sizeof(char*) * number_of_par);
    char* s_w = input_array;
    char* e_w = NULL;
    bool tmp_flag = false;
    for(int i = 0; i < number_of_par - 1; ++i)
    {
        next_word(s_w, e_w, tmp_flag);
        c.par_com[i] = (char*) malloc(strlen(s_w) + 1);
        strcpy(c.par_com[i], s_w);
        s_w = e_w + 1;
    }
    next_word(s_w, e_w, tmp_flag);
    c.par_com[number_of_par - 1] = (char*) malloc(strlen(s_w) + 1);
    strcpy(c.par_com[number_of_par - 1], s_w);
}

int fill_cstruct(com& c, char*& s_w, char*& e_w, bool& end_flag)
{
    int len_tmp_par_com = 16;
    char* tmp_par_com = (char*) malloc(len_tmp_par_com);
    int number_of_par = 0;
    int index_tmp_par_com = 0;
    for( ; ;)
    {
        if(end_flag)
        {
            /*
            The last word was the end of the string.
            Immediately after the word comes the end of the string.
            Example "....... qwerty\0".
            */
            fill_par_com(c, tmp_par_com, index_tmp_par_com, number_of_par);
            free(tmp_par_com);
            return 0;
        }
        s_w = e_w + 1;
        next_word(s_w, e_w, end_flag);
        if(s_w == e_w)
        {
            /*
            There were olnly spaces after the last word.
            Example "....... qwerty     \0".
            */
            fill_par_com(c, tmp_par_com, index_tmp_par_com, number_of_par);
            free(tmp_par_com);
            return 0;
        }
        /* At this stage we have a new word */
        /* Let's check this key of parametr */
        
        if(*s_w == '-')
        {
            bool flag_key_if_found = false;
            for(int i = 0; i < c.num_of_keys; ++i)
            {
                if(strcmp(s_w, c.key_com[i].n_key) == 0)
                {
                    c.key_com[i].key_on = true;
                    flag_key_if_found = true;

                    if(c.key_com[i].exist_par)
                    {
                        if(end_flag)
                        {
                            /*
                            The key has a parametr, but
                            the command does't have it.
                            */
                            free(tmp_par_com);
                            return 1;
                        }
                        s_w = e_w + 1;
                        next_word(s_w, e_w, end_flag);
                        if(s_w == e_w)
                        {
                            /*
                            The key has a parametr, but
                            the command does't have it.
                            */
                            free(tmp_par_com);
                            return 1;
                        }
                        /*
                        At this stage we have a key par.
                        let's add its to par_key.
                        */

                        c.key_com[i].par_key = (char*) malloc((int)(e_w - s_w) + 1);
                        strcpy(c.key_com[i].par_key, s_w); // copy second str to first with \0
                    }

                    break;
                }
            }
            if(!flag_key_if_found)
            {
                /*
                This command hasn't suck key.
                The incorrect key was submitted to the command.
                */
                free(tmp_par_com);
                return 2;
            }
        }
        else
        {
            /* Add par to the tmp array */
            int len_word = strlen(s_w);
            if(len_word + index_tmp_par_com < len_tmp_par_com)
            {
                strcpy(tmp_par_com + index_tmp_par_com, s_w);
                index_tmp_par_com += len_word;
                tmp_par_com[index_tmp_par_com] = ' ';
                ++index_tmp_par_com;
                ++number_of_par;
            }
            else
            {
                char* tmp_mas =(char*) malloc(index_tmp_par_com);
                for(int i = 0; i < index_tmp_par_com; ++i)
                {
                    tmp_mas[i] = tmp_par_com[i];
                }
                free(tmp_par_com);
                len_tmp_par_com += len_word * 2 + 16;
                tmp_par_com = (char*) malloc(len_tmp_par_com);
                for(int i = 0; i < index_tmp_par_com; ++i)
                {
                    tmp_par_com[i] = tmp_mas[i];
                }
                free(tmp_mas);

                strcpy(tmp_par_com + index_tmp_par_com, s_w);
                index_tmp_par_com += len_word;
                tmp_par_com[index_tmp_par_com] = ' ';
                ++index_tmp_par_com;
                ++number_of_par;
            }
        }
    }
}

int count_key_on(com& c)
{
    int count_key_on = 0;
    for(int i = 0; i < c.num_of_keys; ++i)
    {
        if(c.key_com[i].key_on) ++count_key_on;
    }
    return count_key_on;
}

void inf_key_com(com& c)
{
    printf("\x1b[0m# \x1b[1mKEY\x1b[0m : %d\n", c.num_of_keys);
    for(int i = 0; i < c.num_of_keys; ++i)
    {
        printf("\x1b[0m# \x1b[0m\t%s", c.key_com[i].n_key);
        if(c.key_com[i].par_key == NULL)
        {
            printf("\tNULL");
        }
        else
        {
            printf("\t%s", c.key_com[i].par_key);
        }
        if(c.key_com[i].key_on)
        {
            printf("\ton\n");
        }
        else
        {
            printf("\toff\n");
        }
    }
}

int check_c_Howmuch_com_par(com& c)
{
    char* par_1 = c.par_com[0];
    char* tmp_ptr = strchr(par_1, ':');
    if(tmp_ptr == NULL)
    {
        printf("\x1b[0m# 1-st par incorrect\n");
        return 1;
    }
    int day_len = tmp_ptr - par_1;
    if((day_len != 2) && (day_len != 1))
    {
        printf("\x1b[0m# 1-st par incorrect, see day field\n");
        return 1;
    }
    if(day_len == 2)
    {
        if((par_1[0] < '0') || (par_1[0] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see day field\n");
            return 1;
        }
        if((par_1[1] < '0') || (par_1[1] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see day field\n");
            return 1;
        }
    }
    else
    {
        if((par_1[0] < '0') || (par_1[0] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see day field\n");
            return 1;
        }
    }
    /* field day filled in correctly */

    par_1 = tmp_ptr + 1;
    tmp_ptr = strchr(par_1, ':');
    if(tmp_ptr == NULL)
    {
        printf("\x1b[0m# 1-st par incorrect, see month field\n");
        return 1;
    }
    int month_len = tmp_ptr - par_1;
    if((month_len != 2) && (month_len != 1))
    {
        printf("\x1b[0m# 1-st par incorrect, see month field\n");
        return 1;
    }
    if(month_len == 2)
    {
        if((par_1[0] < '0') || (par_1[0] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see month field\n");
            return 1;
        }
        if((par_1[1] < '0') || (par_1[1] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see month field\n");
            return 1;
        }
    }
    else
    {
        if((par_1[0] < '0') || (par_1[0] > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see month field\n");
            return 1;
        }
    }
    /* field month filled in correctly */

    par_1 = tmp_ptr + 1;
    if(*par_1 == '\0')
    {
        printf("\x1b[0m# 1-st par incorrect, see year field\n");
        return 1;
    }
    if(*par_1 == '-')
    {
        ++par_1;
        if(*par_1 == '\0')
        {
            printf("\x1b[0m# 1-st par incorrect, see year field\n");
            return 1;
        }
    }
    for( ; *par_1 != '\0'; ++par_1)
    {
        if((*par_1 < '0') || (*par_1 > '9'))
        {
            printf("\x1b[0m# 1-st par incorrect, see year field\n");
            return 1;
        }
    }
    /* field year filled in correctly */
    /* par_com[0] filled in correctly */
    
    char* par_2 = c.par_com[1];
    tmp_ptr = strchr(par_2, ':');
    if(tmp_ptr == NULL)
    {
        printf("\x1b[0m# 2-d par incorrect\n");
        return 1;
    }
    int hour_len = tmp_ptr - par_2;
    if((hour_len != 2) && (hour_len != 1))
    {
        printf("\x1b[0m# 2-d par incorrect, see hour field\n");
        return 1;
    }
    if(hour_len == 2)
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see hour field\n");
            return 1;
        }
        if((par_2[1] < '0') || (par_2[1] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see hour field\n");
            return 1;
        }
    }
    else
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see hour field\n");
            return 1;
        }
    }
    /* field hour filled in correctly */

    par_2 = tmp_ptr + 1;
    tmp_ptr = strchr(par_2, ':');
    if(tmp_ptr == NULL)
    {
        printf("\x1b[0m# 2-d par incorrect\n");
        return 1;
    }
    int min_len = tmp_ptr - par_2;
    if((min_len != 2) && (min_len != 1))
    {
        printf("\x1b[0m# 2-d par incorrect, see min field\n");
        return 1;
    }
    if(min_len == 2)
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see min field\n");
            return 1;
        }
        if((par_2[1] < '0') || (par_2[1] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see min field\n");
            return 1;
        }
    }
    else
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see min field\n");
            return 1;
        }
    }
    /* field minute filled in correctly */

    par_2 = tmp_ptr + 1;
    int sec_len = strlen(par_2);
    if((sec_len != 2) && (sec_len != 1))
    {
        printf("\x1b[0m# 2-d par incorrect, see sec field\n");
        return 1;
    }
    if(sec_len == 2)
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see sec field\n");
            return 1;
        }
        if((par_2[1] < '0') || (par_2[1] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see sec field\n");
            return 1;
        }
    }
    else
    {
        if((par_2[0] < '0') || (par_2[0] > '9'))
        {
            printf("\x1b[0m# 2-d par incorrect, see sec field\n");
            return 1;
        }
    } 
    /* field second filled in correctly */
    /* par_com[1] filled in correctly */

    return 0;
}

int check_value_dmy_hms(com& c, int* dmy_hms)
{
    char* tmp_ptr = c.par_com[0];
    int tmp_day = strtol(tmp_ptr, &tmp_ptr, 10);
    ++tmp_ptr;
    int tmp_month = strtol(tmp_ptr, &tmp_ptr, 10);
    ++tmp_ptr;
    int tmp_year = strtol(tmp_ptr, NULL, 10);

    tmp_ptr = c.par_com[1];
    int tmp_hour = strtol(tmp_ptr, &tmp_ptr, 10);
    ++tmp_ptr;
    int tmp_minute = strtol(tmp_ptr, &tmp_ptr, 10);
    ++tmp_ptr;
    int tmp_secund = strtol(tmp_ptr, NULL, 10);

    //printf("%d:%d:%d\t%d:%d:%d\n", tmp_day, tmp_month, tmp_year, tmp_hour, tmp_minute, tmp_secund);

    if((tmp_hour > 23) || (tmp_minute > 59) || (tmp_secund > 60))
    {
        printf("\x1b[0m# Time (par 2) isn't correct (h>23 || m>59 || s>60)\n");
        return 1;
    }
    if((tmp_month > 12) || (tmp_month == 0))
    {
        printf("\x1b[0m# Date (par 1) mouth isn't correct (m>12 || m=0)\n");
        return 1;
    }
    switch(tmp_month)
    {
        case 1:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# January has 31 days");
                return 1;
            }
            break;

        case 2:
            if(tmp_year % 4 == 0)
            {
                if(tmp_day > 29)
                {
                    printf("\x1b[0m# February has 29 days in a leap year");
                    return 1;
                }
            }
            else
            {
                if(tmp_day > 28)
                {
                    printf("\x1b[0m# February has 28 days in a typical year");
                    return 1;
                }
            }
            break;

        case 3:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# March has 31 days");
                return 1;
            }
            break;

        case 4:
            if(tmp_day > 30)
            {
                printf("\x1b[0m# April has 30 days");
                return 1;
            }
            break;

        case 5:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# May has 31 days");
                return 1;
            }
            break;

        case 6:
            if(tmp_day > 30)
            {
                printf("\x1b[0m# June has 30 days");
                return 1;
            }
            break;

        case 7:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# July has 31 days");
                return 1;
            }
            break;

        case 8:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# August has 31 days");
                return 1;
            }
            break;

        case 9:
            if(tmp_day > 30)
            {
                printf("\x1b[0m# September has 30 days");
                return 1;
            }
            break;

        case 10:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# October has 31 days");
                return 1;
            }
            break;

        case 11:
            if(tmp_day > 30)
            {
                printf("\x1b[0m# November has 30 days");
                return 1;
            }
            break;

        case 12:
            if(tmp_day > 31)
            {
                printf("\x1b[0m# December has 31 days");
                return 1;
            }
            break;
    }
    dmy_hms[0] = tmp_day;
    dmy_hms[1] = tmp_month;
    dmy_hms[2] = tmp_year;
    dmy_hms[3] = tmp_hour;
    dmy_hms[4] = tmp_minute;
    dmy_hms[5] = tmp_secund;

    return 0;
}

bool get_onkey_c_Howmuch(com& c, int& int_key)
{
    int_key = -1;
    for(int i = 0; i < c.num_of_keys; ++i)
    {
        if(c.key_com[i].key_on)
        {
            int_key = i;
            break;
        }
    }
    if(int_key >= 0) return true;
    else return false;
}

void cou_elap_time(com& c, int* dmy_hms)
{
    tm input_time;
    input_time.tm_mday = dmy_hms[0];
    input_time.tm_mon = dmy_hms[1] - 1;
    input_time.tm_year = dmy_hms[2];
    input_time.tm_hour = dmy_hms[3];
    input_time.tm_min = dmy_hms[4];
    input_time.tm_sec = dmy_hms[5];
    input_time.tm_isdst = 0;
    int drift_year = 0;
    if(input_time.tm_year < 1900)
    {
        drift_year = 1900 - input_time.tm_year;
        input_time.tm_year = 0;
    }
    else
    {
        input_time.tm_year -= 1900;
    }
    time_t i_time = mktime(&input_time);
    time_t cur_time = time(NULL);
    long long d_time = (long long) cur_time - i_time;
    if(drift_year > 0)
    {
        d_time += (drift_year / 4) * (long long)(365 * 3 + 366) * 24 * 3600 + (drift_year % 4) * (long long)365 * 24 * 3600;
    }

    int t_mod = -1;
    get_onkey_c_Howmuch(c, t_mod);
    double dt = double(d_time);
    switch(t_mod)
    {
        case 1:
            printf("\x1b[0m# %lld s\n", d_time);
            break;

        case 2:
            printf("\x1b[0m# %.8lf m\n", d_time/60.);
            break;

        case 3:
            printf("\x1b[0m# %.8lf h\n", d_time/3600.);
            break;

        case 4:
            printf("\x1b[0m# %.8lf y\n", d_time/3600/24/365.25);
            break;
    }
}

bool search_log_for_ban(const char* user_f, char* u_log)
{
    FILE* f_ptr = fopen(user_f, "r");
    if(f_ptr == NULL)
    {
        printf("\x1b[0m# File %s doesn't found\n", user_f);
        exit(-1);
    }

    char* u_log_pas = (char*) malloc(15); // 6 + ' ' + 6 + '\n' + '\0'
    for( ; fgets(u_log_pas, 15, f_ptr) != NULL; )
    {
        char* tmp_ptr = strchr(u_log_pas, ' ');
        *tmp_ptr = '\0';
        if(strcmp(u_log, u_log_pas) == 0)
        {
            fclose(f_ptr);
            free(u_log_pas);
            return true;
        }
    }
    fclose(f_ptr);
    free(u_log_pas);
    return false;
}

bool check_pas_for_ban(char* u_log)
{
    printf("\x1b[0m# Enter pas\n");
    printf("\x1b[0m# \x1b[32m%s: \x1b[30m", u_log);

    int c = getchar();
    if(c != '5')
    {
        if(c == '\n') return false;
        else
        {
            clean_stdin_buf();
            return false;
        }
    }
    c = getchar();
    if(c != '2')
    {
        if(c == '\n') return false;
        else
        {
            clean_stdin_buf();
            return false;
        }
    }
    c = getchar();
    if(c != '\n')
    {
        clean_stdin_buf();
        return false;
    }
    return true;
}

bool is_already_ban(const char* user_ban, char* u_log)
{
    FILE* f_ptr = fopen(user_ban, "r");
    if(f_ptr == NULL)
    {
        printf("\x1b[0m# File %s doesn't found\n", user_ban);
        exit(-1);
    }

    char* u_log_ban = (char*) malloc(8); // 6 + '\n' + '\0'
    for( ; fgets(u_log_ban, 8, f_ptr) != NULL; )
    {
        char* tmp_ptr = strchr(u_log_ban, '\n');
        *tmp_ptr = '\0';
        if(strcmp(u_log, u_log_ban) == 0)
        {
            fclose(f_ptr);
            free(u_log_ban);
            return true;
        }
    }
    fclose(f_ptr);
    free(u_log_ban);
    return false;
}

/* PROCESS_C */

int process_c_q(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_q;
    init_c_q(run_c_q);
    //inf_com(run_c_q);

    if(end_flag)
    {
        clean_com(run_c_q);
        return 1;
    }

    s_w = e_w + 1;
    next_word(s_w, e_w, end_flag);
    if(s_w == e_w)
    {
        clean_com(run_c_q);
        return 1;
    }

    if(strcmp(s_w, run_c_q.key_com[0].n_key) == 0)
    {
        if(end_flag)
        {
            run_c_q.key_com[0].key_on = true;
            printf("\x1b[0m# Name: q\n");
            printf("\x1b[0m# Description: exit from the program\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#      --help - display this help\n");

            clean_com(run_c_q);
            return 0;
        }

        s_w = e_w + 1;
        next_word(s_w, e_w, end_flag);
        if(s_w == e_w)
        {
            run_c_q.key_com[0].key_on = true;
            printf("\x1b[0m# Name: q\n");
            printf("\x1b[0m# Description: exit from the program\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#      --help - display this help\n");

            clean_com(run_c_q);
            return 0;
        }
        else
        {
            printf("\x1b[0m# \x1b[31m%s\x1b[0m: Command q can have only one key\n", s_w);

            clean_com(run_c_q);
            return 0;
        }
    }

    printf("\x1b[0m# \x1b[31m%s \x1b[0mIncorrect par or key\n", s_w);

    clean_com(run_c_q);
    return 0;
}

int process_c_help(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_help;
    init_c_help(run_c_help);
    //inf_com(run_c_q);

    if(end_flag)
    {
        printf("\x1b[0m# Program list:\n");
        printf("\x1b[0m# \tq\n");
        printf("\x1b[0m# \tTime\n");
        printf("\x1b[0m# \tDate\n");
        printf("\x1b[0m# \tHowmuch\n");
        printf("\x1b[0m# \tLogout\n");
        printf("\x1b[0m# \tSanctions\n");
        printf("\x1b[0m# For more information see <program> --help\n");

        clean_com(run_c_help);
        return 0;
    }

    s_w = e_w + 1;
    next_word(s_w, e_w, end_flag);
    if(s_w == e_w)
    {
        printf("\x1b[0m# Program list:\n");
        printf("\x1b[0m# \tq\n");
        printf("\x1b[0m# \tTime\n");
        printf("\x1b[0m# \tDate\n");
        printf("\x1b[0m# \tHowmuch\n");
        printf("\x1b[0m# \tLogout\n");
        printf("\x1b[0m# \tSanctions\n");
        printf("\x1b[0m# For more information see <program> --help\n");

        clean_com(run_c_help);
        return 0;
    }

    printf("\x1b[0m# \x1b[31m%s \x1b[0mIncorrect par or key\n", s_w);
    clean_com(run_c_help);
    return 0;
}

int process_c_Logout(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_Logout;
    init_c_Logout(run_c_Logout);
    //inf_com(run_c_q);

    if(end_flag)
    {
        clean_com(run_c_Logout);
        return 2;
    }

    s_w = e_w + 1;
    next_word(s_w, e_w, end_flag);
    if(s_w == e_w)
    {
        clean_com(run_c_Logout);
        return 2;
    }

    if(strcmp(s_w, run_c_Logout.key_com[0].n_key) == 0)
    {
        if(end_flag)
        {
            run_c_Logout.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Logout\n");
            printf("\x1b[0m# Description: Logout from account\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#      --help - display this help\n");

            clean_com(run_c_Logout);
            return 0;
        }

        s_w = e_w + 1;
        next_word(s_w, e_w, end_flag);
        if(s_w == e_w)
        {
            run_c_Logout.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Logout\n");
            printf("\x1b[0m# Description: Logout from account\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#      --help - display this help\n");

            clean_com(run_c_Logout);
            return 0;
        }
        else
        {
            printf("\x1b[0m# \x1b[31m%s\x1b[0m: Command Logout can have only one key\n", s_w);

            clean_com(run_c_Logout);
            return 0;
        }
    }

    printf("\x1b[0m# \x1b[31m%s \x1b[0mIncorrect par or key\n", s_w);

    clean_com(run_c_Logout);
    return 0;
}

int process_c_Time(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_Time;
    init_c_Time(run_c_Time);

    if(end_flag)
    {
        cur_time();
        clean_com(run_c_Time);
        return 0;
    }

    s_w = e_w + 1;
    next_word(s_w, e_w, end_flag);
    if(s_w == e_w)
    {
        cur_time();
        clean_com(run_c_Time);
        return 0;
    }

    if(strcmp(s_w, run_c_Time.key_com[0].n_key) == 0)
    {
        if(end_flag)
        {
            run_c_Time.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Time\n");
            printf("\x1b[0m# Description: printing current time in format h:m:s\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#     --help - display this help\n");

            clean_com(run_c_Time);
            return 0;
        }

        s_w = e_w + 1;
        next_word(s_w, e_w, end_flag);
        if(s_w == e_w)
        {
            run_c_Time.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Time\n");
            printf("\x1b[0m# Description: printing current time in format h:m:s\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#     --help - display this help\n");

            clean_com(run_c_Time);
            return 0;
        }
        else
        {
            printf("\x1b[0m# \x1b[31m%s\x1b[0m: Command Time can have only one key\n", s_w);

            clean_com(run_c_Time);
            return 0;
        }
    }

    printf("\x1b[0m# \x1b[31m%s \x1b[0mIncorrect par or key\n", s_w);

    clean_com(run_c_Time);
    return 0;
}

int process_c_Date(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_Date;
    init_c_Date(run_c_Date);

    if(end_flag)
    {
        cur_date();
        clean_com(run_c_Date);
        return 0;
    }

    s_w = e_w + 1;
    next_word(s_w, e_w, end_flag);
    if(s_w == e_w)
    {
        cur_date();
        clean_com(run_c_Date);
        return 0;
    }

    if(strcmp(s_w, run_c_Date.key_com[0].n_key) == 0)
    {
        if(end_flag)
        {
            run_c_Date.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Date\n");
            printf("\x1b[0m# Description: printing current date in format d:m:y\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#     --help - display this help\n");

            clean_com(run_c_Date);
            return 0;
        }

        s_w = e_w + 1;
        next_word(s_w, e_w, end_flag);
        if(s_w == e_w)
        {
            run_c_Date.key_com[0].key_on = true;
            printf("\x1b[0m# Name: Date\n");
            printf("\x1b[0m# Description: printing current date in format d:m:y\n");
            printf("\x1b[0m# Options:\n");
            printf("\x1b[0m#     --help - display this help\n");

            clean_com(run_c_Date);
            return 0;
        }
        else
        {
            printf("\x1b[0m# \x1b[31m%s\x1b[0m: Command Date can have only one key\n", s_w);

            clean_com(run_c_Date);
            return 0;
        }
    }

    printf("\x1b[0m# \x1b[31m%s \x1b[0mIncorrect par or key\n", s_w);

    clean_com(run_c_Date);
    return 0;   
}

int process_c_Howmuch(char*& s_w, char*& e_w, bool& end_flag, char* u_log)
{
    com run_c_Howmuch;
    init_c_Howmuch(run_c_Howmuch);
    int catch_error = fill_cstruct(run_c_Howmuch, s_w, e_w, end_flag);
    if(catch_error == 1)
    {
        printf("\x1b[0m# The key has a parametr, but the command does't have it. See last key\n");
        clean_com(run_c_Howmuch);
        return 0;
    }
    if(catch_error == 2)
    {
        printf("\x1b[0m# This command hasn't such key: \x1b[31m%s\x1b[0m\n", s_w);
        printf("\x1b[0m# The incorrect key was submitted to the command.\n");
        clean_com(run_c_Howmuch);
        return 0;
    }

    int cou_k_on = count_key_on(run_c_Howmuch);
    if(cou_k_on > 1)
    {
        printf("\x1b[0m# This command can't has two or more active keys\n");
        inf_key_com(run_c_Howmuch);
        clean_com(run_c_Howmuch);
        return 0;
    }
    if(cou_k_on == 0)
    {
        run_c_Howmuch.key_com[1].key_on = true;
    }
    if(run_c_Howmuch.key_com[0].key_on)
    {
        if(run_c_Howmuch.num_of_par > 0)
        {
            printf("\x1b[0m# Key --help not combine with command parametrs\n");
            clean_com(run_c_Howmuch);
            return 0;
        }

        printf("\x1b[0m# Name: Howmuch\n");
        printf("\x1b[0m# Description: Howmuch d:m:y h:m:s -key\n");
        printf("\x1b[0m#              Howmuch --help\n");
        printf("\x1b[0m# Calculates the time elapsed since the\n");
        printf("\x1b[0m# time command was submitted.\n");
        printf("\x1b[0m# Options:\n");
        printf("\x1b[0m#      --help - display this help\n");
        printf("\x1b[0m#      -s - calculates the time in s\n");
        printf("\x1b[0m#      -m - calculates the time in m\n");
        printf("\x1b[0m#      -h - calculates the time in h\n");
        printf("\x1b[0m#      -y - calculates the time in y\n");

        clean_com(run_c_Howmuch);
        return 0;
    }
    if(run_c_Howmuch.num_of_par != 2)
    {
        printf("\x1b[0m# com Howmuch must have two par: d:m:y h:m:s\n");
        clean_com(run_c_Howmuch);
        return 0;
    }
    /* At this stage we have one key and two par */
    /* Let's check this parametrs */

    catch_error = check_c_Howmuch_com_par(run_c_Howmuch);
    if(catch_error == 1)
    {
        clean_com(run_c_Howmuch);
        return 0;
    }
    /* Parametrs are correct. */
    /* Let's check numeric value of d/m/y h/m/s */

    int* dmy_hms = (int*) malloc(sizeof(int) * 6);
    catch_error = check_value_dmy_hms(run_c_Howmuch, dmy_hms);
    if(catch_error == 1)
    {
        free(dmy_hms);
        clean_com(run_c_Howmuch);
        return 0;
    }

    cou_elap_time(run_c_Howmuch, dmy_hms);

    free(dmy_hms);
    clean_com(run_c_Howmuch);
    return 0;
}

int process_c_Sanctions(char*& s_w, char*& e_w, bool& end_flag, char* u_log, const char* user_f , const char* user_ban)
{
    com run_c_Sanctions;
    init_c_Sanctions(run_c_Sanctions);
    int catch_error = fill_cstruct(run_c_Sanctions, s_w, e_w, end_flag);
    if(catch_error == 1)
    {
        printf("\x1b[0m# The key has a parametr, but the command does't have it. See last key\n");
        clean_com(run_c_Sanctions);
        return 0;
    }
    if(catch_error == 2)
    {
        printf("\x1b[0m# This command hasn't such key: \x1b[31m%s\x1b[0m\n", s_w);
        printf("\x1b[0m# The incorrect key was submitted to the command.\n");
        clean_com(run_c_Sanctions);
        return 0;
    }
    if(run_c_Sanctions.key_com[0].key_on)
    {
        if(run_c_Sanctions.num_of_par > 0)
        {
            printf("\x1b[0m# Key --help not combine with command parametrs\n");
            clean_com(run_c_Sanctions);
            return 0;
        }

        printf("\x1b[0m# Name: Sanctions\n");
        printf("\x1b[0m# Description: Sanctions <username>\n");
        printf("\x1b[0m# \tCommand gets to enter name of account\n");
        printf("\x1b[0m# \tand asks for a password, if enter pas\n");
        printf("\x1b[0m# \tis correct, user gets sanction.\n");
        printf("\x1b[0m# Options:\n");
        printf("\x1b[0m#     --help - display this help\n");
        clean_com(run_c_Sanctions);
        return 0;
    }
    if(run_c_Sanctions.num_of_par != 1)
    {
        printf("\x1b[0m# Com Sanctions must has one parametr\n");
        clean_com(run_c_Sanctions);
        return 0;
    }
    /* At this stage we have: # Sanctions <username> */
    /* Let's check does this account exist */

    if(strlen(run_c_Sanctions.par_com[0]) > 6)
    {
        printf("\x1b[0m# Error: len(<username>) > 6\n");
        return 0;
    }

    /* Check pas */
    if(check_pas_for_ban(u_log))
    {
        printf("\x1b[0m# OK\n");
        /* If such user is exist we will banned him, else we don't do any thing. */
        if(search_log_for_ban(user_f, run_c_Sanctions.par_com[0]))
        {
            if(!is_already_ban(user_ban, run_c_Sanctions.par_com[0]))
            {
                FILE* f_bun_ptr = fopen(user_ban, "a");
                fprintf(f_bun_ptr, "%s\n", run_c_Sanctions.par_com[0]);
                fclose(f_bun_ptr);
            }
        }
    }

    clean_com(run_c_Sanctions);
    return 0;
}

#endif /* COMMAND_STRUCT */