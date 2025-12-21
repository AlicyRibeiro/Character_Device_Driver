
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "meu_driver_char.h"
#include "meu_ioctl.h"


int ler_rtc(int *h, int *m, int *s)
{
    *h = 12;
    *m = 34;
    *s = 56;
    return 0;
}


int main() {
    int fd;
    struct rtc_info info;

    fd = open("/dev/meu_dispositivo", O_RDWR);
    if (fd < 0) {
        perror("Erro ao abrir o dispositivo");
        return 1;
    }

    printf("Chamando ioctl...\n");

    if (ioctl(fd, IOCTL_LER_RTC, &info) < 0) {
        perror("Erro no ioctl");
        close(fd);
        return 1;
    }

    printf("Hora lida: %02d:%02d:%02d\n",
           info.horas, info.minutos, info.segundos);

    close(fd);
    return 0;
}
