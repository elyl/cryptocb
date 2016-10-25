#ifndef __PROC_H__
#define __PROC_H__

#define BUFFER_SIZE	2048
#define KEY_SIZE	8 * 4
#define MASTER_KEY_SIZE	256

AES_KEY		get_master_key(unsigned char *key1, unsigned char *key2);

unsigned char	*find_cb(const char *name);

void		add_cb(const unsigned char *data);
void		bitwise_xor(const unsigned char *n1, const unsigned char *n2, const int size, unsigned char *out);

#endif
