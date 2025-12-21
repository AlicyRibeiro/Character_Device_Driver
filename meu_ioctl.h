
#ifndef MEU_IOCTL_H
#define MEU_IOCTL_H

#include <linux/ioctl.h>

typedef struct rtc_info {
    int horas;
    int minutos;
    int segundos;
} rtc_info_t;

/* Defina aqui o número mágico do IOCTL */
//#define MEU_IOCTL_MAGIC 'k'

/* Comandos IOCTL */
//#define IOCTL_LER_RTC   _IOR(MEU_IOCTL_MAGIC, 1, rtc_info_t)


#define MEU_IOCTL_MAGIC 'G'

#define IOCTL_LER_RTC      _IOR(MEU_IOCTL_MAGIC, 0, struct rtc_info *)
#define IOCTL_ZERAR_BUFFER _IO(MEU_IOCTL_MAGIC, 1)
#define IOCTL_SET_DEBUG    _IOW(MEU_IOCTL_MAGIC, 2, int)

#endif
