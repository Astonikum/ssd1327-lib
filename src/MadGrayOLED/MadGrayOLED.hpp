#pragma once
#include <Adafruit_SSD1327.h>
#include <MadDisplay/buffer.hpp>
#include <MadDisplay/panels.hpp>

namespace mad {
class SSD1327 final : public PaletteBuffer<128,128,4> {
 public:
  explicit SSD1327(Adafruit_SSD1327& driver) : PaletteBuffer(panelPalette(panelSpec("ssd1327-128x128"))),driver_(driver) {}
  bool begin(uint8_t address=0x3d) { ready_=driver_.width()==128 && driver_.height()==128 && driver_.begin(address); return ready_; }
  void pixel(int16_t x,int16_t y,Color color) override { PaletteBuffer::pixel(x,y,gray(color)); }
  void fillSpan(int16_t x,int16_t y,int16_t length,Color color) override { PaletteBuffer::fillSpan(x,y,length,gray(color)); }
  void clear(Color color=Color::Off) override { PaletteBuffer::clear(gray(color)); }
  void present() override {
    if (!ready_) return;
    for (int16_t y=0;y<128;++y) for (int16_t x=0;x<128;++x)
      driver_.drawPixel(x,y,red(PaletteBuffer::pixel(x,y))/17);
    driver_.display();
  }
  Adafruit_SSD1327& driver() { return driver_; }
 private:
  static Color gray(Color c) {
    const uint8_t v=((uint32_t(red(c))*77+uint32_t(green(c))*150+uint32_t(blue(c))*29+128)/256+8)/17;
    return rgb(v*17,v*17,v*17);
  }
  Adafruit_SSD1327& driver_; bool ready_=false;
};
} // namespace mad
