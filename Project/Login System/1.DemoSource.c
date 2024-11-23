#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user{
	char fullName[50];
	char email[50];
	char password[50];
	char username[50];
	char phone[50];
};

void takeinput(char ch[50]){
	fgets(ch, 50, stdin);
	ch[strcspn(ch, "\n")] = '\0';
}

char generateUsername(char email[50], char username[50]){
	//abc123@gmail.com
	for(int i = 0; i < strlen(email); i++){
		if(email[i] == '@') {
			username[i] = '\0';
			break;
		}
		username[i] = email[i];
	}
}

void takepassword(char pwd[50]){
	int i = 0;
	char ch;
	while(1){
		ch = getch();
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}
		else if(ch == BCKSPC){
			if(i > 0){
				i--;
				printf("\b \b");
			}
		}
		else{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}
int main(){
	system("color 0a");
	FILE *fp;
	
	int opt; 
	struct user user, usr;
	char password2[50];
	int usrFound = 0;
	
	
	
	printf("\n\t\t\t\t--------------Welcome to authentication system------------");
	printf("\nPlease choose your operation");
	printf("\n1.Signup");
	printf("\n2.Login");
	printf("\n3.Exit");
	
	printf("\n\nYour choice:\t");
	scanf("%d", &opt);
	fgetc(stdin);
	
	switch(opt){
		case 1:
			
			system("cls");
			
			printf("\nEnter your full name:\t");
			takeinput(user.fullName);
			
			printf("Enter your email:\t");
			takeinput(user.email);
			
			printf("Enter your contact number:\t");
			takeinput(user.phone);
			
			printf("Enter your password:\t");
			takepassword(user.password);
			
			printf("\nConfirm your password: \t");
			takepassword(password2);
			
			if(strcmp(user.password, password2) == 0){				
				generateUsername(user.email, user.username);
				
				 // Kiểm tra xem người dùng đã tồn tại chưa
                fp = fopen("Users.dat", "rb");
                if (fp) {
                    struct user temp;
                    while (fread(&temp, sizeof(struct user), 1, fp)) {
                        if (strcmp(temp.email, user.email) == 0 || strcmp(temp.username, user.username) == 0) {
                            usrFound = 1;
                            break;
                        }
                    }
                    fclose(fp);
                }
                
				if (usrFound) {
                    printf("\nUser already exists. Please use a different email or username.\n");
                } else {
                    fp = fopen("Users.dat", "ab+");
                    if (!fp) {
                        printf("\nError opening file!");
                        return 1;
                    }

                    if (fwrite(&user, sizeof(struct user), 1, fp)) {
                        printf("\n\nUser registration success! Your username is %s", user.username);
                    } else {
                        printf("\n\nSorry! Something went wrong :(");
                    }
                    fclose(fp);
                }
            } else {
                printf("\n\nPasswords do not match");
                Beep(750, 300);
            }

            break;
		
		case 2: 
		{
		    char username[50], pword[50];
		    
		    printf("\nEnter your username:\t");
		    takeinput(username);
			
			
		    printf("\nEnter your password:\t");
		    takepassword(pword);
		    
		    fp = fopen("Users.dat", "r");
		    if (!fp) {
		        printf("\n\nError opening file.");
		        return 1;
		    }
		
		    while (fread(&usr, sizeof(struct user), 1, fp)) {
				if (strcmp(usr.username, username) == 0) {
                    usrFound = 1;
                    if (strcmp(usr.password, pword) == 0) {
                    			
						system("cls");
			
                        printf("\n\t\t\t\t\tWelcome %s", usr.fullName);
                        printf("\n\n| Full Name:\t%s", usr.fullName);
                        printf("\n| Email:\t%s", usr.email);
                        printf("\n| Username:\t%s", usr.username);
                        printf("\n| Contact no.:\t%s", usr.phone);
                    } else {
                        printf("\n\nInvalid Password!");
                        Beep(800, 300);
                    }
                    break;
                }
            }
		
		
		    if (!usrFound) {
		        printf("\n\nUser is not registered");
		        Beep(800, 300);
		    }
		    fclose(fp);
			break;
		}
		case 3:
			printf("\t\tBye Bye :)");
			exit(1);
			
	}
	
	return 0;
}