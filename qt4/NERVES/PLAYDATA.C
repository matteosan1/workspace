#ifndef EXTERN
#define EXTERN extern
#endif
EXTERN enum asc_val {CTRLD=4,TAB=9,CR=13,CTRLS=19,ESC=27,SPACE=32};
EXTERN enum ext_val {F1=59,F2,F3,F4,F5,F6,F7,F8,F9,F10,
		     UP=72,LEFT=75,RIGHT=77,DOWN=80};
EXTERN char playfname[39];	/* filename for playing file */
EXTERN FILE *playfile;		/* file handle for playing file */
EXTERN char filenum[3];		/* file number */
EXTERN int reccnt;		/* record being played */
EXTERN int nrec;		/* number of records in last block */
EXTERN int lastrec;		/* last record of current block */
EXTERN int nblk;		/* number of record blocks allocated */
EXTERN int cblk;		/* current block */
EXTERN int ublk;		/* number of blocks used */
EXTERN int pause;		/* pause in milliseconds */
EXTERN struct recbug {		/* record for one bug recording */
       char Iextname[7];	/* external current name, if changed */
       int Iext;		/* external current, if changed */
       int energy;		/* energy */
       char graphx;		/* graph x pos */
       char graphy1[5];		/* 1st graph y pos */
       char graphy2[5];		/* 2nd graph y pos */
       char footst;		/* foot states */
       char mouthfood;		/* mouth & food states */
       int x;			/* x pos of front of bug */
       int y;			/* y pos of front of bug */
       signed char head[6];	/* points of head */
       signed char body[12];	/* points of body */
       signed char footx[6];	/* foot x's */
       signed char footy[6];	/* foot y's */
       signed char legx[6];	/* leg attachment x's */
       signed char legy[6];	/* leg attachment y's */
       signed char antx[2];	/* antenna x's */
       signed char anty[2];	/* antenna y's */
       signed char antax[2];	/* antenna attachment x's */
       signed char antay[2];	/* antenna attachment y's */
       signed char cercx[2];	/* cercus x's */
       signed char cercy[2];	/* cercus x's */
       signed char cercax[2];	/* cercus attachment x's */
       signed char cercay[2];	/* cercus attachment y's */
       };
EXTERN struct recbug *rp[MAXBLK];/* record block pointer array */
EXTERN struct recbug *rc;	/* current record pointer */
EXTERN struct recgraph {	/* graph structure for recording */
       int gtype;               /* graph types: 0-none, 1-var, 2-gait */
       char gneur[7];           /* graph neuron name */
       int gvar;                /* graph variable: 0-V, 1-F, 2-I */
       int gscale;              /* graph scale */
       } rgr[5];
EXTERN struct recinit {		/* initial data structure for recording */
       int foodr[NFOOD];	/* initial food radius */
       int foodx[NFOOD];	/* initial food x's */
       int foody[NFOOD];	/* initial food y's */
       int nblock;		/* number of blocks */
       int blockx[NBLOCK];	/* block x's */
       int blocky[NBLOCK];	/* block y's */
       } rin;
EXTERN int foodr[3];		/* current food radius */
EXTERN int ofoodr[3];		/* last food radius */
