#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// MAKING SUITABLE FOR EVERY TYPE OF OS (Windows or Linux).
#ifdef _WIN32
#include <windows.h>
void sleep_ms(int ms) { Sleep(ms); }
#else
#include <unistd.h>
void sleep_ms(int ms) { usleep(ms * 1000); }
#endif

// STURCTURE FOR NEW USER.
typedef struct user_details
{
    char name[100];
    long long ph_num;
    char acc_num[10];
    char pass[10];
    double balance;
} data;

typedef struct transaction
{
    char acc[10];
    char type[10]; // DEPOSIT OR WITHDRAW
    double amount; // TRANSACTION AMOUNT
    double balance_after;
} trans;



/*==========================================TO PRINT LINES==========================================*/

void p_line(const char *line, float seconds)
{
    int len = strlen(line);
    if (len == 0 || seconds <= 0) // BASE CONDITION FOR NO LINE
        return;

    int total_ms = (int)(seconds * 1000); // SETTING TIME IN MICROSECONDS
    int per_char_delay = total_ms / len;

    // PRINTING LINE
    if (per_char_delay < 1)
        per_char_delay = 1;

    for (int i = 0; line[i] != '\0'; i++)
    {
        putchar(line[i]);
        fflush(stdout);
        sleep_ms(per_char_delay);
    }
}



/*==========================================TO Handle New-User==========================================*/

void handle_new_user(void)
{
    // USER DECLARE
    data user, temp;     // temp USE TO CHECK DUBLICATE USER
    FILE *fp;            // FILE POINTER
    char new_ph_str[20]; // STRING FOR PHONE NUMBER

    // TAKE INPUT OF USER DETAILS
    // NOTE FOR USER
    p_line("\n=================| Welcome To Our Family |=================\n\n", 1);
    printf("\t\t    ---| NOTE |---\n\n");
    p_line("|\t1. Account should be 6-DIGIT Number!\t |\n", 0.1);
    p_line("|\t2. Password should be 4-CHARECTERS!\t |\n", 0.1);
    p_line("|\t3. Enter a valid Phone Number!\t\t |\n", 0.1);

    // NAME
    p_line("\n\n\n=> Enter Your Name: ", 0.3);
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    // PHONE NUMBER LOOP
    while (1)
    {
        // PHONE NUMBER
        p_line("\n=> Enter Your Phone Number: ", 0.3);
        fgets(new_ph_str, sizeof(new_ph_str), stdin);
        new_ph_str[strcspn(new_ph_str, "\n")] = '\0';

        // LENGTH CHECK
        if (strlen(new_ph_str) != 10)
        {
            p_line("\n\tEnter a Valid Phone Number!\t\n", 0.4);
            p_line("|=========================================|\n\n\n", 0.1);
            continue;
        }

        // DIGIT CHECK
        int valid1 = 1;
        for (int i = 0; i < strlen(new_ph_str); i++)
        {
            if (new_ph_str[i] < '0' || new_ph_str[i] > '9')
            {
                valid1 = 0;
                break;
            }
        }

        if (!valid1)
        {
            p_line("\n\tEnter a Valid Phone Number!\t\n", 0.4);
            p_line("|=========================================|\n\n\n", 0.1);
            continue;
        }

        user.ph_num = atoll(new_ph_str);
        break;
    }

    p_line("\n\n\t\tADDING DATA", 0.5);
    p_line("....\n", 1.5);
    p_line("\t\tData Added ~", 0.5);
    clear_screen();

    // ACCOUNT NUMBER  & PASSWORD LOOP
    while (1)
    {
        int exist = 0; // BOOLEAN VARIABLE

        p_line("\n===========| Create your ACCOUNT & PASSWORD |===========\n\n", 0.1);
        printf("\t\t    ---| NOTE |---\n\n");
        printf("|\t1. Account should be 6-DIGIT Number!\t |\n");
        printf("|\t2. Password should be 4-CHARECTERS!\t |\n");
        printf("|\t3. Enter a valid Phone Number!\t\t |\n\n\n");

        // CREATE ACCOUNT
        p_line("=> Create Your Account_Number: ", 0.3);
        fgets(user.acc_num, sizeof(user.acc_num), stdin);
        user.acc_num[strcspn(user.acc_num, "\n")] = '\0';

        // LENGTH CHECK
        if (strlen(user.acc_num) != 6)
        {
            p_line("\n\tAccount Number must be 6-DIGIT NUMBER!\t\n", 0.4);
            p_line("|====================================================|\n\n\n\n", 0.1);
            clear_screen();
            continue;
        }

        // DIGIT CHECK
        int valid2 = 1;
        for (int i = 0; i < 6; i++)
        {
            if (user.acc_num[i] < '0' || user.acc_num[i] > '9')
            {
                valid2 = 0;
                break;
            }
        }

        if (!valid2)
        {
            p_line("\n\tOnly Digits are Allowed!\t\n", 0.4);
            p_line("|======================================|\n\n\n\n", 0.1);
            clear_screen();
            continue;
        }

        // PASSWORD
        p_line("\n=> Create Your Password: ", 0.3);
        fgets(user.pass, sizeof(user.pass), stdin);
        user.pass[strcspn(user.pass, "\n")] = '\0';

        if (strlen(user.pass) != 4)
        {
            p_line("\n  \tPassword must be 4-CHARECTERS!\t\n", 0.4);
            p_line("|============================================|\n", 0.1);
            clear_screen();
            continue;
        }

        // OPEN FILE TO CHECK DUPLICATE USER
        fp = fopen("data.dat", "rb");

        if (fp != NULL)
        {
            while (fread(&temp, sizeof(temp), 1, fp))
            {
                if (strcmp(temp.acc_num, user.acc_num) == 0)
                {
                    exist = 1;
                    break;
                }
            }
            fclose(fp);
        }

        // IF DUPLICATE USER FOUND
        if (exist)
        {
            p_line("\n\n\tSorry User Already Exists!\n", 0.7);
            p_line("\t   Please Try Again", 0.7);
            p_line("....\n", 1.5);
            printf("|========================================|\n");
            clear_screen();
        }
        else
        {
            break; // UNIQUE ACCOUNT NUMBER
        }
    }

    // SETTING USER BALANCE ZERO
    user.balance = 0;

    // SAVE NEW USER
    fp = fopen("data.dat", "ab");

    // IF DATA FILE NOT FOUND
    if (fp == NULL)
    {
        p_line("\n\tSorry Server Error!\n", 0.7);
        p_line("\t Please Try Again", 0.7);
        printf("|========================================|\n");
        return;
    }

    // ADD DETAILS IN DATA BASE
    fwrite(&user, sizeof(user), 1, fp);
    fclose(fp);

    p_line("\n\n\t      Creating Your Account\n", 0.2);
    p_line("\t\t      .....\n", 2.0);
    p_line("\t| Account Created Successfully |\n\n\n", 0.2);
    p_line("=> Your Acount number: ", 0.5);
    printf("%s |\n", user.acc_num);
    p_line("=> Your Password: ", 0.5);
    printf("%s |\n\n\n", user.pass);
    p_line("Thank You for joining us", 0.7);
    p_line("...\n", 0.7);

    p_line("\n\n=> Press \"ENTER Twice\" to Move Back: ", 0.7);
    getchar();

    while (getchar() != '\n')
        ;

    p_line("\n\tMoving Back to Main Menu", 0.7);
    p_line("...\n", 1.5);
    clear_screen();
    return;
}


/*==========================================TO Handle User-Loggin==========================================*/

void handle_login_acc(void)
{
    data user, temp; // temp USE TO CHECK VALID USER
    FILE *fp;

    while (1)
    {
        p_line("\n\n================| LOG-IN PAGE |================\n\n", 0.7);

        // TAKE ACCOUNT NUMBER INPUT
        p_line("\n=> Enter Your Account Number: ", 0.1);
        fgets(user.acc_num, sizeof(user.acc_num), stdin);
        user.acc_num[strcspn(user.acc_num, "\n")] = '\0';

        // TAKE PASSWORD INPUT
        p_line("\n=> Enter Your Password: ", 0.3);
        fgets(user.pass, sizeof(user.pass), stdin);
        user.pass[strcspn(user.pass, "\n")] = '\0';

        // TO CHECK IN  FILE
        int exist1 = 0;

        fp = fopen("data.dat", "rb");

        if (fp == NULL)
        {
            p_line("\n\n\tSorry Server Error!\n", 0.7);
            p_line("\tPlease Try Again", 0.7);
            p_line("...\n", 1.5);
            return;
        }

        if (fp != NULL)
        {
            while (fread(&temp, sizeof(temp), 1, fp))
            {
                if (strcmp(temp.acc_num, user.acc_num) == 0 &&
                    strcmp(temp.pass, user.pass) == 0)
                {
                    // FOR USER NAME & PHONE NUMBER
                    // strcpy(user.name, temp.name);
                    // user.ph_num = temp.ph_num;
                    user = temp;
                    exist1 = 1;
                    break;
                }
            }
            fclose(fp);
        }

        if (exist1)
        {
            p_line("\n\nLogging In", 0.7);
            p_line(".....\n", 1.5);
            p_line("Logged In Succesfully!\n\n", 0.7);
            break; // USER FOUND
        }
        else
        {
            p_line("\n\n\tNo User Found! or ", 0.7);
            p_line("Incorrect Password!\n", 0.7);
            p_line("\t\tPlease Try Again!", 0.7);
            p_line("...\n", 1.5);
            clear_screen();
        }
    }

    // PRINT ACCOUNT DETAILS
    p_line("\n\n  \tAccount Details\t\n", 0.5);
    p_line("|=============================|\n\n", 0.5);

    p_line("| Account Holder: ", 0.7);
    printf("%s |\n\n", user.name);
    p_line("| Phone Number: ", 0.7);
    printf("  %lld  |\n", user.ph_num);
    p_line("| Account Number: ", 0.7);
    printf("%s      |", user.acc_num);
    p_line(" \n", 0.7);

    // MOVING TOWARDS THE NEXT FUNTION

    char menu_choice;

    do
    {
        {
            p_line("\n\nDo You want move to Transaction Menu (y/n): ", 0.7);
            scanf(" %c", &menu_choice);

            while (getchar() != '\n')
                ;

            menu_choice = tolower(menu_choice);

            if (menu_choice != 'y' && menu_choice != 'n')
            {
                p_line("\nInvalid Input!\n", 0.4);
                p_line("SORRY! Please Try Again", 0.4);
                p_line("-------\n", 0.7);
                continue;
            }
            else if (menu_choice == 'y')
            {
                p_line("\n  \tMoving to Transaction Menu", 0.4);
                p_line("...\n", 1.5);

                // PASSING USER DETAILS TO TRANSACTION FUNCTION
                handle_transaction(&user);
            }
            else
            {
                p_line("\n  \tMoving to Main Menu", 0.4);
                p_line("...\n", 1.5);
                clear_screen();
                break;
            }
        }
    } while (menu_choice != 'y');
}


/*==========================================To Handle Trancastion Menu==========================================*/

void handle_transaction(data *user)
{
    FILE *fp;
    data temp;
    int option;

    double deposit;
    double withdraw;
    do
    {
        clear_screen();
        p_line("\n\n================| TRANSACTION MENU |================\n\n", 0.7);

        p_line("  1 => Check Balance\n", 0.1);
        p_line("  2 => Deposit Amount\n", 0.1);
        p_line("  3 => Withdraw Amount\n", 0.1);
        p_line("  4 => Other Options\n", 0.1);
        p_line("  5 => Log Out\n", 0.1);

        p_line("\n=> Please Select any Option: ", 0.7);

        if (scanf("%d", &option) != 1 || option < 1 || option > 5)
        {

            while (getchar() != '\n')
                ;

            p_line("\n\nInvalid Input!\n", 0.4);
            p_line("SORRY! Please Try Again", 0.4);
            p_line("-------\n", 1.5);

            clear_screen();
            continue;
        }

        getchar();

        switch (option)
        {
        case 1:
            p_line("\n\n=> Your Available Balance is:  ", 0.7);
            printf("---| %g Rupees |---\n", user->balance);
            p_line("\n|==================================================|\n\n", 0.1);
            break;

        case 2:
            p_line("\n\n=> Enter the Amount to Deposit: ", 0.7);
            scanf("%lf", &deposit);

            if (deposit <= 0)
            {
                p_line("\n\n| Invalid Deposit Amount |\n", 0.7);

                while (getchar() != '\n')
                    ;
                break;
            }
            else
            {

                while (getchar() != '\n')
                    ;

                fp = fopen("data.dat", "rb+");
                // READS THE FILE AND WRITE IN THE FILE

                if (fp == NULL)
                {
                    p_line("\n\tSorry Server Error!\n", 0.7);
                    p_line("\t Please Try Again", 0.7);
                    printf("|========================================|\n");
                    return;
                }

                while (fread(&temp, sizeof(temp), 1, fp))
                {
                    // IF THE ACCOUNT NUMBER IS MATHCHED OR FOUND IN THE FILE
                    if (strcmp(temp.acc_num, user->acc_num) == 0)
                    {
                        // THE POINTER POINTS TO THE USER WHOSE USING THE FILE
                        fseek(fp, -sizeof(temp), SEEK_CUR);

                        user->balance += deposit;

                        // APPENDING THE AMOUNT IN THE FILE
                        fwrite(user, sizeof(*user), 1, fp);
                        break; // IF AMOUNT UPDATED THE LOOP TERMINATES
                    }
                }

                fclose(fp);

                p_line("\n\n              In Process", 0.7);
                p_line("....", 2.5);
                p_line("\n---| Amount Deposited Successfully |---\n\n", 0.7);
                p_line("\n=> Amount You Deposit: ", 0.7);
                printf("| %g Rupees |", deposit);
                p_line("\n\n=> Your Current Balance: ", 0.7);
                printf("| %g Rupees |\n", user->balance);
                p_line("\n|==================================================|\n\n", 0.7);

                save_transaction(user->acc_num, "Deposit", deposit, user->balance);
                break;
            }

        case 3:
            p_line("\n\n=> Enter the Amount to withdraw: ", 0.7);
            scanf("%lf", &withdraw);

            if (withdraw > user->balance)
            {
                p_line("\n\n| \t   Your Balance is Low!\t\t   |\n", 0.1);
                p_line("|  Withdraw Not Possible- Process Failed!  |\n", 0.1);

                while (getchar() != '\n')
                    ;
                break;
            }
            else if (withdraw <= 0)
            {
                p_line("\n\n| Invalid Withdraw Amount |\n", 0.7);

                while (getchar() != '\n')
                    ;
                break;
            }
            else
            {

                while (getchar() != '\n')
                    ;

                fp = fopen("data.dat", "rb+");
                // READS THE FILE AND WRITE IN THE FILE

                if (fp == NULL)
                {
                    p_line("\n\tSorry Server Error!\n", 0.7);
                    p_line("\t Please Try Again", 0.7);
                    printf("|========================================|\n");
                    return;
                }

                while (fread(&temp, sizeof(temp), 1, fp))
                {
                    // IF THE ACCOUNT NUMBER IS MATHCHED OR FOUND IN THE FILE
                    if (strcmp(temp.acc_num, user->acc_num) == 0)
                    {
                        // THE POINTER POINTS TO THE USER WHOSE USING THE FILE
                        fseek(fp, -sizeof(temp), SEEK_CUR);

                        user->balance -= withdraw;

                        // APPENDING THE AMOUNT IN THE FILE
                        fwrite(user, sizeof(*user), 1, fp);
                        break; // IF AMOUNT UPDATED THE LOOP TERMINATES
                    }
                }

                fclose(fp);

                p_line("\n\n              In Process", 0.7);
                p_line("....", 2.5);
                p_line("\n---| Amount Withdrawed Successfully |---\n", 0.7);
                p_line("\n\n=> Amount You Withdraw: ", 0.7);
                printf("| %g Rupees |", withdraw);
                p_line("\n\n=> Your Current Balance: ", 0.7);
                printf("| %g Rupees |\n", user->balance);
                p_line("\n|==================================================|\n\n", 0.1);

                save_transaction(user->acc_num, "Withdraw", withdraw, user->balance);
                break;
            }

        case 4:
            p_line("\n  \tMoving to Other Options", 0.7);
            p_line("...\n", 1.5);
            // CALLED IN OTHER OPTION FUNCTIONs
            handle_other_option(user);
            continue;

        case 5:
            p_line("\n\nLogging Out", 0.7);
            p_line(".....\n", 1.5);
            p_line("Logged Out Succesfully!\n\n", 0.7);
            clear_screen();
            return;

        default:
            p_line("\nInvalid Option Input!\n", 0.4);
            p_line("SORRY! Please Try Again", 0.4);
            p_line("...\n", 1.5);
            clear_screen();
            continue;
        }

        if (option != 5)
        {
            p_line("\n\n=> Press \"ENTER Twice\" to Move Back: ", 0.7);
            getchar();

            while (getchar() != '\n')
                ;

            p_line("\n\tReloading Page", 0.7);
            p_line("...\n", 1.5);
            clear_screen();
        }

    } while (1);
}


/*==========================================TO Handle Other Options==========================================*/

void handle_other_option(data *user)
{
    FILE *fp;
    data temp;
    int option;
    char verify[10];
    char verify1[10];

    long long new_ph_num;
    char new_pass[10];
    char new_ph_str[20];

    do
    {
        clear_screen();
        p_line("\n\n================| OTHER OPTION |================\n\n", 0.7);
        p_line("  1 => Change Phone Number\n", 0.1);
        p_line("  2 => Change Password\n", 0.1);
        p_line("  3 => View Transaction History\n", 0.1);
        p_line("  4 => Back\n", 0.1);

        p_line("\n=> Please Select any Option: ", 0.7);

        if (scanf("%d", &option) != 1 || option < 1 || option > 4)
        {

            while (getchar() != '\n')
                ;

            p_line("\n\nInvalid Input!\n", 0.4);
            p_line("SORRY! Please Try Again", 0.4);
            p_line("-------\n", 1.5);

            clear_screen();
            continue;
        }

        getchar();

        switch (option)
        {
        case 1:
            clear_screen();
            // NEW PHONE NUMBER LOOP
            while (1)
            {
                // PHONE NUMBER
                p_line("\n=> Enter Your New Phone Number: ", 0.3);
                fgets(new_ph_str, sizeof(new_ph_str), stdin);
                new_ph_str[strcspn(new_ph_str, "\n")] = '\0';

                // LENGTH CHECK
                if (strlen(new_ph_str) != 10)
                {
                    p_line("\n\tEnter a Valid Phone Number!\t\n", 0.7);
                    p_line("|=========================================|\n\n", 0.4);
                    clear_screen();
                    continue;
                }

                // DIGIT CHECK
                int valid1 = 1;
                for (int i = 0; i < strlen(new_ph_str); i++)
                {
                    if (new_ph_str[i] < '0' || new_ph_str[i] > '9')
                    {
                        valid1 = 0;
                        break;
                    }
                }

                if (!valid1)
                {
                    p_line("\n\tEnter a Valid Phone Number!\t\n", 0.7);
                    p_line("|=========================================|\n\n", 0.4);
                    clear_screen();
                    continue;
                }

                new_ph_num = atoll(new_ph_str);

                // PASSWORD VERIFICATION
                p_line("\n=> Enter Your Current Password: ", 0.3);
                fgets(verify, sizeof(verify), stdin);
                verify[strcspn(verify, "\n")] = '\0';

                int update = 0;

                fp = fopen("data.dat", "rb+");

                if (fp == NULL)
                {
                    p_line("\nSorry Server Error!\n", 0.7);
                    p_line("Please Try Again", 0.7);
                    p_line("...\n", 1.5);
                    clear_screen();
                    return;
                }

                if (fp != NULL)
                {
                    while (fread(&temp, sizeof(temp), 1, fp))
                    {
                        if (strcmp(user->acc_num, temp.acc_num) == 0)
                        {
                            if (strcmp(temp.pass, verify) != 0)
                            {
                                p_line("\n\t\tIncorrect Password!\n", 0.7);
                                p_line("\t\tPlease Try Again!", 0.7);
                                p_line("...\n", 1.5);
                                clear_screen();
                                break;
                            }

                            if (temp.ph_num == new_ph_num)
                            {
                                p_line("\n\n\tEnter a New Phone Number!\t\n", 0.7);
                                p_line("|=======================================|\n\n", 0.4);
                                clear_screen();
                                break;
                            }

                            user->ph_num = new_ph_num;

                            fseek(fp, -sizeof(temp), SEEK_CUR);
                            fwrite(user, sizeof(*user), 1, fp);

                            update = 1;
                            break;
                        }
                    }
                    fclose(fp);
                }

                if (update == 1)
                {
                    break;
                }
                else
                    continue;
            }

            p_line("\n\nUPDATING", 0.5);
            p_line("....\n", 1.5);
            printf("Phone Number Changed ~\n");
            break;

        case 2:
            clear_screen();
            // NEW PASSWORD LOOP
            while (1)
            {

                p_line("\n=> Enter Your New Password: ", 0.3);
                fgets(new_pass, sizeof(new_pass), stdin);
                new_pass[strcspn(new_pass, "\n")] = '\0';

                if (strlen(new_pass) != 4)
                {
                    p_line("\n\n  \tPassword must be 4-CHARECTERS!\t\n", 0.4);
                    p_line("|============================================|\n", 0.1);
                    clear_screen();
                    continue;
                }

                // PASSWORD VERIFICATION
                p_line("\n=> Enter Your Current Password: ", 0.3);
                fgets(verify1, sizeof(verify1), stdin);
                verify1[strcspn(verify1, "\n")] = '\0';

                int update1 = 0;

                fp = fopen("data.dat", "rb+");

                if (fp == NULL)
                {
                    p_line("\nSorry Server Error!\n", 0.7);
                    p_line("Please Try Again", 0.7);
                    p_line("...\n", 1.5);
                    return;
                }

                if (fp != NULL)
                {
                    while (fread(&temp, sizeof(temp), 1, fp))
                    {
                        if (strcmp(user->acc_num, temp.acc_num) == 0)
                        {
                            if (strcmp(temp.pass, verify1) != 0)
                            {
                                p_line("\n\n\t\tIncorrect Password!\n", 0.7);
                                p_line("\t\tPlease Try Again!", 0.7);
                                p_line("...\n", 1.5);
                                clear_screen();
                                break;
                            }

                            if (strcmp(temp.pass, new_pass) == 0)
                            {
                                p_line("\n\n\tEnter a New Password! ******\t\n", 0.4);
                                p_line("|==========================================|\n\n", 0.1);
                                p_line(" ", 1.0);
                                clear_screen();
                                break;
                            }

                            strcpy(user->pass, new_pass);

                            fseek(fp, -sizeof(temp), SEEK_CUR);
                            fwrite(user, sizeof(*user), 1, fp);

                            update1 = 1;
                            break;
                        }
                    }
                    fclose(fp);
                }

                if (update1 == 1)
                {
                    break;
                }
                else
                    continue;
            }

            p_line("\n\nUPDATING", 0.5);
            p_line("....\n", 1.5);
            printf("Password Changed ~\n");
            break;

        case 3:
            p_line("\n  \tMoving to Transaction History", 0.4);
            p_line("...\n", 1.5);
            clear_screen();
            view_transaction(user->acc_num);
            break;

        case 4:
            p_line("\n  \tMoving to Transaction Menu", 0.4);
            p_line("...\n", 1.5);
            clear_screen();
            return;

        default:
            break;
        }

        if (option != 4)
        {
            p_line("\n\n=> Press \"ENTER Twice\" to Move Back: ", 0.7);
            getchar();

            while (getchar() != '\n')
                ;

            p_line("\n\tReloading Page", 0.7);
            p_line("...\n", 1.5);
            clear_screen();
        }

    } while (1);
}


/*==========================================TO Handle Save Transaction==========================================*/

void save_transaction(const char *acc_num, const char *type, double amt, double bal)
{
    FILE *fp;
    trans history;

    strcpy(history.acc, acc_num);
    strcpy(history.type, type);
    history.amount = amt;
    history.balance_after = bal;

    fp = fopen("transaction.dat", "ab");

    if (fp == NULL)
    {
        p_line("\nSorry Server Error!\n", 0.7);
        p_line("Please Try Again", 0.7);
        p_line("...\n", 1.5);
        return;
    }

    fwrite(&history, sizeof(history), 1, fp);
    fclose(fp);
}