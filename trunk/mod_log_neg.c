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


/*
 ********************************************
 * FUN��ES RELACIONADAS COM DESENVOLVEDORES *
 ********************************************
 */

/**
 * Fun��o para verificar se o desenvolvedor existe no banco de dados e se a
 * senha digitada confere com a senha gravada.
 */
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


/**
 * Fun��o que registra um novo desenvolvedor, delegando para o m�dulo de
 * persist�ncia.
 */
int register_new_developer(const struct desenvolvedor *dev)
{
	return(register_developer(dev));
}


/**
 * Fun��o que retorna o n�mero total de desenvolvedores, delegando para o
 * m�dulo de persist�ncia.
 */
int number_of_developers(void)
{
	return(count_developers());
}


/**
 * Fun��o que preenche uma estrutura de desenvolvedor com os dados que est�o
 * no banco de dados.
 */
int load_developer(struct desenvolvedor *dev)
{
	int ret;
	
	ret = read_developer(dev);
	if (ret > 0)
		return SUCCESS;
	else
		return ret;
}


/**
 * Fun��o para sobrescrever um desenvolvedor no banco de dados, delegando
 * para o m�dulo de persist�ncia.
 */
int overwrite_developer(const struct desenvolvedor *dev)
{
	return(rewrite_developer(dev));
}


/**
 * Fun��o que remove um desenvolvedor do bando de dados, delegando para o m�dulo
 * de persist�ncia.
 */
int remove_developer(struct desenvolvedor *dev)
{
	/* FALTA PROCURAR TODOS OS PRODUTOS E DEFEITOS ASSOCIADOS COM O DESENVOLVEDOR E FAZER AS ALTERACOES NECESSARIAS */
	return(delete_developer(dev));
}


/*
 *************************************
 * FUN��ES RELACIONADAS COM PRODUTOS *
 *************************************
 */

/**
 * Fun��o que registra um novo produto, delegando para o m�dulo de persist�ncia.
 */
int register_new_product(const struct produto *prod)
{
	return(register_product(prod));
}


/**
 * Fun��o que preenche uma estrutura de produto com os dados que est�o no banco
 * de dados.
 */
int load_product(struct produto *prod)
{
	int ret;

	ret = read_product(prod);
	if (ret > 0)
		return SUCCESS;
	else
		return ret;
}


/**
 * Fun��o para sobrescrever um produto no banco de dados, delegando
 * para o m�dulo de persist�ncia.
 */
int overwrite_product(const struct produto *prod)
{
	return(rewrite_product(prod));
}


/**
 * Fun��o que remove um produto do bando de dados, delegando para o m�dulo
 * de persist�ncia.
 */
int remove_product(struct produto *prod)
{
	/* FALTA FAZER A BUSCA NO BANDO DE DADOS DE DEFEITOS, REMOVENDO TODOS OS DEFEITOS ASSOCIADOS COM O PRODUTO */
	return(delete_product(prod));
}


/*
 *************************************
 * FUN��ES RELACIONADAS COM DEFEITOS *
 *************************************
 */
 
/**
 * Fun��o que registra um novo defeito, delegando para o m�dulo de persist�ncia.
 */
int register_new_defect(const struct defeito *bug)
{
	return(register_defect(bug));
}


/**
 * Fun��o que preenche uma estrutura de defeito com os dados que est�o no banco
 * de dados.
 */
int load_defect(struct defeito *bug)
{
	int ret;

	ret = read_defect(bug);
	if (ret > 0)
		return SUCCESS;
	else
		return ret;
}


/**
 * Fun��o para sobrescrever um defeito no banco de dados, delegando
 * para o m�dulo de persist�ncia.
 */
int overwrite_defect(const struct defeito *bug)
{
	return(rewrite_defect(bug));
}
