#ifndef KEYDEVIDE_H
#define KEYDEVIDE_H

int KeyDevide(unsigned char * key,unsigned int keylen,unsigned char **dk,unsigned int *dkl);

int KeyMerge(unsigned char *dk1,unsigned int dkl1,unsigned char *dk2,unsigned int dkl2,
	unsigned char *dk3,unsigned int dkl3,unsigned char * key,unsigned int* keylen);

#endif