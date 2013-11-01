#ifndef INT_USR
#define INT_USR

#include "tabela_codigos.h"
#include "i_estruturas.h"

void login_screen(void);
void get_string(char *str, size_t size);
void get_password(char *pass, size_t size);
int get_right_pass(struct desenvolvedor *dev);
void unknown_user(void);
void new_developer_registration_screen(void);
void login_successful(struct desenvolvedor *dev);
void load_logged_menu(const struct desenvolvedor *dev, size_t perfil);

#endif
