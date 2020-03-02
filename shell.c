#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static char shell_getc(void)
{
	return getchar();
}

void shell_cls(void)
{
	printf("\x1b[H\x1b[2J");
}

void shell_init_struct(struct shell_struct *_shell, char *ret_cmd)
{
	_shell->cursor_pos = 0;
	_shell->char_cnt = 0;
	_shell->buf = ret_cmd;
	memset(_shell->buf, '\0', CMD_LEN_MAX);
}

static void shell_reset_struct(struct shell_struct *_shell)
{
	_shell->cursor_pos = 0;
	_shell->char_cnt = 0;
}

static void shell_remove_char(struct shell_struct *_shell)
{
	int i;
	for(i = (_shell->cursor_pos - 1); i < (_shell->char_cnt); i++) {
		_shell->buf[i] = _shell->buf[i + 1];
	}

	_shell->buf[_shell->char_cnt] = '\0';
	_shell->char_cnt--;
	_shell->cursor_pos--;

	if(_shell->cursor_pos > _shell->char_cnt) {
		_shell->cursor_pos = _shell->char_cnt;
	}
}

static void shell_insert_char(struct shell_struct *_shell, char c)
{
	int i;
	for(i = _shell->char_cnt; i > (_shell->cursor_pos - 1); i--) {
		_shell->buf[i] = _shell->buf[i - 1];
	}
	_shell->char_cnt++;
	_shell->buf[_shell->char_cnt] = '\0';

	_shell->buf[_shell->cursor_pos] = c;
	_shell->cursor_pos++;
}

static void shell_refresh_line(struct shell_struct *_shell)
{
	printf("\33[2K\r"   /* clear current line */
               "%s%s\r"     /* show prompt */
               "\033[%dC",  /* move cursor */
               _shell->prompt_msg, _shell->buf, _shell->prompt_len + _shell->cursor_pos);
}

void shell_cli(char *username, struct shell_struct *_shell)
{
	sprintf(_shell->prompt_msg, "%s > ", username);
	_shell->prompt_len = strlen(_shell->prompt_msg);
	printf("%s", _shell->prompt_msg);

	int c;
	char seq[2];
	while(1) {
		c = shell_getc();

		switch(c) {
		case NULL_CH:
			break;
		case CTRL_A:
			printf("\r\033[%dC", _shell->prompt_len);
			break;
		case CTRL_C:
			printf("^C\n\r");
			system("/bin/stty cooked echo");
			exit(0);
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
			printf("\n\r");
			shell_reset_struct(_shell);
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
					if(_shell->cursor_pos < _shell->char_cnt) {
						_shell->cursor_pos++;
						printf("\033[1C");
					}
				} else if(seq[1] == LEFT_ARROW) {
					if(_shell->cursor_pos > 0) {
						printf("\033[1D");
						_shell->cursor_pos--;
					}
				}
			}				
			break;
		case BACKSPACE:
			if(_shell->char_cnt != 0 && _shell->cursor_pos != 0) {
				shell_remove_char(_shell);
				shell_refresh_line(_shell);
			}
			break;
		case SPACE:
		default:
			if(_shell->char_cnt != (CMD_LEN_MAX - 1)) {
				shell_insert_char(_shell, c);
				shell_refresh_line(_shell);
			}
			break;
		}
	}
}
