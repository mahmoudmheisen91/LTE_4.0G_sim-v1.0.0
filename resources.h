/*
 * resources.h
 *
 *  Created on: Jan 7, 2015
 *      Author: redapple
 */
#ifndef RESOURCES_H_
#define RESOURCES_H_

	// Define Constants::
	#define TRUE 		1
	#define FALSE 		0

	// type definition:


	// Functions Prototypes:
	int init(void);
	Sound read_sound_file(char* dir);
    void catch_signal(int sig);
    void wait_for_ctrl_c(void);
    void plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title);


#endif /* RESOURCES_H_ */

