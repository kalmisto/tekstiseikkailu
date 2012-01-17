#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
// #include "huoneet.h"

#define KOKOX 9
#define KOKOY 9



struct point {
	int x;
	int y;
};

char rintamasuunta;


char maailma[9][9] = { {'#','#','#','#','#','#','#','#','#'},
		       {'#',' ','A',' ','#',' ','E',' ','#'},
		       {'#','D',' ','B','o','H',' ','F','#'},
		       {'#',' ','C',' ','#',' ','G',' ','#'},
		       {'#','#','#','#','#','#','o','#','#'},
		       {'#',' ','I',' ','#',' ','M',' ','#'},
		       {'#','L',' ','J','o','P',' ','N','#'},
		       {'#',' ','K',' ','#',' ','O',' ','#'},
		       {'#','#','#','#','#','#','#','#','#'}};

int siirra(char *, struct point *);
int onko_siirto_laillinen(int, int);
void tulosta_maailma(void);
void cls(void);
void katso(struct point *, int *);


int
main(int argc, const char *argv[])
{
	struct point nykykohta;
	struct point vanhakohta;
	char siirto_input[128];

	maailma[2][2] = 'X';
	tulosta_maailma();
	nykykohta.x = 2;
	nykykohta.y = 2;
	rintamasuunta = 'p';

	fprintf(stdout, "\nAnna komento");
	fprintf(stdout, "> ");


	while (fgets(siirto_input, 128, stdin)) {
/*		cls(); */
		int paluu;
		vanhakohta = nykykohta;
		maailma[nykykohta.y][nykykohta.x] = ' ';
		if (siirto_input[0] == 'q')
			break;

		paluu = siirra(siirto_input, &nykykohta);

		if ( paluu == -1) {
			maailma[nykykohta.y][nykykohta.x] = 'X';
			tulosta_maailma();
		} else {
			maailma[nykykohta.y][nykykohta.x] = 'X';
			tulosta_maailma();
		}
		fprintf(stdout, "\nAnna komento");
		fprintf(stdout, "> ");
	}

	return 0;
}

void
help(void)
{
	fprintf(stdout, "\nPelin komennot: \n");
	fprintf(stdout, "Liikkuminen:%-10s(p)ohjoinen, (i)tä, (e)telä, (l)änsi.\n", "");
	fprintf(stdout, "Katso:%-16sk[ilmansuunta], (esim. kp = katso pohjoiseen)\n", "");
	fprintf(stdout, "Ota/irroita:%-10so\n", "");
	fprintf(stdout, "Aseta/kiinnitä/pane:%-2sa\n", "");
	fprintf(stdout, "Ohjeet/komennot:%-6sh\n","");
	fprintf(stdout, "Lopeta peli:%-10sq\n\n", "");
	fprintf(stdout, "\n");
}

void
cls(void)
{
	printf("%c[2J",27);
}

int
siirra(char *siirto, struct point *p)
{
	if ((strncasecmp("kp", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot pohjoiseen, näet %c:n\n", maailma[p->y - 1][p->x]);
		rintamasuunta = 'p';
	}
	else if ((strncasecmp("ki", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot itään, näet %c:n\n", maailma[p->y][p->x + 1]);
		rintamasuunta = 'i';
	}
	else if ((strncasecmp("ke", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot etelään, näet %c:n\n", maailma[p->y + 1][p->x]);
	}
	else if ((strncasecmp("kl", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot länteen, näet %c:n\n", maailma[p->y][p->x - 1]);
	}
	else if ((strncasecmp("kp", siirto, 2) == 0)) {
		cls();
	}
	else if ((strncasecmp("kl", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot länteen, näet %c:n\n", maailma[p->y][p->x - 1]);
	}
	else if ((strncasecmp("kl", siirto, 2) == 0)) {
		fprintf(stdout, "Katsot länteen, näet %c:n\n", maailma[p->y][p->x - 1]);
	}


	switch (siirto[0]) {
	int ovi = 0;
	struct point kohde;
	case 'p':
		if (onko_siirto_laillinen(p->x, p->y - 4) == -1)
			return -1;
		p->y = p->y - 4;
		break;
	case 'e':
		if (onko_siirto_laillinen(p->x, p->y + 4) == -1)
			return -1;
		p->y = p->y + 4;
		break;
	case 'i':
		if (onko_siirto_laillinen(p->x + 4, p->y) == -1)
			return -1;
		p->x = p->x + 4;
		break;
	case 'l':
		if (onko_siirto_laillinen(p->x - 4, p->y) == -1)
			return -1;
		p->x = p->x - 4;
		break;
	case 'k':
		kohde.y = p->y;
		kohde.x = p->x;
		katso(&kohde, &ovi);
		fprintf(stdout, "Näet %c:n", maailma[kohde.y][kohde.x]);
		if (ovi == 1) {
			fprintf(stdout, "ja oven.\n");
		} else {
			fprintf(stdout, ".\n");
		}
		break;
	case 'h':
		help();
	}
	return 0;
}

void
katso(struct point *kohde, int *ovi)
{
	switch (rintamasuunta) {
	case 'p':
		kohde->y = kohde->y - 1;
		if (maailma[kohde->y - 1][kohde->x] == 'o') {
			*ovi = 1;
		}
		break;
	case 'e':
		kohde->y = kohde->y + 1;
		if (maailma[kohde->y + 1][kohde->x] == 'o') {
			*ovi = 1;
		}
		break;
	case 'i':
		kohde->x = kohde->x + 1;
		if (maailma[kohde->y][kohde->x + 1] == 'o') {
			*ovi = 1;
		}
		break;
	case 'l':
		kohde->x = kohde->x - 1;
		if (maailma[kohde->y - 1][kohde->x] == 'o') {
			*ovi = 1;
		}
		break;
	}
}


/* Palauttaa 0, mikäli siirto on laillinen */
int
onko_siirto_laillinen(int x, int y)
{
	if ((x < 2 || x > KOKOX) || (y < 2 || y > KOKOY)) {
		return -1;
	}
	return 0;
}

void
tulosta_maailma() {
	int i = 0;
	int j = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			fprintf(stdout, "%c", maailma[i][j]);
		}
		fprintf(stdout, "\n");
	}
}
