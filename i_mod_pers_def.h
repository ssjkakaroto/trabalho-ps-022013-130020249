#ifndef PERS_DEF
#define PERS_DEF

#ifdef PERS_DEF_SERV
#define EXT_PDEF
#else
#define EXT_PDEF extern
#endif

#include "tabela_codigos.h"
#include "i_estruturas.h"

EXT_PPROD int register_defect(const struct defeito *bug);
EXT_PPROD int read_defect(struct defeito *bug);
EXT_PPROD int rewrite_defect(const struct defeito *bug);
EXT_PPROD int delete_defect(struct defeito *bug);
EXT_PPROD int count_defects(void);

#endif
