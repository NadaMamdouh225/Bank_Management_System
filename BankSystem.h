typedef struct
{
    char full_name[100];
    char address[100];
    unsigned long long int national_id;
    unsigned char age;
    unsigned long int bank_account_id;
    char *guardian;
    unsigned long int guardian_national_id;
    char *account_status;
    double balance;
    unsigned int password;
} back_account_t;

void create_new_account(back_account_t new_account[], int *ptr_account_index);
void DisplayInfo(back_account_t new_account);
void make_transaction(back_account_t *from_account, back_account_t *to_account);
void change_account_status(back_account_t *account);
void get_cash(back_account_t *account);
void deposit(back_account_t *account);
void change_password(back_account_t *account);
int acount_id_to_bank_database_index(unsigned long int account_id, back_account_t database[]);