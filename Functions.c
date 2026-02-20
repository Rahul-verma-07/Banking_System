//TO PRINT LINES

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



// TO CREATE NEW ACCOUNT
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