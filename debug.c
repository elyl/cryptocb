#include <openssl/aes.h>
#include <stdio.h>
#include "proc.h"

void print_key(unsigned char *key)
{
  printf("%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n", key[0], key[1], key[2], key[3], key[4], key[5], key[6], key[7], key[8], key[9], key[10], key[11], key[12], key[13], key[14], key[15]);
}

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
