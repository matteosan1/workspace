int near update(void)
 {
  int i,j,k,n,cf;
  struct neuron *np;
  struct neurcalc *ncp;
  struct Iint *ip;
  long Vinf,l,m,cur,I;
  struct con *cp;
  struct leg {
   long bF;     /* backward force */
   long fF;     /* forward force */
   long lF;     /* lateral force */
   } leg[6];
  long bugx,bugy,mo;
  int ibugx,ibugy,bugang;
  int xinc,yinc;
  int mouthd[NFOOD];

  for (j=0; j<6; j++)
   {
    lfoot[j] = bug.foot[j]; /* save foot states */
    leg[j].bF = leg[j].fF = leg[j].lF = 0;
   }
  for (i=0, ncp=nsc; i<nn; i++, ncp++)
   ncp->Flast = ncp->F; /* save last F's for synaptic connections */
  for (i=0, np=ns, ncp=nsc; i<nn; i++, np++, ncp++)
   {
    if (np->name[0] != 0)        /* undefined? */
     {
      cur = 0;
      for (cp=np->con; cp!=NULL; cp=cp->next)
       { /* get currents from connected neurons */
	l = (long)(nsc+cp->s)->Flast * cp->iIsr; /* nA x 10^5 */
	if (cp->ctype > 0)
	 {
	  I = (long)(nsc+cp->c)->Flast * cp->iIcr;
	  if (cp->ctype == 1)
	   l = l*cp->U + ((l/100L)*(I/100L))/10L;      /* gated */
	  else
	   if (I >= 0)
	    l = l + ((l/100L)*(I/100L))/10L;
	   else
	    {
	     l = l*100L/(100000L - I);
	     l *= 1000L;
	    }
	 }
	cur += l/10; /* nA x 10^4 */
       }

      /* add intrinsic current */
       if (np->Iint != NULL)
	{
	 ip = np->Iint;
	 j = 1;
	 if (!ip->H && ip->type == 0)
	  { /* calculate tmax for V-infinity type */
	    Vinf = (ncp->I/np->iGmem)*10L; /* calculate Vinfinity */
	    if (Vinf > ip->ipL[0])
						      /* using 31.25 */
	     ip->tmax = ip->ipL[1] - (int)(((long)ip->ipL[2]*Vinf)/100000L);
	    else
	     ip->tmax = MAXINT;
	   }
	 if ((ncp->Vlast < np->iVt && ncp->V >= np->iVt) ||
	     (!ip->H && ip->tmax != MAXINT && ip->tint >= ip->tmax))
	  { /* turn on high current */
	   ip->H = TRUE;
	   j = 0; /* restart time count */
	   if (ip->type == 0)
	    ip->tmax = ip->ipH[0]; /* time is constant */
	   else
	    ip->tmax = random(ip->ipH[1] - ip->ipH[0] + 1) + ip->ipH[0];
	  }
	 else
	  if (ip->H && ip->tmax != MAXINT && ip->tint >= ip->tmax)
	   { /* turn off high current */
	    ip->H = FALSE;
	    j = 0; /* restart time count */
	    if (ip->type == 1)
	     ip->tmax = random(ip->ipL[1] - ip->ipL[0] + 1) + ip->ipL[0];
	   }
         if (ip->tmax != MAXINT)
          ip->tint = (ip->tint + DT)*j; /* increment time count */

	 cur += (long)(ip->iIL + ip->H*(ip->iIH - ip->iIL))*100L;
	}

      if (i == Iextind)
       cur += Iextint; /* add external current */

      /* add sensory current */
      cur += sensory(np->Isens,np->name,np->ipI);

      ncp->I = cur; /* save current (nA x 10^4) */

      /* calculate new V */
      l = (cur*100L)/np->iCmem;
      m = (ncp->V * np->iGmem*100L)/np->iCmem;
      ncp->Vlast = ncp->V;
      ncp->V = ncp->V + (l * DT)/10L - (m * DT)/100L; /* mV x 10^3 */

      /* calculate F (0 - 10000) */
      if (ncp->V < np->iVt)
       ncp->F = 0;
      else
       {
	l = (np->iFmin - np->iGain * np->iVt)/100L;
	if (ncp->V < ((100L - l)/np->iGain)*100L)
	 ncp->F = np->iGain * ncp->V + l * 100L;
	else
	 ncp->F = 10000;
       }

      /* calculate any motor output */
      if (np->mtype)
       {
	if (np->mtype == 1 || np->mname == 0)
	 {
	  k = strlen(np->name);
	  if (np->name[k-2] == 'R')
	   j = 2;
	  else
	   j = -1;
	  j += np->name[k-1] - '0';
	 }
	if (np->mtype == 1)
	 { /* force */
	  if (np->mname == 2)
	   leg[j].lF = ((long)np->imconst * ncp->F)/100L; /* 0 - 7000 */
	  else
	   if (np->mname == 0)
	    leg[j].fF = ((long)np->imconst * ncp->F)/100L; /* 0-50000 */
	   else
	    leg[j].bF = ((long)np->imconst * ncp->F)/100L;
	 }
	else
	 { /* state */
	  if (np->mname == 0)
	   { /* foot */
	    if (ncp->F > np->imconst*1000)
	     bug.foot[j] = 1;
	    else
	     bug.foot[j] = 0;
	   }
	  else
	   { /* mouth */
	    if (ncp->F > np->imconst*1000)
	     bug.mouthst = 1;
	    else
	     bug.mouthst = 0;
	   }
	 }
       }
     }
   }

  /* calculate bug position etc., info */
  l = 0;
  for (j=0; j<6; j++) /* sum forces of legs that are down */
   if (bug.foot[j])
    l += leg[j].bF - leg[j].fF;
  l = l/2; /* calculate bug's translational velocity (adjustable!) */
  m = bug.foot[0]*leg[0].lF - bug.foot[3]*leg[3].lF; /* calc turning force */
  m = m/6; /* calculate bug's angular velocity (adjustable!) */
  bugang = (bug.ang + 50L)/100L;
  bugx = bug.x - ((long)lsin(bugang) * l * DT)/1000000L;
  bugy = bug.y + ((long)lcos(bugang) * l * DT)/1000000L;
  l = bug.foot[1]*leg[1].lF - bug.foot[4]*leg[4].lF; /* calc sideways force*/
  l = 2 * l;  /* (adjustable!) 20 to 2 */
  bugx -= (lcos(bugang) * l * DT)/1000000L;
  bugy -= (lsin(bugang) * l * DT)/1000000L;
  ibugx = (bugx + 500L)/1000L;
  ibugy = (bugy + 500L)/1000L;
  bug.ang += m * DT/10L;
  if (bug.ang < 0)                 /* trig!!! */
   bug.ang = TWOPI*100L + bug.ang;
  if (bug.ang >= TWOPI*100L)
   bug.ang = bug.ang - TWOPI*100L;
  bugang = (bug.ang + 50L)/100L;
  for (j=0; j<2; j++) /* calculate antenna & cercus tip positions */
   {
    bug.antx[j] = ibugx + (int)((long)antl * lcos(bugang + antang[j])/1000L);
    bug.anty[j] = ibugy + (int)((long)antl * lsin(bugang + antang[j])/1000L);
    bug.cercx[j] = ibugx + (int)((long)cercl * lcos(bugang + cercang[j])/1000L);
    bug.cercy[j] = ibugy + (int)((long)cercl * lsin(bugang + cercang[j])/1000L);
   }

  /* determine antenna contact, antenna contact angle, & cercus contact */
  xinc = 0;  /* "touching" variables */
  yinc = 0;
  antenna[0] = antenna[1] = 0;
  for (j=0; j<2; j++)
   {
    /* check world edge contact */
    if (bug.antx[j] <= MINX)
     {
      xinc += 1;
      if (!edget[j])
       {
	antenna[j] = TRUE;
	if (bugang > HALFPI && bugang <= PIANDAHALF) /* more trig!!! */
	 antcang[j] = PI - bugang;
	else
	 if (bugang < PIANDAHALF)
	  antcang[j] = bugang;
	 else
	  antcang[j] = TWOPI - bugang;
       }
     }
    else
     if (bug.antx[j] >= MAXX)
      {
       xinc -= 1;
       if (!edget[j])
	{
	 antenna[j] = TRUE;
	 if (bugang <= PIANDAHALF && bugang >= HALFPI)
	  antcang[j] = bugang - PI;
	 else
	  if (bugang > PIANDAHALF)
	   antcang[j] = TWOPI - bugang;
	  else
	   antcang[j] = - bugang;
	}
      }
    if (bug.anty[j] <= MINY)
     {
      yinc += 1;
      if (!edget[j])
       {
	antenna[j] = TRUE;
	if (bugang <= PI)
	 antcang[j] = bugang - HALFPI;
	else
	 antcang[j] = PIANDAHALF - bugang;
       }
     }
    else
     if (bug.anty[j] >= MAXY)
      {
       yinc -= 1;
       if (!edget[j])
	{
	 antenna[j] = TRUE;
	 if (bugang <= PI )
	  antcang[j] = HALFPI - bugang;
	 else
	  antcang[j] = bugang - PIANDAHALF;
	}
      }
    if (bug.cercx[j] <= MINX)
     xinc += 1;
    else
     if (bug.cercx[j] >= MAXX)
      xinc -= 1;
    if (bug.cercy[j] <= MINY)
     yinc += 1;
    else
     if (bug.cercy[j] >= MAXY)
      yinc -= 1;

    /* check box edge contact */
    for (i=0; i<nblock; i++)
     { /* first check antenna */
      if (ibugx < blockx[i]
	  && bug.antx[j] >= blockx[i] - 1
	  && bug.anty[j] >= blocky[i]
	  && bug.anty[j] <= blocky[i] + BLOCKHEIGHT)
       {
	xinc -= 1;
	if (!edget[j])
	 {
	  antenna[j] = TRUE;
	  if (bugang <= PIANDAHALF && bugang >= HALFPI)
	   antcang[j] = bugang - PI;
	  else
	   if (bugang > PIANDAHALF)
	    antcang[j] = TWOPI - bugang;
	   else
	    antcang[j] = - bugang;
	 }
       }
      else
       if (ibugx > blockx[i] + BLOCKWIDTH
	   && bug.antx[j] <= blockx[i] + BLOCKWIDTH + 1
	   && bug.anty[j] >= blocky[i]
	   && bug.anty[j] <= blocky[i] + BLOCKHEIGHT)
	{
	 xinc += 1;
	 if (!edget[j])
	  {
	   antenna[j] = TRUE;
	   if (bugang > HALFPI && bugang <= PIANDAHALF)
	    antcang[j] = PI - bugang;
	   else
	    if (bugang < PIANDAHALF)
	     antcang[j] = bugang;
	    else
	     antcang[j] = TWOPI - bugang;
	  }
	}
      if (ibugy < blocky[i]
	  && bug.anty[j] >= blocky[i] - 2
	  && bug.antx[j] >= blockx[i]
	  && bug.antx[j] <= blockx[i] + BLOCKWIDTH)
       {
	yinc -= 1;
	if (!edget[j])
	 {
	  antenna[j] = TRUE;
	  if (bugang <= PI )
	   antcang[j] = HALFPI - bugang;
	  else
	   antcang[j] = bugang - PIANDAHALF;
	 }
       }
      else
       if (ibugy > blocky[i] + BLOCKHEIGHT
	   && bug.anty[j] <= blocky[i] + BLOCKHEIGHT + 2
	   && bug.antx[j] >= blockx[i]
	   && bug.antx[j] <= blockx[i] + BLOCKWIDTH)
        {
	 yinc += 1;
	 if (!edget[j])
	  {
	   antenna[j] = TRUE;
	   if (bugang <= PI)
	    antcang[j] = bugang - HALFPI;
	   else
	    antcang[j] = PIANDAHALF - bugang;
	  }
	}
      /* now check cerci */
      if (ibugx < blockx[i]
	  && bug.cercx[j] >= blockx[i] - 1
	  && bug.cercy[j] >= blocky[i]
	  && bug.cercy[j] <= blocky[i] + BLOCKHEIGHT)
       xinc -= 1;
      else
       if (ibugx > blockx[i] + BLOCKWIDTH
	   && bug.cercx[j] <= blockx[i] + BLOCKWIDTH + 2
	   && bug.cercy[j] >= blocky[i]
	   && bug.cercy[j] <= blocky[i] + BLOCKHEIGHT)
	xinc += 1;
      if (ibugy < blocky[i]
	  && bug.cercy[j] >= blocky[i] - 2
	  && bug.cercx[j] >= blockx[i]
	  && bug.cercx[j] <= blockx[i] + BLOCKWIDTH)
       yinc -= 1;
      else
       if (ibugy > blocky[i] + BLOCKHEIGHT
	   && bug.cercy[j] <= blocky[i] + BLOCKHEIGHT + 2
	   && bug.cercx[j] >= blockx[i]
	   && bug.cercx[j] <= blockx[i] + BLOCKWIDTH)
	yinc += 1;
     }
   }

  if (xinc || yinc)  /* if it bounced (it didn't if touch was on both sides) */
   { /* calculate bug position from old position + bounce */
    bug.x += 2500 * sgn(xinc);  /* (adjustable!) bounce */
    bug.y += 2500 * sgn(yinc);
    ibugx = (bug.x + 500L)/1000L;
    ibugy = (bug.y + 500L)/1000L;
    for (j=0; j<2; j++) /* recalculate antenna & cercus tip positions */
     {
      bug.antx[j] = ibugx + (int)((long)antl * lcos(bugang + antang[j])/1000L);
      bug.anty[j] = ibugy + (int)((long)antl * lsin(bugang + antang[j])/1000L);
      bug.cercx[j] = ibugx + (int)((long)cercl * lcos(bugang + cercang[j])/1000L);
      bug.cercy[j] = ibugy + (int)((long)cercl * lsin(bugang + cercang[j])/1000L);
     }
   }
  else
   {
    bug.x = bugx;
    bug.y = bugy;
   }

  for (j=0; j<6; j++) /* calculate leg angles & foot positions */
   {
    if (lfoot[j] && bug.foot[j])
     { /* foot stays down, stretch leg */
      k = ibugx + (int)((long)attl[j] * lcos(bugang + attang[j])/1000L);
      n = ibugy + (int)((long)attl[j] * lsin(bugang + attang[j])/1000L);
      n = bug.footy[j] - n;
      k = bug.footx[j] - k;
      if (n == 0 && k == 0)
       legang[j] = 0; /* if leg has no length, set legang to 0 */
      else
       {
	i = atan2(n,k)*1000.;
	if (i < 0)
	 i += TWOPI;
	legang[j] = i - bugang;
	if (j < 3)
	 {
	  while (legang[j] > PI)
	   legang[j] = legang[j] - TWOPI;
	  while (legang[j] <= -PI)
	   legang[j] = TWOPI + legang[j];
	 }
	else
	 {
	  while (legang[j] < 0)
	   legang[j] = TWOPI + legang[j];
	  while (legang[j] >= TWOPI)
	   legang[j] = legang[j] - TWOPI;
	 }
       }
     }
    else
     { /* move foot */
      if (lfoot[j] && ((j >= 3 && legang[j] < maxlegang[j]) ||
		      (j < 3 && legang[j] > maxlegang[j])))
       legang[j] = maxlegang[j];
      if (j < 3)
       legang[j] += (int)(((long)DT * (leg[j].fF + leg[j].bF) * PI)/15000000L);
      else
       legang[j] -= (int)(((long)DT * (leg[j].fF + leg[j].bF) * PI)/15000000L);
      bug.footx[j] = ibugx + (int)(((long)attl[j] * lcos(bugang + attang[j])
		  + (long)legl[j] * lcos(bugang + legang[j]))/1000L);
      bug.footy[j] = ibugy + (int)(((long)attl[j] * lsin(bugang + attang[j])
		  + (long)legl[j] * lsin(bugang + legang[j]))/1000L);
     }
   }
  energy -= ENERGYPERT; /* decrement bug's energy */
  if (energy <= 0)
   {
    bar(422,336,454,348);
    outtextxy(422,336,"RIP");
    return(1); /* back to initsim */
   }
  odor[0] = odor[1] = mouthodor = 0;
  bug.mouthx = ibugx + (int)((long)hdtl * lcos(bugang + hdtang)/1000L);
  bug.mouthy = ibugy + (int)((long)hdtl * lsin(bugang + hdtang)/1000L);
  cf = 0;
  mo = 0;
  for (j=0; j<nfood; j++)
   { /* calculate odors for each antenna & mouth */
    for (k=0; k<2; k++)
     {
      l = bug.antx[k] - foodx[j];
      m = bug.anty[k] - foody[j];
      l = l*l + m*m;
      if (l != 0)
       odor[k] += 3L*foodsize[j]/(4L*l); /* (adjustable!) */
      else
       odor[k] += foodsize[j]; /* if at middle of food */
     }
    l = bug.mouthx - foodx[j];
    m = bug.mouthy - foody[j];
    l = l*l + m*m;
    if (l != 0)
     mouthodor += foodsize[j]/l;
    else
     mouthodor += foodsize[j]; /* if at middle of food */
    mouthd[j] = sqrt(l); /* distance from mouth */
    if (mouthodor > mo)
     { /* save largest mouthodor */
      mo = mouthodor;
      cf = j;
     }
   }

  if (obug.mouthst && !bug.mouthst)  /* mouth was open, now closed */
   {
    energy += BITEENERGY/(2*drawmult);
    foodsize[cf] -= BITEENERGY/(2*drawmult);
    foodr[cf] = sqrt(foodsize[cf]/(PI*10L));
   }
  mouth = 0;
  for (j=0; j<nfood; j++)
   { /* check for mouth contact */
    if (mouthd[j] <= 2*foodr[j])   /* changed from original */
     {
      mouth = TRUE;
      break;
     }
   }
  return(0);
 }

long sensory(enum senst type,char *name,long *pI)
 { /* returns a sensory current */
  int i,j;
  long I;

  switch (type)
   {
    case LAF: /* leg angle forward */
     i = strlen(name);
     if (name[i-2] == 'R')
      j = 2;
     else
      j = -1;
     j += name[i-1] - '0';
     if (j < 3)
      {
       if (legang[j] >= maxlegang[j])
	I = *pI;
       else
	I = 0;
      }
     else
      {
       if (legang[j] <= maxlegang[j])
	I = *pI;
       else
	I = 0;
      }
     break;

    case LAB: /* leg angle backward */
     i = strlen(name);
     if (name[i-2] == 'R')
      j = 2;
     else
      j = -1;
     j += name[i-1] - '0';
     if (j < 3)
      {
       if (legang[j] <= minlegang[j])
	I = *pI;
       else
	I = 0;
      }
     else
      {
       if (legang[j] >= minlegang[j])
	I = *pI;
       else
	I = 0;
      }
     break;

    case AC: /* antenna contact */
     i = strlen(name);
     if (name[i-1] == 'L')
      j = 0;
     else
      j = 1;
     if (!edget[j])
      {
       if (antenna[j])
	{
	 edget[j] = 100;
	 edgecang[j] = antcang[j];
	 I = (*pI * (long)edgecang[j])/1000L;
	}
       else
	I = 0;
      }
     else
      {
       edget[j]--;
       I = (*pI * (long)edgecang[j])/1000L;
      }
     break;

    case OS: /* odor strength */
     i = strlen(name);
     if (name[i-1] == 'L')
      j = 0;
     else
      if (name[i-1] == 'R')
       j = 1;
      else
       j = 2;
     if (j < 2)
      I = (*pI * (long)odor[j])/10000L - *(pI+1);
     else
      I = (*pI * mouthodor)/10000L - *(pI+1);
     break;

    case EC: /* energy capacity */
     I = (*pI * energy)/10000L;
     break;

    case MC: /* mouth contact */
     if (mouth)
      I = *pI;
     else
      I = 0;
     break;

    default:
     I = 0;
     break;
   }

  return(I);
 }

