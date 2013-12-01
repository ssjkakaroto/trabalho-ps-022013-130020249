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
 * Header com as funções utilizadas pelo módulo de interface com o usuário
 *******************************************************************************
 */

#ifndef INT_USR
#define INT_USR

#include "tabela_codigos.h"
#include "i_estruturas.h"

void login_screen(void);
int  get_right_pass(struct desenvolvedor *dev);
void unknown_user(void);
void login_successful(struct desenvolvedor *dev);

void print_new_developer_registration(void);
void print_new_product_registration(void);
void print_new_defect_registration(void);

void print_logged_menu(struct desenvolvedor *dev, int perfil);
void print_common_menu(void);
void print_project_leader_menu(void);
void print_product_leader_menu(void);
void print_non_leader_menu(void);
void print_assigned_to_bug_menu(void);

void process_option(struct desenvolvedor *dev, size_t opcao, int perfil);
void load_option_1(struct desenvolvedor *dev);
void load_option_2(struct desenvolvedor *dev);
int  load_option_3(struct desenvolvedor *dev);
void load_option_4(void);
void load_option_5(void);
void load_option_6(const struct desenvolvedor *dev);
void load_option_7(void);
void load_option_8(void);
void load_option_101(void);
void load_option_102(void);
void load_option_103(void);
void load_option_104(void);
void load_option_201(void);
void load_option_202(void);
void load_option_301(void);
void load_option_401(struct desenvolvedor *dev);

void print_product(const struct produto *prod);
void print_developer(const struct desenvolvedor *dev);
void print_defect(const struct defeito *bug);
void print_error(int erro);

#endif
