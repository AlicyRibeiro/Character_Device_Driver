/*
 * =====================================================================================
 *
 *       Filename: meu_ioctl.h
 *
 *
 *        Version:  1.0
 *        Created:  2025
 *       Revision:  none
 *
 *         Author:  Ana Alicy Ribeiro
 *        Contact:  github.com/<AlicyRibeiro>
 *   Organization:  Universidade Federal do Ceará - Campus Quixadá
 *
 *   GitHub Repo:  Character_Device_Driver 
 *
 *
 *
 * =====================================================================================
 */


#ifndef MEU_IOCTL_H
#define MEU_IOCTL_H

#include <linux/ioctl.h>

typedef struct rtc_info {
    int horas;
    int minutos;
    int segundos;
} rtc_info_t;


#define MEU_IOCTL_MAGIC 'G'

#define IOCTL_LER_RTC      _IOR(MEU_IOCTL_MAGIC, 0, struct rtc_info *)
#define IOCTL_ZERAR_BUFFER _IO(MEU_IOCTL_MAGIC, 1)
#define IOCTL_SET_DEBUG    _IOW(MEU_IOCTL_MAGIC, 2, int)

#endif
