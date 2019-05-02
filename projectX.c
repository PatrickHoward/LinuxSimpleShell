// projectX - Linux Shell
// Created by Patrick M. Howard - pmh41@zips.uakron.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS 64
#define MAXARGLEN 16
#define LINELEN 80
#define STD_PARSER_DELIMITER ' '


typedef struct Command
{
  char* cmdName;
  char* binName;
  char* argValues[MAXARGS];

  int argCount;

} Command;

void command_newCommand(Command* command)
{
    command->cmdName = (char*) malloc(MAXARGLEN);
    command->binName = (char*) malloc(MAXARGLEN);
}

void command_clear(Command* command)
{
    command->cmdName = NULL;
    command->binName = NULL;

    command->argCount = 0;
}

void command_parseCommand(Command* command, char* userInput, char delim)
{
    char* tokens[MAXARGS];
    int numberOfTokens = 0;

    tokens[numberOfTokens++] = userInput;

    while(*userInput != '\0')
    {
        if(*userInput == delim)
        {
            *userInput = '\0';
            ++userInput;

            tokens[numberOfTokens++] = userInput;
        }
        else
        {
            ++userInput;
        }
    }

    command->cmdName = tokens[0];
    command->argCount = numberOfTokens - 1;
    for(int i = 1; i < numberOfTokens; ++i)
    {
        command->argValues[i - 1] = tokens[i];
    }

    command->argValues[numberOfTokens - 1] = (void*)0;

}

void command_findbin(Command* command)
{
    if(strcmp(command->cmdName, "C"))
    {
        strcpy(command->binName, "cp");
    }
    else if(strcmp(command->cmdName, "D"))
    {
        strcpy(command->binName, "rm");
    }
    else if(strcmp(command->cmdName, "E"))
    {
        strcpy(command->binName, "echo");
    }
    else if(strcmp(command->cmdName, "H"))
    {
        strcpy(command->binName, "help");
    }
    else if(strcmp(command->cmdName, "L"))
    {
        strcpy(command->binName, "ls");
    }
    else if(strcmp(command->cmdName, "M"))
    {
        strcpy(command->binName, "nano");
    }
    else if(strcmp(command->cmdName, "P"))
    {
        strcpy(command->binName, "cat");
    }
    else if(strcmp(command->cmdName, "Q"))
    {
        strcpy(command->binName, "exit");
    }
    else if(strcmp(command->cmdName, "S"))
    {
        strcpy(command->binName, "firefox");
    }
    else if(strcmp(command->cmdName, "W"))
    {
        strcpy(command->binName, "clear");
    }
    else if(strcmp(command->cmdName, "X"))
    {
        strcpy(command->binName, command->argValues[0]);
    }

    // if(command->argCount == 0)
    // {
    //     command->argValues[0] = '\0';
    // }
}

void command_runbin(Command* command)
{
    
    execvp(command->binName, command->argValues);

}

void printPrompt(char* userName, char* hostName)
{
    printf("linux - %s@%s - > ", userName, hostName);
}

void getInput(char* userInput)
{
    fgets(userInput, LINELEN, stdin);
}

int main()
{
    char sysUser[1024];
    char sysHost[1024];
    getlogin_r(sysUser, 1024);
    gethostname(sysHost, 1024);

    char buffer[LINELEN];
    Command activeCommand;

    while(1)
    {
        printPrompt(sysUser, sysHost);
        getInput(buffer);

        command_clear(&activeCommand);
        command_newCommand(&activeCommand);
        command_parseCommand(&activeCommand, buffer, STD_PARSER_DELIMITER);
        command_findbin(&activeCommand);
        printf("%s\n", activeCommand.binName);
        
        command_runbin(&activeCommand);
    }

}
