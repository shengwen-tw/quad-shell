#ifndef __SHELL_H__
#define __SHELL_H__

#define CMD_LEN_MAX 50
#define PROMPT_LEN_MAX 50

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

struct shell_struct {
	int cursor_pos;
	int char_cnt;
	int prompt_len;
	char *buf;
	char prompt_msg[PROMPT_LEN_MAX];
};

void shell_init_struct(struct shell_struct *_shell, char *ret_cmd);
void shell_cls(void);
void shell(char *username, struct shell_struct *_shell);

#endif
