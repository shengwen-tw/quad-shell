#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN_MAX 50
#define PROMPT_LEN_MAX 50

int buf_curr = 0;

enum {
	NULL_CH = 0,       /* null character */
	CTRL_A = 1,        /* ctrl + a*/
	CTRL_C = 3,        /* ctrl + c */
	CTRL_D = 4,        /* ctrl + d */
	CTRL_E = 5,        /* ctrl + e */
	CTRL_F = 6,        /* ctrl + f */
	CTRL_H = 8,        /* ctrl + h */
	TAB = 9,           /* tab */
	CTRL_K = 11,       /* ctrl + k */
	CTRL_L = 12,       /* ctrl + l */
	ENTER = 13,        /* enter */
	CTRL_N = 14,       /* ctrl - n */
	CTRL_P = 16,       /* ctrl - p */
	CTRL_T = 20,       /* ctrl - t */
	CTRL_U = 21,       /* ctrl + u */
	CTRL_W = 23,       /* ctrl + w */
	ESCAPE_SEQ = 27,   /* start of escape sequence */
	SPACE = 32,        /* space */
	UP_ARROW = 65,     /* last character of up arrow */
	DOWN_ARROW = 66,   /* last character of down arrow */
	RIGHT_ARROW = 67,  /* last character of right arrow */
	LEFT_ARROW = 68,   /* last character of left arrow */
	ARROW_PREFIX = 91, /* any arrow = ESC_SEQ + '[' + 'A' ~ 'D' */
	BACKSPACE = 127,   /* backspace */
} KEYS;

char shell_getc(void)
{
	return getchar();
}

void shell_cls(void)
{
	printf("\x1b[H\x1b[2J");
}

void shell(char *username, char *ret_cmd)
{
	char prompt[PROMPT_LEN_MAX] = {0};
	printf("%s > ", username);

	int c;
	char seq[2];
	while(1) {
		c = shell_getc();

		switch(c) {
		case NULL_CH:
			break;
		case CTRL_A:
			break;
		case CTRL_C:
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
			ret_cmd[buf_curr] = 0;
			buf_curr = 0;
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
				} else if(seq[1] == LEFT_ARROW) {
				}
			}				
			break;
		case SPACE:
			break;
		case UP_ARROW:
			break;
		case DOWN_ARROW:
			break;
		case RIGHT_ARROW:
			break;
		case LEFT_ARROW:
			break;
		case ARROW_PREFIX:
			break;
		case BACKSPACE:
			break;
		default:
			if(buf_curr <= (CMD_LEN_MAX - 1)) {
				ret_cmd[buf_curr] = c;
				buf_curr++;
				printf("%c", c);
			}
			break;
		}
	}
}

int main(void)
{
	system ("/bin/stty raw -echo");

	char user_cmd[CMD_LEN_MAX];

	while(1) {
		shell("shell", user_cmd);

		printf("received command [%s] from shell.\n\r", user_cmd);
	}

	return 0;
}
