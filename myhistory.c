#include "myhistory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include  <sys/types.h>

char history[100][80];
int history_count = -1;

//This function performs as a parse, instead of going
//through the line given manually, I use strtok()
//to separate into the char** commands. After this,
//I will put into execvp to execute the command
void tokenize(char newline[], char** commands)
{
    int token_counter = 0;
    char* token; 

    token = strtok(newline, " ");
    while (token) 
	 {
    
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
    history_count++;
    char *historyAccepter = text; //history acceptor accepts the command as its next history
	int cpy2 = 0; //index to copy array
	int dohistory = 0; //boolean check for history
	
	//code to quit, this is entered through the line
    //so I am counting it as a command
    //in which it should be "executed" by the shell
    //portion of the program	
	
    if(text[0] == 'q' && text[1] == 'u' &&
	   text[2] == 'i' && text[3] == 't')
	    exit(-1);
		
        //error check, when we hit enter without a command,
		//it wont print anything to history, just like the 
		//history command with agate
		if (text[0] == '\0')
		{
		history_count--;
	}
	
    while (historyAccepter[cpy2] != '\0')
     {
      history[history_count][cpy2] = historyAccepter[cpy2];
	  cpy2++;
     } historyAccepter[cpy2] = '\0';
         
	   

    //fork processing
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
             wait(&status);			 
         }
          if (childpid == 0)
           { 
	   
	      if(text[0] == 'h' && text[1] == 'i' &&
	   text[2] == 's' && text[3] == 't' && 
	   text[4] == 'o' && text[5] == 'r' && text[6] == 'y')
	           {
	          int i = 0;
	          int j = 0;
	          fprintf(stdout, "History: \n~~~~~~~~~~~\n\n");
	          for ( i = 0; i < history_count; i++)
	           {
	             fprintf(stdout, "%d     %s\n", i+1, history[i]);
	           }
	        }
	      else
	      {
	       execvp(commands[0], commands);
		  fprintf(stdout, "%s is not a command, try again\n", commands[0]);
             exit(-1);
	     }
	  //this is the child process 
	 
	  
    }
}




int main(int argc, char** argv){
 size_t buffersize = 100;
 size_t bytes_read;
 int history_count = -1; //-1 because we start by incrementing 
 
 char *text = (char *)malloc(buffersize+1);
 char newline[256];
 char** commands = malloc(100);
 
 
 
 for(;;) 
  {
   //prompt
   printf("myhistory> ");
   
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
