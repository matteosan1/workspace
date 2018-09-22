#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/utime.h>

#include "stuff.h"

#define	READ		"rb"
#define	WRITE	"wb"

#define	MAXHUFBIT		8*sizeof(dword)

struct elem
	{
	 long		num;
	 struct nodo	*foglia;
	};

struct lista
	{
	 long		peso;
	 struct nodo	*testa;
	};

struct nodo
	{
	 char		car;
	 struct nodo	*su;
	 struct nodo	*sin;
	 struct nodo	*des;
	};

struct entab
	{
	 char		car;
	 byte		len;
	 dword		cod;
	};

struct header
	{
	 byte		algoritmo;
	 byte		checksum;
	 word		crc;
	 long		lunghezza;
	 long		timestamp;
	};

typedef	struct elem	ELEM;
typedef	struct lista	LISTA;
typedef	struct nodo	NODO;
typedef 	struct entab	ENTAB;
typedef	struct header	HEADER;

NODO *maketree(FILE *, HEADER *);
dword gethufcode(int *, int);
int selectmin(LISTA *, int);
void encode(char *, char *);
void decode(char *, char *);
void usage(void);
void writeheader(HEADER *, NODO *, FILE *);
NODO *readheader(HEADER *, FILE *);
void writetree(NODO *, FILE *);
NODO *readtree(FILE *);
void killtree(NODO *);
void putbit(int, FILE *);
bit getbit(FILE *);
void writehuf(int, FILE *);
int readhuf(NODO *, FILE *);
void flushbit(FILE *);
void putbyte(byte, FILE *);
byte getbyte(FILE *);
void initcrc(void);
word chrcrc(byte);



