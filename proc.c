#include <openssl/aes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "proc.h"

unsigned char	master_key[KEY_SIZE];
int		secret_file;

void init(unsigned char *key1, unsigned char *key2)
{
  get_master_key(key1, key2);
  open_secret_file();
}

void open_secret_file()
{
  if ((secret_file = open("secret_file", O_RDWR)) == -1)
    {
      fprintf(stderr, "Error opening the secret file\n");
      cmd_exit(NULL);
    }
}

unsigned char	*get_master_key(unsigned char *key1, unsigned char *key2)
{
  int		fd;
  char		buffer[KEY_SIZE];
  AES_KEY	key;
  unsigned char	iv[AES_BLOCK_SIZE];
  unsigned char	raw_key[KEY_SIZE];

  if ((fd = open("master_key", O_RDONLY)) == -1)
    {
      fprintf(stderr, "Error while opening master key file\n");
      exit(EXIT_FAILURE);
    }
  if (read(fd, buffer, KEY_SIZE) != KEY_SIZE)
    {
      fprintf(stderr, "Error while reading master key file\n");
      exit(EXIT_FAILURE);
    }
  close(fd);
  bitwise_xor(key1, key2, KEY_SIZE, raw_key);
  memset(iv, 0, AES_BLOCK_SIZE);
  AES_set_decrypt_key(raw_key, MASTER_KEY_SIZE, &key);
  AES_cbc_encrypt((unsigned char *)buffer, master_key, KEY_SIZE, &key, iv, AES_DECRYPT);
  memset(raw_key, 0, KEY_SIZE);
  print_key(master_key); //DEBUG
  return (master_key);
}

void	bitwise_xor(const unsigned char *n1, const unsigned char *n2, const int size, unsigned char *out)
{
  int	i;

  i = 0;
  while (i < size)
    {
      out[i] = n1[i] ^ n2[i];
      ++i;
    }
}
