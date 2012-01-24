#ifndef _SLIST_H_
#define _SLIST_H_

//#include "peli.h"

struct	node {
	char mukana[1];
	struct node *next;
};

void inventaario(void);
void insert_begining(char *);
void remove_begining(void);
#endif /* _SLIST_H_ */
