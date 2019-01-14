// PFT

#include "colorblock_section.h"

#include <GL/gl.h>

#include "colors.h"
#include "fonts.h"
#include "modulation_look_and_feel.h"
#include "text_look_and_feel.h"

#include "helm_common.h"

#include <stdlib.h>
#include <unistd.h>

struct sigaction sigaction_;

static void* currentObj;
//sig_atomic_t ColorBlockSection::handler_var = 0;

int ColorBlockSection::fd = 0;  // socket
struct sockaddr_in ColorBlockSection::myaddr;  //our address
struct sockaddr_in ColorBlockSection::remaddr;  //remote address
socklen_t ColorBlockSection::addrlen = sizeof(remaddr);  //length of addresses
volatile int ColorBlockSection::block_c = 0xA000A0;

ColorBlockSection::ColorBlockSection(String name) : SynthSection(name) {
  sigaction_.sa_handler = ColorBlockSection::signal_callback_handler;
  sigemptyset(&sigaction_.sa_mask);

  if(sigaction(SIGIO, &sigaction_,0) < 0) {
    std::cout << "sigaction error, exiting." << std::endl;
    std::cout.flush();
    exit(-1);
  }

  //create a UDP socket
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("cannot create socket\n");
    exit(-1);
  }

  //bind the socket to any valid IP address and a specific port
  memset((char *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(PORT);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
    perror("bind failed");
    exit(-1);
  }

  // https://stackoverflow.com/questions/45373879/why-i-cant-receive-sigpoll-signal-from-ioctl-function
  fcntl(fd, F_SETFL, O_ASYNC);
  fcntl(fd, F_SETOWN, getpid());
  currentObj = this;
  std::cout << "ColorBlockSection constructed" << std::endl;
}

ColorBlockSection::~ColorBlockSection(){}

void ColorBlockSection::paint (Graphics& g)
{
    /*int offset = rand();
    this->c += offset;
    this->c = this->c % 0x00ffffff;*/
    //startTimerHz(20);
/*
    if(handler_var) {
      handler_var = 0;
      std::cout << "Signal Handler was called.." << std::endl;
    }
*/
    //int i = (int)strtol("A000A0", NULL, 16);
    //std::cout << i << std::endl;
    g.fillAll(Colour(0xff000000 | block_c));
}
void ColorBlockSection::timerCallback() {
  /*
    if(handler_var) {
      handler_var = 0;
      std::cout << "Signal Handler was called.." << std::endl;
    }
    //repaint();
    */
}

void ColorBlockSection::signal_callback_handler(int signum) {
    //std::cout << "Signal arrived: " << signum << std::endl;
    //std::cout.flush();
    unsigned char buf[BUFSIZE];
    int recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
    if(recvlen > 0) {
      block_c = (int)strtol((const char*)buf, NULL, 16);
      //block_c = buf[2] << 16 | buf[1] << 8 | buf[0];
    }
    if (((ColorBlockSection*)currentObj) != NULL) {
      ((ColorBlockSection*)currentObj)->repaint();
    }
    //handler_var = 1;

}
