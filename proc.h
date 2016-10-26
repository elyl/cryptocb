#ifndef __PROC_H__
#define __PROC_H__

#define KEY_SIZE	8 * 4
#define MASTER_KEY_SIZE	256
#define CMD_SIZE	255
#define CMD_COUNT	4
#define AES_BLOCK_SIZE	16
#define ENTRY_SIZE 	48
#define BUFFER_SIZE	ENTRY_SIZE * 50

typedef struct s_cmd
{
  char	com[CMD_SIZE];
  void	(*fn)(char**);
}	t_cmd;

typedef struct s_entry
{
  char	name[29];
  char	cb[16];
  char	pin[3];
}	t_entry;
union u_entry
{
  unsigned char	buffer[ENTRY_SIZE];
  t_entry	entry;
};

extern t_cmd		cmd_list[CMD_COUNT];
extern unsigned char	master_key[KEY_SIZE];
extern int		secret_file;

unsigned char	*get_master_key(unsigned char *key1, unsigned char *key2);
unsigned char	*find_cb(const char *name);

char		**parse_entry(char *buffer);

int		char_count(char *buffer, char c);

void		add_cb(const unsigned char *data);
void		bitwise_xor(const unsigned char *n1, const unsigned char *n2, const int size, unsigned char *out);
void		read_cmd();
void		parse_cmd(char **args);

void		init(unsigned char *key1, unsigned char *key2);
void		open_secret_file();

void		cmd_add(char **args);
void		cmd_show(char **args);
void		cmd_exit(char **args);
void		cmd_show_all(char **args);
void		print_entry(t_entry *entry);

void		print_key(unsigned char *key);
void		print_tab(char **tab);
void		base_file();

void		new_key();
void		generate_key_pair(unsigned char *key1, unsigned char *key2);
void		generate_master_key(unsigned char *key1, unsigned char *key2);

#endif
