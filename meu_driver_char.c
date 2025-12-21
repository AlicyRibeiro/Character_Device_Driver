#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include "meu_driver_char.h"
#include "meu_ioctl.h"

/* Variáveis globais */
static dev_t device_number;               // major/minor
static struct class *device_class;        // classe em /sys/class
static struct cdev meu_device;            // estrutura do dispositivo


/* ---------------------------------------- */
/*                   BUFFER   	            */
/* ---------------------------------------- */
#define BUFFER_SIZE 100
static char device_buffer[BUFFER_SIZE] = {0};

/*
struct rtc_info {
    int hora;
    int minuto;
    int segundo;
};
*/


/* Prototipos */
static int my_open(struct inode *inode, struct file *file);
static int my_close(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char *buf, size_t len, loff_t *off);
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Operações do driver */
static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write,
    .unlocked_ioctl = my_ioctl
};


static struct rtc_info info_rtc;

/* ---------------------------------------- */
/*             FUNÇÕES DO DRIVER            */
/* ---------------------------------------- */

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[meu_driver_char] Dispositivo aberto\n");
    return 0;
}

static int my_close(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[meu_driver_char] Dispositivo fechado\n");
    return 0;
}

static ssize_t my_read(struct file *f, char *buf, size_t len, loff_t *off)
{
    size_t bytes_lidos = 0;

    if (!buf)
        return -ENOMEM;

    /* No exemplo, o RTC devolve 3 bytes — você pode adaptar */
    if(len != 3)
        return -EINVAL;

    /* Aqui futuramente você chamará o ler_rtc() */
    // if (ler_rtc(&device_buffer[0], &device_buffer[1], &device_buffer[2]))
    //     return -EBUSY;

    /* Envia dados do kernel → user space */
    if (copy_to_user(buf, device_buffer, len))
        return -ENOMEM;

    bytes_lidos = len;

    printk(KERN_INFO "Leu o arquivo do dispositivo\n");
    return bytes_lidos;
}


static ssize_t my_write(struct file *f, const char *buf, size_t len, loff_t *off)
{
    if (len >= BUFFER_SIZE)
        return -EINVAL;

    /* Copia dados do user → kernel */
    if (copy_from_user(device_buffer, buf, len))
        return -ENOMEM;

    /* Garante terminação */
    device_buffer[len] = 0;
    device_buffer[BUFFER_SIZE - 1] = 0;

    printk(KERN_INFO "Escreveu no dispositivo: %s\n", device_buffer);
    return len;
}



static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    printk(KERN_INFO "[meu_driver_char] IOCTL chamado: cmd=%u\n", cmd);

    switch (cmd)
    {
   
        case IOCTL_LER_RTC:
            printk(KERN_INFO "IOCTL: lendo RTC\n");

            if (copy_to_user((struct rtc_info *)arg, &info_rtc, sizeof(info_rtc)))
                return -EFAULT;

            break;

        case IOCTL_ZERAR_BUFFER:
            printk(KERN_INFO "IOCTL: zerando o buffer\n");
            memset(device_buffer, 0, BUFFER_SIZE);
            break;

        case IOCTL_SET_DEBUG:
        {
            int debug_state;

            if (copy_from_user(&debug_state, (int *)arg, sizeof(int)))
                return -EFAULT;

            printk(KERN_INFO "IOCTL: set debug para %d\n", debug_state);
            break;
        }

        default:
            return -EINVAL;
    }

    return 0;
}


/* ---------------------------------------- */
/*        INIT E EXIT DO MÓDULO             */
/* ---------------------------------------- */

static int __init meu_driver_init(void)
{
    printk(KERN_INFO "Driver char iniciado!\n");

    // 1. Alocar major/minor
    if (alloc_chrdev_region(&device_number, FIRST_MINOR, N_DEVICES, DRIVER_NAME) < 0)
        return -1;

    // 2. Criar classe — novo formato no kernel 6.8+
    device_class = class_create(CLASS_NAME);
    if (IS_ERR(device_class))
    {
        printk(KERN_ERR "ERRO: class_create falhou\n");
        unregister_chrdev_region(device_number, N_DEVICES);
        return -1;
    }

    // 3. Criar o device node
    if (IS_ERR(device_create(device_class, NULL, device_number, NULL, DEVICE_NAME)))
    {
        printk(KERN_ERR "ERRO: device_create falhou\n");
        class_destroy(device_class);
        unregister_chrdev_region(device_number, N_DEVICES);
        return -1;
    }

    // 4. Registrar operações
    cdev_init(&meu_device, &fops);
    if (cdev_add(&meu_device, device_number, 1) < 0)
    {
        device_destroy(device_class, device_number);
        class_destroy(device_class);
        unregister_chrdev_region(device_number, N_DEVICES);
        return -1;
    }

    return 0;
}

static void __exit meu_driver_exit(void)
{
    cdev_del(&meu_device);
    device_destroy(device_class, device_number);
    class_destroy(device_class);
    unregister_chrdev_region(device_number, N_DEVICES);

    printk(KERN_INFO "Driver char finalizado!\n");
}

module_init(meu_driver_init);
module_exit(meu_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ana Alicy");
MODULE_DESCRIPTION("Character Device Driver");
