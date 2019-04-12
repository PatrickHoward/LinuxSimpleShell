// projectX - Linux Shell
// Created by Patrick M. Howard - pmh41@zips.uakron.edu

#include <stdio.h>
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

void command_parseCommand(Command* command, char* userInput, char delim)
{
    //I would put them in directly into a command type object, but I'm lazy...
    //TODO: Remove token array and place information directly into command object.
    char* tokens[MAXARGS];
    int numberOfTokens = 0;

    tokens[numberOfTokens] = userInput;

    while(*userInput != '\0')
    {
        if(*userInput == delim)
        {
            *userInput = '\0';
            ++userInput;

            tokens[++numberOfTokens] = userInput;
        }
        ++userInput;
    }

    strcpy(command->cmdName, tokens[0]);
    command->argCount = numberOfTokens - 1;
    for(int i = 0; i < numberOfTokens - 1; ++i)
    {
        strcpy(command->argValues[i], tokens[i]);
    }

        command->argValues[numberOfTokens] = (void*)0;

}

void command_clear(Command* command)
{
    command->cmdName = NULL;
    command->binName = NULL;

    command->argCount = 0;
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
    char* usr = getlogin();
    char sysHost[1024];
    gethostname(sysHost, 1024);

    char buffer[LINELEN];
    Command activeCommand;

    while(1)
    {
        printPrompt(usr, sysHost);
        getInput(buffer);

        command_parseCommand(&activeCommand, buffer, ' ');
        printf("%s %s\n", activeCommand.cmdName, activeCommand.argValues[0]);
    }

}
