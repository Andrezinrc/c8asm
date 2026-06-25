#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#define PDEBUG 0

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define IS_REG(tok) ((tok)[0] == 'v' && isxdigit((unsigned char)(tok)[1]) && (tok)[2] == '\0')

#define PARSE_REG(tok) ((int)strtol(&(tok)[1], NULL, 16))

typedef void (*InstructionHandler)(FILE *src, const char *mnemonic);

typedef struct {
    const char *mnemonic;
    InstructionHandler handler;
} InstructionDef;

void parse_source(FILE *src);

#endif
