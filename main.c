#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_dev.h"
#include "i_mod_log_neg.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void imprimir_dev(struct desenvolvedor dev);

int main(void)
{
	char test[] = "Hello world!";
	size_t a;
	int retorno;
	struct desenvolvedor newdev, otherdev, otherdev1;
	
	strcpy(newdev.nome,"nome do dev");
	strcpy(newdev.email,"dev@dominio");
	strcpy(newdev.senha,"asdf");
	newdev.lid_proj = 1;
	newdev.lid_prod = 3;
	newdev.sol_def = 1;
	newdev.cand_def = 2;
	newdev.excluido = 0;
	
	strcpy(otherdev.nome,"aaron");
	strcpy(otherdev.email,"aaron1@dominio");
	strcpy(otherdev.senha,"lkjh");
	otherdev.lid_proj = 0;
	otherdev.lid_prod = 0;
	otherdev.sol_def = 0;
	otherdev.cand_def = 0;
	otherdev.excluido = 0;
	
	strcpy(otherdev1.nome,"aaronsue");
	strcpy(otherdev1.email,"aaronsue2@dominio");
	strcpy(otherdev1.senha,"1234");
	otherdev1.lid_proj = 0;
	otherdev1.lid_prod = 0;
	otherdev1.sol_def = 1;
	otherdev1.cand_def = 0;
	otherdev1.excluido = 0;
	
	retorno = cadastrar_desenvolvedor(&newdev);
	retorno = cadastrar_desenvolvedor(&otherdev);
	retorno = cadastrar_desenvolvedor(&otherdev1);
	
	imprimir_dev(otherdev1);
	retorno = consultar_desenvolvedor(&otherdev1);
	printf("%d\n", retorno);
	retorno = remover_desenvolvedor(2);
	printf("%d\n", retorno);
	retorno = consultar_desenvolvedor(&otherdev1);
	imprimir_dev(newdev);
	imprimir_dev(otherdev);
	imprimir_dev(otherdev1);
	
	a = verificar_email(test);
	
	return 0;
}

void imprimir_dev(struct desenvolvedor dev)
{
	printf("%s\n", dev.nome);
	printf("%s\n", dev.email);
	printf("%s\n", dev.senha);
	printf("%d\n\n", dev.excluido);
}
