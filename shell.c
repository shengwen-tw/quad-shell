#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static char shell_getc(void)
{
	return getchar();
}

static void shell_puts(char *s)
{
	int len = strlen(s);

	int i;
	for(i = 0; i < len; i++) {
		putchar(s[i]);
	}
}

void shell_cls(void)
{
	shell_puts("\x1b[H\x1b[2J");
}

void shell_init_struct(struct shell_struct *shell, char *prompt_msg, char *ret_cmd)
{
	shell->prompt_msg = prompt_msg;
	shell->prompt_len = strlen(shell->prompt_msg);

	shell->cursor_pos = 0;
	shell->char_cnt = 0;
	shell->buf = ret_cmd;
	memset(shell->buf, '\0', CMD_LEN_MAX);
}

static void shell_reset_struct(struct shell_struct *shell)
{
	shell->cursor_pos = 0;
	shell->char_cnt = 0;
}

static void shell_remove_char(struct shell_struct *shell)
{
	int i;
	for(i = (shell->cursor_pos - 1); i < (shell->char_cnt); i++) {
		shell->buf[i] = shell->buf[i + 1];
	}

	shell->buf[shell->char_cnt] = '\0';
	shell->char_cnt--;
	shell->cursor_pos--;

	if(shell->cursor_pos > shell->char_cnt) {
		shell->cursor_pos = shell->char_cnt;
	}
}

static void shell_insert_char(struct shell_struct *shell, char c)
{
	int i;
	for(i = shell->char_cnt; i > (shell->cursor_pos - 1); i--) {
		shell->buf[i] = shell->buf[i - 1];
	}
	shell->char_cnt++;
	shell->buf[shell->char_cnt] = '\0';

	shell->buf[shell->cursor_pos] = c;
	shell->cursor_pos++;
}

static void shell_refresh_line(struct shell_struct *shell)
{
	char s[PROMPT_LEN_MAX * 2];
	sprintf(s, "\33[2K\r"   /* clear current line */
                "%s%s\r"     /* show prompt */
                "\033[%dC",  /* move cursor */
                shell->prompt_msg, shell->buf, shell->prompt_len + shell->cursor_pos);
	shell_puts(s);
}

void shell_cli(struct shell_struct *shell)
{
	shell_puts(shell->prompt_msg);

	char s[PROMPT_LEN_MAX];

	int c;
	char seq[2];
	while(1) {
		c = shell_getc();

		switch(c) {
		case NULL_CH:
			break;
		case CTRL_A:
			sprintf(s, "\r\033[%dC", shell->prompt_len);
			shell_puts(s);
			break;
		case CTRL_C:
			shell_puts("^C\n\r");
			system("/bin/stty cooked echo");
			exit(0);
			return;
			break;
		case CTRL_D:
			break;
		case CTRL_E:
			break;
		case CTRL_F:
			break;
		case CTRL_H:
			break;
		case TAB:
			break;
		case ENTER:
			shell_puts("\n\r");
			shell_reset_struct(shell);
			return;
			break;
		case CTRL_K:
			break;
		case CTRL_L:
			break;
		case CTRL_N:
			break;
		case CTRL_P:
			break;
		case CTRL_T:
			break;
		case CTRL_U:
			break;
		case CTRL_W:
			break;
		case ESCAPE_SEQ:
			seq[0] = shell_getc();
			seq[1] = shell_getc();
			if(seq[0] == ARROW_PREFIX) {
				if(seq[1] == UP_ARROW) {
				} else if(seq[1] == DOWN_ARROW) {
				} else if(seq[1] == RIGHT_ARROW) {
					if(shell->cursor_pos < shell->char_cnt) {
						shell->cursor_pos++;
						shell_puts("\033[1C");
					}
				} else if(seq[1] == LEFT_ARROW) {
					if(shell->cursor_pos > 0) {
						shell_puts("\033[1D");
						shell->cursor_pos--;
					}
				}
			}				
			break;
		case BACKSPACE:
			if(shell->char_cnt != 0 && shell->cursor_pos != 0) {
				shell_remove_char(shell);
				shell_refresh_line(shell);
			}
			break;
		case SPACE:
		default:
			if(shell->char_cnt != (CMD_LEN_MAX - 1)) {
				shell_insert_char(shell, c);
				shell_refresh_line(shell);
			}
			break;
		}
	}
}
