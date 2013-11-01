#define LOGICA_NEGOCIO_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_dev.h"
#include "i_mod_pers_prod.h"
#include "i_mod_pers_def.h"
#include "i_mod_log_neg.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>





int retorna_desenvolvedor(struct desenvolvedor *dev)
{
	int ret;
	
	ret = consultar_desenvolvedor(dev);
	
	return(ret);
}
