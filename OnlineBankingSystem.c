#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void HomeScreen();
void RegisterScreen();
void LoginScreen();
void Transaction();
void UpdateAccountDetails();
void ShowAccountDetails();

struct user
{
    char phone[50];
    char ac[50];
    char password[50];
    char name[50];
    char dob[50];
    char add[50];
    float balance;
};

struct user usr,usr1;
FILE *fp;
char filename[50],phone[50],password[50],name[50];
int option,choice,rec;
float amount;
char cont='y';

void HomeScreen()
{
    system("cls");
    printf("\n");
    printf("\t\t\t\t-----------------------------Welcome to Online Banking [DIGITAL INDIA]----------------------------------- ");
    printf("\n\n\t\t1. Register an account");
    printf("\n\n\t\t2. Login to Account");
    printf("\n\n\t\t3. Exit");

    
    printf("\n\n\t\t Enter Your Selection: \t");
    scanf("%d",&option);

    
    if(option == 1)
    {   
        RegisterScreen();
    }
    if(option == 2)
    {
        LoginScreen();
    }
    if(option == 3)
    {
        system("cls");
        exit(0);
    }

}
void RegisterScreen()
{
    system("cls");
    printf("   Enter the name of Account Holder :- \t");
    scanf("%s",usr.name);
    printf("\n Enter Your Account number. :- \t");
    scanf("%s",usr.ac);
    printf("\n Enter Your Phone number.:- \t");
    scanf("%s",usr.phone);
    printf("\n Enter Your New Password:- \t");
    scanf("%s",usr.password);
    printf("\n Enter your Date of Birth:- \t");
    scanf("%s",usr.dob);
    printf("\n Enter Your Current Address:- \t");
    scanf("%s",usr.add);
    usr.balance=0;
    strcpy(filename,usr.phone);
    fp=fopen(strcat(filename,".dat"),"w");
    fwrite(&usr,sizeof(struct user),1,fp);
    if(fwrite != 0)
    {
        printf("\n\n Account Successfully Registered");
    }
    else 
    {
        printf("\n\n something went wrong please try again");
    }
    fclose(fp);
    HomeScreen();
}
void LoginScreen()
{   
    char y;
    system("cls");
    printf("\n Phone number:\t");
    scanf("%s",phone);
    printf("\n Password:\t");
    scanf("%s",password);
    strcpy(filename,phone);
    fp = fopen(strcat(filename,".dat"),"r");
    if(fp == NULL)
    {   
        printf("\nAccount number not registered");
        printf("\nDo you want to create account?");
        printf("\nPress any key");
        getch();
        printf("\n[y/n]");
        scanf("%c", &y);
        x:
        if(y == 'y')
        {
            RegisterScreen();
        }
        else if(y == 'n')
        {
            HomeScreen();
        }
        else
        {   system("cls");
            printf("\n\t\t !!!!!!Invalid input!!!!! \n");
            printf("\t\t\t TRY AGAIN");

            printf("\nAccount number not registered");
            printf("\nDo you want to create account?");
            printf("\n[y/n]:- ");
            scanf("%c", &y);
            goto x;
        }
    }
    else
    {
        fread(&usr,sizeof(struct user),1,fp);
        fclose(fp);
        if(!strcmp(password,usr.password))
        {
            while(TRUE)
            {
                printf("\n\t Welcome %s",usr.name);
                printf("\n");
                printf("\n1.Transaction");
                printf("\n");
                printf("\n2.Show Account Details ");
                printf("\n");
                printf("\n3.Update Account Details");
                printf("\n");
                printf("\n4.Go To Home");
                printf("\n");
                printf("\n Your Choice:\t");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                    Transaction();
                    break;
                    case 2:
                    ShowAccountDetails();
                    break;
                    case 3:
                    UpdateAccountDetails();
                    break;
                    case 4:
                    HomeScreen();
                    default:
                    printf("\nEnter a valid choice");
                }
            }
        }
        else
        {
            printf("\nInvalid Password");
            LoginScreen();
        }
    }
}
void Transaction()
{
    printf("\n\t Welcome %s",usr.name);
    while(cont == 'y')
    {
        system("cls");
        printf("\n\nPress 1 for balance inquiry");
        printf("\nPress 2 for depositing cash");
        printf("\nPress 3 for cash withdrawl");
        printf("\nPress 4 for online transfer");
        printf("\nPress 5 for password change");
        printf("\n Your Choice:\t");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            printf("\n Your current balance is Rs. %.2f",usr.balance);
            break;
            case 2:
            printf("\n Enter the amount you want to deposite:\t");
            scanf("%f",&amount);
            usr.balance += amount;
            fp = fopen(filename,"w");
            fwrite(&usr,sizeof(struct user),1,fp);
            if(fwrite != NULL)
            printf("\nSuccesfully deposited.");
            fclose(fp);
            break;
            case 3:
            printf("\n Enter the amount you want to withdrawl:\t");
            scanf("%f",&amount);
            usr.balance -= amount;
            fp = fopen(filename,"w");
            fwrite(&usr,sizeof(struct user),1,fp);
            if(fwrite != NULL)
            printf("\nYou have withdrawn Rs. %.2f",amount);
            fclose(fp);
            break;
            case 4:
            printf("\nPlease enter the phone number to transfer the balance:\t");
            scanf("%s",phone);
            printf("\n Please enter the amount to transfer:\t");
            scanf("%f",&amount);
            strcpy(filename,phone);
            fp=fopen(strcat(filename,".dat"),"r");
            if(fp == NULL)
            printf("\n Account number not registered");
            else
            {
                fread(&usr1,sizeof(struct user),1,fp);
                fclose(fp);
            }
            if(amount>usr.balance)
            printf("\n Insufficient balance");
            else
            {
                fp=fopen(filename,"w");
                usr1.balance += amount;
                fwrite(&usr1,sizeof(struct user),1,fp);
                fclose(fp);
                if(fwrite!=NULL)
                {
                    printf("\n You have succesfully transfered Rs. %.2f to %s",amount,phone);
                    strcpy(filename,usr.phone);
                    fp=fopen(strcat(filename,".dat"),"w");
                    usr.balance -= amount;
                    fwrite(&usr,sizeof(struct user),1,fp);
                    fclose(fp);
                }
            }
            break;
            case 5:
            printf("\nPlease enter your new password:\t");
            scanf("%s",password);
            fp=fopen(filename,"w");
            strcpy(usr.password,password);
            fwrite(&usr,sizeof(struct user),1,fp);
            if(fwrite != NULL)
            {
                printf("\nPassword succesfully changed");
            }
            break;
            default:
            printf("\nInvalid option");
        }
        printf("\nDo you want to continue the transaction [y/n]\t");
        scanf("%s",&cont);
    }
            
}
void UpdateAccountDetails()
{
    printf("Enter your choice want-----you want to change");
    printf("\n1.Name of Account Holder \n2.Password \n3.Date of Birth \n4.Address");
    printf("\n Your Choice:\t");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        printf("\nEnter the name:- ");
        scanf("%s",usr.name);
        break;
        case 2:
        printf("\nEnter new password:- ");
        scanf("%s",usr.password);
        break;
        case 3:
        printf("\n Enter Date of Birth:- ");
        scanf("%s",usr.dob);
        break;
        case 4:
        printf("\nEnter new address:- ");
        scanf("%s",usr.add);
        break;
        default:
        printf("Invalid Choice");
    }
    strcpy(filename,usr.phone);
    fp=fopen(strcat(filename,".dat"),"w");
    fwrite(&usr,sizeof(struct user),1,fp);
    if(fwrite != 0)
    {
        printf("\n\n Account Successfully Registered");
    }
    else 
    {
        printf("\n\n something went wrong please try again");
    }
    fclose(fp);
}
void ShowAccountDetails()
{
    printf("\nAccount Holder Name- %s",usr.name);
    printf("\nAccount Holder Phone Number- %s",usr.phone);
    printf("\nAccount Holder Date of Birth- %s",usr.dob);
    printf("\nAccount Holder Address- %s",usr.add);
    printf("\nAccount Balance- %f",usr.balance);
}
int main()
{
    system("color 9F");
    HomeScreen();          
    return 0;
}