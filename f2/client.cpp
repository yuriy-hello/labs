#include <stdio.h>
#include <stdlib.h>

#include "func.h"

int main()
{
    check_data_f("u_data.txt", "u_ban.txt");
    hello();
    enter("u_data.txt", "u_ban.txt");

    return 0;
}