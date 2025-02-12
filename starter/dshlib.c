#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    //Initialize vars for token, rest of the command and command count
    char *token;
    char *rest = cmd_line;
    int cmd_count = 0;

    //Initialize command list count and clear command list
    clist->num = 0;
    memset(clist->commands, 0, sizeof(clist->commands));

    //Loop through command using strtok_r to  split command by pipe
    //Loop over every token which is a tab or space
    while ((token = strtok_r(rest, PIPE_STRING, &rest)))
    {
        while (isspace((unsigned char)*token)) token++;
        //Set pointer to last char of token, reverse loop to remove trailing spaces
        char *end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end)) end--;

        //Check if command count is greater than max commands
        if (cmd_count >= CMD_MAX)
        {
            return ERR_TOO_MANY_COMMANDS;
        }

        
        //Split command into executable and arguments
        char *exe = strtok(token, " ");
        char *args = strtok(NULL, "");

        //Check if command or args are too big
        if (strlen(exe) >= EXE_MAX || (args && strlen(args) >= ARG_MAX))
        {
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }

        //Copy executable and args, increment command count
        strcpy(clist->commands[cmd_count].exe, exe);
        if (args)
        {
            strcpy(clist->commands[cmd_count].args, args);
        }
        cmd_count++;
    }

    //Set command count
    clist->num = cmd_count;

    //Check if no commands
    if (cmd_count == 0)
    {
        return WARN_NO_CMDS;
    }

    return OK;
}