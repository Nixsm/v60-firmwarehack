#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {
	FILE* file (fopen (argv[1], "rb+"));
	fseek (file, -0x23C, SEEK_END);
	struct
	{
	    char unk_0[0x228];
	    uint32_t key_a;
	    uint32_t key_b;
	    char unk_230[8];
	    uint32_t key_verifier;
	} info;
	fread (&info, 0x23c, 1, file);

	uint32_t const iv = 'GYrS';
	uint32_t const check = 'HTPT';

	info.key_a ^= iv;
	info.key_b ^= iv;

	char key[4];
	if (check == (info.key_a ^ info.key_verifier))
		    *((uint32_t*)&key) = info.key_a;
	else if (check == (info.key_b ^ info.key_verifier))
		    *((uint32_t*)&key) = info.key_b;

	return 1;
}
