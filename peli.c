#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <bsd/stdlib.h>

#include "peli.h"
#include "slist.h"

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
			fprintf(stdout, "Et voi liikkua seinien läpi!\n");
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
	int ovi = 0;
	struct point kohde;
	kohde.y = p->y;
	kohde.x = p->x;

	if ((strncasecmp("kp", siirto, 2) == 0)) {
		rintamasuunta = 'p';
		katso(&kohde, &ovi);
		return 0;
	}
	else if ((strncasecmp("ki", siirto, 2) == 0)) {
		rintamasuunta = 'i';
		katso(&kohde, &ovi);
		return 0;
	}
	else if ((strncasecmp("ke", siirto, 2) == 0)) {
		rintamasuunta = 'e';
		katso(&kohde, &ovi);
		return 0;
	}
	else if ((strncasecmp("kl", siirto, 2) == 0)) {
		rintamasuunta = 'l';
		katso(&kohde, &ovi);
		return 0;
	}

	switch (siirto[0]) {
	case 'p':
		rintamasuunta = 'p';
		if (onko_siirto_laillinen(p->x, p->y - 4, p) == -1)
			return -1;
		p->y = p->y - 4;
		fprintf(stdout, "\n");
		break;
	case 'e':
		rintamasuunta = 'e';
		if (onko_siirto_laillinen(p->x, p->y + 4, p) == -1)
			return -1;
		p->y = p->y + 4;
		break;
	case 'i':
		rintamasuunta = 'i';
		if (onko_siirto_laillinen(p->x + 4, p->y, p) == -1)
			return -1;
		p->x = p->x + 4;
		break;
	case 'l':
		rintamasuunta = 'l';
		if (onko_siirto_laillinen(p->x - 4, p->y, p) == -1)
			return -1;
		p->x = p->x - 4;
		break;
	case 'o':
		ota(siirto, p);
		break;
	case 'a':
		aseta(&kohde);
		break;
	case 'm':
		inventaario();
		break;
	case 'k':
		katso(&kohde, &ovi);
		break;
	case 't':
		testi();
		break;
	case 'h':
		help();
	}
	return 0;
}

/*void
testi(piste)
{
	siirto(
}*/
void
aseta(struct point *p)
{
	char merkki = 'O';
	poista_node_idx(merkki);
}
void
ota(char *siirto, struct point *p)
{
	switch (rintamasuunta) {
	case 'p':
		toteuta_ota(&maailma[p->y - 1][p->x]);
		break;
	case 'e':
		toteuta_ota(&maailma[p->y + 1][p->x]);
		break;
	case 'l':
		toteuta_ota(&maailma[p->y][p->x - 1]);
		break;
	case 'i':
		toteuta_ota(&maailma[p->y][p->x + 1]);
		break;
	}
}

void
toteuta_ota(char *m)
{
	if (*m == ' ') {
		fprintf(stdout, "Et voi ottaa tyhjää!\n");
	} else {
		insert_begining(m);
		fprintf(stdout, "Otit %c:n\n", *m);
		*m = ' ';
	}
}

void
katso(struct point *kohde, int *ovi)
{
	switch (rintamasuunta) {
	case 'p':
		kohde->y = kohde->y - 1;
		fprintf(stdout, "Katsot pohjoiseen, näet");
		if (maailma[kohde->y - 1][kohde->x] == 'o') {
		*ovi = 1;
		}
		break;
	case 'e':
		kohde->y = kohde->y + 1;
		fprintf(stdout, "Katsot etelään, näet");
		if (maailma[kohde->y + 1][kohde->x] == 'o') {
			*ovi = 1;
		}
		break;
	case 'i':
		kohde->x = kohde->x + 1;
		fprintf(stdout, "Katsot itään, näet");
		if (maailma[kohde->y][kohde->x + 1] == 'o') {
			*ovi = 1;
		}
		break;
	case 'l':
		kohde->x = kohde->x - 1;
		fprintf(stdout, "Katsot länteen, näet");
		if (maailma[kohde->y][kohde->x - 1] == 'o') {
			*ovi = 1;
		}
		break;
	}
		if (maailma[kohde->y][kohde->x] == ' ') {
			fprintf(stdout, " seinän");
		} else {
			fprintf(stdout, " %c:n", maailma[kohde->y][kohde->x]);
			}
		if (*ovi == 1) {
			fprintf(stdout, " ja oven.\n");
		} else {
			fprintf(stdout, ".\n");
		}
}


/* Palauttaa 0, mikäli siirto on laillinen */
int
onko_siirto_laillinen(int x, int y, struct point *nykykohta)
{
	if ((x < 2 || x > KOKOX) || (y < 2 || y > KOKOY)) {
		return -1;
	} else if (maailma[(y + nykykohta->y)/2][(x + nykykohta->x)/2] == '#') {
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
