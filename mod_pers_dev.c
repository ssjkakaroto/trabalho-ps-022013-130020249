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
 * H� o retorno do valor da fun��o fwrite:
 * The total number of elements successfully written is returned.
 * If this number differs from the count parameter, a writing error prevented
 * the function from completing. In this case, the error indicator (ferror) will
 * be set for the stream.
 * If either size or count is zero, the function returns zero and the error
 * indicator remains unchanged.
 * size_t is an unsigned integral type.
 */
int escrever_desenvolvedor(const struct desenvolvedor *dev, size_t posicao)
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
 * Retorna o valor de retorno da fun��o escrever_desenvolvedor. Se o
 * desenvolvedor j� existir, retorna ERROR_STRT_EXISTS.
 */
int cadastrar_desenvolvedor(const struct desenvolvedor *dev)
{
	int ret, verif, pos;
	struct desenvolvedor devtmp;

	devtmp = *dev;

	verif = consultar_desenvolvedor(&devtmp);
	if (verif < 0) {
		ret = escrever_desenvolvedor(dev, 0);
	} else if (verif == 0) {
		pos = consultar_desenvolvedor_apagado();
		if (pos >= 0)
			ret = escrever_desenvolvedor(dev, pos);
		else
			return(ret);
	} else {
		return(ERROR_STRT_EXISTS);
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
 * H� o retorno do valor da fun��o fread:
 * The total number of elements successfully read is returned.
 * If this number differs from the count parameter, either a reading error
 * occurred or the end-of-file was reached while reading. In both cases, the
 * proper indicator is set, which can be checked with ferror and feof,
 * respectively.
 * If either size or count is zero, the function returns zero and both the
 * stream state and the content pointed by ptr remain unchanged.
 * size_t is an unsigned integral type.
 */
int consultar_desenvolvedor(struct desenvolvedor *dev)
{
	FILE *input;
	struct desenvolvedor devcheck;
	int ret = 0;
	
	input = fopen("cad_devs.bin", "rb");
	
	if (input == NULL)
		return(ERROR_FILE_ACCESS);
	
	/*printf("%s\n", dev->email);*/
	while (fread(&devcheck, sizeof(struct desenvolvedor), 1, input) == 1) {
		/*printf("entrou no while\n");*/
		ret++;
		/*printf("%s\n", devcheck.email);*/
		if (strcmp(devcheck.email, dev->email) == 0) {
			/*printf("entrou no if\n");*/
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

	ret = 0;
	
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
int consultar_desenvolvedor_apagado(void)
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
int remover_desenvolvedor(size_t posicao)
{
	FILE *input;
	int ret;
	struct desenvolvedor tmp;

	input = fopen("cad_devs.bin", "rb+");

	if (input == NULL) {
		return(ERROR);
	}

	ret = fseek(input, (posicao-1) * sizeof(struct desenvolvedor), SEEK_SET);
	ret += fread(&tmp, sizeof(struct desenvolvedor), 1, input);
	tmp.excluido = 1;
	ret += fseek(input, (posicao-1) * sizeof(struct desenvolvedor), SEEK_SET);
	ret += fwrite(&tmp, sizeof(struct desenvolvedor), 1, input);

	fclose(input);
	
	ret -= 1;

	/*printf("%d\n", ret);*/

	return(ret);
}
