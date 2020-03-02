#include <string.h>
#include "shell.h"

static void split_shell_cmd_token(char *cmd, char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX])
{
	int param_list_index = 0;
	int i;
	for(i = 0; i < strlen(cmd); i++) {
		if(cmd[i] == ' ') {
			i++;
			param_list_index++;
			while(i < strlen(cmd)) {
				if(cmd[i] == ' ') i++;
				else break;
			}
		} else {
			param_list[param_list_index][i] = cmd[i];
		}
	}
}

void shell_cmd_exec(char *cmd, struct cmd_list_entry *cmd_list, int list_size)
{
	char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX] = {0};
	split_shell_cmd_token(cmd, param_list);

	int i;
	for(i = 0; i < list_size; i++) {
		if(strcmp(param_list[0], cmd_list[i].name) == 0) {
			cmd_list[i].handler(param_list);
			return;
		}
	}
}
