#include <openssl/aes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "proc.h"

int main(int agrc, char **argv)
{
  unsigned char in[] = "toto";
  unsigned char out[2000];
  unsigned char out2[2000];
  unsigned char cipher[] = "aaaaaaaaaaaaaaaa";
  AES_KEY	key;

  AES_set_encrypt_key(cipher, 128, &key);
  AES_encrypt(in, out, &key);
  
  AES_set_decrypt_key(cipher, 128, &key);
  AES_decrypt(out, out2, &key);
  printf("%x %x %x %x\n", out2[0], out2[1],out2[2], out2[3]);
  return (0);
}

AES_KEY get_master_key(unsigned char *key1, unsigned char *key2)
{
  int		fd;
  char		buffer[BUFFER_SIZE + 1];
  AES_KEY	key;
  unsigned char	raw_key[KEY_SIZE + 1];

  if ((fd = open("master_key", O_RDONLY)) == -1)
    {
      fprintf(stderr, "Error while opening master key file\n");
      exit(EXIT_FAILURE);
    }
  if (read(fd, buffer, MASTER_KEY_SIZE) != MASTER_KEY_SIZE)
    {
      fprintf(stderr, "Error while reading master key file\n");
      exit(EXIT_FAILURE);
    }
  close(fd);
  bitwise_xor(key1, key2, KEY_SIZE, raw_key);
  AES_set_decrypt_key(raw_key, KEY_SIZE * 8, &key);
  AES_decrypt((unsigned char *)buffer, raw_key, &key);
  AES_set_decrypt_key(raw_key, KEY_SIZE * 8, &key);
  memset(raw_key, 0, KEY_SIZE + 1);
  memset(buffer, 0, BUFFER_SIZE + 1);
  return (key);
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
