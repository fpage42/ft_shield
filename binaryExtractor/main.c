#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *start = "unsigned char octets[] = {";
    char *end = "};\n";
    FILE *fp;
    FILE *extract;
    int c;
    int first = 1;

    fp = fopen(argv[1], "rb");
    extract = fopen(argv[2], "wb");
    if (fp == NULL || extract == NULL) {
        if (fp != NULL)
            fclose(fp);
        if (extract != NULL)
            fclose(extract);
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    fwrite(start, strlen(start), 1, extract);
    while ((c = fgetc(fp)) != EOF) {
        if (!first) {
            fprintf(extract, ", ");
        }
        fprintf(extract, "0x%0x", c);
        first = 0;
    }
    fwrite(end, strlen(end), 1, extract);
    fclose(fp);
    fclose(extract);
    return 0;
}
