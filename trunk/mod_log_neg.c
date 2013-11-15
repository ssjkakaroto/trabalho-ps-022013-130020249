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
 * FUNÇÕES RELACIONADAS COM DESENVOLVEDORES *
 ********************************************
 */

/**
 * Função para verificar se o desenvolvedor existe no banco de dados e se a
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
 * Função que registra um novo desenvolvedor, delegando para o módulo de
 * persistência.
 */
int register_new_developer(const struct desenvolvedor *dev)
{
	return(register_developer(dev));
}


/**
 * Função que retorna o número total de desenvolvedores, delegando para o
 * módulo de persistência.
 */
int number_of_developers(void)
{
	return(count_developers());
}


/**
 * Função que preenche uma estrutura de desenvolvedor com os dados que estão
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
 * Função para sobrescrever um desenvolvedor no banco de dados, delegando
 * para o módulo de persistência.
 */
int overwrite_developer(const struct desenvolvedor *dev)
{
	return(rewrite_developer(dev));
}


/**
 * Função que remove um desenvolvedor do bando de dados, delegando para o módulo
 * de persistência.
 */
int remove_developer(struct desenvolvedor *dev)
{
	/* FALTA PROCURAR TODOS OS PRODUTOS E DEFEITOS ASSOCIADOS COM O DESENVOLVEDOR E FAZER AS ALTERACOES NECESSARIAS */
	return(delete_developer(dev));
}


/*
 *************************************
 * FUNÇÕES RELACIONADAS COM PRODUTOS *
 *************************************
 */

/**
 * Função que registra um novo produto, delegando para o módulo de persistência.
 */
int register_new_product(const struct produto *prod)
{
	return(register_product(prod));
}


/**
 * Função que preenche uma estrutura de produto com os dados que estão no banco
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
 * Função para sobrescrever um produto no banco de dados, delegando
 * para o módulo de persistência.
 */
int overwrite_product(const struct produto *prod)
{
	return(rewrite_product(prod));
}


/**
 * Função que remove um produto do bando de dados, delegando para o módulo
 * de persistência.
 */
int remove_product(struct produto *prod)
{
	/* FALTA FAZER A BUSCA NO BANDO DE DADOS DE DEFEITOS, REMOVENDO TODOS OS DEFEITOS ASSOCIADOS COM O PRODUTO */
	return(delete_product(prod));
}


/*
 *************************************
 * FUNÇÕES RELACIONADAS COM DEFEITOS *
 *************************************
 */
 
/**
 * Função que registra um novo defeito, delegando para o módulo de persistência.
 */
int register_new_defect(const struct defeito *bug)
{
	return(register_defect(bug));
}


/**
 * Função que preenche uma estrutura de defeito com os dados que estão no banco
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
 * Função para sobrescrever um defeito no banco de dados, delegando
 * para o módulo de persistência.
 */
int overwrite_defect(const struct defeito *bug)
{
	return(rewrite_defect(bug));
}
