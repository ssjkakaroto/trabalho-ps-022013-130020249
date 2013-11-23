/*
 *******************************************************************************
 * Universidade de Bras�lia
 * Instituto de Ci�ncias Exatas
 * Departamento de Ci�ncia da Computa��o
 * Mat�ria: Programa��o Sistem�tica
 * Professor: Fernando Albuquerque
 * Aluno: Aaron Sue
 * Matr�cula: 13/0020249
 * Trabalho Pr�tico
 * M�dulo de persist�ncia de defeitos
 *******************************************************************************
 */

#define PERS_DEF_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_def.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * Fun��o interna para escrever um novo defeito em disco
 *
 * A fun��o cadastra um novo defeito no arquivo 'cad_bugs.bin', em
 * formato bin�rio, na posi��o 'posicao'. Se 'posicao = 0' ent�o o defeito
 * ser� gravado no final do arquivo.
 * N�o h� verifica��o se o defeito j� existe no arquivo ou n�o.
 *
 * Valor de retorno:
 * H� o retorno do valor da fun��o fwrite (fseek retorna zero no sucesso):
 * The total number of elements successfully written is returned.
 * If this number differs from the count parameter, a writing error prevented
 * the function from completing. In this case, the error indicator (ferror) will
 * be set for the stream.
 * If either size or count is zero, the function returns zero and the error
 * indicator remains unchanged.
 * size_t is an unsigned integral type.
 */
int write_defect(const struct defeito *bug, size_t posicao)
{
	FILE *output;
	int ret;

	if (posicao == 0) {
		output = fopen("cad_bugs.bin", "ab");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);

		ret = fwrite(bug, sizeof(struct defeito), 1, output);

		fclose(output);
		return(ret);
	} else {
		output = fopen("cad_bugs.bin", "rb+");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);

		ret = fseek(output, (posicao-1) * sizeof(struct defeito),
		            SEEK_SET);
		ret += fwrite(bug, sizeof(struct defeito), 1, output);

		fclose(output);
		return(ret);
	}
}


/**
 * Fun��o para consultar um defeito
 *
 * A fun��o receber� uma struct de defeito que s� precisa do codigo
 * preenchido.
 * Essa struct ser� preenchida com o restante dos dados caso o defeito
 * exista. Caso o defeito n�o exista, a struct n�o ser� alterada.
 *
 * Valor de retorno:
 * H� o retorno do valor da posi��o do defeito, se ele existir. Caso n�o
 * exista ser� retornado ELEMENT_NOT_EXIST, caso exista mas esteja apagado,
 * retorna 0.
 * The total number of elements successfully read is returned.
 * If this number differs from the count parameter, either a reading error
 * occurred or the end-of-file was reached while reading. In both cases, the
 * proper indicator is set, which can be checked with ferror and feof,
 * respectively.
 * If either size or count is zero, the function returns zero and both the
 * stream state and the content pointed by ptr remain unchanged.
 * size_t is an unsigned integral type.
 */
int read_defect(struct defeito *bug)
{
	FILE *input;
	struct defeito bugcheck;
	int ret = 0;

	input = fopen("cad_bugs.bin", "rb");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&bugcheck, sizeof(struct defeito), 1, input) == 1) {
		ret++;

		if (strcmp(bugcheck.cod, bug->cod) == 0) {
			if (bugcheck.excluido == 1) {
				ret = 0;
				fclose(input);
				return(ret);
			} else {
				*bug = bugcheck;
				fclose(input);
				return(ret);
			}
		}
	}

	ret = ELEMENT_NOT_EXIST;

	fclose(input);

	return(ret);
}


/**
 * Fun��o para achar o primeiro defeito apagado.
 *
 * Valor de retorno:
 * Se houver um defeito apagado, ser� retornada a posi��o desse
 * defeito. Se n�o houver nenhum apagado retornar� 0. Se houver problema
 * ao abrir o arquivo, retorna ERROR_FILE_ACCESS.
 */
int read_defect_deleted(void)
{
	FILE *input;
	struct defeito bugcheck;
	int ret = 0;

	input = fopen("cad_bugs.bin", "rb");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&bugcheck, sizeof(struct defeito), 1, input) == 1) {
		ret++;

		if (bugcheck.excluido == 1) {
			fclose(input);
			return(ret);
		}
	}

	ret = 0;

	fclose(input);

	return(ret);
}


/**
 * Fun��o exportada para cadastrar um defeito.
 *
 * Cadastra um defeito fazendo as verifica��es necess�rias, de forma que
 * seja gravado na posi��o correta do arquivo.
 *
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_defect. Se o
 * defeito j� existir, retorna ELEMENT_EXISTS.
 */
int register_defect(const struct defeito *bug)
{
	int ret, verif, pos;
	struct defeito bugtmp;

	bugtmp = *bug;

	verif = read_defect(&bugtmp);
	if (verif < 0) {
		if (verif == ELEMENT_NOT_EXIST) {
			pos = read_defect_deleted();
			if (pos >= 0)
				ret = write_defect(bug, pos);
			else
				return(pos);
		} else {
			ret = write_defect(bug, 0);
		}
	} else if (verif == 0) {
		pos = read_defect_deleted();
		if (pos >= 0)
			ret = write_defect(bug, pos);
		else
			return(pos);
	} else {
		return(ELEMENT_EXISTS);
	}

	return(ret);
}


/**
 * Fun��o que vai sobrescrever um defeito
 *
 * A fun��o recebe um defeito, que j� existe, e o sobrescreve. A
 * exist�ncia, ou n�o do defeito, dever� ser checada previamente.
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_defect.
 */
 int rewrite_defect(const struct defeito *bug)
 {
 	int ret, verif, pos;
	struct defeito bugtmp;

	bugtmp = *bug;

	pos = read_defect(&bugtmp);
	ret = write_defect(bug, pos);

	return(ret);
 }


/**
 * Funcao para remover um defeito
 *
 * A fun��o apenas ir� mudar o valor de excluido de 0 para 1, do defeito
 * na posi��o 'posicao', permitindo que o espa�o seja reutilizado para grava��o
 * de um novo defeito, por cima do antigo.
 *
 * Valor de retorno:
 * Retorna 1 no caso de sucesso, ERROR_FILE_ACCESS no caso de erro ao
 * abrir o arquivo e um valor diferente de 2 no caso de outro erro.
 */
int delete_defect(struct defeito *bug)
{
	int ret, pos;

	pos = read_defect(bug);

	if (pos < 0) {
		return(ERROR_FILE_ACCESS);
	} else if (pos == 0) {
		return(ELEMENT_NOT_EXIST);
	} else {
		bug->excluido = 1;
		ret = write_defect(bug, pos);
		return(ret);
	}
}

/**
 * Fun��o para contar o n�mero de defeitos cadastrados.
 */
 int count_defects(void)
{
	FILE *input;
	struct defeito bugcheck;
	int ret = 0;

	input = fopen("cad_bugs.bin", "rb");

	if (input == NULL)
		return(ret);

	while (fread(&bugcheck, sizeof(struct defeito), 1, input) == 1) {
		ret++;

		if (bugcheck.excluido == 1) {
			ret--;
		}
	}

	fclose(input);

	return(ret);
}


/**
 * Fun��o que remove todos os defeitos associados com determinado produto.
 */
int remove_product_defects(char *cod_prod)
{
	FILE *input;
	struct defeito bugtmp;
	int ret = 0;
	size_t pos = 0;

	input = fopen("cad_bugs.bin", "rb+");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&bugtmp, sizeof(struct defeito), 1, input) == 1) {
		pos++;
		if (strcmp(bugtmp.prod, cod_prod) == 0) {
			bugtmp.excluido = 1;
			ret = fseek(input, (pos-1) * sizeof(struct defeito), SEEK_SET);
			ret += fwrite(&bugtmp, sizeof(struct defeito), 1, input);
			ret += fseek(input, pos * sizeof(struct defeito), SEEK_SET);
		}
	}

	fclose(input);

	return(ret);
}
