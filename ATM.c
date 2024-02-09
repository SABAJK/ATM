#include "ATM.h"

//FUNCTIONS:

ATM* LOAD(char *file_name) 
{
    CUSTOMER_LIST *PHead = NULL, *PNew_data = NULL, *PLast_data = NULL, tmp;
    int i;
    FILE *fp = NULL;
    fp = fopen(file_name, "r+");
    if (fp == NULL) 
    {
        printf(ANSI_COLOR_GREEN     "Problem with opening the file"     ANSI_COLOR_RESET"\n");
        exit(1);
    }

    for (i = 0; i < NUMBER_OF_ACCOUNTS; ++i) 
    {
        PNew_data = (CUSTOMER_LIST*)malloc(sizeof(CUSTOMER_LIST));

        if (PHead == NULL) 
        {
            PNew_data->PNext = PNew_data->PBefore = NULL;
            PHead = PLast_data = PNew_data;
        } else 
        {
            PNew_data->PNext = NULL;
            PNew_data->PBefore = PLast_data;
            PLast_data->PNext = PNew_data;
            PLast_data = PNew_data;
        }
    }

    fclose(fp);

    ATM *PAtm_data = (ATM*)malloc(sizeof(ATM));
    PAtm_data->number_of_accounts = i;

    for (i = 0; i < PAtm_data->number_of_accounts && PHead != NULL; ++i) 
    {
        PAtm_data->Accounts[i] = *PHead;
        PHead = PHead->PNext;
    }

    return PAtm_data;
}

int LOGIN(ATM *PHead)
{
    int id, password, i;
    printf(ANSI_COLOR_GREEN "Please enter your ID:\n"   ANSI_COLOR_RESET);
    scanf("%d",&id);
    printf(ANSI_COLOR_GREEN "Please enter your password:\n" ANSI_COLOR_RESET);
    scanf("%d",&password);
    if(id < 0 || password < 0)
    {
        printf(ANSI_COLOR_GREEN "Invalid input\n"   ANSI_COLOR_RESET);
        return 0;
    }
    for(i = 0;i < NUMBER_OF_ACCOUNTS;++i)
    {
        if(id == PHead->Accounts[i].Customer_info.ID && password == PHead->Accounts[i].Customer_info.Password)
        {
            return i;
        }
    }
    printf(ANSI_COLOR_GREEN     "Invalid input\n"   ANSI_COLOR_RESET);
    return 0; 
}

void HELP()
{
    printf(ANSI_COLOR_YELLOW    "\nPlease enter 1 for:Withdraw\n"   ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW    "Please enter 2 for:Deposit\n"  ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW    "Please enter 3 for:Checking the balance\n"     ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW    "Please enter 4 for:Money transter\n"   ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW    "Please enter 5 for:Display last 10 transaction\n"   ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW    "Please enter 0 for:exit\n" ANSI_COLOR_RESET);
}

void WITHDRAW(ATM* PHead, int Customer_number)
{
    int input, i;
    char operation[20] = "Withdraw";
    printf(ANSI_COLOR_GREEN     "How much money do you want to withdraw ?\n"    ANSI_COLOR_RESET);
    scanf("%d",&input);
    if(input < 0)
    {
        printf(ANSI_COLOR_GREEN     "Invalid input\n"   ANSI_COLOR_RESET);
        return;
    }
    if(input <= PHead->Accounts[Customer_number].Customer_info.Credit)
    {
        PHead->Accounts[Customer_number].Customer_info.Credit = PHead->Accounts[Customer_number].Customer_info.Credit - input;
    }
    else 
    {
        printf(ANSI_COLOR_GREEN     "Not enough money\n"    ANSI_COLOR_RESET);
        return;
    }
    WRITE(PHead);
    PRINT_RECEIPT(PHead, Customer_number);
    LAST_10_TRANSACTION(PHead, Customer_number, operation);
}

void DEPOSIT(ATM *PHead, int Customer_number)
{
    int input, i;
    char operation[20] = "Deposit";
    printf(ANSI_COLOR_GREEN     "How much money do you want to deposit ?\n"     ANSI_COLOR_RESET);
    scanf("%d",&input);
    if(input < 0)
    {
        printf(ANSI_COLOR_GREEN     "Invalid input\n"       ANSI_COLOR_RESET);
        return;
    }
    PHead->Accounts[Customer_number].Customer_info.Credit += input;
    WRITE(PHead);
    PRINT_RECEIPT(PHead,Customer_number);
    LAST_10_TRANSACTION(PHead,Customer_number,operation);
}

void TRANSFER(ATM *PHead, int Customer_number)
{
    ATM *PCustomer_data = NULL;
    int number_of_account ,input ,i;
    char name_of_bank[20], operation[20] = "Transfer";
    printf(ANSI_COLOR_GREEN     "How much money do you want to transfer ?\n"    ANSI_COLOR_RESET);
    scanf("%d",&input);
    if(input <= PHead->Accounts[Customer_number].Customer_info.Credit)
    {
        printf(ANSI_COLOR_GREEN     "Please enter the account number that you want to transfer to\n"    ANSI_COLOR_RESET);
        scanf("%d",&number_of_account);
        printf(ANSI_COLOR_GREEN     "Please enter name of destination bank\n"    ANSI_COLOR_RESET);
        scanf("%s",name_of_bank);
        for(i = 0;i < NUMBER_OF_ACCOUNTS;++i)
        {
            if(number_of_account == PHead->Accounts[i].Customer_info.Account_number && strcmp(name_of_bank,PHead->Accounts[i].Customer_info.Bank_name) == 0)
            {
                PHead->Accounts[i].Customer_info.Credit += input;
                PHead->Accounts[Customer_number].Customer_info.Credit -= input;
                WRITE(PHead);
                PRINT_RECEIPT(PHead,Customer_number);
                LAST_10_TRANSACTION(PHead,Customer_number,operation);
                return;
            }
        }
        printf(ANSI_COLOR_GREEN     "Invalid destination data\n"    ANSI_COLOR_RESET);
    }   
    else
        printf(ANSI_COLOR_GREEN     "Not enough money to transfer\n"    ANSI_COLOR_RESET);
}
void WRITE(ATM *PHead)
{
    int i;
    FILE *fp;
    fp = fopen("d:\\data.txt","w+");
    if(fp == NULL)
    {
        printf(ANSI_COLOR_GREEN     "Problem with opening the file\n"    ANSI_COLOR_RESET);
        return;
    }
    rewind(fp);
    for(i = 0;i < NUMBER_OF_ACCOUNTS;++i)
    {
        fprintf(fp,"%s %d %d %d %s %d\n",PHead->Accounts[i].Customer_info.First_name,PHead->Accounts[i].Customer_info.ID,PHead->Accounts[i].Customer_info.Password,PHead->Accounts[i].Customer_info.Account_number,PHead->Accounts[i].Customer_info.Bank_name,PHead->Accounts[i].Customer_info.Credit);
    }
    fclose(fp);
}

void READ_FILE(ATM *PHead)
{
    int i;
    FILE *fp = NULL;
    fp = fopen("d:\\data.txt","r+");
    if(fp == NULL)
    {
        printf(ANSI_COLOR_GREEN     "Problem with opening the file\n"    ANSI_COLOR_RESET);
        return;
    }
    for(i = 0;i < NUMBER_OF_ACCOUNTS;++i)
    {
        fscanf(fp,"%s %d %d %d %s %d",PHead->Accounts[i].Customer_info.First_name,&PHead->Accounts[i].Customer_info.ID,&PHead->Accounts[i].Customer_info.Password,&PHead->Accounts[i].Customer_info.Account_number,PHead->Accounts[i].Customer_info.Bank_name,&PHead->Accounts[i].Customer_info.Credit);
    }
    fclose(fp);
} 

void PRINT_RECEIPT(ATM *PHead, int Customer_number)
{
    FILE *fp = NULL;
    fp = fopen("d:\\data.txt","r+");
    if (fp == NULL)
    {
        printf(ANSI_COLOR_GREEN     "Problem with opening the file"     ANSI_COLOR_RESET);
        exit(0);
    }
    printf(ANSI_COLOR_MAGENTA"\n%s %d %d %d %s %d\n"ANSI_COLOR_RESET,PHead->Accounts[Customer_number].Customer_info.First_name,PHead->Accounts[Customer_number].Customer_info.ID,PHead->Accounts[Customer_number].Customer_info.Password,PHead->Accounts[Customer_number].Customer_info.Account_number,PHead->Accounts[Customer_number].Customer_info.Bank_name,PHead->Accounts[Customer_number].Customer_info.Credit);

    fclose(fp);
}

void CHECK_BALANCE(ATM *PHead, int Customer_number)
{
    char operation[20] = "Check balance";
    PRINT_RECEIPT(PHead,Customer_number);
    LAST_10_TRANSACTION(PHead,Customer_number,operation);
}

int LAST_10_TRANSACTION(ATM *PHead, int Customer_number, char operation[20])
{
    int i = 0, j = 0, id = 0, password = 0, account_number = 0, credit = 0;
    static int counter = 0;
    char first_name[30] = "", bank_name[10] = "", str[20] = "";
    char c;
    FILE *ft = NULL;
    ft = fopen("d:\\TRANSACTION.txt","a+");
    if(ft == NULL)
    {
        printf(ANSI_COLOR_GREEN     "Problem with opening the file"     ANSI_COLOR_RESET);
        exit(1);
    }
    if(strcmp(operation,"Withdraw") == 0)
    {
        counter++;
        rewind(ft);
        fprintf(ft,"%s %s %d %d %d %s %d\n","Withdraw:",PHead->Accounts[Customer_number].Customer_info.First_name,PHead->Accounts[Customer_number].Customer_info.ID,PHead->Accounts[Customer_number].Customer_info.Password,PHead->Accounts[Customer_number].Customer_info.Account_number,PHead->Accounts[Customer_number].Customer_info.Bank_name,PHead->Accounts[Customer_number].Customer_info.Credit); 
    }
    else
    {
        if(strcmp(operation,"Deposit") == 0)
        {
            counter++;
            rewind(ft);
            fprintf(ft,"%s %s %d %d %d %s %d\n","Deposit:",PHead->Accounts[Customer_number].Customer_info.First_name,PHead->Accounts[Customer_number].Customer_info.ID,PHead->Accounts[Customer_number].Customer_info.Password,PHead->Accounts[Customer_number].Customer_info.Account_number,PHead->Accounts[Customer_number].Customer_info.Bank_name,PHead->Accounts[Customer_number].Customer_info.Credit); 
        }
        else
        {
            if(strcmp(operation,"Check balance") == 0)
            {
                counter++;
                rewind(ft);
                fprintf(ft,"%s %s %d %d %d %s %d\n","Balance:",PHead->Accounts[Customer_number].Customer_info.First_name,PHead->Accounts[Customer_number].Customer_info.ID,PHead->Accounts[Customer_number].Customer_info.Password,PHead->Accounts[Customer_number].Customer_info.Account_number,PHead->Accounts[Customer_number].Customer_info.Bank_name,PHead->Accounts[Customer_number].Customer_info.Credit); 
            }
            else
            {
                if(strcmp(operation,"Transfer") == 0)
                {
                    counter++;
                    rewind(ft);
                    fprintf(ft,"%s %s %d %d %d %s %d\n","Transfer:",PHead->Accounts[Customer_number].Customer_info.First_name,PHead->Accounts[Customer_number].Customer_info.ID,PHead->Accounts[Customer_number].Customer_info.Password,PHead->Accounts[Customer_number].Customer_info.Account_number,PHead->Accounts[Customer_number].Customer_info.Bank_name,PHead->Accounts[Customer_number].Customer_info.Credit); 
                }
                else
                { 
                    if(strcmp(operation,"last_10_transaction") == 0)
                    {
                        if(counter <= 10)
                        {
                            for(i = 0;i < counter;++i)
                            {
                                fscanf(ft,"%s%s%d%d%d%s%d",str,first_name,&id,&password,&account_number,bank_name,&credit);
                                printf(ANSI_COLOR_MAGENTA   "\n%s %s %d %d %d %s %d\n"  ANSI_COLOR_RESET,str,first_name,id,password,account_number,bank_name,credit);
                            }
                        }
                        else
                        {
                            if(counter > 10)
                            {
                                for(j = 0;j < (counter - 10);++j)
                                {
                                    fscanf(ft,"%s%s%d%d%d%s%d",str,first_name,&id,&password,&account_number,bank_name,&credit);
                                }
                                for(i = 0;i < 10;++i)
                                {
                                    fscanf(ft,"%s%s%d%d%d%s%d",str,first_name,&id,&password,&account_number,bank_name,&credit);
                                    printf(ANSI_COLOR_MAGENTA"\n%s %s %d %d %d %s %d\n"ANSI_COLOR_RESET,str,first_name,id,password,account_number,bank_name,credit);
                                }   
                            }
                        }
                    }
                }
            }
        }
    }    
    fclose(ft);
    return counter;
}

void FREE(ATM *PHead)
{
    CUSTOMER_LIST *current = PHead->Accounts[0].PNext;
    while (current != NULL)
    {
        CUSTOMER_LIST *temp = current;
        current = current->PNext;
        free(temp);
    }
    free(PHead);
}