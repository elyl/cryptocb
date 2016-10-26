#include <openssl/aes.h>
#include "proc.h"

int main(int agrc, char **argv)
{
  //read_cmd();
  AES_KEY	key, key2;
  unsigned char out_buffer[255];
  unsigned char key_raw[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  unsigned char in_buffer[] = "aaaaaaaaaaaaaaa";
  unsigned char	iv[16];
  unsigned char tmp[17];

  memset(out_buffer, 0, 255);
  memset(iv, 0, 16);
  AES_set_encrypt_key(key_raw, 256, &key);
  AES_cbc_encrypt(in_buffer, out_buffer, 16, &key, iv, AES_ENCRYPT);
  memset(iv, 0, 16);
  AES_set_decrypt_key(key_raw, 256, &key2);
  AES_cbc_encrypt(out_buffer, tmp, 16, &key2, iv, AES_DECRYPT);
  tmp[16] = '\0';
  printf("%s\n", tmp);
}
