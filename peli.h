#ifndef _PELI_H
#define _PELI_H

#define KOKOX 9
#define KOKOY 9
#define WORDLEN 128

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
int onko_siirto_laillinen(int, int, struct point *);
void tulosta_maailma(void);
void cls(void);
void katso(struct point *, int *);
void ota(char *, struct point *);
void toteuta_ota(char *);

#endif
