#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <openssl/aes.h>
#include "proc.h"

void cmd_add(char **args)
{
  unsigned char	iv[AES_BLOCK_SIZE];
  unsigned char	out_buffer[ENTRY_SIZE];
  AES_KEY	key;
  union u_entry	new_entry;

  //TODO: Verifier que l'on a bien au moins ASE_BLOCK_SIZE donnees dans le fichier
  lseek(secret_file, -AES_BLOCK_SIZE, SEEK_END);
  if (read(secret_file, iv, AES_BLOCK_SIZE) == -1)
    {
      fprintf(stderr, "Error reading from secret file\n");
      cmd_exit(NULL);
    }
  memset(new_entry.buffer, 0, ENTRY_SIZE);
  memcpy(new_entry.buffer, args[1], MIN(strlen(args[1]), 29));
  memcpy(new_entry.entry.cb, args[2], 16);
  memcpy(new_entry.entry.pin, args[3], 3);
  //TODO: Verifier le bon formatage des donnees d'entree
  AES_set_encrypt_key(master_key, MASTER_KEY_SIZE, &key);
  AES_cbc_encrypt(new_entry.buffer, out_buffer, ENTRY_SIZE, &key, iv, AES_ENCRYPT);
  write(secret_file, out_buffer, ENTRY_SIZE);
}

void cmd_show(char **args)
{
  unsigned char	buffer[BUFFER_SIZE];
  unsigned char	iv[AES_BLOCK_SIZE];
  int		n;
  int		i;
  AES_KEY	key;
  union u_entry	entry;
  
  memset(iv, 0, AES_BLOCK_SIZE);
  AES_set_decrypt_key(master_key, MASTER_KEY_SIZE, &key);
  lseek(secret_file, 0, SEEK_SET);
  while ((n = read(secret_file, buffer, BUFFER_SIZE)) != 0)
    {
      i = 0;
      while (i < n)
	{
	  memset(entry.entry.name, 0, 29);
	  AES_cbc_encrypt(&buffer[i], entry.buffer, ENTRY_SIZE, &key, iv, AES_DECRYPT);
	  if (strcmp(entry.entry.name, args[1]) == 0)
	    {
	      print_entry(&entry.entry);
	      return;
	    }
	  i += ENTRY_SIZE;
	}
    }
  printf("%s not found\n", args[1]);
}

void cmd_exit(char **args)
{
  args = args;
  memset(&master_key, 0, sizeof(AES_KEY));
  exit(0);
}

void cmd_show_all(char **args)
{
  unsigned char	buffer[BUFFER_SIZE];
  unsigned char iv[AES_BLOCK_SIZE];
  int		n;
  int		i;
  union u_entry	entry;
  AES_KEY	key;

  args = args;
  memset(iv, 0, AES_BLOCK_SIZE);
  AES_set_decrypt_key(master_key, MASTER_KEY_SIZE, &key);
  lseek(secret_file, 0, SEEK_SET);
  while ((n = read(secret_file, buffer, BUFFER_SIZE)) != 0)
    {
      i = 0;
      while (i < n)
	{
	  AES_cbc_encrypt(&buffer[i], entry.buffer, ENTRY_SIZE, &key, iv, AES_DECRYPT);
	  print_entry(&entry.entry);
	  i += ENTRY_SIZE;
	}
    }
}

void print_entry(t_entry *entry)
{
  char	name[30];
  char	cb[17];
  char	pin[4];

  memcpy(name, entry->name, 29);
  name[29] = '\0';
  memcpy(cb, entry->cb, 16);
  cb[16] = '0';
  memcpy(pin, entry->pin, 3);
  pin[3] = '\0';
  printf("Name : %s; CB : %s; PIN : %s\n", name, cb, pin);
}
