#include <stdio.h>
#include <stdlib.h>

#define KOKOX 2
#define KOKOY 2

struct point {
	int x;
	int y;
};

int siirto(char suunta, struct point *);
int onko_siirto_laillinen(int, int);
void testi(void);

int
main(int argc, const char *argv[])
{
	struct point nykykohta;
/*	struct point maailma[KOKOX][KOKOY]; */
	char siirto_input;

	nykykohta.x = 0;
	nykykohta.y = 0;

	fprintf(stdout, "\nAnna suunta (olet nyt pisteessä [%d, %d])\n", nykykohta.x, nykykohta.y);
	fprintf(stdout, "> ");


	while (fscanf(stdin, "%s", &siirto_input)) {
		int paluu;
		fprintf(stdout, "Inputtisi on: %s\n", &siirto_input);
		if (siirto_input == 'q')
			break;
		paluu = siirto(siirto_input, &nykykohta);
		fprintf(stdout, "Pisteesi on [%d, %d] (%d)\n", nykykohta.x, nykykohta.y, paluu);

		if ( paluu == -1) {
			fprintf(stdout, "Pisteesi on edelleen [%d, %d]\n", nykykohta.x, nykykohta.y);
		} else {
			fprintf(stdout, "Uusi pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);
		}

		fprintf(stdout, "\nAnna suunta (olet nyt pisteessä [%d, %d])\n", nykykohta.x, nykykohta.y);
		fprintf(stdout, "> ");
	}

	return 0;
}


/* Siirtää (tai ei siirrä) pistettä */
int
siirto(char suunta, struct point *p)
{
	switch (suunta) {
	case 'p':
		if (onko_siirto_laillinen(p->x, p->y - 1) == -1)
			return -1;
		p->y = p->y - 1;
		break;
	case 'e':
		if (onko_siirto_laillinen(p->x, p->y + 1) == -1)
			return -1;
		p->y = p->y + 1;
		break;
	case 'i':
		if (onko_siirto_laillinen(p->x + 1, p->y) == -1)
			return -1;
		p->x = p->x + 1;
		break;
	case 'l':
		if (onko_siirto_laillinen(p->x - 1, p->y) == -1)
			return -1;
		p->x = p->x - 1;
		break;
	}
	return 0;
}

/* Palauttaa 0, mikäli siirto on laillinen */
int
onko_siirto_laillinen(int x, int y)
{
	if (x < 0 || x > KOKOX)
		return -1;
	if (y < 0 || y > KOKOY)
		return -1;
	return 0;
}

void
testi(void)
{
	struct point nykykohta;
/*	struct point maailma[KOKOX][KOKOY]; */
	char siirto_input;

	nykykohta.x = 0;
	nykykohta.y = 0;

	siirto(siirto_input, &nykykohta);
	fprintf(stdout, "Pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);
	siirto_input = 'e';
	siirto(siirto_input, &nykykohta);
	fprintf(stdout, "Pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);
	siirto_input = 'i';
	siirto(siirto_input, &nykykohta);
	fprintf(stdout, "Pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);
	siirto_input = 'p';
	siirto(siirto_input, &nykykohta);
	fprintf(stdout, "Pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);
	siirto_input = 'l';
	siirto(siirto_input, &nykykohta);
	fprintf(stdout, "Pisteesi on [%d, %d]\n", nykykohta.x, nykykohta.y);

}

