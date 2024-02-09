#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "ATM.h"

//Main function
int main()
{

    ATM *PHead = NULL;
    char data_file[MAX_SIZE],transaction_file[MAX_SIZE], operation[20] = "last_10_transaction";
    int cmd1 = 0, cmd2 = 0, Customer_number = 0;
    FILE *fp = NULL;
    strcpy(data_file, "d:\\ATM.txt");
    strcpy(transaction_file, "d:\\TRANSACTION.txt");
    fp = fopen(data_file,"r+");
    if(fp == NULL)
    {
        printf("Problem with opening the file");
        return 1;
    }
    PHead = LOAD(data_file);
    READ_FILE(PHead);
    printf(ANSI_COLOR_MAGENTA   "                      HELLO"     ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_BLUE      "THANK YOU FOR CHOOSING THIS APP AS YOUR PERSONAL ATM"      ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN     "Enter 1 to login and 0 to store your data and start:"       ANSI_COLOR_RESET "\n");
    scanf("%d",&cmd1);
    while (cmd1)
    {
        switch(cmd1)
        {
            case 1:
                Customer_number = LOGIN(PHead);
                //function to delete information of last customer stored in transaction file
                remove(transaction_file);
                if(Customer_number == 0)
                {
                    printf(ANSI_COLOR_GREEN       "Please login again : enter 1"      ANSI_COLOR_RESET "\n");
                }
                break;
            default:
                printf("Invalid command\n");
        }
        printf(ANSI_COLOR_GREEN      "Enter 1 to login and 0 to store your data and start:"        ANSI_COLOR_RESET"\n");
        scanf("%d",&cmd1);
    }
    HELP();
    scanf("%d",&cmd2);
    while(1)
    {
        switch(cmd2)
        {
            case 1:
                WITHDRAW(PHead, Customer_number);
                break;
            case 2:
                DEPOSIT(PHead, Customer_number);
                break;
            case 3:
                CHECK_BALANCE(PHead, Customer_number);
                break;
            case 4:
                TRANSFER(PHead, Customer_number);
                break;
            case 5:
                LAST_10_TRANSACTION(PHead,Customer_number,operation);
                break;
            case 0:
                FREE(PHead);
                fclose(fp);
                exit(0);
            default:
                printf(ANSI_COLOR_GREEN       "Invalid command"        ANSI_COLOR_RESET "\n");
        }
        HELP();
        scanf("%d",&cmd2);
    }

    FREE(PHead);
    fclose(fp);
    return 0;
}