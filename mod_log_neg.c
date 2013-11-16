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
#include <time.h>


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
int register_new_developer(struct desenvolvedor *dev)
{
	size_t i;
	
	if (number_of_developers() == 0)
		dev->lid_proj = 1;
	else
		dev->lid_proj = 0;

	dev->lid_prod = 0;
	dev->cand_def = 0;
	dev->sol_def = 0;
	dev->excluido = 0;

	for (i = 0; i < CODE_SIZE; i++) {
		dev->cand1[i] = '\0';
		dev->cand2[i] = '\0';
	}
	
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
	size_t i;
	
	for (i = 0; i < EMAIL_SIZE; i++)
		prod->lider[i] = '\0';

	prod->excluido = 0;
	
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
 * Fun��o que remove um produto do banco de dados, delegando para o m�dulo
 * de persist�ncia.
 */
int remove_product(struct produto *prod)
{
	/* FALTA FAZER A BUSCA NO BANDO DE DADOS DE DEFEITOS, REMOVENDO TODOS OS DEFEITOS ASSOCIADOS COM O PRODUTO */
	return(delete_product(prod));
}


/**
 * Fun��o que vai indicar um l�der de produto
 */
int assign_product_leader(char *dev_email, char *prod_cod)
{
	struct desenvolvedor dev;
	struct produto prod;
	int ret;
	
	strcpy(dev.email, dev_email);
	strcpy(prod.cod, prod_cod);
	
	ret = read_product(&prod);
	if (ret > 0) {
		ret = read_developer(&dev);
		if (ret > 0) {
			if (dev.lid_prod < 5) {
				dev.lid_prod++;
				ret = rewrite_developer(&dev);
				if (ret > 0) {
					strcpy(prod.lider, dev.email);
					ret = rewrite_product(&prod);
				}
			} else {
				return(TOO_MANY_PRODUCTS);
			}
   		}
	}
	
	return(ret);
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
	time_t data_hora;
	struct tm *data_str;
	struct produto prodtmp;
	
	strcpy(prodtmp.cod, bug->prod);
	
	
	/* FAZER UMA FUNCAO NA LOGICA DE NEGOCIO PARA ESTE CADASTRO E VERIFICAR SE O PRODUTO EXISTE */
	
	

	bug->est = 1;
	bug->votos = 0;
	bug->excluido = 0;

	time(&data_hora);
	data_str = localtime(&data_hora);
	strftime(bug->dt_ab, DATE_SIZE, "%d-%m-%Y", data_str);

	for (i = 0; i < DATE_SIZE; i++)
		bug->dt_fc[i] = '\0';
	for (i = 0; i < EMAIL_SIZE; i++)
		bug->des_sel[i] = '\0';

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


int associate_defect(struct desenvolvedor *dev, char *cod_def)
{
	int ret;
	struct defeito bugtmp;
	
	strcpy(bugtmp.cod, cod_def);
	
	ret = read_defect(&bugtmp);
	if ((ret == 0) || (ret == ELEMENT_NOT_EXIST)) {
		return(ELEMENT_NOT_EXIST);
	} else {
		switch (dev->cand_def) {
		case 0:
			strcpy(dev->cand1, cod_def);
			dev->cand_def = 1;
			ret = rewrite_developer(dev);
			break;
		case 1:
			strcpy(dev->cand2, cod_def);
			dev->cand_def = 2;
			ret = rewrite_developer(dev);
			break;
		default:
			return(TOO_MANY_DEFECTS);
		}
		return(ret);
	}
}
