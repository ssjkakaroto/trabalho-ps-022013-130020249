#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_log_neg.h"
#include "mod_int_user.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	
	login_screen();
	return 0;
}


/**
 * Tela inicial do sistema que solicita identificador e senha do desenvolvedor.
 */
void login_screen(void)
{
	size_t i;
	int verif;
	struct desenvolvedor dev;
	
	printf("login: ");
	get_string(dev.email, EMAIL_SIZE);

	printf("%s\'s senha: ", dev.email);
	get_password(dev.senha, PASS_SIZE);

	printf("\n");
	
	verif = check_login(&dev);
	
	if (verif == WRONG_PASS) {
		verif = get_right_pass(&dev);
	}
	else if (verif == SUCCESS) {
		login_successful(&dev);
	}
	else if (verif == ERROR_FILE_ACCESS) {
		printf("Erro ao acessar o arquivo.\n");
		unknown_user();
	}
	else {
		printf("Usuario inexistente.\n");
		unknown_user();
	}
}


/**
 * Fun��o auxiliar para capturar strings, que recebe a string e seu tamanho.
 * O �ltimo caracter ser� sempre '\0', por isso o tamanho m�ximo da string �
 * (size - 1).
 */
void get_string(char *str, size_t size)
{	
	size_t i;
	
	str[size - 1] = '\0'; /* Para garantir que n�o vai dar problema na struct */
	for (i = 0; i < (size - 1); i++) {
		str[i] = getchar();
		
		if (str[i] == '\n') {
			str[i] = '\0';
			break;
		}
	}
}


/**
 * Fun��o auxiliar para capturar senhas, que recebe a string da senha e o
 * tamanho da senha.
 * O �ltimo caracter ser� sempre '\0', por isso o tamanho m�ximo da senha �
 * (size - 1)
 * N�o da echo dos caracteres e termina automaticamente quando chega no tamanho
 * (size - 1).
 */
void get_password(char *pass, size_t size)
{
	size_t i;
	
	pass[size - 1] = '\0';
	for (i = 0; i < (size - 1); i++) {
		pass[i] = getch();
		
		if (pass[i] == '\n') {
			pass[i] = '\0';
			break;
		}
	}
}


/**
 * Fun��o que fica em loop at� que a senha digitada pelo usu�rio seja igual a
 * senha cadastrada no banco de dados.
 */
int get_right_pass(struct desenvolvedor *dev)
{
	int verif;
	size_t i;

	do {
		printf("\nAcesso negado\n");
		printf("%s\'s senha: ", dev->email);
	
		get_password(dev->senha, PASS_SIZE);
		
		verif = check_login(dev);		
	} while (verif == WRONG_PASS);
	
	login_successful(dev);
	
	return(verif);
}


/**
 * Fun��o chamada quando o usu�rio n�o est� no bando de dados. D� op��o de
 * registrar um novo usu�rio.
 */
void unknown_user(void)
{
	char c = 'z';

	printf("Deseja cadastrar um novo usuario? (S ou N): ");
	c = tolower(getchar());
	getchar();
	
	do {
		switch (c) {
		case 's':
			new_developer_registration_screen();
			break;
		case 'n':
			printf("O programa ira fechar\n");
			break;
		default:
			printf("Opcao invalida. Informe S ou N.\n");
		}
	} while ((c != 's') && (c != 'n'));
}


/**
 * Fun��o chamada quando se deseja cadastrar um novo usu�rio.
 * Os dados da struct desenvolvedor ser�o preenchidos e ser� verificado se o
 * banco de dados existe ou n�o, caso n�o, o primeiro usu�rio cadastrado ser�
 * o l�der do projeto.
 */
void new_developer_registration_screen(void)
{
	struct desenvolvedor dev;
	char senha[6];
	size_t i;
	int verif;
	
	system("cls");
	
	/*
	 * NESTA FUN��O QUE DEVEM SER FEITAS AS VERIFICA��ES DE FORMATO
	 */
	
	
	printf("Informe o email: ");
	get_string(dev.email, EMAIL_SIZE);
	
	printf("Informe o nome: ");
	get_string(dev.nome, 16);
	
	/* printf("%d\n", number_of_developers()); */
	
	if (number_of_developers() == 0)
		dev.lid_proj = 1;
	else
		dev.lid_proj = 0;
	
	dev.lid_prod = 0;
	dev.cand_def = 0;
	dev.sol_def = 0;
	dev.excluido = 0;
	
	for (i = 0; i < 5; i++) {
		dev.cand1[i] = '\0';
		dev.cand2[i] = '\0';
	}
	
	do {
		printf("Informe a senha: ");
		get_password(dev.senha, 6);
		printf("\nRepita a senha: ");
		get_password(senha, 6);
		
		if (strcmp(dev.senha, senha) != 0)
			printf("\nSenha nao confere.\n");
		else
			loop = 0;
	} while (loop == 1);
	
	verif = register_new_developer(&dev);
	if (verif == 1)
		printf("\nDesenvolvedor cadastrado com sucesso.\n");
	else
		printf("\nFalar qual foi o erro\n");
	
}


/**
 * Fun��o que chama o menu correto dependendo do perfil do desenvolvedor.
 */
void login_successful(struct desenvolvedor *dev)
{
	size_t perfil;
	
	load_developer(dev);

	if (dev->lid_proj == 1)
		perfil = 1;
	else if (dev->lid_prod == 1)
		perfil = 2;
	else
		perfil = 3;

	load_logged_menu(dev, perfil);
}

/**
 * Menu de usu�rio logado, dependendo do perfil.
 *
 * 1: Lider de projeto
 * 2: Lider de produto
 * 3: Desenvolvedor
 */
void load_logged_menu(const struct desenvolvedor *dev, size_t perfil)
{

	switch (perfil) {
	case 1:
		printf("proj1");
		printf("proj2");
	case 2:
		printf("prod1");
		printf("prod2");
	case 3:
		printf("dev1");
		printf("dev2");
		break;
	}
}
