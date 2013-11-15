#define PERS_PROD_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_prod.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * Fun��o interna para escrever um novo produto em disco
 *
 * A fun��o cadastra um novo produto no arquivo 'cad_prods.bin', em
 * formato bin�rio, na posi��o 'posicao'. Se 'posicao = 0' ent�o o produto
 * ser� gravado no final do arquivo.
 * N�o h� verifica��o se o produto j� existe no arquivo ou n�o.
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
int write_product(const struct produto *prod, size_t posicao)
{
	FILE *output;
	int ret;

	if (posicao == 0) {
		output = fopen("cad_prods.bin", "ab");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);

		ret = fwrite(prod, sizeof(struct produto), 1, output);

		fclose(output);
		return(ret);
	} else {
		output = fopen("cad_prods.bin", "rb+");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);

		ret = fseek(output, (posicao-1) * sizeof(struct produto),
		            SEEK_SET);
		ret += fwrite(prod, sizeof(struct produto), 1, output);

		fclose(output);
		return(ret);
	}
}


/**
 * Fun��o para consultar um produto
 *
 * A fun��o receber� uma struct de produto que s� precisa do codigo
 * preenchido.
 * Essa struct ser� preenchida com o restante dos dados caso o produto
 * exista. Caso o produto n�o exista, a struct n�o ser� alterada.
 *
 * Valor de retorno:
 * H� o retorno do valor da posi��o do produto, se ele existir. Caso n�o
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
int read_product(struct produto *prod)
{
	FILE *input;
	struct produto prodcheck;
	int ret = 0;

	input = fopen("cad_prods.bin", "rb");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&prodcheck, sizeof(struct produto), 1, input) == 1) {
		ret++;

		if (strcmp(prodcheck.cod, prod->cod) == 0) {
			if (prodcheck.excluido == 1) {
				ret = 0;
				fclose(input);
				return(ret);
			} else {
				*prod = prodcheck;
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
 * Fun��o para achar o primeiro produto apagado.
 *
 * Valor de retorno:
 * Se houver um produto apagado, ser� retornada a posi��o desse
 * produto. Se n�o houver nenhum apagado retornar� 0. Se houver problema
 * ao abrir o arquivo, retorna ERROR_FILE_ACCESS.
 */
int read_product_deleted(void)
{
	FILE *input;
	struct produto prodcheck;
	int ret = 0;

	input = fopen("cad_prods.bin", "rb");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&prodcheck, sizeof(struct produto), 1, input) == 1) {
		ret++;

		if (prodcheck.excluido == 1) {
			fclose(input);
			return(ret);
		}
	}

	ret = 0;

	fclose(input);

	return(ret);
}


/**
 * Fun��o exportada para cadastrar um produto.
 *
 * Cadastra um produto fazendo as verifica��es necess�rias, de forma que
 * seja gravado na posi��o correta do arquivo.
 *
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_product. Se o
 * produto j� existir, retorna ELEMENT_EXISTS.
 */
int register_product(const struct produto *prod)
{
	int ret, verif, pos;
	struct produto prodtmp;

	prodtmp = *prod;

	verif = read_product(&prodtmp);
	if (verif < 0) {
		if (verif == ELEMENT_NOT_EXIST) {
			pos = read_product_deleted();
			if (pos >= 0)
				ret = write_product(prod, pos);
			else
				return(pos);
		} else {
			ret = write_product(prod, 0);
		}
	} else if (verif == 0) {
		pos = read_product_deleted();
		if (pos >= 0)
			ret = write_product(prod, pos);
		else
			return(pos);
	} else {
		return(ELEMENT_EXISTS);
	}

	return(ret);
}


/**
 * Fun��o que vai sobrescrever um produto
 *
 * A fun��o recebe um produto, que j� existe, e o sobrescreve. A
 * exist�ncia, ou n�o do produto, dever� ser checada previamente.
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_product.
 */
 int rewrite_product(const struct produto *prod)
 {
 	int ret, verif, pos;
	struct produto prodtmp;

	prodtmp = *prod;

	pos = read_product(&prodtmp);
	ret = write_product(prod, pos);

	return(ret);
 }


/**
 * Funcao para remover um produto
 *
 * A fun��o apenas ir� mudar o valor de excluido de 0 para 1, do produto
 * na posi��o 'posicao', permitindo que o espa�o seja reutilizado para grava��o
 * de um novo produto, por cima do antigo.
 *
 * Valor de retorno:
 * Retorna 1 no caso de sucesso, ERROR_FILE_ACCESS no caso de erro ao
 * abrir o arquivo e um valor diferente de 2 no caso de outro erro.
 */
int delete_product(struct produto *prod)
{
	int ret, pos;

	pos = read_product(prod);

	if (pos < 0) {
		return(ERROR_FILE_ACCESS);
	} else if (pos == 0) {
		return(ELEMENT_NOT_EXIST);
	} else {
		prod->excluido = 1;
		ret = write_product(prod, pos);
		return(ret);
	}
}

/**
 * Fun��o para contar o n�mero de produtoes cadastrados.
 */
 int count_products(void)
{
	FILE *input;
	struct produto prodcheck;
	int ret = 0;

	input = fopen("cad_prods.bin", "rb");

	if (input == NULL)
		return(ret);

	while (fread(&prodcheck, sizeof(struct produto), 1, input) == 1) {
		ret++;

		if (prodcheck.excluido == 1) {
			ret--;
		}
	}

	fclose(input);

	return(ret);
}
