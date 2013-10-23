#include "i_estruturas.h"
#include "i_mod_pers_dev.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char test[] = "Hello world!";
	uint8_t a;
	size_t retorno;
	struct desenvolvedor newdev;
	
	strcpy(newdev.nome,"nome do dev");
	strcpy(newdev.email,"dev@dominio");
	strcpy(newdev.senha,"abcdef");
	newdev.lid_proj = 1;
	newdev.lid_prod = 3;
	newdev.sol_def = 1;
	newdev.cand_def = 2;
	
	retorno = cadastrar_desenvolvedor(&newdev);
	printf("%d %d\n", newdev.lid_prod, retorno);
	
	a = verificar_email(test);
	
	return 0;
}
