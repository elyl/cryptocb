#include <openssl/aes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "proc.h"

t_cmd cmd_list[CMD_COUNT] = {
  {"add", cmd_add},
  {"show", cmd_show},
  {"exit", cmd_exit}};


void read_cmd()
{
  char	buffer[BUFFER_SIZE + 1];
  char	**args;
  int	n;
  
  while (42)
    {
      printf("$>");
      fflush(stdout);
      if ((n = read(0, &buffer[0], BUFFER_SIZE) == -1))
	{
	  fprintf(stderr, "Error while reading cmd\n");
	  exit(1);
	}
      printf("%d\n", n);
      buffer[n] = '\0';
      args = parse_entry(buffer);
      parse_cmd(args);
    }
}

void	parse_cmd(char **args)
{
  int	i;

  print_tab(args);
  i = 0;
  while (i < CMD_COUNT)
    {
      if (strcmp(cmd_list[i].com, args[0]) == 0)
	{
	  cmd_list[i].fn(args);
	  return;
	}
      ++i;
    }
  fprintf(stderr, "Command not found\n");
}

char **parse_entry(char *buffer)
{
  char	**args;
  char	*ptr;
  int	n;

  if ((args = malloc((char_count(buffer, ' ') + 2) * sizeof(char*))) == NULL)
    {
      fprintf(stderr, "Error while allocating memory\n");
      exit (1);
    }      
  args[0] = buffer;
  ptr = strtok(buffer, " ");
  n = 1;
  while (ptr != NULL)
    {
      args[n++] = ptr;
      ptr = strtok(NULL, " ");
    }
  args[n] = NULL;
  return (args);
}

int char_count(char *buffer, char c)
{
  int	n;

  n = 0;
  while (*buffer)
    {
      if (*buffer == c)
	++n;
      ++buffer;
    }
  return (n);
}

