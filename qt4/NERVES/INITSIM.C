#include "defn.h"
#include "nsdata.c"
#include "proto.h"
#include "update.c"

int initsim(void)
 { /* initialize simulation */

  int i,j,k,step,savIext;
  char str[26],*p;
  enum asc_val asc;
  enum ext_val ext;
  int r,t;
  long time;
  float f;
  struct neuron *np,*nq;
  struct con *cp;
  struct neurcalc *ncp;
  struct Iint *ip;
  int bugx,bugy,bugang;
  FILE *recfile;

  /* find all connection names */
  for (j=0, np=ns; j<nn; j++, np++)
   {
    if (np->name[0])
     for (cp=np->con; cp != NULL; cp=cp->next)
      {
       for (i=0, nq=ns; i<nn; i++, nq++)
	if (nq->name[0] && !strcmp(cp->sname,nq->name))
	 break;
       if (i == nn)
	{ /* name not found */
	 gotoxy(1,1);
	 cprintf("Sending neuron %s for neuron %s not found",cp->sname,np->name);
	 gotoxy(1,2);
	 cprintf("Press any key and N to correct");
	 bioskey(0);
	 clrline(1);
	 clrline(2);
	 erasecursor();
	 return(0);
	}
       else
	cp->s = i;
       if (cp->ctype)
	{
	 for (i=0, nq=ns; i<nn; i++, nq++)
	  if (nq->name[0] && !strcmp(cp->cname,nq->name))
	   break;
	 if (i == nn)
	  { /* name not found */
	   gotoxy(1,1);
	   cprintf("Compound neuron %s for neuron %s not found",cp->cname,np->name);
	   gotoxy(1,2);
	   cprintf("Press any key and N to correct");
	   bioskey(0);
	   clrline(1);
	   clrline(2);
	   erasecursor();
	   return(0);
	  }
	 else
	  cp->c = i;
	}
      }
   }

  /* find all graph names */
  for (j=0; j<5; j++)
   if (gr[j].gtype == 1)
    {
     for (i=0, nq=ns; i<nn; i++, nq++)
      if (nq->name[0] && !strcmp(gr[j].gneur,nq->name))
       break;
     if (i == nn)
      { /* name not found */
       gotoxy(1,1);
       cprintf("Graph neuron %s for graph %d not found",gr[j].gneur,j+1);
       gotoxy(1,2);
       cprintf("Press any key and N or G to correct");
       bioskey(0);
       clrline(1);
       clrline(2);
       erasecursor();
       return(0);
      }
     else
      gr[j].g = i;
    }

  if (Iextgr >= 0 && gr[Iextgr].gtype == 1) /* set Iext neuron */
   Iextind = gr[Iextgr].g;
  else
   Iextind = -1;

  for (i=0, ip=Iinta; i<ni; i++, ip++)
   {
    ip->H = 0;
    ip->tint = 0;
    if (ip->type == 1) /* if random, initialize tmax */
     ip->tmax = random(ip->ipL[1] - ip->ipL[0]+1) + ip->ipL[0];
   }

  /* initialize leg angles, foot states, and foot positions */
  legang[0] = legang[1] = legang[2] = 0;
  legang[3] = legang[4] = legang[5] = PI;
  bugx = (bug.x + 500L)/1000L;
  bugy = (bug.y + 500L)/1000L;
  bugang = (bug.ang + 50L)/100L;
  for (j=0; j<6; j++)
   {
    bug.foot[j] = 1; /* all down */
    bug.footx[j] = bugx + ((long)attl[j] * lcos(bugang + attang[j])
		    + (long)legl[j] * lcos(bugang + legang[j]))/1000L;
    bug.footy[j] = bugy + ((long)attl[j] * lsin(bugang + attang[j])
		    + (long)legl[j] * lsin(bugang + legang[j]))/1000L;
   }

  /* initialize antenna and cercus ends */
  for (j=0; j<2; j++)
   {
    bug.antx[j] = bugx + ((long)antl * lcos(bugang + antang[j]))/1000L;
    bug.anty[j] = bugy + ((long)antl * lsin(bugang + antang[j]))/1000L;
    bug.cercx[j] = bugx + ((long)cercl * lcos(bugang + cercang[j]))/1000L;
    bug.cercy[j] = bugy + ((long)cercl * lsin(bugang + cercang[j]))/1000L;
    edget[j] = 0;
   }
  /* initialize mouth and odors */
  odor[0] = odor[1] = mouthodor = 0;
  bug.mouthx = bugx + ((long)hdtl * lcos(bugang + hdtang))/1000L;
  bug.mouthy = bugy + ((long)hdtl * lsin(bugang + hdtang))/1000L;
  for (j=0; j<nfood; j++)
   { /* calculate odors for each antenna & mouth */
    for (k=0; k<2; k++)
     {
      r = bug.antx[k] - foodx[j];
      t = bug.anty[k] - foody[j];
      r = r*r + t*t;
      if (r != 0)
       odor[k] += 3L*foodsize[j]/r*40000L; /* change from vers 1 */
      else
       odor[k] += foodsize[j]/10000L;
     }
    r = bug.mouthx - foodx[j];
    t = bug.mouthy - foody[j];
    r = r*r + t*t;
    if (r != 0)
     mouthodor += foodsize[j]/r*10000L;
    else
     mouthodor += foodsize[j]/10000L;
    foodr[j] = sqrt(foodsize[j]/(PI*10L));
    ofoodr[j] = foodr[j];
   }
  bug.mouthst = 0; /* initialize mouth state to closed */
  mouth = 0;

  for (i=0, ncp=nsc; i<nn; i++, ncp++)
   {
    ncp->V = (ns+i)->iVt;
    ncp->F = 0;
    ncp->Vlast = ncp->V;
    ncp->I = 0;
   }

  graph();
  setviewport(1,1,478,329,1);
  setcolor(7);
  for (j=0; j<nfood; j++)
   circle(foodx[j]/2, ((long)AspR * foody[j])/200L, foodr[j]);
  obug = bug;
  drawbug(bug,15);
  setviewport(0,0,639,349,0);
  time = 0;
  step = 0;

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
	if (recnum != 0)
	 {
stoprec:  fclose(recfile);
	  setcolor(3);
	  bar(226,336,370,348);
	  outtextxy(226,336,"Menu  Tab:ChgPlots");
	  recnum = 0;
	  goto getkey;
	 }
	else
	 return(0);
       }
      if (asc == CR)
       {
	i = multstep(&step,&time,recfile,&savIext); /* run indefinitely */
	if (i)
	 {
	  if (recnum != 0)
	   goto stoprec;
	  else
	   return(0);
	 }
       }
      else
       if (asc == SPACE)
	{
	 if (!singstep(&step,&time,recfile,&savIext)) /* run one step */
	  singstep(&step,&time,recfile,&savIext);
	}
       else
	if (asc == 'D')
	 {
	  if (!recnum)
	   {
	    drawmult *= 2;
	    if (drawmult > 64)
	     drawmult = 2;
	    setcolor(3);
	    bar(400,336,417,348);
	    sprintf(str,"%d ",drawmult);
	    outtextxy(400,336,str);
	   }
	 }
	else
	 if (asc >= '0' && asc <= '9')
	  {
	   p = str;
	   while (asc != CR)
	    {
	     *p = asc;
	     p++;
	     asc = bioskey(0) & 0xff;
	    }
	   *p = 0;
	   if (str[0] >= '0' && str[0] <= '5' && str[1] == '=')
	    {
	     j = str[0] - '1';
	     setcolor(3);
	     if (j < 0)
	      {
	       bar(455,348,629,336);
	       Iextgr = -1;
	       Iextind = -1;
	      }
	     else
	      if (gr[j].gtype == 1)
	       {
		f = atof(str+2);
		if (fabs(f) < 100.)
		 {
		  Iextgr = j;
		  Iextind = gr[j].g;
		  Iextint = f*10000;
		  bar(455,348,629,336);
		  settextjustify(2,2);
		  sprintf(str,"Iext(%s)[nA]:%-.1f",gr[Iextgr].gneur,(float)Iextint/10000.);
		  outtextxy(629,336,str);
		  settextjustify(0,2);
		  savIext = TRUE;
		 }
	       }
	    }
	  }
	 else
	  if (asc == TAB)
	   if (!recnum)
	    { /* change plot type */
	     bar(480,1,638,329); /* first blank entire block */
	     plottype = !plottype;
	     if (!plottype)
	      graphsetup();
	     else
	      activesetup();
	    }
     }
    else
     {
      ext = i>>8;
      if (ext >= F1 && ext <= F10)
       { /* start recording */
	if ((step%4) != 0) /* if not where bug should be drawn, get there */
	 {
	  singstep(&step,&time,recfile,&savIext);
	  singstep(&step,&time,recfile,&savIext);
	 }
	if (recnum != 0)
	 fclose(recfile);
	recnum = ext - F1 + 1;
	if (recpath[0] == 0)
	 sprintf(str,"ns%d.sav",recnum);
	else
	 sprintf(str,"%s\\ns%d.sav\0",recpath,recnum);
	recfile = fopen(str,"wb");
	if (recfile == NULL)
	 {
	  recnum = 0;
	  return(1); /* return 1 to indicate recording path bad */
	 }
	else
	 {
	  setcolor(3);
	  bar(226,336,370,348);
	  sprintf(str,"Stop  RECORDING:%d",recnum);
	  outtextxy(226,336,str);
	  if (drawmult > 2)
	   {
	    drawmult = 2; /* reset drawmult to 2 for recording */
	    setcolor(3);
	    bar(400,336,417,348);
	    sprintf(str,"%d ",drawmult);
	    outtextxy(400,336,str);
	   }
	  if (plottype)
	   { /* if on neuron activity plots, switch back to graphs */
	    bar(480,1,638,329); /* first blank entire block */
	    plottype = 0;
	    graphsetup();
	   }

	  /* write code and version to file */
	  i = PLAYBUG;
	  fwrite(&i,2,1,recfile);
	  i = VERSION;
	  fwrite(&i,2,1,recfile);

	  /* write initial data to file */
	  for (i=0; i<NFOOD; i++)
	   rin.foodr[i] = 0;
	  for (i=0; i<nfood; i++)
	   {
	    rin.foodr[i] = foodr[i];
	    rin.foodx[i] = foodx[i]/2;
	    rin.foody[i] = ((long)AspR * foody[i])/200L;
	   }
	  rin.nblock = nblock;
	  for (i=0; i<nblock; i++)
	   {
	    rin.blockx[i] = blockx[i]/2;
	    rin.blocky[i] = ((long)AspR * blocky[i])/200L;
	   }
	  fwrite(&rin.foodr[0],sizeof(struct recinit),1,recfile);

	  /* write graph data to file */
	  for (i=0; i<5; i++)
	   {
	    rgr[i].gtype = gr[i].gtype;
	    strcpy(rgr[i].gneur,gr[i].gneur);
	    rgr[i].gvar = gr[i].gvar;
	    rgr[i].gscale = rgr[i].gscale;
	   }
	  fwrite(rgr,sizeof(struct recgraph),5,recfile);

	  reccnt = 0; /* initialize records */
	  for (i=0; i<NREC; i++)
	   {
	    rc[i].footst = 0;
	    rc[i].mouthfood = 0;
	   }
	  if (Iextgr >= 0 && gr[Iextgr].gtype == 1)
	   savIext = TRUE;
	  else
	   savIext = FALSE;
	 }
       }
     }
   }
 }

int near multstep(int *step,long *time,FILE *recfile,int *savIext)
 {
  int i;
  enum asc_val asc;

  while (TRUE)
   {
    if (singstep(step,time,recfile,savIext))
     return(FALSE);
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
   }
 }

int near singstep(int *step,long *time,FILE *recfile,int *savIext)
 {
  int y,j,i,k;
  char str[6],c;
  struct neuron *np;
  struct neurcalc *ncp;

  if (update())
   goto stoprec;
  (*step)++;
  if (!(*step%2))
   { /* graph */
    if (!plottype)
     {
      if (recnum && (*step%(2*drawmult)))
       rc[reccnt].graphx = *time/10; /* record x plot for graph */
      for (j=0; j<5; j++) /* plot graph points */
       {
	if (gr[j].gtype == 1)
	 { /* variable */
	  if (gr[j].gvar == 1)
	   { /* F, 0 to 1 */
	    y = 52 - (nsc+gr[j].g)->F/200;
	   }
	  else
	   {
	    if (gr[j].gvar == 0)
	     y = 28 - (((nsc+gr[j].g)->V)/40)/gr[j].gscale;
	    else
	     y = 28 - (((nsc+gr[j].g)->I)/400)/gr[j].gscale;
	   }
	  if (y < 3)
	   y = 3;
	  else
	   if (y > 52)
	    y = 52;
	  putpixel(538 + *time/10,y + 66*j,15);
	  if (recnum)
	   { /* record y plot for graph */
	    if ((*step%(2*drawmult)))
	     rc[reccnt].graphy1[j] = y;
	    else
	     rc[reccnt].graphy2[j] = y;
           }
	 }
	else
	 if (gr[j].gtype == 2)
	  { /* step */
	   for (i=0; i<6; i++)
	    {
	     if (!bug.foot[i])
	      putpixel(538 + (*time)/10,49-i*9+66*j,15);
	    }
	  }
       }
     }
    else
     { /* plot neuron activity */
      i = 0;
      k = 0;
      for (j=0, np=ns, ncp=nsc; j<nn; j++,np++,ncp++)
       {
	if (np->name[0] != 0) /* if defined */
	 {
	  if (ncp->F == 0) /* set color depending on frequency */
	   setcolor(1);
	  else
	   if (ncp->F < 3300)
	    setcolor(3);
	   else
	    if (ncp->F < 6600)
	     setcolor(5);
	    else
	     setcolor(7);
	  outtextxy(483 + i*52,1 + k*8,np->name);
	  if (k < 39)
	   k++;
	  else
	   {
	    if (i < 2)
	     {
	      k = 0;
	      i++;
	     }
	    else
	     break;
	   }
	 }
       }
     }
    if (!(*step%(2*drawmult)))
     { /* draw bug */
      setviewport(1,1,478,329,1);
      for (j=0; j<nfood; j++)
       {
	if (ofoodr[j] != foodr[j])
	 y = 4;
	else
	 y = 1;
	if (mouth || y == 4)
	 {
	  setcolor(0);
	  circle(foodx[j]/2, (long)AspR * foody[j]/200L, ofoodr[j]);
	  ofoodr[j] = foodr[j];
	  setcolor(7);
	  circle(foodx[j]/2, (long)AspR * foody[j]/200L, foodr[j]);
	  if (recnum)
	   { /* note to redraw or reduce circle */
	    c = (1 << (j+y));
	    rc[reccnt].mouthfood = rc[reccnt].mouthfood | c;
	   }
	 }
       }
      setviewport(1,1,478,329,0);
      showbug(obug,0); /* erase old bug */
      obug = bug;
      drawbug(bug,15);
      setviewport(0,0,639,349,0);
      bar(422,336,454,348);
      sprintf(str,"%d",(int)(energy/10000L));
      setcolor(3);
      outtextxy(422,336,str);
      setcolor(7);
      if (recnum)
       {
	if (*savIext)
	 {
	  strcpy(rc[reccnt].Iextname,gr[Iextgr].gneur);
	  rc[reccnt].Iext = (Iextint+500L*sgn(Iextint))/1000L;
	  *savIext = FALSE;
	 }
	else
	 rc[reccnt].Iextname[0] = 0;
	reccnt++;
	if (reccnt == NREC)
	 { /* write to file */
	  if (fwrite(rc,sizeof(struct recbug),NREC,recfile) != NREC)
	   { /* disk full - close file & stop recording */
stoprec:    fclose(recfile);
	    recnum = 0;
	    setcolor(3);
	    bar(226,336,370,348);
	    outtextxy(226,336,"Menu  Tab:ChgPlots");
	    return(TRUE);
	   }
	  reccnt = 0;
	  for (i=0; i<NREC; i++)
	   {
	    rc[i].footst = 0;
	    rc[i].mouthfood = 0;
	   }
	 }
       }
     }
    if (!(*step%200) && !plottype)
     { /* reset graphs */
      *time = -DT;
      for (j=0; j<5; j++)
       {
	if (gr[j].gtype)
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
   }
  *time += DT;
  return(0);
 }

