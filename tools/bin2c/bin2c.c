#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s input output name\n", argv[0]);
        return 1;
    }
    const char *in_path = argv[1];
    const char *out_path = argv[2];
    const char *sym = argv[3];
    FILE *in = fopen(in_path, "rb");
    if (!in) {
        perror("fopen input");
        return 1;
    }
    FILE *out = fopen(out_path, "w");
    if (!out) {
        perror("fopen output");
        fclose(in);
        return 1;
    }
    unsigned char byte;
    size_t count = 0;
    fprintf(out, "unsigned char %s[] = {", sym);
    while (fread(&byte, 1, 1, in) == 1) {
        if (count % 12 == 0)
            fprintf(out, "\n ");
        fprintf(out, "0x%02x,", byte);
        count++;
    }
    fprintf(out, "\n};\nunsigned int size_%s = %zu;\n", sym, count);
    fclose(in);
    fclose(out);
    return 0;
}
