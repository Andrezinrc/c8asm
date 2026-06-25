#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "compiler.h"
#include "parser.h"

struct CompilerState state;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("%s <source.c8> <output.ch8>\n", argv[0]);
        return 1;
    }

    FILE* src = fopen(argv[1], "r");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    printf("\033[1;36mCompiling \033[0m\033[1;37m%s...\033[0m\n", argv[1]);

    clock_t start_time = clock();

    state.pass = 1;
    state.current_line = 1;
    state.pc = ROM_START_ADDRESS;
    state.label_count = 0;
    state.token_count = 0;
    memset(state.rom, 0, MAX_ROM_SIZE);
    
    parse_source(src);

    rewind(src);
    state.pass = 2;
    state.current_line = 1;
    state.pc = ROM_START_ADDRESS;
    state.token_count = 0;
    memset(state.rom, 0, MAX_ROM_SIZE);

    parse_source(src);
    fclose(src);

    FILE* out = fopen(argv[2], "wb");
    if (!out) {
        perror("Error creating output file");
        return 1;
    }

    uint16_t bytes_written = state.pc - ROM_START_ADDRESS;
    fwrite(state.rom, 1, bytes_written, out);
    fclose(out);

    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\033[1;32mSuccess! \033[0m\033[1;37m%d tokens processed.\n%d bytes written to %s\033[0m\n", state.token_count, bytes_written, argv[2]);
    printf("\033[1;33mCompilation time: %.4f seconds\033[0m\n", time_spent);

    return 0;
}
