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
#include <string.h>


int check_login(struct desenvolvedor *dev)
{
	int verif, chkpass;
	struct desenvolvedor devchk;
	
	devchk = *dev;
	
	verif = read_developer(&devchk);
	if (verif > 0) {
		chkpass = strcmp(devchk.senha, dev->senha);
		if (chkpass == 0)
			return(SUCCESS);
		else
			return(WRONG_PASS);
	} else {
		return(verif);
	}
}

int register_new_developer(const struct desenvolvedor *dev)
{
	return(register_developer(dev));
}

int number_of_developers(void)
{
	return(count_developers());
}

int load_developer(struct desenvolvedor *dev)
{
	int ret;
	
	ret = read_developer(dev);
	if (ret > 0)
		return SUCCESS;
	else
		return ret;
}
