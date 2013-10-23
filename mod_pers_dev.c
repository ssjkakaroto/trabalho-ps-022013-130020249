#define PERS_DEV_SERV

#include "i_estruturas.h"
#include "i_mod_pers_dev.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


size_t cadastrar_desenvolvedor(const struct desenvolvedor *dev)
{
	FILE *output;
	size_t ret;

	output = fopen("cad_devs.bin", "ab");

	ret = fwrite(dev, sizeof(struct desenvolvedor), 1, output);
	fclose(output);

	return(ret);
}
