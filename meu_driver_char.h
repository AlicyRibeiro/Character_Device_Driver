/*

#ifndef MEU_DRIVER_H
#define MEU_DRIVER_H

#include <linux/ioctl.h>

#define MY_TIMEOUT 1000
#define DRIVER_NAME "meu_driver"
#define DEVICE_NAME "meu_driver"

// Portas de acesso ao CMOS/RTC
#define CMOS_ADDRESS_PORT 0x70
#define CMOS_DATA_PORT    0x71

// Registradores do RTC
#define RTC_HOUR_REG 0x04
#define RTC_MIN_REG  0x02
#define RTC_SEC_REG  0x00

#endif
*/

#ifndef MEU_DRIVER_H
#define MEU_DRIVER_H

#define N_DEVICES     1
#define FIRST_MINOR   0

#define DRIVER_NAME   "meu_driver_char"
#define CLASS_NAME    "minha_classe"
#define DEVICE_NAME   "meu_dispositivo"

#endif

