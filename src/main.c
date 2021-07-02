#include <stdlib.h>
#include <curses.h>

#include "flow.h"

void grid_info(struct grid); //This is defined in `flow.c`. It should only be used for debug

struct grid g;
char groupSelection = 0;

char point_to_char(int x, int y){
	char group = g.map[x][y].group;
	if(group==0)
		return '.';
	if(g.map[x][y].is_node){ //TODO: Do this better
		return group+'A'-1;
	} else {
		return group+'a'-1;
	}
}

void draw(){
	int orig_y, orig_x;
	getyx(stdscr, orig_y, orig_x);
	for(int y = 0; y<g.height; y++){
		for(int x = 0; x<g.width; x++){
			mvaddch(y, x, point_to_char(x, y));
		}
	}
	move(orig_y, orig_x);
}

int init(char* file){
	FILE *f = fopen(file, "r");
	if(f == NULL){
		fprintf(stderr, "Failed to open file");
		return 0;
	}
	g = load(f);

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

	return 1;
}

void action(){
	int curs_x, curs_y;
	getyx(stdscr, curs_y, curs_x);
	
	struct point current_point = g.map[curs_x][curs_y];
	
	if(current_point.is_node)
		groupSelection = current_point.group;
	else{
		if(current_point.group == 0){
			g.map[curs_x][curs_y].group = groupSelection;
		} else {
			g.map[curs_x][curs_y].group = 0;
		}
	}
}

int loop(){
	int ch;
	int max_y, max_x;
	int curs_y, curs_x;
	int bound_y, bound_x;
	
	getmaxyx(stdscr, max_y, max_x);
	getyx(stdscr, curs_y, curs_x);
	
	bound_y = g.height; bound_x = g.width;

	draw();
	
	switch(ch = getch()){
		case KEY_UP:
			if(curs_y>0)
				move(--curs_y, curs_x);
			else
				beep();
			break;
		case KEY_DOWN:
			if(curs_y<bound_y-1 && curs_y<max_y-1)
				move(++curs_y, curs_x);
			else
				beep();
			break;
		case KEY_LEFT:
			if(curs_x>0)
				move(curs_y, --curs_x);
			else
				beep();
			break;
		case KEY_RIGHT:
			if(curs_x<bound_x-1 && curs_x<max_x-1)
				move(curs_y, ++curs_x);
			else
				beep();
			break;
		case ' ':
			action();
			break;
		case 'q':
			return 0;
			break;
		default:
			beep();
	}

	return 1;
}


int end(){
	if(endwin()==OK)
		return EXIT_SUCCESS;
	else 
		return EXIT_FAILURE;
}

int main(int argc, char** argv){
	(void) argc;
	
	if(!init(argv[1]))
		return EXIT_FAILURE;
	
	while (loop());

	return end();
}


