#include <stdio.h>
#include <stdlib.h>
#include "BankSys.h"

int main()
{
    unsigned char userType;
    back_account_t *bank_database[100]; // create array of struct pointer to store users
    int account_index = 0;
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
                    bank_database[account_index] = create_new_account();
                    DisplayInfo(bank_database[account_index]);
                    account_index++;
                    break;

                case 2:
                    int op = 0;
                    int acc_index;
                    unsigned long int bank_account_id;
                    printf("Enter Client Bank Account ID: ");
                    scanf("%ld", &bank_account_id);
                    acc_index = acount_id_to_bank_database_index(bank_account_id, bank_database);
                    printf("%d\n", acc_index);
                    while (op != 5)
                    {
                        printf("\t\n---------------------------------------------------------------\n");
                        printf("1-Make Transaction\n2-Change Account Status\n3-Get Cash\n4-Deposit in Account\n5-Return to main menu\n6-Display Account Info\n");
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            make_transaction(&bank_database[acc_index], bank_database);
                            break;

                        case 5:
                            op = 5;
                            break;
                        case 6:
                            printf("Enter Client Bank Account ID: ");
                            scanf("%ld", &bank_account_id);
                            acc_index = acount_id_to_bank_database_index(bank_account_id, bank_database);
                            DisplayInfo(bank_database[acc_index]);
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
            printf("\t----------------- Client Window -----------------\n");
        }
        else
            break;
    }
    return 0;
}

back_account_t create_new_account(void)
{
    back_account_t new_account;
    printf("Full Name: ");
    scanf("%[^\n]", new_account.full_name);

    printf("Address: ");
    getchar();
    scanf("%[^\n]%*c", new_account.address);

    printf("Age: ");
    scanf("%d", &new_account.age);

    if (new_account.age < 21)
    {
        new_account.guardian = "True";
        new_account.national_id = 0;
        printf("Guardian National ID: ");
        scanf("%d", &new_account.guardian_national_id);
    }
    else
    {
        new_account.guardian = "False";
        new_account.guardian_national_id = 0;
        printf("National ID: ");
        scanf("%lld", &new_account.national_id);
    }
    printf("Balance: ");
    scanf("%lf", &new_account.balance);

    /*** Automatically generated ***/
    new_account.account_status = "Active";
    new_account.bank_account_id = 1000000000 + (new_account.national_id % 15) + (new_account.age * 1000) + (rand() % 20 * 100000);
    new_account.password = 1000 + (rand() % 9 * 1000) + (rand() % 30);

    return new_account;
}

void DisplayInfo(back_account_t *new_account)
{
    printf("---------------------- Account Info ----------------------\n");
    printf("Full Name: %s\n", new_account->full_name);
    printf("Address: %s\n", new_account->address);
    printf("Age: %d\n", new_account->age);
    printf("Guardian: %s\n", new_account->guardian);
    printf("Guardian National ID: %d\n", new_account->guardian_national_id);
    printf("National ID: %lld\n", new_account->national_id);
    printf("Balance: %0.4lf\n", new_account->balance);
    printf("Account Status: %s\n", new_account->account_status);
    printf("Bank Account ID: %lld\n", new_account->bank_account_id);
    printf("Password: %d\n", new_account->password);
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
            for (int i = 0; i < 100; i++)
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