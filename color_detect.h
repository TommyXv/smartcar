#ifndef COLOR_DETECT_H
#define COLOR_DETECT_H

void color_init();
void color_T0interrupt();
void color_INT0interrupt();
void color_calibrate();
int color_printf(colors);
void color_shutdown();
int color_count1();
enum colors{
  red = 1,
  green,
  blue
}colors;

#endif