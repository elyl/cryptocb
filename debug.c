#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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

void base_file()
{
  int		fd;
  char		buffer[ENTRY_SIZE];
  char		buffer2[ENTRY_SIZE];
  unsigned char	iv[KEY_SIZE];
  AES_KEY	key;

  fd = open("secret_file", O_RDWR | O_CREAT | O_TRUNC);
  AES_set_encrypt_key(master_key, MASTER_KEY_SIZE, &key);
  memset(iv, 0, KEY_SIZE);
  memcpy(buffer, "Robert Dupont                0102030405060708000", ENTRY_SIZE);
  AES_cbc_encrypt((unsigned char*)buffer, (unsigned char*)buffer2, ENTRY_SIZE, &key, iv, AES_ENCRYPT);
  write(fd, buffer2, ENTRY_SIZE);
  AES_cbc_encrypt((unsigned char*)buffer, (unsigned char*)buffer2, ENTRY_SIZE, &key, iv, AES_ENCRYPT);
  write(fd, buffer2, ENTRY_SIZE);
  AES_cbc_encrypt((unsigned char*)buffer, (unsigned char*)buffer2, ENTRY_SIZE, &key, iv, AES_ENCRYPT);
  write(fd, buffer2, ENTRY_SIZE);
  close(fd);
}
