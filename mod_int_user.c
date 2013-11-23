/*
 *******************************************************************************
 * Universidade de Brasília
 * Instituto de Ciências Exatas
 * Departamento de Ciência da Computação
 * Matéria: Programação Sistemática
 * Professor: Fernando Albuquerque
 * Aluno: Aaron Sue
 * Matrícula: 13/0020249
 * Trabalho Prático
 * Módulo de interface com o usuário
 *******************************************************************************
 */

#include "tabela_codigos.h"
#include "i_estruturas.h"
#include "i_mod_log_neg.h"
#include "mod_int_user.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
	
	system("cls");
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
 * Função que fica em loop até que a senha digitada pelo usuário seja igual a
 * senha cadastrada no banco de dados.
 */
int get_right_pass(struct desenvolvedor *dev)
{
	int verif;
	size_t i;

	do {
		printf("\nSenha incorreta. Acesso negado.\n");
		printf("%s\'s senha: ", dev->email);
	
		get_password(dev->senha, PASS_SIZE);
		
		verif = check_login(dev);		
	} while (verif == WRONG_PASS);
	
	login_successful(dev);
	
	return(verif);
}


/**
 * Função chamada quando o usuário não está no bando de dados. Dá opção de
 * registrar um novo usuário.
 */
void unknown_user(void)
{
	char c = 'z';
	
	do {
		printf("Deseja cadastrar um novo usuario? (S ou N): ");
		c = tolower(fgetc(stdin));
		if (fgetc(stdin) != '\n')
			fgetc(stdin);

		switch (c) {
		case 's':
			print_new_developer_registration();
			break;
		case 'n':
			printf("O programa ira fechar\n");
			break;
		default:
			printf("Opcao invalida.\n");

		}
	} while ((c != 's') && (c != 'n'));
}


/**
 * Função chamada quando se deseja cadastrar um novo usuário.
 * Os dados da struct desenvolvedor serão preenchidos e será verificado se o
 * banco de dados existe ou não, caso não, o primeiro usuário cadastrado será
 * o líder do projeto.
 */
void print_new_developer_registration(void)
{
	struct desenvolvedor dev;
	char senha[6];
	size_t i;
	int verif;
	
	system("cls");
	
	printf("Cadastro de novo desenvolvedor.\n\n");
	
	verif = 0;
	do {
		printf("Informe o email: ");
		get_string(dev.email, EMAIL_SIZE);
		verif = validate_email(dev.email);
		if (verif == INVALID_EMAIL)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_EMAIL);
	
	verif = 0;
	do {
		printf("Informe o nome: ");
		get_string(dev.nome, NAME_SIZE);
		verif = validate_name(dev.nome);
		if (verif == INVALID_NAME)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_NAME);
	
	i = 1;

	do {
		printf("Informe a senha: ");
		get_password(dev.senha, 6);
		printf("\nRepita a senha: ");
		get_password(senha, 6);

		if (strcmp(dev.senha, senha) != 0)
			printf("\nSenha nao confere.\n");
		else
			i = 0;
	} while (i == 1);
	
	verif = register_new_developer(&dev);

	if (verif == SUCCESS) {
		printf("\nDesenvolvedor cadastrado com sucesso.\n");
		system("pause");
		login_screen();
	}
	else {
		print_error(verif);
	}
}


void print_new_product_registration(void)
{
	struct produto prod;
	char cod[CODE_SIZE];
	int verif;

	system("cls");

	printf("Cadastro de um novo produto.\n\n");

	verif = 0;
	do {
		printf("Informe o codigo: ");
		get_string(prod.cod, CODE_SIZE);
		verif = validate_code(prod.cod);
		if (verif == INVALID_CODE)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_CODE);

	verif = 0;
	do {
		printf("Informe o nome: ");
		get_string(prod.nome, NAME_SIZE);
		verif = validate_name(prod.nome);
		if (verif == INVALID_NAME)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_NAME);

	verif = 0;
	do {
		printf("Infome a versao: ");
		get_string(prod.versao, VERSION_SIZE);
		verif = validate_version(prod.versao);
		if (verif == INVALID_VERSION)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_VERSION);

	verif = register_new_product(&prod);
	if (verif == SUCCESS)
		printf("\nProduto cadastrado com sucesso.\n");
	else
		print_error(verif);
}


void print_new_defect_registration(void)
{
	struct defeito bug;
	size_t i;
	int verif;

 	system("cls");

	printf("Cadastro de um novo defeito.\n\n");

	verif = 0;
	do {
		printf("Informe o codigo: ");
		get_string(bug.cod, CODE_SIZE);
		verif = validate_code(bug.cod);
		if (verif == INVALID_CODE)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_CODE);

	printf("Informe a descricao: ");
	get_string(bug.desc, DESC_SIZE);

	verif = 0;
	do {
		printf("Infome o codigo do produto ao qual o defeito esta associado: ");
		get_string(bug.prod, CODE_SIZE);
		verif = validate_code(bug.prod);
		if (verif == INVALID_CODE)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_CODE);

	verif = register_new_defect(&bug);
	if (verif == SUCCESS)
		printf("\nDefeito cadastrado com sucesso.\n");
	else
		print_error(verif);
}


/**
 * Função que chama o menu correto dependendo do perfil do desenvolvedor,
 * apos o login.
 */
void login_successful(struct desenvolvedor *dev)
{
	load_developer(dev);
	
	/* print_developer(dev);

	system("pause"); */

	print_logged_menu(dev, return_profile(dev));
}

/**
 * Menu de usuário logado, dependendo do perfil.
 *
 * 1: Lider de projeto
 * 2: Lider de produto
 * 3: Desenvolvedor
 *
 * Todos:
 * -Alterar nome
 * -Alterar senha
 * -Cadastrar defeito
 * -Votar em defeito
 * -Apagar conta
 *
 * Lider de projeto:
 * -Cadastrar produtos
 * -Editar produtos
 * -Indicar lider de produto
 * -Descontinuar produto
 *
 * Lider de produto:
 * -Escolher responsavel para solucionar defeitos
 * -Alterar status do defeito (reparado -> encerrado ou reparado -> confirmado)
 *
 * Desenvolvedores que nao sejam lideres:
 * -Candidatar para solucionar defeito
 *
 * Responsavel pelo defeito
 * -Alterar status do defeito (novo -> confirmado -> em reparo -> reparado)
 */
void print_logged_menu(struct desenvolvedor *dev, int perfil)
{
	int loop = 665;

	do {
		system("cls");
		
		printf("Sistema de gerencia de defeitos\n\n");
		
		switch (perfil) {
		case 1:
			print_common_menu();
			print_project_leader_menu();
			loop = load_option(dev, perfil);
			break;
		case 2:
			print_common_menu();
			print_product_leader_menu();
			loop = load_option(dev, perfil);
			break;
		case 3:
			print_common_menu();
			if (dev->sol_def == 1)
				print_assigned_to_bug_menu();
			print_non_leader_menu();
			loop = load_option(dev, perfil);
			break;
		}
	} while (loop != 666);
}


void print_common_menu(void)
{
	printf("1) Alterar nome\n");
	printf("2) Alterar senha\n");
	printf("3) Apagar conta\n");
	printf("4) Cadastrar defeito\n");
	printf("5) Votar em defeito\n");
	printf("6) Imprimir desenvolvedor\n");
	printf("7) Imprimir defeito\n");
	printf("8) Imprimir produto\n");
}


void print_project_leader_menu(void)
{
	printf("101) Cadastrar produto\n");
	printf("102) Editar produto\n");
	printf("103) Descontinuar produto\n");
	printf("104) Indicar lider de produto\n");
	printf("201) Indicar desenvolvedor para solucionar defeito\n");
	printf("202) Alterar status de defeito\n");
	printf("666) Sair\n");
}


void print_product_leader_menu(void)
{
	printf("201) Indicar desenvolvedor para solucionar defeito\n");
	printf("202) Alterar status de defeito\n");
	printf("666) Sair\n");
}

void print_non_leader_menu(void)
{
	printf("401) Candidatar-se para solucionar defeito\n");
	printf("666) Sair\n");
}


void print_assigned_to_bug_menu(void)
{
	printf("301) Alterar status de defeito\n");
}


int load_option(struct desenvolvedor *dev, size_t perfil)
{
	size_t opcao;
	
	printf("\nEscolha a opcao desejada: ");
	scanf("%d", &opcao);
	getchar();

	process_option(dev, opcao, perfil);
	
	return(opcao);
}


void process_option(struct desenvolvedor *dev, size_t opcao, int perfil)
{
	int check;
	
	system("cls");
	
	switch (opcao) {
		case 1:
			load_option_1(dev);
			break;
		case 2:
			load_option_2(dev);
			break;
		case 3:
			check = load_option_3(dev);
			if (check == SUCCESS)
				exit(0);
			break;
		case 4:
			load_option_4();
			break;
  		case 5:
			load_option_5();
			break;
    	case 6:
			load_option_6(dev);
			break;
  		case 7:
			load_option_7();
			break;
  		case 8:
			load_option_8();
			break;
		case 101:
			if (perfil != 1)
				printf("Voce nao possui perfil para esta opcao.\n");
			else
				load_option_101();
			break;
  		case 102:
			if (perfil != 1)
				printf("Voce nao possui perfil para esta opcao.\n");
			else
				load_option_102();
			break;
		case 103:
			if (perfil != 1)
				printf("Voce nao possui perfil para esta opcao.\n");
			else
				load_option_103();
			break;
		case 104:
			if (perfil != 1)
				printf("Voce nao possui perfil para esta opcao.\n");
			else
				load_option_104();
			break;
  		case 201:
  			if ((perfil != 1) && (perfil != 2)) {
				printf("Voce nao possui perfil para esta opcao.\n");
				system("pause");
			}
			else {
				load_option_201();
			}
			break;
		case 202:
			if ((perfil != 1) && (perfil != 2)) {
				printf("Voce nao possui perfil para esta opcao.\n");
				system("pause");
			}
			else {
				load_option_202();
			}
			break;
  		case 301:
  			if ((perfil != 3) && (dev->sol_def != 1)) {
  				printf("Voce nao possui perfil para esta opcao.\n");
				system("pause");
  			} else {
  				load_option_301();
  			}
		case 401:
			load_option_401(dev);
			break;
		case 666:
			break;
  		default:
			printf("Opcao invalida.\n");
	}
}

/**
 * Opcao 1: alterar nome
 */
void load_option_1(struct desenvolvedor *dev)
{
	struct desenvolvedor devtmp;
	char c;
	int check, verif;

	devtmp = *dev;
	
	printf("Alteracao de nome\n");
	print_developer(dev);
	printf("Nome atual: %s\n", dev->nome);

	verif = 0;
	do {
		printf("Novo nome: ");
		get_string(dev->nome, NAME_SIZE);
		verif = validate_name(dev->nome);
		if (verif == INVALID_NAME)
			print_error(verif);
		printf("\n");
	} while (verif == INVALID_NAME);

	printf("Confirma alterar o nome de %s\npara %s?\n", devtmp.nome,
           dev->nome);
	printf("(S ou N): ");
	c = tolower(getchar());
	getchar();

	do {
		switch (c) {
		case 's':
			check = overwrite_developer(dev);
			if (check == 1) {
				printf("Nome alterado com sucesso.\n");
			}
			else {
				print_error(check);
				printf("Erro ao alterar nome\n");
			}
			break;
		case 'n':
			strcpy(dev->nome, devtmp.nome);
			printf("Retornando ao menu principal\n");
			system("pause");
			break;
		default:
			printf("Opcao invalida. Informe S ou N.\n");
		}

	} while ((c != 's') && (c != 'n'));
}


/**
 * Opcao 2: alterar senha
 */
void load_option_2(struct desenvolvedor *dev)
{
	struct desenvolvedor devtmp;
	char c, senhatmp[PASS_SIZE];
	int check, loop;

	devtmp = *dev;

	printf("Alteracao de senha\n");
	printf("Informe a senha atual: ");
	get_password(dev->senha, PASS_SIZE);

	if (strcmp(dev->senha, devtmp.senha) != 0) {
		printf("\nSenha nao confere.\n");
		strcpy(dev->senha, devtmp.senha);
		printf("Retornando ao menu principal.\n");
	} else {
		loop = 1;
		
		while (loop == 1) {
			printf("\nInforme a nova senha: ");
			get_password(dev->senha, PASS_SIZE);
			
			/* FAZER VERIFICACAO DE FORMATO DE SENHA */
			
			printf("\nRepita a nova senha: ");
			get_password(senhatmp, PASS_SIZE);

			if (strcmp(dev->senha, senhatmp) != 0) {
				printf("\nSenha nao confere.\n");
				strcpy(dev->senha, devtmp.senha);
			}
			else {
				loop = 0;
			}
		}
		
		printf("\nConfirma alteracao de senha? (S ou N): ");
		c = tolower(getchar());
		getchar();
		
		do {
			switch (c) {
			case 's':
				check = overwrite_developer(dev);
				if (check == 1)
					printf("\nSenha alterada com sucesso.\n");
				else
					printf("Erro ao alterar senha\n");
				break;
			case 'n':
				strcpy(dev->senha, devtmp.senha);
				printf("Retornando ao menu principal\n");
				system("pause");
				break;
			default:
				printf("Opcao invalida. Informe S ou N.\n");
			}
		} while ((c != 's') && (c != 'n'));
	}
}


/**
 * Opcao 3: apagar conta
 */
int load_option_3(struct desenvolvedor *dev)
{
	int ret;
	char novo_dev_email[EMAIL_SIZE];
	
	ret = remove_developer(dev);
	
	if (ret == DEV_IS_PROJ_LEADER) {
		printf("\nO atual desenvolvedor e' o lider do projeto.\n");
		printf("Sera necessario designar novo lider de projeto.\n");
		printf("Informe o email do novo lider: ");
		get_string(novo_dev_email, EMAIL_SIZE);
		ret = assign_new_project_leader(dev, novo_dev_email);
		if (ret < SUCCESS)
			print_error(ret);
		else
			ret = remove_developer(dev);
	} else {
		if (ret < SUCCESS)
			print_error(ret);
	}
	
	return(ret);
}


/**
 * Opcao 4: cadastrar novo defeito
 */
void load_option_4(void)
{
	system("cls");

	print_new_defect_registration();

	system("pause");
}


/**
 * Opcao 5: votar em defeito
 */
void load_option_5(void)
{
	struct defeito bug;
	int check;
	char c;
	
	system("cls");

 	printf("Votar em defeito\n\n");
	printf("Informe o codigo do defeito: ");
	get_string(bug.cod, CODE_SIZE);
	
	check = load_defect(&bug);
	
	if (check != SUCCESS) {
		print_error(check);
	} else {
		print_defect(&bug);
		if (bug.votos < 100 && bug.est == 1) {
			printf("Confirma o voto?\n");
			printf("(S ou N): ");
			c = tolower(getchar());
			getchar();

			do {
				switch (c) {
				case 's':
					bug.votos++;
					check = overwrite_defect(&bug);
					if (check == 1) {
						printf("Voto registrado com sucesso.\n");
						system("pause");
					} else {
						printf("Erro ao regsitrar voto\n");
						system("pause");
					}
					break;
				case 'n':
					printf("Retornando ao menu principal\n");
					system("pause");
					break;
				default:
					printf("Opcao invalida. Informe S ou N.\n");
				}

			} while ((c != 's') && (c != 'n'));
		} else {
  			printf("Numero máximo de votos atingido ou produto nao é novo\n");
			system("pause");
		}
	}
}


void load_option_6(const struct desenvolvedor *dev)
{
	system("cls");
	print_developer(dev);
	system("pause");
}


void load_option_7(void)
{
	struct defeito bugtmp;
	
	system("cls");
	printf("Infome o codigo do defeito: ");
	get_string(bugtmp.cod, CODE_SIZE);
	load_defect(&bugtmp);
	print_defect(&bugtmp);
	system("pause");
}


void load_option_8(void)
{
	struct produto prodtmp;

	system("cls");
	printf("Infome o codigo do produto: ");
	get_string(prodtmp.cod, CODE_SIZE);
	load_product(&prodtmp);
	print_product(&prodtmp);
	system("pause");
}

/**
 * Opcao 101: cadastrar novo produto
 */
void load_option_101(void)
{
 	system("cls");
	
	print_new_product_registration();
	
	system("pause");
}


/**
 * Opcao 102: alterar produto
 */
void load_option_102(void)
{
	struct produto prod, prodtmp;
	char c;
	int check, opcao, verif;

	system("cls");
	
 	printf("Alteracao de produto\n\n");
	printf("Informe o codigo do produto: ");
	get_string(prod.cod, CODE_SIZE);

 	check = load_product(&prod);
	
	if (check != SUCCESS) {
		print_error(check);
	} else {
		prodtmp = prod;
		
		printf("\nProduto:\n");
		print_product(&prod);
		printf("\n");
		printf("1) Alterar nome\n");
		printf("2) Alterar versao\n");
		printf("Outra opcao retorna ao menu anterior.\n");
		printf("Opcao: ");
		scanf("%d", &opcao);
		getchar();
		
		switch (opcao) {
		case 1:
			verif = 0;
			do {
				printf("Informe o novo nome: ");
				get_string(prod.nome, NAME_SIZE);
				verif = validate_name(prod.nome);
				if (verif == INVALID_NAME)
					print_error(verif);
				printf("\n");
			} while (verif == INVALID_NAME);

			printf("Confirma alterar o nome de %s\npara %s?\n", prodtmp.nome,
                   prod.nome);
			printf("(S ou N): ");
			c = tolower(getchar());
			getchar();
			
			do {
				switch (c) {
				case 's':
					check = overwrite_product(&prod);
					if (check == 1)
						printf("Nome alterado com sucesso.\n");
					else
						printf("Erro ao alterar nome\n");
					break;
				case 'n':
					printf("Retornando ao menu principal\n");
					break;
				default:
					printf("Opcao invalida. Informe S ou N.\n");
				}

			} while ((c != 's') && (c != 'n'));
			
			break;
		case 2:
			verif = 0;
			do {
				printf("Infome a nova versao: ");
				get_string(prod.versao, VERSION_SIZE);
				verif = validate_version(prod.versao);
				if (verif == INVALID_VERSION)
					print_error(verif);
				printf("\n");
			} while (verif == INVALID_VERSION);

			printf("Confirma alterar a versao de\n%s para %s?\n",
			        prodtmp.versao, prod.versao);
			printf("(S ou N): ");
			c = tolower(getchar());
			getchar();

			do {
				switch (c) {
				case 's':
					check = overwrite_product(&prod);
					if (check == 1)
						printf("Nome alterado com sucesso.\n");
					else
						printf("Erro ao alterar nome\n");
					break;
				case 'n':
					printf("Retornando ao menu principal\n");
					break;
				default:
					printf("Opcao invalida. Informe S ou N.\n");
				}

			} while ((c != 's') && (c != 'n'));
			
			break;
		default:
			printf("\nRetornando ao menu anterior");
		}
	}
}


/**
 * Opcao 103: descontinuar produto
 */
void load_option_103(void)
{
	
	int check;
	struct produto prod, prodtmp;
	char c;

	system("cls");

 	printf("Descontinuar produto\n\n");
	printf("Informe o codigo do produto: ");
	get_string(prod.cod, CODE_SIZE);

	check = load_product(&prod);

	if (check != SUCCESS) {
		print_error(check);
	} else {
		check = remove_product(&prod);
		
		if (check != SUCCESS)
			print_error(check);
		else
			printf("\nProduto removido com sucesso\n");

		system("pause");
	}
}


/**
 * Opcao 104: designar lider de produto
 */
void load_option_104(void)
{
	int check;
	char dev_email[EMAIL_SIZE], prod_cod[CODE_SIZE];
	
	system("cls");
	
	printf("Designar lider de produto\n\n");
	printf("Informe o codigo do produto: ");
	get_string(prod_cod, CODE_SIZE);
	printf("Informe o email do desenvolvedor: ");
	get_string(dev_email, EMAIL_SIZE);
	
	check = assign_product_leader(dev_email, prod_cod);
	
	if (check != SUCCESS)
		print_error(check);
	else
		printf("\nDesenvolvedor indicado com sucesso\n");

	system("pause");
}


/**
 * Opcao 201: indicar desenvolvedor para solucionar defeito
 */
void load_option_201(void)
{
	int check;
	char dev_email[EMAIL_SIZE], def_cod[CODE_SIZE];

	system("cls");

	printf("Designar desenvolvedor para solucionar defeito\n\n");
	printf("Informe o codigo do defeito: ");
	get_string(def_cod, CODE_SIZE);
	printf("Informe o email do desenvolvedor: ");
	get_string(dev_email, EMAIL_SIZE);

	check = assign_defect_to_developer(dev_email, def_cod);

	if (check != SUCCESS)
		print_error(check);
	else
		printf("\nDesenvolvedor indicado com sucesso\n");

	system("pause");
}


/**
 * Opcao 202: alterar estado de defeito
 */
void load_option_202(void)
{
	struct defeito bug;
	int check, opcao;

	system("cls");

 	printf("Alterar estado de defeito\n\n");
	printf("Informe o codigo do defeito: ");
	get_string(bug.cod, CODE_SIZE);

	check = load_defect(&bug);

	if (check != SUCCESS) {
		print_error(check);
	} else {
		print_defect(&bug);
		if (bug.est == 4) {
			printf("Estados possiveis\n");
			printf("4) Mantem o estado atual\n");
			printf("5) Encerrado\n");
			printf("6) Confirmado\n");
			printf("Opcao (9 retorna ao menu principal): ");
			scanf("%d", &opcao);

			switch (opcao) {
			case 5: case 6:
				bug.est = opcao;
				check = overwrite_defect(&bug);
				if (check == 1) {
					printf("Estado alterado com sucesso.\n");
					system("pause");
				} else {
					printf("Erro ao alterar estado\n");
					system("pause");
				}
				break;
			default:
				printf("Retornando...\n");
				system("pause");
			}

		} else {
  			printf("O estado atual não permite alteracao\n");
			system("pause");
		}
	}
}


/**
 * Opcao 301: alterar estado de defeito
 */
void load_option_301(void)
{
	struct defeito bug;
	int check, opcao;

	system("cls");

 	printf("Alterar estado de defeito\n\n");
	printf("Informe o codigo do defeito: ");
	get_string(bug.cod, CODE_SIZE);

	check = load_defect(&bug);

	if (check != SUCCESS) {
		print_error(check);
	} else {
		print_defect(&bug);
		if (bug.est <= 4) {
			printf("Estados possiveis\n");
			printf("1) Novo\n");
			printf("2) Confirmado\n");
			printf("3) Em reparo\n");
			printf("4) Reparado\n");
			printf("Opcao (9 retorna ao menu principal): ");
			scanf("%d", &opcao);
			
			switch (opcao) {
			case 1: case 2: case 3: case 4:
				bug.est = opcao;
				check = overwrite_defect(&bug);
				if (check == 1) {
					printf("Estado alterado com sucesso.\n");
					system("pause");
				} else {
					printf("Erro ao alterar estado\n");
					system("pause");
				}
				break;
			default:
				printf("Retornando...\n");
				system("pause");
			}

		} else {
  			printf("O estado atual não permite alteracao\n");
			system("pause");
		}
	}
}

/**
 * Opcao 401: candidatar-se para a solucao de um defeito
 */
void load_option_401(struct desenvolvedor *dev)
{
	char cod_def[CODE_SIZE];
	int ret;

	system("cls");
	
    printf("Cadastramento para solucao de um defeito\n\n");
	printf("Informe o codigo do defeito: ");
	get_string(cod_def, CODE_SIZE);

	ret = associate_defect(dev, cod_def);
	print_error(ret);
}


void print_developer(const struct desenvolvedor *dev)
{
	printf("Nome: %s\n", dev->nome);
	printf("Email: %s\n", dev->email);
	printf("Senha: %s\n", dev->senha);
	printf("Lider de projeto: %d\n", dev->lid_proj);
	printf("Lider de produto: %d\n", dev->lid_prod);
	printf("# de defeitos que e' candidato: %d\n", dev->cand_def);
	printf("Defeito 1: %s\n", dev->cand1);
	printf("Defeito 2: %s\n", dev->cand2);
	printf("Numero de defeitos que esta solucionando: %d\n", dev->sol_def);
	printf("Defeito solucionando: %s\n", dev->def);
}

void print_product(const struct produto *prod)
{
	printf("Codigo: %s\n", prod->cod);
	printf("Nome: %s\n", prod->nome);
	printf("Versao: %s\n", prod->versao);
	printf("Lider: %s\n", prod->lider);
}

void print_defect(const struct defeito *bug)
{
	printf("Codigo: %s\n", bug->cod);
	printf("Descricao: %s\n", bug->desc);
	printf("Data de abertura: %s\n", bug->dt_ab);
	printf("Data de fechamento: %s\n", bug->dt_fc);
	printf("Desenvolvedor solucionando: %s\n", bug->des_sel);
	printf("Produto associado: %s\n", bug->prod);
	printf("Estado: %d\n", bug->est);
	printf("Votos: %d\n", bug->votos);
}

void print_error(int erro)
{
	switch (erro) {
	case ERROR:
		printf("\nErro ao executar comando.\n");
		system("pause");
		break;
 	case ERROR_FILE_ACCESS:
		printf("\nErro ao acessar arquivo.\n");
		system("pause");
		break;
 	case ELEMENT_EXISTS:
		printf("\nErro. Elemento ja existe no banco de dados.\n");
		system("pause");
		break;
 	case ELEMENT_NOT_EXIST:
		printf("\nErro. Elemento nao existe no banco de dados.\n");
		system("pause");
		break;
 	case WRONG_PASS:
		printf("\nSenha incorreta.\n");
		system("pause");
		break;
 	case TOO_MANY_PRODUCTS:
		printf("\nErro. Desenvolvedor ja atingiu o numero maximo de produtos ");
		printf("para ser lider.\n");
		system("pause");
		break;
 	case TOO_MANY_DEFECTS:
		printf("\nErro. Desenvolvedor ja atingiu o numero maximo de defeitos ");
		printf("para se candidatar.\n");
		system("pause");
		break;
  	case INVALID_EMAIL:
		printf("\nEmail em formato invalido. Insira email em formato correto.\n");
		system("pause");
		break;
  	case INVALID_NAME:
		printf("\nNome em formato invalido. Insira nome em formato correto.\n");
		system("pause");
		break;
  	case INVALID_CODE:
		printf("\nCodigo em formato invalido. Insira codigo em formato correto.\n");
		system("pause");
		break;
  	case DEV_NOT_CANDIDATE:
		printf("\nO desenvolvedor nao e' candidato para solucionar esse ");
		printf("defeito.\n");
		system("pause");
		break;
 	case ALREADY_SOLVING:
		printf("\nErro. Desenvolvedor ja' esta solucionando um defeito.\n");
		system("pause");
		break;
	default:
		printf("\nValor retornado: %d\n", erro);
		system("pause");
	}
}
