#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "CuTest.h"
#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_dev.h"

/* Definições dos dados de teste. */
#define TOTALDEVS 2

/* Declarações de protótipos das funções. */
void executarTestes(void);
void TestIncludeDev(CuTest *teste);
void TestIncludeDev2(CuTest *teste);
void TestReadDev(CuTest *teste);
void TestCountDevs(CuTest *teste);
void TestRemoveDev(CuTest *teste);
void TestCountDeletedDev(CuTest *teste);

int main(int argc, char *argv[])
{
	/* Solicitar a execução dos testes.	*/
	executarTestes();
	getch();
	return 0;
}

/* Função responsável por executar os casos de teste. */
void executarTestes(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
	
	/* Cria o conjunto de testes. */
	CuSuiteAdd(suite, CuTestNew("Desenvolvedor Incluido.", TestIncludeDev));
	CuSuiteAdd(suite, CuTestNew("Desenvolvedor Incluido.", TestIncludeDev2));
	CuSuiteAdd(suite, CuTestNew("Desenvolvedor Lido.", TestReadDev));
	CuSuiteAdd(suite, CuTestNew("Desevolvedores contados.", TestCountDevs));
	CuSuiteAdd(suite, CuTestNew("Desenvolvedor removido.", TestRemoveDev));
	CuSuiteAdd(suite, CuTestNew("Desenvolvedor removido contado.", TestCountDeletedDev));
	
	/*Executa o conjunto de testes e apresenta os resultados. */
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

/* Definições dos casos de teste. */
void TestIncludeDev(CuTest *teste)
{
	struct desenvolvedor devtmp;
	
	strcpy(devtmp.nome, "Nome Sobrenome");
	strcpy(devtmp.email, "teste@dev1.com");
	strcpy(devtmp.senha, "13579");
	strcpy(devtmp.cand1, "tsta");
	strcpy(devtmp.cand2, "tstb");
	strcpy(devtmp.def, "deft");
	devtmp.lid_prod = 0;
	devtmp.lid_proj = 1;
	devtmp.cand_def = 0;
	devtmp.sol_def = 0;
	devtmp.excluido = 0;
	
	CuAssertIntEquals(teste, SUCCESS, register_developer(&devtmp));
	
	printf("Incluiu o primeiro desenvolvedor na base de dados.\n");
}


void TestIncludeDev2(CuTest *teste)
{
	struct desenvolvedor devtmp;

	strcpy(devtmp.nome, "Nome Beta");
	strcpy(devtmp.email, "teste@dev2.com");
	strcpy(devtmp.senha, "02468");
	strcpy(devtmp.cand1, "tstc");
	strcpy(devtmp.cand2, "tstd");
	strcpy(devtmp.def, "deft");
	devtmp.lid_prod = 0;
	devtmp.lid_proj = 0;
	devtmp.cand_def = 0;
	devtmp.sol_def = 1;
	devtmp.excluido = 0;

	CuAssertIntEquals(teste, SUCCESS, register_developer(&devtmp));
	
	printf("Incluiu o segundo desenvolvedor na base de dados.\n");
}

void TestReadDev(CuTest *teste)
{
	struct desenvolvedor devtmp;

	strcpy(devtmp.email, "teste@dev1.com");

	CuAssertIntEquals(teste, SUCCESS, read_developer(&devtmp));
	
	printf("Leu o primeiro desenvolvedor da base de dados.\n");
}


void TestRemoveDev(CuTest *teste)
{
	struct desenvolvedor devtmp;

	strcpy(devtmp.email, "teste@dev2.com");

	CuAssertIntEquals(teste, SUCCESS, delete_developer(&devtmp));
	
	printf("Removeu o segundo desenvolvedor da base de dados.\n");
}

void TestCountDevs(CuTest *teste)
{
	CuAssertIntEquals(teste, TOTALDEVS, count_developers());
	
	printf("Contou o total de desenvolvedores.\n");
}


void TestCountDeletedDev(CuTest *teste)
{
		CuAssertIntEquals(teste, TOTALDEVS, read_developer_deleted());
		
		printf("Achou a posicao do primeiro desenvolvedor apagado\n");
}
