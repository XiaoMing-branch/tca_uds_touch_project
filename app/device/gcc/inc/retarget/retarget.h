// All credit to Carmine Noviello for this code


#ifndef _RETARGET_H__
#define _RETARGET_H__

#include "TCAE01.h"
#include <sys/stat.h>


void RetargetInit(uint32_t baud);
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);

#endif //#ifndef _RETARGET_H__
