#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void)
{
	system ("/bin/stty raw -echo");

	char user_cmd[CMD_LEN_MAX];
	struct shell_struct _shell_struct;
	shell_init_struct(&_shell_struct, user_cmd);

	shell_cls();
	while(1) {
		shell("shell", &_shell_struct);
		printf("received command [%s] from shell.\n\r", user_cmd);
	}

	return 0;
}
