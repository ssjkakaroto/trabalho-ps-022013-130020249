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

int overwrite_developer(const struct desenvolvedor *dev)
{
	return(rewrite_developer(dev));
}


int remove_developer(struct desenvolvedor *dev)
{
	return(delete_developer(dev));
}


int register_new_product(const struct produto *prod)
{
	return(register_product(prod));
}


int load_product(struct produto *prod)
{
	int ret;

	ret = read_product(prod);
	if (ret > 0)
		return SUCCESS;
	else
		return ret;
}


int overwrite_product(const struct produto *prod)
{
	return(rewrite_product(prod));
}


int remove_product(struct produto *prod)
{
	/* FALTA FAZER A BUSTA NO BANDO DE DADOS DE DEFEITOS, REMOVENDO TODOS OS DEFEITOS ASSOCIADOS COM O PRODUTO */
	return(delete_product(prod));
}
