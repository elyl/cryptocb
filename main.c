#include <openssl/aes.h>
#include "proc.h"

int main(int agrc, char **argv)
{
  read_cmd();
  /*  AES_KEY	key;
  unsigned char out_buffer[255];
  unsigned char key_raw[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  unsigned char in_buffer[] = "aaaaaaaaaaaaaaaa";
  unsigned char	iv[16];

  memset(out_buffer, 0, 255);
  memset(iv, 0, 16);
  AES_set_encrypt_key(key_raw, 256, &key);
  AES_cbc_encrypt(in_buffer, out_buffer, 16, &key, iv, 256);
  printf("%x\n", out_buffer[15]);*/
}
