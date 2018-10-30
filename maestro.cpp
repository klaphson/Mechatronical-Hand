#include "maestro.hpp"




Maestro::Maestro(int fd_)
{ 
	fd = fd_;
	servos = false;
#ifdef _WIN32
  _setmode(fd, _O_BINARY);
#else
  struct termios options;
  tcgetattr(fd, &options);
  options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
  options.c_oflag &= ~(ONLCR | OCRNL);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  tcsetattr(fd, TCSANOW, &options);
#endif
}

int Maestro::maestroGetPosition(unsigned char channel)
{
	unsigned char command[] = {0x90, channel};
  if(write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
 
  unsigned char response[2];
  if(read(fd,response,2) != 2)
  {
    perror("error reading");
    return -1;
  }
 
  return response[0] + 256*response[1];
}

int Maestro::maestroSetTarget(unsigned char channel, unsigned short target)
{
	unsigned char command[] = {0x84, channel, (unsigned char)(target & 0x7F), (unsigned char)(target >> 7 & 0x7F)};
  if (write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
  return 0;
}

bool Maestro::returnServos()
{
	return servos;
}

void Maestro::startServos()
{
	servos = true;
}




