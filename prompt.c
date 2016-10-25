#include <openssl/aes.h>
#include <stdio.h>
#include "proc.h"

void read_cmd()
{
  char	buffer[BUFFER_SIZE + 1];
  char	**args;
  int	n;
  
  while (42)
    {
      printf("$>");
      fflush(stdout);
      if ((n = read(0, buffer, BUFFER_SIZE) == -1))
	{
	  fprintf(stderr, "Error while reading cmd\n");
	  exit(1);
	}
      buffer[n] = '\0';
      args = parse_entry(buffer);
      parse_cmd(buffer);
    }
}

char **parse_entry(char *buffer)
{
  char	*args[MAX_ARGS + 1];
  char	*ptr;

  
  args[0] = buffer;
  while (ptr != NULL)
    {
      
    }
}

void	parse_cmd(char *args)
{
  char	*ptr;

  ptr = strtok(args, ' ');
}

/*t_cmd cmd_list[CMD_COUNT] = {
  {"add", cmd_add},
  {"show", cmd_show},
  {"exit", cmd_exit}};*/
    


