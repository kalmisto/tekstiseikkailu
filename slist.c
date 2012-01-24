#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "slist.h"

struct node *head = NULL;

struct node *
gethead(void)
{
	return head;
}

void
insert_begining(char *kannossa)
{
	struct node *tmp;

        tmp = malloc(sizeof(struct node));
        if (tmp == NULL) {
            printf("Error! memory is not available\n");
            exit(0);
        }
        memset(tmp, 0, sizeof(struct node));
        memcpy(&tmp->mukana, kannossa, sizeof(char));
        tmp->next = NULL;

	if (head == NULL) {
	        head = tmp;
	} else {
	        tmp->next = head;
		head = tmp;
	}
}

void
remove_begining(void)
{
	if (head != NULL) {
		struct node *tmp;

		tmp = head;
		free(head);
		head = tmp->next;
		tmp = NULL;
	}
}

void
inventaario(void)
{
	struct node *tmp;

	tmp = head;
	fprintf(stdout, "Sinulla on mukana:\n");

	do {
		printf("%s\n", tmp->mukana);
		tmp = tmp->next;
	} while (tmp != NULL);
}

/*void
main(int argc, const char *argv[])
{
	struct sana_st	 spari1, spari2, spari3;

	strncpy(spari1.eng, "house", WORDLEN);
	strncpy(spari1.fin, "talo", WORDLEN);
	strncpy(spari2.eng, "cat", WORDLEN);
	strncpy(spari2.fin, "kissa", WORDLEN);
	strncpy(spari3.eng, "dog", WORDLEN);
	strncpy(spari3.fin, "koira", WORDLEN);

	insert_begining(&spari1);
	insert_begining(&spari2);
	insert_begining(&spari3);

	print_linked_list();

	printf("\n== Poisto\n");
	remove_begining();
	print_linked_list();

}
*/
