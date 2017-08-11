#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int filecharacters=0; // number of characters in the read file
int UserType=0;
char userid [50]; //username
char password [50];
int oldFlag =0; // flags for user validation
int newFlag=0;
void userChoices();

void printfile(char filename[50])  // this function can print any file with the entered name + .txt
{
    FILE *fptr;
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; /// assumes max line size of 250 chars
    char* line = malloc(line_size); //dynamic allocation of a string to hold the line of mac length
    while (fgets(line, line_size, fptr) != NULL)    //while there are still lines to get, get the line
    {
        printf("%s",line); //print the line
    }
    free(line); //free the string allocated from the memory
    fclose(fptr); // close the file
}

void modifyFile(char filename[50], char lineToRemove[250], char lineToAdd[250]) // removes, adds or modify lines in a file
{

    FILE *fptr;
    fptr = fopen(filename,"r"); // open for read
    int deleteFlag=0; // flag for checking if there's something to delete
    const size_t line_size = 250; ///assumed max line size of 250 chars
    char* line = malloc(line_size); // dynamic allocation of the line
    const size_t file_size = 5000; ///assumed max file size of 250 chars
    char* file = malloc(file_size);
    file[0] = '\0'; // remove anything in the string that will hold the file
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret; // variable to hold the line to remove if it exists (holds null if it doesn't)
        ret = strstr(line, lineToRemove); // check if the line exists
        if (ret != NULL)
        {
            strcat(file, lineToAdd); //add the line to add in its place
            strcat(file, "\n"); //add a new line
            deleteFlag=1; // indicate that deletion has happened
        }
        else  //fill the rest of the file as it is
        {
            strcat(file, line);
        }
    }
    if (deleteFlag!=1)  // if there was nothing to remove
    {
        strcat(file, lineToAdd); // add the new line at the end
        strcat(file, "\n");
    }
    free(line); //free allocation
    fclose(fptr); //close file

    fptr = fopen(filename,"w"); // open the file for write (deletes what's already in the file)
    int w =0; // loop counter
    int len = strlen(file); //get file length
    for(w=0; w<len; w++)
    {
        fprintf(fptr,"%c",file[w]);//print the file
    }
    fclose(fptr); //close file

}

void searchFileS(char filename[50], char keyword[50]) //searches for any keyword in any file
{

    FILE *fptr;
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; ///assumed line size
    char* line = malloc(line_size); //allocation
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret;
        ret = strstr(line, keyword); // check if the line has the keyword
        if (ret != NULL)
        {
            printf("%s",line); //print the line
        }
    }
    free(line);
    fclose(fptr);
}
char* searchFileD(char filename[50], char keyword1[50], char keyword2[50]) // get a line containing two keywords from any file
{
    int FLAAAG =0;
    FILE *fptr;
    fptr = fopen(filename,"r"); // open the file for read
    const size_t line_size = 250; /// assumed line size of 250
    char* line = malloc(line_size);
    char* output = malloc(line_size); // variable to hold the function output
    while (fgets(line, line_size, fptr) != NULL)    //get the line
    {
        char *ret1;
        ret1 = strstr(line, keyword1); // check if the line has the keyword1
        char *ret2;
        ret2 = strstr(line, keyword2); // check if the line has the keyword2
        if (ret1 != NULL && ret2 != NULL) // if both keywords are found in a line
        {
            strcpy(output, line);  // put that line in the output variable
            newFlag++; // used in user validation indicates that a user havjng the inserted username and pass exists
            FLAAAG = 1;

        }
    }
    free(line);
    fclose(fptr);
    if(FLAAAG ==1){return output;}
    else{return "s";}

}
char* fillAttendance() // adds a new student to attendance log
{
    char* newLine = malloc(250); ///allocate the new line with an assumed length of 250
    newLine[0] = '\n'; // insert a new line at the begining
    newLine[1] = '\0'; // remove whatever else is there
    char state [20]; // vars to hold the info inserted by the user
    char StName [20];
    char date [20];
    char start [20];
    char end [20]; ///assumed max length of each entity 20 chars
    char mod [20];
    char code [20];

    printf("enter attendance state:\t");
    scanf("%s", state);
    strcat(newLine, state); // insert the user input into the line
    strcat(newLine, " "); // insert a space afterwards
    printf("enter student name:\t");
    scanf("%s", StName);
    strcat(newLine, StName);
    strcat(newLine, " ");
    printf("enter date:\t");
    scanf("%s", date);
    strcat(newLine, date);
    strcat(newLine, " ");
    printf("enter start time:\t");
    scanf("%s", start);
    strcat(newLine, start);
    strcat(newLine, " ");
    printf("enter end time:\t");
    scanf("%s", end);
    strcat(newLine, end);
    strcat(newLine, " ");
    printf("enter module name:\t");
    scanf("%s", mod);
    strcat(newLine, mod);
    strcat(newLine, " ");
    printf("enter instance code:\t");
    scanf("%s", code);
    strcat(newLine, code);
    strcat(newLine, " ");
    strcat(newLine, userid);
    strcat(newLine, " ");
    return newLine;
}
void modifyAttendance() //modifies any student's attendance
{
    // modify a student's attendance
    char studentName[50];
    char date[50];
    char newAttendance[250]; // holds the new string after modification
    printf("enter student's name to modify attendance:\t");
    scanf("%s", studentName);
    printf("enter date to modify attendance:\t");
    scanf("%s", date);
    char* oldLine;
    oldLine = malloc(200);
    oldLine = searchFileD("attendance.txt", studentName, date); //get the line to modify
    if(strncmp(oldLine,"s",250)!=0){
    int i = 0; //loop counters
    int w =0;
    int k =0;
    char temp [250]; //temporary string to hold the old line without the student status
    while (oldLine[i]!=' ') //loop until the first word is over (the status word) and let (i) hold that value
    {
        i++;
    }
    for(w=i; w<(strlen(oldLine)+1); w++) // loop from i to the end of the old string
    {
        temp[k]=oldLine[w]; //fill the temp string from the begining with the old one from after the status
        k++;

    }


    printf("\n enter new attendance status: \t");
    if(UserType==2)
    {
        scanf("%s", newAttendance);   //if user is a lecturer allow him to add only a single word
    }
    if(UserType==3)
    {
        scanf("%*c%[^\n]s%*c", newAttendance);   //if user is an admin allow him to add absent with reason
    }
    strcat(newAttendance, temp ); //put the temp after the new status
    newAttendance[strlen(newAttendance)-1]='\0'; // remove the extra new line character
    modifyFile("attendance.txt", oldLine, newAttendance); // write to the file
    }
    else{
        printf("no match found \n");
        modifyAttendance();
    }
}
void login() // login function
{

    printf("Enter 1 for student, 2 for lecturer, 3 for admin:\t");
    scanf("%d", &UserType);
    printf("Enter username:\t");
    scanf("%s", userid);
    printf("Enter password:\t");
    scanf("%s", password);
    searchFileD("log.txt", userid, password); //check if there's a line in the database with matching username and pass
    if(newFlag>oldFlag) // if there's a match
    {
        oldFlag=newFlag; // reset the flags
        userChoices(); // move to choosing action
    }
    else // if no match
    {
        oldFlag=newFlag; //reset flags
        printf("invalid, try again\n");
        system("cls"); //clear the screen
        login(); // call the same function again
    }

}
void exito(){ // choices at the end of any operation
        int exit =0; //holds user choice
        printf("\nenter 1 for another operation, and 2 to logout: \t");
        scanf("%d", &exit);
        if(exit == 1)//if user chose to do another operation
        {
            userChoices(); // recall the function
        }
        else if(exit == 2)// if user chose to logout
        {
            login(); //call back the login function for a new user to log
        }
        else
        {

            printf("\nInvalid choice, choose again");
            scanf("%d", &exit);
            exito();
        }
    }
void userChoices() // handles user choices
{

    if(UserType==1) // if the user is a student
    {
        printf("attendance:\n");
        printf("format:\n");
        printf("status name date start end modName code lecturer absenceReason\n");
        searchFileS("attendance.txt", userid); // get the user's attendance right away
        char date [50];
        char absenceReason [50];
        printf("\nchoose date to provide absence reason for:\t");
        scanf("%s", date);
        printf("\nprovide reason:");
        scanf("%*c%[^\n]s%*c", absenceReason); // scanf modifies to read spaces and ignore any extra new line characters

        char* oldLine;
        oldLine = malloc(250);
        oldLine = searchFileD("attendance.txt", userid, date); // get that entity
        if(oldLine==NULL){
                printf("invalid input, try again");
                userChoices();
                }
        else{
            char newLine [250];
            newLine[0] = '\0'; // remove anything inside
            strcat(newLine, oldLine); // put the old line in the new line string to make things clearer
            newLine[strlen(newLine)-1] = ' '; // to remove the new line character
            strcat(newLine, absenceReason); // put the reason at the end of the line
            modifyFile("attendance.txt", oldLine, newLine); // write to file
            printf("\n Your reason has been added"); //reassure user
        }
    }
    else if(UserType==2) // if user is a teacher
    {
        char* newLine = malloc(250);
        printf("\nassigned students' attendance:\n");
        printf("format:\n");
        printf("status name date start end modName code lecturer absenceReason\n");
        searchFileS("attendance.txt", userid); // get the assigned students' attendace right away
        int userChoic = 0; //holds the next choice of the user
        printf("\nEnter 1 for new student attendance and 2 for modifications:\n");
        scanf("%d", &userChoic);
        if(userChoic==1) //if user wants to add a new attendance
        {
            newLine = fillAttendance(); //get the line of the filled attendance
            modifyFile("attendance.txt", "dummyWord", newLine); //put it to the file without removing anything
        }
        else if (userChoic==2) // if the user wants to modify
        {
            modifyAttendance();
        }
        else{

                printf("\nInvalid choice, choose again");
                scanf("%*s");
                userChoices();
        }
    }

    else if(UserType==3) // if the user is an admin
    {
        int choice=0; // holds the next choice
        printf("\nSystem users :\n");
        printf("format:\n");
        printf("UserType userName Password\n");
        printfile("log.txt"); // shows the system users imediatly
        printf("\nEnter 1 to register a new user, 2 to view attendance :\t");
        scanf("%d", &choice);
        if (choice==1) // if admin wants to add a user
        {
            char type [20];
            char id [20];
            char password [20];
            char theLine [200];
            theLine[0]='\n'; //add new line
            theLine[1]='\0'; // remove extras
            printf("Enter user's type :\n");
            scanf("%s", type);
            strcat(theLine, type);
            strcat(theLine, " ");
            printf("id :\n");
            scanf("%s", id);
            strcat(theLine, id);
            strcat(theLine, " ");
            printf("password :\n");
            scanf("%s", password);
            strcat(theLine, password);
            strcat(theLine, " ");
            modifyFile("log.txt", "dummy woord", theLine); // modify the file
        }
        else if (choice==2) // if user wants to change attendance
        {
            printf("format:\n");
            printf("status name date start end modName code lecturer absenceReason\n");
            printfile("attendance.txt"); // show attendance on the screen
            int c=0;
            printf("\nEnter 1 to modify attendance :\n");
            scanf("%d", &c);
            if(c==1)
            {
                modifyAttendance();
            }
            else
            {
                printf("\nInvalid choice, choose again");
                scanf("%d", &c);
                userChoices();

            }
        }
        else
            {
                printf("\nInvalid choice, choose again");
                scanf("%d", &choice);
                userChoices();
            }
    }
    else
    {

        printf("\nInvalid choice, choose again");
                scanf("%d", &UserType);
        login();
    }



    exito();

}
int main()
{
    login();
    return 0;
}
