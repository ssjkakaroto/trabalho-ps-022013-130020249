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

	printf("Deseja cadastrar um novo usuario? (S ou N): ");
	c = tolower(getchar());
	getchar();
	
	do {
		switch (c) {
		case 's':
			print_new_developer_registration();
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
	
	/*
	 * NESTA FUNÇÃO QUE DEVEM SER FEITAS AS VERIFICAÇÕES DE FORMATO
	 */
	
	printf("Cadastro de novo desenvolvedor.\n\n");
	
	printf("Informe o email: ");
	get_string(dev.email, EMAIL_SIZE);
	
	printf("Informe o nome: ");
	get_string(dev.nome, NAME_SIZE);
	
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
	if (verif == 1) {
		printf("\nDesenvolvedor cadastrado com sucesso.\n");
		login_screen();
	}
	else {
		printf("\nFalar qual foi o erro\n");
	}
}


void print_new_product_registration(void)
{
	struct produto prod;
	char cod[CODE_SIZE];
	size_t i;
	int verif;

	system("cls");

	/*
	 * NESTA FUNÇÃO QUE DEVEM SER FEITAS AS VERIFICAÇÕES DE FORMATO
	 */

	printf("Cadastro de um novo produto.\n\n");

	printf("Informe o codigo: ");
	get_string(prod.cod, CODE_SIZE);

	printf("Informe o nome: ");
	get_string(prod.nome, NAME_SIZE);

	printf("Infome a versao: ");
	get_string(prod.versao, VERSION_SIZE);

	for (i = 0; i < EMAIL_SIZE; i++)
		prod.lider[i] = '\0';

	prod.excluido = 0;

	verif = register_new_product(&prod);
	if (verif == 1)
		printf("\nProduto cadastrado com sucesso.\n");
	else
		printf("\nFalar qual foi o erro\n");
}


void print_new_defect_registration(void)
{
	struct defeito bug;
	size_t i;
	int verif;
	time_t data_hora;
	struct tm *data_str;
	
 	system("cls");
	
	/*
	 * NESTA FUNÇÃO QUE DEVEM SER FEITAS AS VERIFICAÇÕES DE FORMATO
	 */

	printf("Cadastro de um novo defeito.\n\n");

	printf("Informe o codigo: ");
	get_string(bug.cod, CODE_SIZE);

	printf("Informe a descricao: ");
	get_string(bug.desc, DESC_SIZE);

	printf("Infome o codigo do produto ao qual o defeito esta associado: ");
	get_string(bug.prod, CODE_SIZE);

	bug.est = 1;
	bug.votos = 0;
	bug.excluido = 0;

	time(&data_hora);
	data_str = localtime(&data_hora);
	strftime(bug.dt_ab, DATE_SIZE, "%d-%m-%Y", data_str);

	for (i = 0; i < DATE_SIZE; i++)
		bug.dt_fc[i] = '\0';
	for (i = 0; i < EMAIL_SIZE; i++)
		bug.des_sel[i] = '\0';

	verif = register_new_defect(&bug);
	if (verif == 1)
		printf("\nProduto cadastrado com sucesso.\n");
	else
		printf("\nFalar qual foi o erro\n");
}


/**
 * Função que chama o menu correto dependendo do perfil do desenvolvedor.
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

	print_logged_menu(dev, perfil);
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
void print_logged_menu(struct desenvolvedor *dev, size_t perfil)
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


void process_option(struct desenvolvedor *dev, size_t opcao, size_t perfil)
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
  		case 201:
		case 202:
  		case 301:
		case 401:
		case 666:
			break;
  		default:
			printf("Opcao invalida.\n");
	}
}


void load_option_1(struct desenvolvedor *dev)
{
	struct desenvolvedor devtmp;
	char c;
	int check;

	devtmp = *dev;
	
	printf("Alteracao de nome\n");
	printf("Nome atual: %s\n", dev->nome);
	printf("Novo nome: ");
	get_string(dev->nome, NAME_SIZE);

	/* FAZER VERIFICACAO SE O NOME ESTA NA ESTRUTURA CORRETA */

	printf("Confirma alterar o nome de %s\npara %s?\n", devtmp.nome,
           dev->nome);
	printf("(S ou N): ");
	c = tolower(getchar());
	getchar();

	do {
		switch (c) {
		case 's':
			check = overwrite_developer(dev);
			if (check == 1)
				printf("Nome alterado com sucesso.\n");
			else
				printf("Erro ao alterar nome\n");
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


int load_option_3(struct desenvolvedor *dev)
{
	int ret;
	
	ret = remove_developer(dev);
	
	switch (ret) {
	case ERROR_FILE_ACCESS:
		printf("\nErro de acesso ao arquivo\n");
		break;
	case ELEMENT_NOT_EXIST:
		printf("\nDesenvolvedor inexistente\n");
		break;
	case SUCCESS:
		printf("\nDesenvolvedor removido com sucesso\n");
		break;
	default:
		printf("\nErro\n");
	}
	
	return(ret);
}


void load_option_4(void)
{
	system("cls");

	print_new_defect_registration();
}


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
		printf("EXPLICAR O ERRO");
	} else {
		printf("Confirma o voto?\n");
		printf("(S ou N): ");
		c = tolower(getchar());
		getchar();

		do {
			switch (c) {
			case 's':
				bug.votos++;
				check = overwrite_defect(&bug);
				if (check == 1)
					printf("Voto registrado com sucesso.\n");
					system("pause");
				else
					printf("Erro ao regsitrar voto\n");
				break;
			case 'n':
				printf("Retornando ao menu principal\n");
				break;
			default:
				printf("Opcao invalida. Informe S ou N.\n");
			}

		} while ((c != 's') && (c != 'n'));
	}
}


void load_option_101(void)
{
 	system("cls");
	
	print_new_product_registration();
}


void load_option_102(void)
{
	struct produto prod, prodtmp;
	char c;
	int check, opcao;

	system("cls");
	
 	printf("Alteracao de produto\n\n");
	printf("Informe o codigo do produto: ");
	get_string(prod.cod, CODE_SIZE);

 	check = load_product(&prod);
	
	if (check != SUCCESS) {
		printf("EXPLICAR O ERRO");
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
			printf("\nInforme o novo nome: ");
			get_string(prod.nome, NAME_SIZE);
			
			/* FAZER CHECAGEM DE FORMATO */
			
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
			printf("\nInforme a nova versao: ");
			get_string(prod.versao, VERSION_SIZE);
			
			/* FAZER CHECAGEM DE FORMATO */

			printf("Confirma alterar a versao de\n%s para %s?\n", prodtmp.versao,
                   prod.versao);
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


void load_option_103(void)
{
	
	int ret, check, opcao;;
	struct produto prod, prodtmp;
	char c;

	system("cls");

 	printf("Descontinuar produto\n\n");
	printf("Informe o codigo do produto: ");
	get_string(prod.cod, CODE_SIZE);

	check = load_product(&prod);

	if (check != SUCCESS) {
		printf("EXPLICAR O ERRO");
	} else {
		check = remove_product(&prod);

		switch (check) {
		case ERROR_FILE_ACCESS:
			printf("\nErro de acesso ao arquivo\n");
			break;
		case ELEMENT_NOT_EXIST:
			printf("\nProduto inexistente\n");
			break;
		case SUCCESS:
			printf("\nProduto removido com sucesso\n");
			break;
		default:
			printf("\nErro\n");
		}
	}
}


void print_developer(const struct desenvolvedor *dev)
{
	printf("Nome: %s\n", dev->nome);
	printf("Email: %s\n", dev->email);
	printf("Senha: %s\n", dev->senha);
	printf("Lider de projeto: %d\n", dev->lid_proj);
	printf("Lider de produto: %d\n", dev->lid_prod);
	printf("# de defeitos que eh candidato: %d\n", dev->cand_def);
	printf("Defeito 1: %s\n", dev->cand1);
	printf("Defeito 2: %s\n", dev->cand2);
	printf("Numero de defeitos que esta solucionando: %d\n", dev->sol_def);
	
	system("pause");
}

void print_product(const struct produto *prod)
{
	printf("Codigo: %s\n", prod->cod);
	printf("Nome: %s\n", prod->nome);
	printf("Versao: %s\n", prod->versao);
	printf("Lider: %s\n", prod->lider);
	
	system("pause");
}

void print_defect(const struct defeito *bug)
{
	printf("Codigo: %s\n", bug->cod);
	printf("Descricao: %s\n", bug->desc);
	printf("Data de abertura: %s\n", bug->dt_ab);
	printf("Data de fechamento: %s\n", bug->dt_fc);
	printf("Desenvolvedor solucionado: %s\n", bug->des_sel);
	printf("Produto associado: %s\n", bug->prod);
	printf("Estado: %d\n", bug->est);
	printf("Votos: %d\n", bug->votos);
	
	system("pause");
}
