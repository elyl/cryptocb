#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
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
  int		fd;
  unsigned char	iv[AES_BLOCK_SIZE];
  unsigned char	out_buffer[BUFFER_SIZE];

  //TODO: Passer le fichier en global
  if ((fd = open("secret_file", O_RDWR)) == -1)
    {
      fprintf(stderr, "Error opening secret file\n");
      cmd_exit(NULL);
    }
  //TODO: Verifier que l'on a bien au moins ASE_BLOCK_SIZE donnees dans le fichier
  lseek(fd, -AES_BLOCK_SIZE, SEEK_END);
  if (read(fd, iv, AES_BLOCK_SIZE) == -1)
    {
      fprintf(stderr, "Error reading from secret file\n");
      cmd_exit(NULL);
    }
  //TODO: Concatener l'ensemble des donnees pour faire une seule chaine
  //TODO: Formater les donnees pour avoir des enregistrements de forme standard
  //TODO: Verifier le bon formatage des donnes d'entree
  AES_cbc_encrypt(args[1], out_buffer, strlen(args[1]), &master_key, iv, 256);
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
  print_tab(args);
  printf("show_all not yet implemented\n");
}
