#include <openssl/aes.h>
#include <stdio.h>
#include "proc.h"

void print_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    {
      printf("%s\n", tab[i]);
      ++i;
    }
}

void cmd_add(char **args)
{
  print_tab(args);
  printf("add not yet implemented\n");
}

void cmd_show(char **args)
{
  print_tab(args);
  printf("show not yet implemented\n");
}

void cmd_exit(char **args)
{
  print_tab(args);
  printf("exit not yet implemented\n");
}

void cmd_show_all(char **args)
{
  print_tab(args);
  printf("show_all not yet implemented\n");
}
