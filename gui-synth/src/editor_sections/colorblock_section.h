// PFT
// color blocks for artist eye selection feedback

#ifndef COLORBLOCK_SECTION_H_
#define COLORBLOCK_SECTION_H_

#include "JuceHeader.h"
#include "memory.h"
//#include "open_gl_wave_viewer.h"
#include "open_gl_peak_meter.h"

#include "synth_section.h"

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 2048
#define PORT 8899


class ColorBlockSection : public SynthSection , public Timer {
  public:
    ColorBlockSection(String name);
    ~ColorBlockSection();

    void timerCallback();
    //void paintBackground(Graphics& g) override;
    //void resized() override;
    //void reset() override;

    void paint (Graphics& g);
  private:
    int c = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColorBlockSection)
};


#endif  // COLORBLOCK_SECTION_H_
