#ifndef _H_DRAW_PIXMAP
#define _H_DRAW_PIXMAP

void g_clear_screen(void);
void lcd_graphics_plot_pixel(unsigned short x, unsigned short y, unsigned char state);
void g_clear(void);
void copy_logo(uint8_t yc, uint8_t xc);

#endif // _H_DRAW_PIXMAP

