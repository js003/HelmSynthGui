// PFT
// color blocks for artist eye selection feedback

#ifndef COLORBLOCK_SECTION_H_
#define COLORBLOCK_SECTION_H_

#include "JuceHeader.h"
#include "memory.h"
#include "open_gl_peak_meter.h"

#include "synth_section.h"

#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>

#define BUFSIZE 8
#define PORT 8899


class ColorBlockSection : public SynthSection , public Timer {
  public:
    ColorBlockSection(String name);
    ~ColorBlockSection();

    void timerCallback();
    static void signal_callback_handler(int signum);

    void paint (Graphics& g);
  private:
    int c = 0;
    static volatile int block_c;
    static int fd;  // socket
    static struct sockaddr_in myaddr;  //our address
    static struct sockaddr_in remaddr;  //remote address
    static socklen_t addrlen;  //length of addresses

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorBlockSection)
};

#endif  // COLORBLOCK_SECTION_H_
