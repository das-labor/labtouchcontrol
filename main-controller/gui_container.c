//
// This file is part of the gui-library for microcontrollers 
// by Peter Fuhrmann.
//

#include <stdlib.h>
#include <stdint.h>
#include "dc_com.h"
#include "gui.h"
#include "list.h"


void gui_container_add (gui_container_t * c, gui_element_t * e) {
	list_append(&c->childs, e);
	
	if (c->orientation == ORIENTATION_HORIZONTAL) {
		e->box.x = c->box.x + c->pos;
		e->box.y = c->box.y;
		c->pos += e->box.w-1;
	} else {
		e->box.x = c->box.x;
		e->box.y = c->box.y + c->pos;
		c->pos += e->box.h-1;
	}
	
	if (c->on_screen) {
		e->draw(e,0);
		e->set_on_screen(e,1);
		
	}
}

static gui_element_t * child_at (gui_container_t * s,uint16_t x, uint16_t y){
	gui_element_t * child;
	list_foreach_begin(&s->childs);
	
	while ( (child = list_foreach(&s->childs)) != 0 ) {
		if(rectangle_contains(child->box, x, y)){
			return child;
		}
	}
	
	return 0;
	
}

void gui_container_draw (gui_element_t * self, uint8_t redraw) {
	gui_container_t * s = (gui_container_t*)self;
	
	if (s->frame_size & 0x80) {
		g_draw_rectangle(&s->box);
	}
	
	gui_element_t * child;
	list_foreach_begin(&s->childs);
	
	while ( (child = list_foreach(&s->childs)) != 0 ) {
		child->draw(child, 0);
	}

}

void gui_container_set_on_screen (gui_element_t *self, uint8_t state) {

}

void gui_container_touch_handler (gui_element_t *self, touch_event_t t) {
	gui_container_t * s = (gui_container_t*)self;
	
	gui_element_t * child;
	if( (child = child_at(s, t.x, t.y)) != 0){
		child->touch_handler(child, t);
	}
}


//constructor
gui_container_t * new_gui_container(){
	gui_container_t * c = malloc(sizeof(gui_container_t));
	c->draw = gui_container_draw;
	c->set_on_screen = gui_container_set_on_screen;
	c->touch_handler = gui_container_touch_handler;
	c->box = (rectangle_t){0,0,0,0};
	c->on_screen = 0;
	c->orientation = ORIENTATION_HORIZONTAL;
	c->frame_size = 0;
	init_list(&c->childs);
	c->pos = 0;
	return c;
}
