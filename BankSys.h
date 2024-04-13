typedef struct
{
    char full_name;
    char address;
    unsigned long long int national_id;
    unsigned char age;
    unsigned long int bank_account_id;
    char *guardian;
    unsigned long int guardian_national_id;
    char *account_status;
    double balance;
    unsigned int password;
} back_account_t;

back_account_t create_new_account(void);
void DisplayInfo(back_account_t new_account);
void make_transaction(back_account_t *from_account, back_account_t bank_database[]);
int acount_id_to_bank_database_index(unsigned long int account_id, back_account_t database[]);