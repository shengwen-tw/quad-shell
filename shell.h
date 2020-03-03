#ifndef __SHELL_H__
#define __SHELL_H__

#define CMD_LEN_MAX 50
#define PROMPT_LEN_MAX 50

#define PARAM_LIST_SIZE_MAX 10
#define PARAM_LEN_MAX 10

#define SIZE_OF_SHELL_CMD_LIST(list) (sizeof(list) / sizeof(struct cmd_list_entry))
#define DEF_SHELL_CMD(cmd_name) {.handler = shell_cmd_ ## cmd_name, .name = #cmd_name},

enum {
	NULL_CH = 0,       /* null character */
	CTRL_A = 1,        /* ctrl + a*/
	CTRL_C = 3,        /* ctrl + c */
	CTRL_D = 4,        /* ctrl + d */
	CTRL_E = 5,        /* ctrl + e */
	CTRL_F = 6,        /* ctrl + f */
	CTRL_G = 7,        /* ctrl + g */
	CTRL_H = 8,        /* ctrl + h */
	TAB = 9,           /* tab */
	CTRL_J = 10,       /* ctrl + j */
	CTRL_K = 11,       /* ctrl + k */
	CTRL_L = 12,       /* ctrl + l */
	ENTER = 13,        /* enter */
	CTRL_N = 14,       /* ctrl + n */
	CTRL_O = 15,       /* ctrl + o */
	CTRL_P = 16,       /* ctrl + p */
	CTRL_Q = 17,       /* ctrl + r */
	CTRL_R = 18,       /* ctrl + r */
	CTRL_S = 19,       /* ctrl + s */
	CTRL_T = 20,       /* ctrl + t */
	CTRL_U = 21,       /* ctrl + u */
	CTRL_W = 23,       /* ctrl + w */
	CTRL_X = 24,       /* ctrl + x */
	CTRL_Y = 25,       /* ctrl + y */
	CTRL_Z = 26,       /* ctrl + z */
	VET_SEQ1 = 27,     /* first byte of the vt escape sequence */
	SPACE = 32,        /* space */
	UP_ARROW = 65,     /* up arrow, third byte of the vt escape sequence */
	DOWN_ARROW = 66,   /* down arrow, third byte of the vt escape sequence */
	RIGHT_ARROW = 67,  /* right arrow, third byte of the vt escape sequence */
	LEFT_ARROW = 68,   /* left arrow, third byte of the vt escape sequence */
	END = 70,          /* end, third byte of the vt escape sequence */
	HOME = 72,         /* home, third byte of the vt escape sequence */
	VT_SEQ2 = 91,      /* second byte of the vt escape sequence */
	BACKSPACE = 127,   /* backspace */
} KEYS;

struct shell_struct {
	int cursor_pos;
	int char_cnt;
	int prompt_len;
	char *buf;
	char *prompt_msg;
};

struct cmd_list_entry {
	void (*handler)(char param_list[PARAM_LIST_SIZE_MAX][PARAM_LEN_MAX]);
	char name[PROMPT_LEN_MAX];
};

void shell_init_struct(struct shell_struct *_shell, char *prompt_msg, char *ret_cmd);
void shell_cls(void);
void shell_cli(struct shell_struct *_shell);
void shell_cmd_exec(char *cmd, struct cmd_list_entry *cmd_list, int list_size);

#endif
