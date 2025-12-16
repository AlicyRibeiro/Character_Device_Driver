# Character_Device_Driver - Driver de Dispositivo de Caractere

Este diretório contém a implementação do **driver de dispositivo de caractere** baseado na seção **5.3.2** do material *Técnicas de Programação para Sistemas Embarcados II*. 

Ele apresenta os conceitos e etapas necessárias para criar um **driver de caractere** no Linux, registrando o driver, criando a classe e o device node, e implementando funções para controle do dispositivo como `open`, `release`, `read`, `write`, e `ioctl`.

---

##  Estrutura dos Arquivos

* meu_driver_char/
* ├── Makefile        
* ├── meu_driver.c       
* └── meu_driver.h

---

##  Funcionalidades do Módulo

###  Inicialização e Finalização

O driver imprime mensagens no log ao ser carregado e removido. As funções `module_init` e `module_exit` são usadas para inicializar e finalizar o módulo, respectivamente.

- `module_init(meu_driver_init)`
- `module_exit(meu_driver_exit)`
- `printk(KERN_INFO "...")`

---

###  Registrando o Driver

O driver é registrado utilizando a função `alloc_chrdev_region`, e o dispositivo é associado ao driver com um número de **major** e **minor**.

---

###  Criando a Classe do Dispositivo

Usamos a função `class_create` para criar uma classe no **sysfs**, e a função `class_destroy` para removê-la durante a finalização.

---

###  Criando o Device Node

A função `device_create` cria o **device node** no diretório `/dev`, e o driver mapeia as funções de leitura e escrita para operações específicas do dispositivo.

---

###  Controlando o Acesso ao Dispositivo

Usando a variável global `is_open`, controlamos se o dispositivo está aberto ou não. Isso é feito nas funções `my_open` e `my_close` associadas aos métodos do Virtual File System (VFS):

- `open`
- `release`
- `read`
- `write`
- `ioctl`

---

##  Como Compilar

Dentro da pasta `meu_driver_char/` execute:

```bash
make
```


Isso gera o arquivo:

```bash
meu_driver.ko
```
---

## Como carregar o módulo

```bash
sudo insmod meu_driver.ko
```
Verifique as mensagens:

```bash
dmesg -w
```

---
## Como remover o módulo

```bash
sudo rmmod meu_driver
```

⚠️ Sempre remova o módulo antes de recompilar ou carregar novamente.

## Logs úteis

Para acompanhar as mensagens do driver:

```bash
dmesg -w
```

Ou:

```bash
tail -f /var/log/syslog
```
##  Funções Implementadas

### Abertura e Fechamento
- `my_open()`
- `my_close()`

### Leitura e Escrita
- `my_read()`
- `my_write()`

### Controle de Dispositivo
- `my_ioctl()`

---

##  Referências

- **LDD3 — Linux Device Drivers**  
  https://lwn.net/Kernel/LDD3/

- **Sysplay Linux Drivers Book**  
  https://sysplay.github.io/books/LinuxDrivers/book/

- **Sysplay Drivers Documentation**  
  https://sysplay.in/index.php?pagefile=linux_drivers

---

## Ambiente de Desenvolvimento e Testes

Este módulo foi desenvolvido e testado em uma **máquina virtual Linux**, garantindo um ambiente seguro para compilação e carregamento de módulos de kernel.
