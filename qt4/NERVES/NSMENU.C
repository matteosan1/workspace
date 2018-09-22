#include "defn.h"
#include "nsdata.c"
#include "proto.h"
#include "lsin.c"
#include "lcos.c"

void nsmenu(void)
 { /* main menu */
  int i,j,k,m,done,msg;
  enum asc_val asc;
  char str[41];
  char *p;
  FILE *file;
  struct neuron *np;
  struct con *cp;
  struct Iint *ip;
  float f;

  msg = FALSE;
display: /* display menu */
  clrscr();
  if (msg)
   {
    gotoxy(1,1);
    cputs("Recording path not found, Press P to change");
    msg = FALSE;
   }
  gotoxy(5,8);
  textattr(WHITE);
  cputs("R");
  textattr(LIGHTGRAY);
  cputs("ead files");
  gotoxy(5,10);
  textattr(WHITE);
  cputs("W");
  textattr(LIGHTGRAY);
  cputs("rite files");
  gotoxy(5,12);
  textattr(WHITE);
  cputs("N");
  textattr(LIGHTGRAY);
  cputs("euron data modification");
  gotoxy(5,14);
  textattr(WHITE);
  cputs("E");
  textattr(LIGHTGRAY);
  cputs("nvironment specification");
  gotoxy(5,16);
  textattr(WHITE);
  cputs("I");
  textattr(LIGHTGRAY);
  cputs("nitialize conditions");
  gotoxy(5,18);
  textattr(WHITE);
  cputs("G");
  textattr(LIGHTGRAY);
  cputs("raph specification");
  gotoxy(5,20);
  textattr(WHITE);
  cputs("P");
  textattr(LIGHTGRAY);
  cputs("ath specification for recording");
  gotoxy(5,22);
  textattr(WHITE);
  cputs("S");
  textattr(LIGHTGRAY);
  cputs("imulate");
  gotoxy(5,24);
  textattr(WHITE);
  cputs("Q");
  textattr(LIGHTGRAY);
  cputs("uit");
  gotoxy(37,8);
  if (neurfname[0])
   cprintf("Neuron file: %s",neurfname);
  gotoxy(37,9);
  if (envfname[0])
   cprintf("Environment file: %s",envfname);
  gotoxy(37,10);
  if (recpath[0])
   cprintf("Recording path: %s",recpath);
  erasecursor();

  /* get choice */
  done = FALSE;
  while (!done)
   {
    i = toupper(bioskey(0) & 0xff);
    switch (i)
     {
      case 'R': /* read files */
start: /* get the neuron filespec & read in */
       gotoxy(1,1);
       cputs("Enter neuron file spec:                                       ");
       gotoxy(25,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == ESC)
	{
	 bioskey(0);
	 goto display;
	}
       else
	if (asc == CR)
	 {
	  bioskey(0);
	  goto envfile;
	 }
       str[0] = 25;
       p = cgets(str);
       file = fopen(p,"rb");
       if (file == NULL)
	goto start;
       else
	{ /* read in file */
	 fread(&nn,2,1,file);
	 for (np=ns, j=0; j<nn; np++, j++)
	  {
	   fread(np,sizeof(struct neuron)-22,1,file);
	   np->iGmem = np->Gmem * 1e8 + .5;
	   np->iCmem = np->Cmem * 1e11 + .5;
	   np->iVt = np->Vt * 1e6 + fsgn(np->Vt)*.5;
	   np->iFmin = np->Fmin * 10000 + .5;
	   np->iGain = np->Gain * 1e-2 + .5;
	   np->ipI[0] = np->pI[0] * 1e13 + fsgn(np->pI[0])*.5;
	   np->ipI[1] = np->pI[1] * 1e13 + fsgn(np->pI[1])*.5;
	   np->imconst = np->mconst * 1e1 + fsgn(np->mconst)*.5;
	  }
	 fread(&ni,2,1,file);
	 for (ip=Iinta, j=0; j<ni; ip++, j++)
	  {
	   fread(ip,40,1,file);
	   ip->iIL = ip->IL * 1e11 + fsgn(ip->IL)*.5;
	   if (ip->type == 0)
	    ip->ipL[0] = ip->pL[0] * 1e6 + fsgn(ip->pL[0])*.5;
	   else
	    ip->ipL[0] = ip->pL[0] * 1e3 + .5;
	   ip->ipL[1] = ip->pL[1] * 1e3 + .5;
	   ip->ipL[2] = ip->pL[2] * 1e2 + .5;
	   ip->iIH = ip->IH * 1e11 + fsgn(ip->IH)*.5;
	   ip->ipH[0] = ip->pH[0] * 1e3 + .5;
	   ip->ipH[1] = ip->pH[1] * 1e3 + .5;
	  }
	 fread(&nc,2,1,file);
	 for (cp=cona, j=0; j<nc; cp++, j++)
	  {
	   fread(cp,sizeof(struct con)-4,1,file);
	   cp->iIsr = cp->Isr * 1e10 + fsgn(cp->Isr)*.5;
	   cp->iIcr = cp->Icr * 1e10 + fsgn(cp->Icr)*.5;
	  }
	 fclose(file);
	 /* change pointers */
	 for (j=0, np=ns; j<nn; j++, np++)
	  {
	   if (np->Iint != NULL)
	    np->Iint = Iinta + ((int)np->Iint - 1)/40;
	   if (np->con != NULL)
	    np->con = cona + ((int)np->con - 1)/32;
	  }
	 for (j=0, cp=cona; j<nc; j++, cp++)
	  {
	   if (cp->next != NULL)
	    cp->next = cona + ((int)cp->next - 1)/32;
	  }
	 strcpy(neurfname,p);
	 gotoxy(37,8);
	 cprintf("Neuron file: %s                                ",neurfname);
	}
envfile:
       gotoxy(1,1);
       cputs("Enter environment file spec:                                       ");
       gotoxy(30,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == ESC || asc == CR)
	{
	 bioskey(0);
	 goto display;
	}
       str[0] = 25;
       p = cgets(str);
       file = fopen(p,"rb");
       if (file == NULL)
	goto envfile;
       else
	{ /* read in file */
	 fread(&f,sizeof(float),1,file);
	 bug.x = f*1000. + .5;
	 fread(&f,sizeof(float),1,file);
	 bug.y = f*1000. + .5;
	 fread(&f,sizeof(float),1,file);
	 bug.ang = f*100000. + .5;
	 fread(&nfood,2,1,file);
	 fread(foodx,2,NFOOD,file);
	 fread(foody,2,NFOOD,file);
	 for (k=0; k<NFOOD; k++)
	  {
	   fread(&j,2,1,file);
	   foodsize[k] = (long)j * 10000L;
	  }
	 fread(&nblock,2,1,file);
	 fread(blockx,2,NBLOCK,file);
	 fread(blocky,2,NBLOCK,file);
	 fread(gr,sizeof(struct graph),5,file);
	 fclose(file);
	 strcpy(envfname,p);
	}
       goto display;
      case 'W': /* write files */
       gotoxy(1,1);
       cputs("Write neuron file? ");
       if (toupper(bioskey(0) & 0xff) != 'Y')
	goto wenvfile;
       /* write neuron file */
       /* count neurons */
       for (i=0, j=0, np=ns; i<nn; i++, np++)
	if (np->name[0])
	 j++;
       gotoxy(1,1);
       if (neurfname[0])
	{
	 cprintf("Save neurons to %s? ",neurfname);
	 i = toupper(bioskey(0) & 0xff);
	}
       if (!neurfname[0] || i != 'Y')
	{
	 gotoxy(1,1);
	 cputs("Enter file spec:                                      ");
	 gotoxy(18,1);
	 str[0] = 38;
	 p = cgets(str);
	 strcpy(neurfname,p);
	}
       file = fopen(neurfname,"wb");
       fwrite(&j,2,1,file);
       for (i=0, np=ns; i<nn; i++, np++)
	if (np->name[0])
	 {
	  fwrite(np,27,1,file);
	  if (np->Iint)
	   j = (int)np->Iint - (int)Iinta + 1;
	  else
	   j = 0;
	  fwrite(&j,2,1,file);
	  fwrite(&(np->Isens),18,1,file);
	  if (np->con)
	   j = (int)np->con - (int)cona + 1;
	  else
	   j = 0;
	  fwrite(&j,2,1,file);
	 }
       fwrite(&ni,2,1,file);
       for (i=0; i<ni; i++)
	fwrite(Iinta+i,19,1,file);
       fwrite(&nc,2,1,file);
       for (i=0, cp=cona; i<nc; i++, cp++)
	{
	 fwrite(cp,sizeof(struct con)-6,1,file);
	 if (cp->next)
	  j = (int)cp->next - (int)cona + 1;
	 else
	  j = 0;
	 fwrite(&j,2,1,file);
	}
       fclose(file);
wenvfile: /* write environment file */
       gotoxy(1,1);
       cputs("Write environment file?                                    ");
       gotoxy(1,25);
       if (toupper(bioskey(0) & 0xff) != 'Y')
	goto display;
       gotoxy(1,1);
       if (envfname[0])
	{
	 cprintf("Save environment to %s? ",envfname);
	 j = toupper(bioskey(0) & 0xff);
	}
       if (!envfname[0] || j != 'Y')
	{
	 gotoxy(1,1);
	 cputs("Enter file spec:                                      ");
	 gotoxy(18,1);
	 str[0] = 38;
	 p = cgets(str);
	 strcpy(envfname,p);
	}
       file = fopen(envfname,"wb");
       f = (double)bug.x/1000.;
       fwrite(&f,sizeof(float),1,file);
       f = (double)bug.y/1000.;
       fwrite(&f,sizeof(float),1,file);
       f = (float)bug.ang/100000.;
       fwrite(&f,sizeof(float),1,file);
       fwrite(&nfood,2,1,file);
       fwrite(foodx,2,NFOOD,file);
       fwrite(foody,2,NFOOD,file);
       for (k=0; k<NFOOD; k++)
	{
	 j = foodsize[k]/10000L;
	 fwrite(&j,2,1,file);
	}
       fwrite(&nblock,2,1,file);
       fwrite(blockx,2,NBLOCK,file);
       fwrite(blocky,2,NBLOCK,file);
       fwrite(gr,sizeof(struct graph),5,file);
       fclose(file);
       goto display;
      case 'N': /* neuron data modification */
       datamod();
       goto display;
      case 'E': /* environment set up */
pent:  gotoxy(1,1);
       cprintf("Enter number of food patches (0 - %d): %d   ",NFOOD,nfood);
       gotoxy(39,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR)
	{
	 bioskey(0);
	 goto pdat;
	}
       else
	if (asc == ESC)
	 {
	  bioskey(0);
	  goto display;
	 }
       gotoxy(39,1);
       cputs("   ");
       gotoxy(39,1);
       str[0] = 3;
       p = cgets(str);
       j = atoi(p);
       if (j < 0 || j > NFOOD)
	goto pent;
       nfood = j;
pdat:  clrline(1);
       for (k=0; k<nfood; k++)
	{
	 gotoxy(1,1);
	 cprintf("Food patch #%d",k+1);
xpat:	 gotoxy(1,2);
	 cprintf("Enter patch's x coordinate (0 - 956): %d   ",foodx[k]);
	 gotoxy(39,2);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto ypat;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(39,2);
	 cputs("     ");
	 gotoxy(39,2);
	 str[0] = 4;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < MINY || j > MAXX)
	  goto xpat;
	 foodx[k] = j;
	 gotoxy(39,2);
	 cprintf("%d",foodx[k]);
ypat:	 gotoxy(1,3);
	 cprintf("Enter patch's y coordinate (0 - 902): %d   ",foody[k]);
	 gotoxy(39,3);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto patsiz;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(39,3);
	 cputs("     ");
	 gotoxy(39,3);
	 str[0] = 4;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < MINY || j > MAXY)
	  goto ypat;
	 foody[k] = j;
	 gotoxy(39,3);
	 cprintf("%d",foody[k]);
patsiz:	 gotoxy(1,4);
	 cprintf("Enter size of patch (0 - 5000): %d   ",
				 (int)(foodsize[k]/10000L));
	 gotoxy(33,4);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto patdone;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(33,4);
	 cputs("     ");
	 gotoxy(33,4);
	 str[0] = 5;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < 0 || j > 5000)
	  goto patsiz;
	 foodsize[k] = (long)j*10000L;
	 gotoxy(33,4);
	 cprintf("%d",j);
patdone: clrline(1);
	 clrline(2);
	 clrline(3);
	 clrline(4);
	}
bent:  clrline(1);
       gotoxy(1,1);
       cprintf("Enter number of blocks (0 - %d): %d   ",NBLOCK,nblock);
       gotoxy(33,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR)
	{
	 bioskey(0);
	 goto bdat;
	}
       else
	if (asc == ESC)
	 {
	  bioskey(0);
	  goto display;
	 }
       gotoxy(33,1);
       cputs("   ");
       gotoxy(33,1);
       str[0] = 3;
       p = cgets(str);
       nblock = atoi(p);
       if (nblock < 0 || nblock > NBLOCK)
	goto bent;
bdat:  clrline(1);
       for (k=0; k<nblock; k++)
	{
	 gotoxy(1,1);
	 cprintf("Block #%d",k+1);
xblk:	 gotoxy(1,2);
	 cprintf("Enter block's x coordinate (0 - 760): %d   ",blockx[k]);
	 gotoxy(39,2);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto yblk;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(39,2);
	 cputs("     ");
	 gotoxy(39,2);
	 str[0] = 4;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < 0 || j > 760)
	  goto xblk;
	 blockx[k] = j;
	 gotoxy(39,2);
	 cprintf("%d",blockx[k]);
yblk:	 gotoxy(1,3);
	 cprintf("Enter block's y coordinate (0 - 805): %d   ",blocky[k]);
	 gotoxy(39,3);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto blockdone;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(39,3);
	 cputs("     ");
	 gotoxy(39,3);
	 str[0] = 4;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < 0 || j > 805)
	  goto yblk;
	 blocky[k] = j;
	 gotoxy(39,3);
	 cprintf("%d",blocky[k]);
blockdone: clrline(1);
	 clrline(2);
	 clrline(3);
	}
       goto display;
      case 'I': /* initial conditions */
xent:  gotoxy(1,1);
       cprintf("Enter x coordinate of bug (80 - 880): %d    ",(int)(bug.x/1000L));
       gotoxy(39,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR)
	{
	 bioskey(0);
	 goto yent;
	}
       else
	if (asc == ESC)
	 {
	  bioskey(0);
	  goto display;
	 }
       gotoxy(39,1);
       cputs("      ");
       gotoxy(39,1);
       str[0] = 4;
       p = cgets(str);
       j = atoi(p);
       if (j < 80 || j > 880)
	goto xent;
       bug.x = j*1000L;
       gotoxy(39,1);
       cprintf("%d",j);
yent:  gotoxy(1,2);
       cprintf("Enter y coordinate of bug (80 - 820): %d    ",(int)(bug.y/1000L));
       gotoxy(39,2);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR)
	{
	 bioskey(0);
	 goto aent;
	}
       else
	if (asc == ESC)
	 {
	  bioskey(0);
	  goto display;
	 }
       gotoxy(39,2);
       cputs("      ");
       gotoxy(39,2);
       str[0] = 4;
       p = cgets(str);
       j = atoi(p);
       if (j < 80 || j > 820)
	goto yent;
       bug.y = j*1000L;
       gotoxy(39,2);
       cprintf("%d",j);
aent:  gotoxy(1,3);
       cprintf("Enter bug angle (0 - 359): %d    ",(int)(180L*(bug.ang/100L)/PI));
       gotoxy(28,3);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR)
	{
	 bioskey(0);
	 goto eent;
	}
       else
	if (asc == ESC)
	 goto display;
       gotoxy(28,3);
       cputs("      ");
       gotoxy(28,3);
       str[0] = 4;
       p = cgets(str);
       j = atoi(p);
       if (j < 0 || j > 359)
	goto aent;
       bug.ang = ((PI*(long)j)/180L)*100L;
       gotoxy(28,3);
       cprintf("%d",j);
eent:  gotoxy(1,4);
       cprintf("Enter energy (100 - 999): %d    ",(int)(energy/10000L));
       gotoxy(27,4);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == CR || asc == ESC)
	{
	 bioskey(0);
	 goto display;
	}
       gotoxy(27,4);
       cputs("      ");
       gotoxy(27,4);
       str[0] = 4;
       p = cgets(str);
       j = atoi(p);
       if (j < 100 || j > 999)
	goto eent;
       energy = j*10000L;
       gotoxy(27,4);
       cprintf("%d",j);
       goto display;
      case 'G': /* graph specification */
       for (k=0; k<5; k++)
	{
	 gotoxy(1,1);
	 cprintf("Graph #%d",k+1);
gtent:	 gotoxy(1,2);
	 cprintf("Enter graph type (0=None, 1=Variable, 2=Gait): %d   ",gr[k].gtype);
	 gotoxy(48,2);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   if (gr[k].gtype != 1)
	    goto grend;
	   goto gneur;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(48,2);
	 cputs("      ");
	 gotoxy(48,2);
	 str[0] = 2;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < 0 || j > 2)
	  goto gtent;
	 gr[k].gtype = j;
	 gotoxy(48,2);
	 cprintf("%d",gr[k].gtype);
	 if (gr[k].gtype != 1)
	  goto grend;
gneur:   gotoxy(1,3);
	 cprintf("Enter neuron name: %s       ",gr[k].gneur);
	 gotoxy(20,3);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto gvar;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(20,3);
	 cputs("      ");
	 gotoxy(20,3);
	 str[0] = 7;
	 p = cgets(str);
	 strcpy(gr[k].gneur,p);
gvar:    gotoxy(1,4);
	 cprintf("Enter variable (0=V [milliV], 1=F, 2=I [pA]): %d",gr[k].gvar);
	 gotoxy(47,4);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   if (gr[k].gvar == 1)
	    goto grend;
	   goto gscale;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(47,4);
	 cputs("      ");
	 gotoxy(47,4);
	 str[0] = 2;
	 p = cgets(str);
	 j = atoi(p);
	 if (j < 0 || j > 2)
	  goto gvar;
	 gr[k].gvar = j;
	 gotoxy(47,4);
	 cprintf("%d",gr[k].gvar);
	 if (gr[k].gvar == 1)
	  goto grend;
gscale:  gotoxy(1,5);
	 gr[k].gscale = 50;
	 cprintf("Enter scale (1 - 300): %d",gr[k].gscale);
	 gotoxy(24,5);
	 j = 0;
	 while (!j)
	  j = bioskey(1);
	 asc = j & 0xff;
	 if (asc == CR)
	  {
	   bioskey(0);
	   goto grend;
	  }
	 else
	  if (asc == ESC)
	   {
	    bioskey(0);
	    goto display;
	   }
	 gotoxy(24,5);
	 cputs("      ");
	 gotoxy(24,5);
	 str[0] = 10;
	 p = cgets(str);
	 m = atoi(p);
	 if (m < 1 || m > 300)
	  goto gscale;
	 gr[k].gscale = m;
	 gotoxy(24,5);
	 cprintf("%d",gr[k].gscale);
grend:   clrline(1);
	 clrline(2);
	 clrline(3);
	 clrline(4);
	 clrline(5);
	}
       goto display;
      case 'P': /* path for recording */
       gotoxy(1,1);
       cputs("Enter recording path:                                       ");
       gotoxy(23,1);
       j = 0;
       while (!j)
	j = bioskey(1);
       asc = j & 0xff;
       if (asc == ESC || asc == CR)
	{
	 bioskey(0);
	 goto display;
	}
       str[0] = 25;
       p = cgets(str);
       strcpy(recpath,p);
       i = strlen(recpath) - 1;
       if (recpath[i] == '\\')
	recpath[i] = 0; /* get rid of final \ */
       goto display;
      case 'S': /* simulate */
       msg = initsim();
       closegraph();
       goto display;
      case 'Q': /* quit */
       done = TRUE;
       break;
      default:
       break;
     }
   }
 }

void erasecursor(void)
 {
  union REGS regs;

  regs.x.bx = 0;
  regs.x.dx = 0x1900;
  regs.x.ax = 0x200;
  int86(0x10,&regs,&regs);
 }

void clrline(int n)
 {
  gotoxy(1,n);
  cputs("                                                              ");
 }

