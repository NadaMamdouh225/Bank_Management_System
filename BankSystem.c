#include <stdio.h>
#include <stdlib.h>

#include "BankSystem.h"

#define MAX_NO_OF_ACCOUNTS 100
int main()
{
    unsigned char userType;
    back_account_t bank_database[MAX_NO_OF_ACCOUNTS] =
        {
            {"Sherlock Holmes",
             "55 st",
             20106740299827,
             30,
             1001430005,
             "False",
             0,
             "Active",
             5000000,
             1234}}; // create array of structs to store users
    int account_index = 1;

    while (1)
    {
        printf("\t---------------------- BANK SYSTEM ----------------------\n");
        printf("1-Admin Window\n2-Client Window\n");
        scanf("%d", &userType);
        getchar();
        if (userType == 1)
        {
            int op = 0;
            while (op != 3)
            {
                printf("\t----------------- Admin Window -----------------\n");
                printf("1-Create New Account\n2-Open Existing Account\n3-Exit the System\n");
                scanf("%d", &op);
                getchar();
                switch (op)
                {
                case 1:
                    create_new_account(bank_database, &account_index);
                    DisplayInfo(bank_database[account_index - 1]);
                    break;

                case 2:
                    int op = 0;
                    int acc_index;
                    unsigned long int bank_account_id;
                    printf("Enter Client Bank Account ID: ");
                    scanf("%ld", &bank_account_id);
                    acc_index = acount_id_to_bank_database_index(bank_account_id, bank_database);
                    while (op != 6)
                    {
                        printf("\t---------------------------------------------------------------\n");
                        printf("1-Make Transaction\n2-Change Account Status\n3-Get Cash\n4-Deposit in Account\n5-Display Account Info\n6-Return to main menu\n");
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            make_transaction(&bank_database[acc_index], bank_database);
                            break;
                        case 2:
                            change_account_status(&bank_database[acc_index]);
                            break;
                        case 3:
                            get_cash(&bank_database[acc_index]);
                            break;
                        case 4:
                            deposit(&bank_database[acc_index]);
                            break;
                        case 5:
                            DisplayInfo(bank_database[acc_index]);
                            break;
                        case 6:
                            op = 6;
                            break;
                        }
                    }
                    break;

                case 3:
                    op = 3;
                    break;
                }
            }
        }
        else if (userType == 2)
        {
            int op = 0;
            int password;
            int acc_index;
            unsigned long int bank_account_id;
            printf("\t----------------- Client Window -----------------\n");
            printf("Bank Account ID: ");
            scanf("%ld", &bank_account_id);
            printf("Password: ");
            scanf("%u", &password);
            acc_index = acount_id_to_bank_database_index(bank_account_id, bank_database);
            if (bank_database[acc_index].password == password)
            {
                printf("\t -----------------------------------------\n");
                printf("\t------> Welcome %s <------\n", bank_database[acc_index].full_name);
                while (op != 6)
                {
                    printf("\t---------------------------------------------------------------\n");
                    printf("1-Make Transaction\n2-Change Account Password\n3-Get Cash\n4-Deposit in Account\n5-Display Account Info\n6-Return to main menu\n");
                    scanf("%d", &op);
                    switch (op)
                    {
                    case 1:
                        make_transaction(&bank_database[acc_index], bank_database);
                        break;
                    case 2:
                        change_password(&bank_database[acc_index]);
                        break;
                    case 3:
                        get_cash(&bank_database[acc_index]);
                        break;
                    case 4:
                        deposit(&bank_database[acc_index]);
                        break;
                    case 5:
                        DisplayInfo(bank_database[acc_index]);
                        break;
                    case 6:
                        op = 6;
                        break;
                    }
                }
            }
            else
            {
                printf("Bank account id or password might be wrong\n");
            }
        }
        else
            break;
    }
    return 0;
}

void create_new_account(back_account_t new_account[], int *ptr_account_index)
{
    printf("Full Name: ");
    scanf("%[^\n]", new_account[(*ptr_account_index)].full_name);

    printf("Address: ");
    getchar();
    scanf("%[^\n]%*c", new_account[(*ptr_account_index)].address);

    printf("Age: ");
    scanf("%d", &new_account[(*ptr_account_index)].age);

    if (new_account[(*ptr_account_index)].age < 21)
    {
        new_account[(*ptr_account_index)].guardian = "True";
        new_account[(*ptr_account_index)].national_id = 0;
        printf("Guardian National ID: ");
        scanf("%d", &new_account[(*ptr_account_index)].guardian_national_id);
    }
    else
    {
        new_account[(*ptr_account_index)].guardian = "False";
        new_account[(*ptr_account_index)].guardian_national_id = 0;
        printf("National ID: ");
        scanf("%lld", &new_account[(*ptr_account_index)].national_id);
    }
    printf("Balance: ");
    scanf("%lf", &new_account[(*ptr_account_index)].balance);

    /*** Automatically generated ***/
    new_account[(*ptr_account_index)].account_status = "Active";
    new_account[(*ptr_account_index)].bank_account_id = 1000000000 + (new_account[(*ptr_account_index)].national_id % 15) + (new_account[(*ptr_account_index)].age * 1000) + (rand() % 20 * 100000);
    new_account[(*ptr_account_index)].password = 1000 + (rand() % 9 * 1000) + (rand() % 30);
    (*ptr_account_index)++;
}

void DisplayInfo(back_account_t new_account)
{
    printf("\t---------------------- Account Info ----------------------\n");
    printf("Full Name: %s\n", new_account.full_name);
    printf("Address: %s\n", new_account.address);
    printf("Age: %d\n", new_account.age);
    printf("Guardian: %s\n", new_account.guardian);
    printf("Guardian National ID: %d\n", new_account.guardian_national_id);
    printf("National ID: %lld\n", new_account.national_id);
    printf("Balance: %0.4lf\n", new_account.balance);
    printf("Account Status: %s\n", new_account.account_status);
    printf("Bank Account ID: %lld\n", new_account.bank_account_id);
    printf("Password: %d\n", new_account.password);
}

void make_transaction(back_account_t *from_account, back_account_t bank_database[])
{
    unsigned long int to_bank_account_id;
    double amount;
    if (from_account->account_status == "Active")
    {
        printf("Enter Bank Account ID you want to transfer money to: ");
        scanf("%ld", &to_bank_account_id);
        printf("Amount: ");
        scanf("%ld", &amount);

        // Search inside bank database
        if (amount < from_account->balance)
        {
            for (int i = 0; i < MAX_NO_OF_ACCOUNTS; i++)
            {
                if (to_bank_account_id == bank_database[i].bank_account_id)
                {
                    if (bank_database[i].account_status == "Active")
                    {
                        bank_database[i].balance += amount;
                        from_account->balance -= amount;
                        printf("Transaction Completed\n");
                        break;
                    }
                    else
                    {
                        printf("Transaction couldn't be completed, you're transfering to an inactive account\n");
                        break;
                    }
                }
            }
        }
        else
        {
            printf("Transaction couldn't be completed, your balance isn't enough\n");
        }
    }
    else
    {
        printf("Transaction couldn't be completed, your account isn't Active\n");
    }
}

int acount_id_to_bank_database_index(unsigned long int account_id, back_account_t database[])
{
    for (int i = 0; i < 100; i++)
    {
        if (account_id == database[i].bank_account_id)
        {
            return i;
        }
    }
    return -1; // account doesn't exist
}
void change_account_status(back_account_t *account)
{
    int op;
    printf("Change account status to:\n1-Active\n2-Restricted\n3-Closed\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        account->account_status = "Active";
        break;
    case 2:
        account->account_status = "Restricted";
        break;
    case 3:
        account->account_status = "Closed";
        break;
    }
}
void get_cash(back_account_t *account)
{
    double amount;
    printf("Amount:");
    scanf("%lf", &amount);
    if (amount <= account->balance)
    {
        account->balance -= amount;
        printf("Processing you request...\n");
    }
    else
    {
        printf("Your balance is insufficient to complete the process");
    }
}

void deposit(back_account_t *account)
{
    double amount;
    printf("Amount:");
    scanf("%lf", &amount);
    account->balance += amount;
    printf("Processing you request...\n");
}
void change_password(back_account_t *account)
{
    int new_password_1, new_password_2;
    printf("New password: ");
    scanf("%d", &new_password_1);
    printf("New password: ");
    scanf("%d", &new_password_2);
    if (new_password_1 == new_password_2)
    {
        account->password = new_password_1;
        printf("\nPassword changed successfully\n");
    }
    else
    {
        printf("Can't change password\n");
    }
}