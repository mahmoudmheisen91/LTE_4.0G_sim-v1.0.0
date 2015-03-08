/*
 * resources.h
 *
 *  Created on: Mar 7, 2015
 *      Author: redapple
 */
#ifndef RESOURCES_H_
#define RESOURCES_H_

	// Define Constants::
	#define TRUE 		1
	#define FALSE 		0

	// type definition:
	typedef int bool;
	typedef struct _Sound {
	    double* data;
	    double Fs;
	    int nbits;
	}Sound;

	// Functions Prototypes:
	int init(void);
	Sound read_sound_file(char* dir);


#endif /* RESOURCES_H_ */

