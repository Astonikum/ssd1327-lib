#include <MadDisplay.h>
#include <MadGrayOLED.h>
Adafruit_SSD1327 driver(128,128,&Wire,-1);
mad::SSD1327 adapter(driver);
mad::Display<mad::SSD1327> display(adapter);
mad::VerticalLayout root;
mad::Page page(root,mad::Color::Black);
mad::Label title("MAD DISPLAY",mad::LabelStyle(mad::Color::White,1));
void setup() {
  if (!display.begin()) while (true) { delay(100); }
  root.add(title); display.setFps(20);
  display.openPage(display.registerPage(page));
}
void loop() { display.render(micros()); }
