// PFT

#include "colorblock_section.h"

#include <GL/gl.h>

#include "colors.h"
#include "fonts.h"
#include "modulation_look_and_feel.h"
#include "text_look_and_feel.h"

#include "helm_common.h"

#include <stdlib.h>

ColorBlockSection::ColorBlockSection(String name) : SynthSection(name) {}
ColorBlockSection::~ColorBlockSection(){}

void ColorBlockSection::paint (Graphics& g)
{
    int offset = rand();
    this->c += offset;
    this->c = this->c % 0x00ffffff;
    startTimerHz(5);

    g.fillAll(Colour(0x80000000 | c));
}

void ColorBlockSection::timerCallback() {
    repaint();
}
