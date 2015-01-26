#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include  <sys/types.h>



//This function performs as a parse, instead of going
//through the line given manually, I use strtok()
//to separate into the char** commands. After this,
//I will put into execvp to execute the command
void tokenize(char newline[], char** commands)
{

    int token_counter = 0;
    char* token; 

    token = strtok(newline, " ");
    while (token) {
    
	commands[token_counter] = malloc(100);
    commands[token_counter] = token;

	token = strtok(NULL, " ");
	token_counter++;

  
     commands[token_counter] = '\0';
}

}

//the shell is split up from the getting of the input
//this void function will perform the neccessary commands given
void shell( char** commands, char* text)
{

	//code to quit, this is entered through the line
    //so I am counting it as a command
    //in which it should be "executed" by the shell
    //portion of the program	
	
   if(text[0] == 'q' && text[1] == 'u' &&
	   text[2] == 'i' && text[3] == 't')
	    exit(-1);
		
		
		
 //fork processing, shell does fork processing
       int childpid = fork();
       int status = 0;

         if (childpid < 0)
          {
		   //fork failed, handle it 
           perror("fork Failed");
		   exit(-1);
          }
          if (childpid > 0)
           {
		   
		   
             //this is the parent process
             //while (wait(&status) != childpid);
               wait(&status);			 
           }
            if (childpid == 0)
             { 

			 
			 execvp(commands[0], commands);
			 fprintf(stdout, "%s is not a command, try again\n", commands[0]);
              //this is the child process 
			 
			  
			  exit(-1);
           }
}


int main(int argc, char** argv){
 size_t buffersize = 100;
 size_t bytes_read;
 
 char *text = (char *)malloc(buffersize+1);
 char newline[256];
 char** commands = malloc(100);
 
 
 for(;;) 
  {
   //prompt
   printf("myshell> ");
   
   //read line
   bytes_read = getline(&text, &buffersize, stdin);
   text[bytes_read-1] = '\0';
   

  //make char[] instead of char* 
  //so it can be processed by the tokenizer function
  int cpy = 0;
  while (text[cpy] != '\0')
  {
    newline[cpy] = text[cpy];
	cpy++;
  } newline[cpy] = '\0';
  

    //use the tokenizer for parsing with spaces
	//get into the format: arg[0] = "cat" arg[1] = "mouse"
	//with a *char[]
	
	tokenize(newline, commands);
     
	 //do command given by tokenize
	 shell(commands, text);
      

	}
	
	
	
	
    return 0;
}