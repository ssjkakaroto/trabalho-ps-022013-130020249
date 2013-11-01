#define PERS_DEV_SERV

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_pers_dev.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * Fun��o para escrever um novo desenvolvedor em disco
 *
 * A fun��o cadastra um novo desenvolvedor no arquivo 'cad_devs.bin', em
 * formato bin�rio, na posi��o 'posicao'. Se 'posicao = 0' ent�o o desenvolvedor
 * ser� gravado no final do arquivo.
 * N�o h� verifica��o se o desenvolvedor j� existe no arquivo ou n�o.
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
int write_developer(const struct desenvolvedor *dev, size_t posicao)
{
	FILE *output;
	int ret;
	
	if (posicao == 0) {
		output = fopen("cad_devs.bin", "ab");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);

		ret = fwrite(dev, sizeof(struct desenvolvedor), 1, output);

		fclose(output);
		return(ret);
	} else {
		output = fopen("cad_devs.bin", "rb+");
		if (output == NULL)
			return(ERROR_FILE_ACCESS);
		
		ret = fseek(output, (posicao-1) * sizeof(struct desenvolvedor),
		            SEEK_SET);
		ret += fwrite(dev, sizeof(struct desenvolvedor), 1, output);

		fclose(output);
		return(ret);
	}
}


/**
 * Fun��o exportada para cadastrar um desenvolvedor.
 *
 * Cadastra um desenvolvedor fazendo as verifica��es necess�rias, de forma que
 * seja gravado na posi��o correta do arquivo.
 *
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_developer. Se o
 * desenvolvedor j� existir, retorna ELEMENT_EXISTS.
 */
int register_developer(const struct desenvolvedor *dev)
{
	int ret, verif, pos;
	struct desenvolvedor devtmp;

	devtmp = *dev;

	verif = read_developer(&devtmp);
	if (verif < 0) {
		ret = write_developer(dev, 0);
	} else if (verif == 0) {
		pos = read_developer_deleted();
		if (pos >= 0)
			ret = write_developer(dev, pos);
		else
			return(ret);
	} else {
		return(ELEMENT_EXISTS);
	}

	return(ret);
}
	

/**
 * Fun��o para consultar um desenvolvedor
 *
 * A fun��o receber� uma struct de desenvolvedor que s� precisa do email
 * preenchido.
 * Essa struct ser� preenchida com o restante dos dados caso o desenvolvedor
 * exista. Caso o desenvolvedor n�o exista, a struct n�o ser� alterada.
 *
 * Valor de retorno:
 * H� o retorno do valor da posi��o do desenvolvedor, se ele existir. Caso n�o
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
int read_developer(struct desenvolvedor *dev)
{
	FILE *input;
	struct desenvolvedor devcheck;
	int ret = 0;
	
	input = fopen("cad_devs.bin", "rb");
	
	if (input == NULL)
		return(ERROR_FILE_ACCESS);
	
	while (fread(&devcheck, sizeof(struct desenvolvedor), 1, input) == 1) {
		ret++;

		if (strcmp(devcheck.email, dev->email) == 0) {
			if (devcheck.excluido == 1) {
				ret = 0;
				fclose(input);
				return(ret);
			} else {
				*dev = devcheck;
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
 * Fun��o para achar o primeiro desenvolvedor apagado.
 *
 * Valor de retorno:
 * Se houver um desenvolvedor apagado, ser� retornada a posi��o desse
 * desenvolvedor. Se n�o houver nenhum apagado retornar� 0. Se houver problema
 * ao abrir o arquivo, retorna ERROR_FILE_ACCESS.
 */
int read_developer_deleted(void)
{
	FILE *input;
	struct desenvolvedor devcheck;
	int ret = 0;

	input = fopen("cad_devs.bin", "rb");

	if (input == NULL)
		return(ERROR_FILE_ACCESS);

	while (fread(&devcheck, sizeof(struct desenvolvedor), 1, input) == 1) {
		ret++;
		
		if (devcheck.excluido == 1) {
			fclose(input);
			return(ret);
		}
	}

	ret = 0;

	fclose(input);

	return(ret);
}


/**
 * Fun��o que vai sobrescrever um desenvolvedor
 *
 * A fun��o recebe um desenvolvedor, que j� existe, e o sobrescreve. A
 * exist�ncia, ou n�o do desenvolvedor, dever� ser checada previamente.
 * Valor de retorno:
 * Retorna o valor de retorno da fun��o write_developer.
 */
 int rewrite_developer(const struct desenvolvedor *dev)
 {
 	int ret, verif, pos;
	struct desenvolvedor devtmp;
	
	devtmp = *dev;
	
	pos = read_developer(&devtmp);
	ret = write_developer(dev, pos);
	
	return(ret);	
 }


/**
 * Funcao para remover um desenvolvedor
 *
 * A fun��o apenas ir� mudar o valor de excluido de 0 para 1, do desenvolvedor
 * na posi��o 'posicao', permitindo que o espa�o seja reutilizado para grava��o
 * de um novo desenvolvedor, por cima do antigo.
 *
 * Valor de retorno:
 * Retorna 1 no caso de sucesso, ERROR_FILE_ACCESS no caso de erro ao
 * abrir o arquivo e um valor diferente de 2 no caso de outro erro.
 */
int delete_developer(struct desenvolvedor *dev)
{
	int ret, pos;

	pos = read_developer(dev);
	
	if (pos < 0) {
		return(ERROR_FILE_ACCESS);
	} else if (pos == 0) {
		return(ELEMENT_NOT_EXIST);
	} else {
		dev->excluido = 1;
		ret = write_developer(dev, pos);	
		return(ret);
	}
}

/**
 * Fun��o para contar o n�mero de desenvolvedores cadastrados.
 */
 int count_developers(void)
{
	FILE *input;
	struct desenvolvedor devcheck;
	int ret = 0;

	input = fopen("cad_devs.bin", "rb");

	if (input == NULL)
		return(ret);

	while (fread(&devcheck, sizeof(struct desenvolvedor), 1, input) == 1) {
		ret++;
		
		if (devcheck.excluido == 1) {
			ret--;
		}
	}

	fclose(input);

	return(ret);
}
