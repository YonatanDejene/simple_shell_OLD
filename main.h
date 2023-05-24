#ifndef _MAIN_H
#define _MAIN_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>


#define CMD_OR		1
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_CHAIN	3

#define BUF_FLUSH -1
#define _READBUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USEget_ln 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Singly linked ls.
 * @num: Num field.
 * @str: String.
 * @next: Point 2 the nxt node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Pseudo-arguements to pass into a function contained here.
 * @arg: String generated from getline.
 * @argv: Array of strings generated from arg.
 * @path: String path for the current cmnd.
 * @argc: Argument count.
 * @line_count: Error count.
 * @err_num: Error code for exit()s.
 * @alias: Alias node.
 * @env_changed: on environment changed.
 * @status: Return status of last exec'd command.
 * @cmd_buf: Addr of pointer to cmd_buff.
 * @cmd_buf_type: ----
 * @readfd: Fd from which to read the line input.
 * @histcount: History line count.
 * @linecount_flag: ---
 * @fname: Filename
 * @env: Local copy of environment.
 * @environ: custom modified copy of environ from LL env
 * @history: History node.
 */

typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char *arg;
	char **argv;
	char *path;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	list_t *env;
	list_t *history;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Builtin string and related function contained here.
 * @type: Builtin command flag.
 * @func: Func.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int is_cmd(info_t *, char *);
char *dp_char(char *, int, int);
char *fnd_pth(info_t *, char *, char *);

int msh(info_t *, char **);
int fnd_bltin(info_t *);
void _fndcmd(info_t *);
void _frkcmd(info_t *);

void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

int loopmsh(char **);

char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);
char *str_dup(const char *);

int str_len(char *);
char *strt_w(const char *, const char *);
int str_cmp(char *, char *);
char *str_cat(char *, char *);

char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_chr(char *, char);

char **str_tow(char *, char *);
char **str_tow2(char *, char);


int bfree(void **);

char *mem_set(char *, char, unsigned int);
void ffree(char **);
void *re_alloc(void *, unsigned int, unsigned int);

int intractv(info_t *);
int is_delim(char, char *);
int is_alpha(int);
int at(char *);

int myext(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

void prnt_err(info_t *, char *);
int errat(char *);
char *cnvrt_num(long int, int, int);
void rm_cmnt(char *);
int prntd(int, int);


ssize_t _gtinput(info_t *);
int get_ln(info_t *, char **, size_t *);
void sigintHandler(int);

int myhstr(info_t *);
int my_als(info_t *);

void _frinfo(info_t *, int);
void clr_inf(info_t *);
void _setinf(info_t *, char **);

int set_env(info_t *, char *, char *);
int unset_env(info_t *, char *);
char **get_envron(info_t *);

int wr_hstr(info_t *info);
int rd_hstr(info_t *info);
int bld_hstr_ls(info_t *info, char *buf, int linecount);
char *gt_hstr(info_t *info);
int renum_hstr(info_t *info);

char **ls_to_str(list_t *);
size_t prnt_ls(const list_t *);
list_t *nd_strt_wt(list_t *, char *, char);
size_t list_len(const list_t *);
ssize_t get_nd_indx(list_t *, list_t *);

int my_unstenv(info_t *);
int p_env_list(info_t *);
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_stenv(info_t *);


void chck_chn(info_t *, char *, size_t *, size_t, size_t);
int _ischain(info_t *, char *, size_t *);
int replc_str(char **, char *);
int rplc_als(info_t *);
int rplc_vrs(info_t *);

size_t prnt_ls_str(const list_t *);
int dlt_nd_at_indx(list_t **, unsigned int);
void fr_ls(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_nd_en(list_t **, const char *, int);

int sub(int number1, int number2);

