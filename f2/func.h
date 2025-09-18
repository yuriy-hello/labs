#ifndef FUNC_H
#define FUNC_H

/* print hello only */
void hello();

/* ensures correct input login */
void enter(const char* user_f, const char* user_ban);

bool check_c(char c);
bool check_log(char* i_login, bool &flag_end_str);
void clean_stdin_buf();

int search_log(char* log, const char* user_f, char* u_pas);
void check_data_f(const char* user_f, const char* user_ban);

bool user_answer();

void reg(char* i_pas, char* i_login);
bool check_pas(char* i_pas, bool &flag_end_str, char* i_login, char* u_pas = NULL);
bool check_cp(char cp);

void add_account(const char* user_f, char* i_login, char* i_pas);
int u_session(const char* user_f, char* u_log, char* u_pas, const char* user_ban);
void aut(char* i_login, char* u_pas);

int get_com(char** input_com);
void inc_mas(char** input_com, int& len);
void next_word(char*& s_w, char*& e_w, bool& end_flag);

bool check_u_ban(char* u_log, const char* user_ban);
void remov_ban(char* u_log, const char* user_ban);

#endif /* FUNC_H */