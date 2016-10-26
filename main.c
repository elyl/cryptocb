#include <openssl/aes.h>
#include <stdio.h>
#include "proc.h"

int main(int argc, char **argv)
{
  new_key();
  if (argc < 3)
    {
      fprintf(stderr, "Missing arguments\n");
      return (1);
    }
  init((unsigned char*)argv[1], (unsigned char*)argv[2]);
  read_cmd();
  return (0);
}
