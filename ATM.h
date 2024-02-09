#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//Defenitions
#define MAX_SIZE 100
#define NUMBER_OF_ACCOUNTS 10 

#define ANSI_COLOR_RED     "\e[0;91m"
#define ANSI_COLOR_GREEN   "\e[0;92m"
#define ANSI_COLOR_YELLOW  "\e[0;93m"
#define ANSI_COLOR_BLUE    "\e[0;94m"
#define ANSI_COLOR_MAGENTA "\e[0;95m"
#define ANSI_COLOR_CYAN    "\e[0;96m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//Customer's information
typedef struct CUSTOMER_INFO
{
    char First_name[MAX_SIZE];
    int ID;
    int Password;
    int Account_number;
    char Bank_name[20];
    int Credit;
} CUSTOMER_INFO;

typedef struct CUSTOMER_LIST
{
    CUSTOMER_INFO Customer_info;
    struct CUSTOMER_LIST *PNext;
    struct CUSTOMER_LIST *PBefore;
} CUSTOMER_LIST;

typedef struct ATM
{
    CUSTOMER_LIST Accounts[10];
    int number_of_accounts;
} ATM;

//Function to help the customer to choose the desired operation
//Input:---
//Output:--- 
void HELP();

//Function to receive customer's id and password to find and access to customer's account
//Input:Customer's ID,Customer's password
//Output:---
int LOGIN(ATM *PHead);

//Function to de-allocate the space allocated by malloc function
//Input:---
//Output:--- 
void FREE(ATM *PHead);

//Function to write updated customer information  
//Input:---
//Output:--- 
void WRITE(ATM *PHEAD); 

//Function to load information of customers stored in a file
//Input:---
//Output:--- 
ATM* LOAD(char *file_name);

//Function to read information of customers stored in a file
//Input:---
//Output:--- 
void READ_FILE(ATM *PHead);

//Function for customer to deposit money and print receipt
//Input:Customer number
//Output:Transaction's receipt
void DEPOSIT(ATM *PHead, int Customer_number);

//Function for customer to withdraw money and print receipt
//Input:(deposited)Money
//Output:Transaction's receipt
void WITHDRAW(ATM *PHead, int Customer_number); 

//Function for customer to transfer money to another valid bank account and print receipt
//Input:(withdrawn)Money, Customer number
//Output:Transaction's receipt
void TRANSFER(ATM *PHead, int Customer_number);

//Function to check account balance
//Input:Money to be transfered, name of destination bank, destination account number, Customer number
//Output:Transaction's receipt
void CHECK_BALANCE(ATM *PHead, int Customer_number);

//Function to print transaction's receipt
//Input:Customer number
//Output:Transaction's receipt
void PRINT_RECEIPT(ATM *PHead, int Customer_number);

//Function to print customer's last 10 transation
//Input:Customer number, selected transaction(by customer)
//Output:Receipt of customer's last 10 transaction
int LAST_10_TRANSACTION(ATM *PHead, int Customer_number, char operation[20]);