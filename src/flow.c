#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "flow.h"

struct grid load(FILE* f){ 
	int c, i;
	struct grid out;
	
	//We get the width here
	char width_s[11];
	i = 0;
	while((c=fgetc(f)) != EOF){
		if( c<'0' || c>'9' || i>9){
			if(c != '\n')
				fprintf(stderr, "Warning: Misformatted map file");
			break;
		}
		width_s[i] = c;
		i++;
	}
	
	width_s[i] = '\0';
	out.width = atoi(width_s);
	
	//We get the height here - This is exactly the same as the width getter, except it gets the height
	char height_s[11];
	i = 0;
	while((c=fgetc(f)) != EOF){
		if( c<'0' || c>'9' || i>9){
			if(c != '\n')
				fprintf(stderr, "Warning: Misformatted map file");
			break;
		}
		height_s[i] = c;
		i++;
	}
	
	height_s[i] = '\0';
	out.height = atoi(height_s);

	//Init the points
	
	out.map = (struct point**) malloc(sizeof(struct point*) * out.width);
	for(int x = 0; x < out.width; x++){
		out.map[x] = (struct point*) calloc(out.height, sizeof(struct point));
	}

	//We get each point here
	c = 0;
	char group = 1;
	int part = 0;
	while (c != EOF) {
		//Get x
		char x_s[11];
		i = 0;
		while((c=fgetc(f)) != EOF){
			if (c<'0' || c>'9' || i>9){
				if (c!=',')
					fprintf(stderr, "Warning: Misformatted map file");
				break;
			}
			x_s[i] = c;
			i++;
		}
		x_s[i] = '\0';

		//Get y
		char y_s[11];
		i = 0;
		while((c=fgetc(f)) != EOF){
			if (c<'0' || c>'9' || i>0){
				if(c!='\n')
					fprintf(stderr, "Warning: Misformatted map file");
				break;
			}
			y_s[i] = c;
			i++;
		}
		y_s[i]='\0';

		//Put it into grid
		if (c == EOF)
			break; //Don't put it in the grid if we're at EOF - bug check:(
		struct point p;
		p.group = group;
		p.is_node = true;
		out.map[atoi(x_s)][atoi(y_s)] = p;

		if(part == 0){
			part++;
		} else {
			part = 0;
			group++;
		}
	} 
	

	return out;
}

/*
 * This is a debug function - Don't actually use it
 */
void grid_info(struct grid g){
	printf(
			"Height: %d\n"
			"Width:  %d\n",
			g.height, g.width
	      );

	for (int y = 0; y < g.height; y++){
		for (int x = 0; x < g.width; x++) {
			printf("%d ", g.map[x][y].group);
		}
		printf("\n");
	}
}
