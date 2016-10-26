#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <openssl/aes.h>
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
  unsigned char	iv[AES_BLOCK_SIZE];
  unsigned char	out_buffer[BUFFER_SIZE];
  AES_KEY	key;
  t_entry	new_entry;

  //TODO: Verifier que l'on a bien au moins ASE_BLOCK_SIZE donnees dans le fichier
  lseek(secret_file, -AES_BLOCK_SIZE, SEEK_END);
  if (read(secret_file, iv, AES_BLOCK_SIZE) == -1)
    {
      fprintf(stderr, "Error reading from secret file\n");
      cmd_exit(NULL);
    }
  //TODO: Remplacer par une union
  memset(new_entry.name, 0, 29);
  memcpy(new_entry.name, args[1], strlen(args[1]));
  memcpy(new_entry.cb, args[2], 16);
  memcpy(new_entry.pin, args[3], 3);
  //TODO: Verifier le bon formatage des donnees d'entree
  AES_set_encrypt_key(master_key, KEY_SIZE, &key);
  AES_cbc_encrypt((unsigned char*)&new_entry, out_buffer, sizeof(t_entry), &key, iv, KEY_SIZE);
  write(secret_file, out_buffer, sizeof(t_entry));
}

void cmd_show(char **args)
{
  print_tab(args);
  printf("show not yet implemented\n");
}

void cmd_exit(char **args)
{
  memset(&master_key, 0, sizeof(AES_KEY));
  exit(0);
}

void cmd_show_all(char **args)
{
  unsigned char	buffer[BUFFER_SIZE];
  int		n;

  while ((n = read(secret_file, buffer, BUFFER_SIZE)) != 0)
    {
      
    }
}

void print_entry(t_entry *entry)
{
  printf("Name : %s; CB : %s; PIN : %s\n", entry->name, entry->cb, entry->pin);
}
