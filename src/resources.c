/*-------------------------------------------------------------------------*/
/**
  @file     resources.c
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    Resource file for LTE simulator

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
#include "resources.h"

// Print Heading:
int init(void) {

	printf("---------------------------------\n");
	printf("PROJECT : LTE SIMULATOR\n");
	printf("AUTHOR  : MAHMOUD MHEISEN\n");
	printf("COURSE  : Undergraduate Project\n");
	printf("---------------------------------\n");

	return SUCCESS;
}

// Empty signal handler:
void catch_signal(int sig) {
}

// Catch signal CTRL-C:
void wait_for_ctrl_c(void) {
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);
    pause();
}

int nbits_number(int num) {
    int nbits = 1;

    nbits = log10(num+1)/log10(2) + 1;

    return nbits;
}
