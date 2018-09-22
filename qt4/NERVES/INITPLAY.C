#include "defn.h"
#define EXTERN
#include "playdata.c"
#include "playproto.h"

void main(int argc,char *argv[])
 { /* initialize playback */

  int i,j,k,step;
  enum asc_val asc;
  enum ext_val ext;

  if (argc < 2)
   {
    printf("Must include filename as command line parameter\n");
    exit(0);
   }

  /* allocate space for recorded data */
  for (nblk=0; nblk<MAXBLK; nblk++)
   {
    rp[nblk] = calloc(MAXREC,sizeof(struct recbug));
    if (rp[nblk] == NULL)
     {
      if (nblk == 0)
       {
	printf("Not enough memory\n");
	exit(0);
       }
      break;
     }
   }

  pause = 0; /* initialize pause to none */
  step = 0;

  strcpy(playfname,argv[1]);

  playfile = fopen(playfname,"rb");
  if (playfile == NULL)
   {
    printf("Cannot open %s\n",playfname);
    exit(0);
   }
  fread(&i,2,1,playfile);
  fread(&j,2,1,playfile);
  if (i != PLAYBUG || j != VERSION)
   {
    printf("Illegal file\n");
    exit(0);
   }

  /* extract file number from filename */
  i = strlen(playfname) - 5;
  filenum[0] = playfname[i];
  if (filenum[0] == '0')
   strcpy(filenum,"10");
  else
   {
    if (filenum[0] < '1' || filenum[0] > '9')
     filenum[0] = '?';
    filenum[1] = 0;
   }

  /* read in initial data */
  fread(&rin.foodr[0],sizeof(struct recinit),1,playfile);
  fread(rgr,sizeof(struct recgraph),5,playfile);
  for (i=0; i<NFOOD; i++)  /* initialize current food radii */
   foodr[i] = ofoodr[i] = rin.foodr[i];

  reccnt = 0;
  cblk = 0;
  rc = rp[0];
  nrec = MAXREC;
  for (ublk=0; ublk<nblk && nrec==MAXREC; ublk++)
   {
    nrec = fread(rp[ublk],sizeof(struct recbug),MAXREC,playfile);
    if (nrec == 0 && ublk == 0)
     {
      printf("File too short\n");
      exit(0);
     }
   }
  if (nrec == 0)
   ublk--; /* decrement ublk if last block empty */
  if (ublk == 1)
   lastrec = nrec;
  else
   lastrec = MAXREC;

  playgraph(); /* put up initial screen */

  setviewport(1,1,478,329,1);
  setcolor(7);  /* draw food */
  for (j=0; j<NFOOD; j++)
   if (rin.foodr[j] != 0)
    circle(rin.foodx[j],rin.foody[j],foodr[j]);

  showbug(rc,15);
  setviewport(0,0,639,349,0);

  while (TRUE)
   {
getkey:
    /* wait for key */
    i = bioskey(0);
    asc = toupper(i & 0xff);
    if (asc != 0)
     {
      if (asc == ESC)
       {
quit:	fclose(playfile);
	closegraph();
	exit(0);
       }
      if (asc == CR)
       {
	i = multstep(&step); /* run indefinitely */
	if (i)
	 goto quit; /* if ESC, quit */
       }
      else
       if (asc == SPACE)
	singstep(&step); /* run one step */
       else
	if (asc == '+' && pause != 0)
	 {
	  pause -= PAUSEINC;
	  if (pause == 0)
	   bar(266,336,282,348); /* change menu to - only */
	 }
	else
	 if (asc == '-')
	  {
	   pause += PAUSEINC;
	   if (pause == PAUSEINC)
	    {
	     setcolor(3);
	     outtextxy(266,336,"+/");
	    }
	  }
     }
   }
 }

int near multstep(int *step)
 {
  int i;
  enum asc_val asc;

  while (TRUE)
   {
    singstep(step);
    i = bioskey(1);
    if (i)
     {
      bioskey(0);
      asc = i & 0xff;
      if (asc == ESC)
       return(TRUE);
      if (asc == SPACE)
       return(FALSE);
     }
    delay(pause);
   }
 }

void near singstep(int *step)
 {
  int y,j,i,k,drawfood;
  char str[25],c;

  (*step)++;
  for (j=0; j<5; j++) /* plot graph points */
   {
    if (rgr[j].gtype == 1)
     { /* variable */
      putpixel(536 + *step*2,rc->graphy1[j] + 66*j,15);
      putpixel(537 + *step*2,rc->graphy2[j] + 66*j,15);
     }
    else
     if (rgr[j].gtype == 2)
      { /* step */
       for (i=0; i<6; i++)
	{
	 if (!(rc->footst & (1<<i)))
	  {
	   putpixel(536 + *step*2,49-i*9+66*j,15);
	   putpixel(537 + *step*2,49-i*9+66*j,15);
	  }
	}
      }
   }

  /* redraw food if necessary */
  setviewport(1,1,478,329,1);
  for (j=0; j<NFOOD; j++)
   {
    drawfood = FALSE;
    if (foodr[j] != 0)
     {
      if (rc->mouthfood & (1<<(j+4)))
       {
	ofoodr[j] = foodr[j];
	foodr[j]--;
	drawfood = TRUE;
       }
      else
       if (rc->mouthfood & (1<<(j+1)))
	drawfood = TRUE;
     }
    if (drawfood)
     {
      setcolor(0);
      circle(rin.foodx[j], rin.foody[j], ofoodr[j]);
      setcolor(7);
      circle(rin.foodx[j], rin.foody[j], foodr[j]);
     }
   }

  /* draw bug */
  setviewport(1,1,478,329,0);
  if (reccnt != 0)
   showbug(rc-1,0); /* erase old bug */
  showbug(rc,15);

  /* display energy */
  setviewport(0,0,639,349,0);
  bar(422,336,454,348);
  sprintf(str,"%d",rc->energy);
  setcolor(3);
  outtextxy(422,336,str);

  /* change Iext if necessary */
  if (rc->Iextname[0])
   {
    bar(455,348,629,336);
    settextjustify(2,2);
    sprintf(str,"Iext(%s)[nA]:%-.1f",rc->Iextname,(float)rc->Iext/10.);
    outtextxy(629,336,str);
    settextjustify(0,2);
   }
  if (*step == 50)
   { /* reset graphs */
    *step = 0;
    for (j=0; j<5; j++)
     {
      if (rgr[j].gtype)
       {
	bar(538,3+j*66,638,52+j*66);
	setcolor(3);
	line(547,3+j*66,547,55+j*66); /*graph x-axis ticks */
	line(557,3+j*66,557,55+j*66);
	line(567,3+j*66,567,55+j*66);
	line(577,3+j*66,577,55+j*66);
	line(587,3+j*66,587,56+j*66);
	line(597,3+j*66,597,55+j*66);
	line(607,3+j*66,607,55+j*66);
	line(617,3+j*66,617,55+j*66);
	line(627,3+j*66,627,55+j*66);
	line(637,3+j*66,637,56+j*66);
	setcolor(15);
       }
     }
   }

  reccnt++;
  if (reccnt == lastrec)
   {
    setviewport(1,1,478,329,1);
    showbug(rc,0); /* erase bug */
    reccnt = 0;
    cblk++;
    if (cblk == ublk)
     { /* finished last read block */
      rc = rp[0];
      cblk = 0;
      if (ublk < nblk)
       { /* finished file, start again */
close: 	fclose(playfile);
	setcolor(0);
	for (i=0; i<NFOOD; i++) /* erase any food */
	 if (ofoodr[i] != 0)
	  circle(rin.foodx[i], rin.foody[i], foodr[i]);
	playfile = fopen(playfname,"rb");
	fread(&i,2,2,playfile);
	fread(&rin.foodr[0],sizeof(struct recinit),1,playfile);
	fread(rgr,sizeof(struct recgraph),5,playfile);
	setcolor(3);
	for (i=0; i<NFOOD; i++)
	 {
	  foodr[i] = ofoodr[i] = rin.foodr[i];
	  if (foodr[i] != 0)
	   circle(rin.foodx[i],rin.foody[i],foodr[i]);
	 }
	*step = 0;
	nrec = MAXREC;
	for (ublk=0; ublk<nblk && nrec==MAXREC; ublk++)
	 nrec = fread(rp[ublk],sizeof(struct recbug),MAXREC,playfile);
	if (nrec == 0)
	 ublk--; /* decrement ublk if last block empty */
	if (ublk == 1)
	 lastrec = nrec;
	else
	 lastrec = MAXREC;
	setviewport(0,0,639,349,0);
	bar(455,348,629,336); /* erase Iext */
	for (j=0; j<5; j++) /* reset graphs */
	 {
	  if (rgr[j].gtype)
	   {
	    bar(538,3+j*66,638,52+j*66);
	    setcolor(3);
	    line(547,3+j*66,547,55+j*66); /*graph x-axis ticks */
	    line(557,3+j*66,557,55+j*66);
	    line(567,3+j*66,567,55+j*66);
	    line(577,3+j*66,577,55+j*66);
	    line(587,3+j*66,587,56+j*66);
	    line(597,3+j*66,597,55+j*66);
	    line(607,3+j*66,607,55+j*66);
	    line(617,3+j*66,617,55+j*66);
	    line(627,3+j*66,627,55+j*66);
	    line(637,3+j*66,637,56+j*66);
	    setcolor(15);
	   }
	 }
       }
      else
       { /* read next part of file */
	nrec = MAXREC;
	for (ublk=0; ublk<nblk && nrec==MAXREC; ublk++)
	 nrec = fread(rp[ublk],sizeof(struct recbug),MAXREC,playfile);
	if (nrec == 0)
	 ublk--; /* decrement ublk if last block empty */
	if (ublk == 0)
	 goto close;
	if (ublk == 1)
	 lastrec = nrec;
	else
	 lastrec = MAXREC;
	setviewport(0,0,639,349,0);
       }
     }
    else
     {
      setviewport(0,0,639,349,0);
      rc = rp[cblk];
      if (cblk == ublk-1)
       lastrec = nrec;
      else
       lastrec = MAXREC;
     }
   }
  else
   rc++;

  return;
 }

