#ifndef __PROC_H__
#define __PROC_H__

#define BUFFER_SIZE	2048
#define KEY_SIZE	8 * 4
#define MASTER_KEY_SIZE	256
#define CMD_SIZE	255
#define CMD_COUNT	3
#define MAX_ARGS	3

typedef struct s_cmd
{
  char	com[CMD_SIZE];
  void	(*fn)(char*);
}	t_cmd;

extern t_cmd cmd_list[CMD_COUNT];

AES_KEY		get_master_key(unsigned char *key1, unsigned char *key2);

unsigned char	*find_cb(const char *name);

char		**parse_entry(char *buffer);

void		add_cb(const unsigned char *data);
void		bitwise_xor(const unsigned char *n1, const unsigned char *n2, const int size, unsigned char *out);
void		read_cmd();
void		parse_cmd(char *buffer);

void		cmd_add(char *arg);
void		cmd_show(char *arg);
void		cmd_exit(char *arg);

#endif
