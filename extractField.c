/*
 *
 * Here is the Program to Display the Fields as per specified by the User along with conditions
 * For Example: displaying all First names where the Degree is MSc followed by Gender to be 'F' and the Year as 2024
 * Then Program must check the details from .csv file provided, Firstly it must check if the row is of Degree MSc or Not, then Gender and so On
 * If All Conditions satisfied, then It must display the First Name of the Student */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/* This Problem is Solved as per the expectations like, 
 * if the user have given the conditions to check as Degree Msc followed by Gender to be 'F' and the Year as 2024, 
 * Then this program will search for the Degree Field in the Particular Row, after meeting the requirements,
 * it will proceed to search for Gender Field, and then Year Field,
 * preserving the order given by the user and will Display the output Field if all conditions are checked */

/* Here the Keywords are defined as
 * -r : Roll No
 * -fn : First Name
 * -mn : Middle Name
 * -ln : Last Name
 * -g : Gender
 * -y : Year
 * -d : Degree
 *  These are the Fields of the csv file
 *
 *  And Assumption is taken that the Structure for csv file is as follows:
 *  
 *  RollNo, FirstName MiddleName LastName, Gender, Year, Degree
 *
 *  without having extra spaces
 *
 *  -print is defined for mentioning which field you want as an Output
 *
 *  Note: -print only takes one field at a time and is not programmed to take multiple fields for Output*/


/* Syntax For Using this Program, run following commands in terminal
 * $ make
 * $ ./extractField <your csv File> <field1> <value1> <field2> <value2> .. -print <fieldx>
 *
 * here second argument is name of your csv file
 * <field1>, <field2> and so on are the Keywords for the fields as defined above;
 * For Eg: Your have to type -r for Roll No
 * <value1>, <value2> and so on are the respective values as per the fields passed for providing the search Conditions
 * after giving conditions -print is given so to understand that after -print that field is mentioned which user supposes to be displayed
 * as <fieldx>
 *
 * For the Example Discussed Above,
 * If User want to Display all First names where the Degree is MSc followed by Gender to be 'F' and the Year as 2024
 * For that, User have to Type: ./extractField <your-csv-file> -d MSc -g F -y 2024 -print -fn
 * */

/* Global Declarations, So that these can be accessed throughout the Program, 
 * *args[] contains the fields that can be selected for conditions as well as for print operation,
 * Note : print is also defined in that but is not part of it, 
 * *fields[] contains the condition values,
 * delimitor[] is designed to separate out the fields of csv,
 * printField contains the index for printing Field*/

char *args[] = {"-r","-fn","-mn","-ln","-g","-y","-d","-print"};
char *fields[7] = {0,0,0,0,0,0,0};
char delimitor[7] = {',',' ',' ',',',',',',','\n'};
int printField;


/* It is the Code to Check Whether the Input Data File have extension as .csv or Not */
int checkForCSV(char *fileName)
{
        int len = strlen(fileName);

        if(len > 4 && strcmp(&fileName[len-4],".csv")==0)
                return 1;
        else
                return 0;
}


/* It is function to validate whether the Number of Arguments given by User are Valid or Not */
int validateNoOfArgs(int argc){
	if((argc%2)==1 || argc>18 || argc < 6)
		return 0;
	else
		return 1;
}


/* It is the Function which checks whether the passed value in match function does exist in *args[] or not and returns the index if found else -1 */
int match(char *value)
{
	for(int i=0;i<8;i++){
		if(strcmp(value,args[i])==0){
			return i;
		}
	}
	return -1;
}


/* It is the Function to Validate the Passed Arguments as Fields and print operation */
int validateArgs(int argc, char *argv[], int seq[], int k)
{
	int flag=0;
	k--;
	if(strcmp(argv[argc-2],"-print")!=0)
		return 0;
	argc--;
	while(argc>=2)
	{
		if(match(argv[argc])==-1)
			return 0;
		else
		{
			if(flag==0){
				printField = match(argv[argc]);
				flag=1;
				argc--;
			}
			else{
				if(strcmp(argv[argc],"-print")!=0){
					fields[match(argv[argc])] = argv[argc+1];
					seq[k] = match(argv[argc]);
					k--;
				}
				argc = argc - 2;
			}
		}
	}
	return 1;
}


/* This is the Function which checks whether the condition Value Passed with Field is same or not as of Field in .csv File
 * Also it print Output for the Required field if Proper match with specified conditions are Found */

int checkForField(FILE * file, int pointer, int print)
{
	int length=0, i=0;
	char ch;
	while((ch=fgetc(file))!=delimitor[pointer]){
		if(ch==EOF)
			break;
		length++;
	}
	
	fseek(file,-(length+1),SEEK_CUR);

	char word[length];

	while((ch=fgetc(file))!=delimitor[pointer])
	{
		if(ch==EOF)
			break;
		word[i] = ch;
		i++;
	}
	word[i] = '\0';
	
	fseek(file,-(length+1),SEEK_CUR);
	
	if(print == 1)
		printf("%s\n",word);
	else{
		if(strcmp(word,fields[pointer])==0)
			return 1;
		else{
			if(ch==EOF)
				return -1;
			else
				return 0;
		}
	}
}


/* This Function moves the File Pointer to the Start of the Current Field */
void takeToStart(FILE *file, int pointer)
{
	int index;
	char ch;
	if((pointer-1)<0)
		index = 7-1;
	else
		index = pointer-1;
	while((ch=fgetc(file))!=delimitor[index])
		fseek(file,-2,SEEK_CUR);
}


/* This Function skips the current line by moving the File Pointer to the New Line in .csv File */
int takeToNextLine(FILE *file)
{
	char ch;
        while((ch=fgetc(file))!='\n')
	{
		if(ch==EOF)
			break;
	}
	return 1;
}

/* This Function is mainly dealing with the main purpose and whole algorithm to solve the Problem
 * This Function is dealing with the Fields of a Single Line as per the matches Found in the Field */
void extractFile(FILE * file, int seq[], int k)
{
	int pointer=0, i=0, getFlag=0;
	char ch;
	while((ch=fgetc(file))!=EOF)
	{
		if(ch==delimitor[pointer])
		{
			if(getFlag == 0){
				if(pointer < seq[i])
					pointer = (pointer+1)%7;
			}
			else
				if(pointer < printField)
					pointer = (pointer+1)%7;
		}
		if(getFlag == 0){
			if(pointer==seq[i])
			{
				if(checkForField(file,pointer,0)==1)
				{
					if(i==(k-1))
					{
						getFlag = 1;
					}	
					else
						i++;
				}
				else if(checkForField(file,pointer,0)==-1)
					break;
				else{
					i=0;
					takeToNextLine(file);
					fseek(file,-1,SEEK_CUR);
					pointer=0;
				}
	
			}else if(pointer > seq[i]){
				fseek(file,-2,SEEK_CUR);
				if(ch==delimitor[pointer-1])
				{
					pointer=(pointer-1)%7;
					takeToStart(file,pointer);
					fseek(file,-1,SEEK_CUR);
				}
			}
		}
		else{
			if(pointer==printField)
                	{
				if(printField==seq[i])
					fseek(file,-1,SEEK_CUR);
                       		checkForField(file,pointer,1);
                                i=0;
                                takeToNextLine(file);
				fseek(file,-1,SEEK_CUR);
                                pointer=0;
				getFlag = 0;

                	}else if(pointer > printField){
                        	fseek(file,-2,SEEK_CUR);
                        	if(ch==delimitor[pointer-1])
                        	{
                        	        pointer=(pointer-1)%7;
                        	        takeToStart(file,pointer);
                        	        fseek(file,-1,SEEK_CUR);
                        	}
                	}
		}
	}
}

/* Main Function is mainly dealing with Composition of all Functions along with all input Validations */
int main(int argc, char *argv[])
{
	if(!validateNoOfArgs(argc)){
                printf("Error: Invalid Number of Arguments\n");
                return 0;
        }
	int seq[(argc-4)/2];
	
        if(!checkForCSV(argv[1]))
        {
                printf("Error: .csv File is expected as an Input\n");
                return 0;
        }
	
	if(!validateArgs(argc,argv,seq,(argc-4)/2))
	{
		printf("Error: Invalid Fields Passed\n");
		return 0;
	}

        FILE * file = fopen(argv[1],"r");
        if(!file){
                perror("Error: ");
                return 0;
        }

	extractFile(file,seq,(argc-4)/2);
        fclose(file);
}
