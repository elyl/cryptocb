#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "proc.h"

void new_key()
{
  unsigned char	key1[KEY_SIZE];
  unsigned char	key2[KEY_SIZE];
  
  generate_key_pair(key1, key2);
  generate_master_key(key1, key2);
}

//TODO: Generer des vraies clefs
//TODO: Ecrire les clefs dans des fichiers
void generate_key_pair(unsigned char *key1, unsigned char *key2)
{
  memcpy(key1, "0123456789abcdef0123456789abcdef", KEY_SIZE);
  memcpy(key2, "abcdef0123456789abcdef0123456789", KEY_SIZE);
}

//TODO: Rechiffrer le fichier de cb avec la nouvelle clef (en option)
void generate_master_key(unsigned char *key1, unsigned char *key2)
{
  unsigned char	buffer[KEY_SIZE];
  unsigned char raw_key[KEY_SIZE];
  unsigned char	iv[AES_BLOCK_SIZE];
  AES_KEY	key;
  int		fd;

  memset(iv, 0, AES_BLOCK_SIZE);
  bitwise_xor(key1, key2, KEY_SIZE, raw_key);
  AES_set_encrypt_key(raw_key, MASTER_KEY_SIZE, &key);
  AES_cbc_encrypt(raw_key, buffer, KEY_SIZE, &key, iv, AES_ENCRYPT);
  if ((fd = open("master_key", O_WRONLY | O_CREAT | O_TRUNC)) == -1)
    {
      fprintf(stderr, "Error while opening file for master key saving");
      exit (1);
    }
  write(fd, buffer, KEY_SIZE);
  close(fd);
  print_key(raw_key);
}
