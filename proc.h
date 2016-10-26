#ifndef __PROC_H__
#define __PROC_H__

#include <openssl/aes.h>

#define BUFFER_SIZE	2048
#define KEY_SIZE	8 * 4
#define MASTER_KEY_SIZE	256
#define CMD_SIZE	255
#define CMD_COUNT	3
#define AES_BLOCK_SIZE	16

typedef struct s_cmd
{
  char	com[CMD_SIZE];
  void	(*fn)(char**);
}	t_cmd;

extern t_cmd	cmd_list[CMD_COUNT];
extern AES_KEY	master_key;

AES_KEY		get_master_key(unsigned char *key1, unsigned char *key2);

unsigned char	*find_cb(const char *name);

char		**parse_entry(char *buffer);

int		char_count(char *buffer, char c);

void		add_cb(const unsigned char *data);
void		bitwise_xor(const unsigned char *n1, const unsigned char *n2, const int size, unsigned char *out);
void		read_cmd();
void		parse_cmd(char **args);

void		cmd_add(char **args);
void		cmd_show(char **args);
void		cmd_exit(char **args);
void		cmd_show_all(char **args);
void		print_tab(char **tab);

#endif
