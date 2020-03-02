#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

void shell_cmd_help(char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX]);
void shell_cmd_echo(char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX]);

#define DEF_SHELL_CMD(cmd_name) {.handler = shell_cmd_ ## cmd_name, .name = #cmd_name},

struct cmd_list_entry shell_cmd_list[] = {
	DEF_SHELL_CMD(help)
	DEF_SHELL_CMD(echo)
};

void shell_cmd_help(char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX])
{
	printf("help\n\r");
}

void shell_cmd_echo(char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX])
{
	printf("echo\n\r");
}

int main(void)
{
	system ("/bin/stty raw -echo");

	char user_cmd[CMD_LEN_MAX];
	struct shell_struct _shell_struct;
	shell_init_struct(&_shell_struct, user_cmd);

	int shell_cmd_cnt = sizeof(shell_cmd_list) / sizeof(struct cmd_list_entry);

	shell_cls();
	while(1) {
		shell_cli("shell", &_shell_struct);
		shell_cmd_exec(user_cmd, shell_cmd_list, shell_cmd_cnt);
	
	}

	return 0;
}
