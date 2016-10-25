#include <stdio.h>
#include <unistd.h>

int main()
{
  char	buffer[256];
  int	n;

  while ((n = read(0, &buffer[0], n)) <= 1)
    ;
  buffer[n] = '\0';
  printf("%n - %s\n", buffer);
}
