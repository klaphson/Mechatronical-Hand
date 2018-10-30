#ifndef _MAESTRO_
#define _MAESTRO_
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 
#ifdef _WIN32
#define O_NOCTTY 0
#else
#include <termios.h>
#endif


class Maestro{
	
int fd;
bool servos;

public:

Maestro(int fd);
int maestroGetPosition(unsigned char channel);
int maestroSetTarget(unsigned char channel, unsigned short target);
bool returnServos();
void startServos();

};

#endif
