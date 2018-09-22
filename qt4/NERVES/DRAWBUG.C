#include "defn.h"
#include "nsdata.c"
#include "proto.h"

void drawbug(struct bug bug,int col)
 {
  int i;
  int temp1,temp2,temp3;
  int bugx,bugy,bugang;

  bugx = (bug.x + 1000L)/2000L;
  bugy = (bug.y*AspR + 100000L)/200000L;
  bugang = (bug.ang + 50L)/100L;

  /* calculate bug pts */
  bugp.head[0] = bug.mouthx/2;
  bugp.head[1] = ((long)AspR * bug.mouthy)/200L;
  temp1 = bugang + hdsang[0]; /* calculate head pts */
  bugp.head[2] = bugx + (int)(((long)hdsl * lcos(temp1))/2000L);
  bugp.head[3] = bugy + (int)(((long)AspR * hdsl * lsin(temp1))/200000L);
  temp3 = bugang + hdbang;
  bugp.head[4] = bugx + (int)(((long)hdbl * lcos(temp3))/2000L);
  bugp.head[5] = bugy + (int)(((long)AspR * hdbl * lsin(temp3))/200000L);
  temp1 = bugang + hdsang[1];
  bugp.head[6] = bugx + (int)(((long)hdsl * lcos(temp1))/2000L);
  bugp.head[7] = bugy + (int)(((long)AspR * hdsl * lsin(temp1))/200000L);

  temp1 = bugang + btang[0]; /* calculate body pts */
  temp2 = bugang + bmang[0];
  temp3 = bugang + bbang[0];
  bugp.body[0] = bugx + (int)(((long)btl * lcos(temp1))/2000L);
  bugp.body[1] = bugy + (int)(((long)AspR * btl * lsin(temp1))/200000L);
  bugp.body[2] = bugx + (int)(((long)bml * lcos(temp2))/2000L);
  bugp.body[3] = bugy + (int)(((long)AspR * bml * lsin(temp2))/200000L);
  bugp.body[4] = bugx + (int)(((long)bbl * lcos(temp3))/2000L);
  bugp.body[5] = bugy + (int)(((long)AspR * bbl * lsin(temp3))/200000L);
  temp1 = bugang + btang[1];
  temp2 = bugang + bmang[1];
  temp3 = bugang + bbang[1];
  bugp.body[10] = bugx + (int)(((long)btl * lcos(temp1))/2000L);
  bugp.body[11] = bugy + (int)(((long)AspR * btl * lsin(temp1))/200000L);
  bugp.body[8] = bugx + (int)(((long)bml * lcos(temp2))/2000L);
  bugp.body[9] = bugy + (int)(((long)AspR * bml * lsin(temp2))/200000L);
  bugp.body[6] = bugx + (int)(((long)bbl * lcos(temp3))/2000L);
  bugp.body[7] = bugy + (int)(((long)AspR * bbl * lsin(temp3))/200000L);

  bugp.legx[1] = bugp.body[2]; /* calculate leg attachment pts */
  bugp.legy[1] = bugp.body[3];
  bugp.legx[4] = bugp.body[8];
  bugp.legy[4] = bugp.body[9];
  for (i=0; i<6; i++)
   {
    if (i != 1 && i != 4)
     {
      temp1 = bugang + attang[i];
      bugp.legx[i] = bugx + (int)(((long)attl[i] * lcos(temp1))/2000L);
      bugp.legy[i] = bugy + (int)(((long)AspR * attl[i] * lsin(temp1))/200000L);
     }
    bugp.footx[i] = bug.footx[i]/2;
    bugp.footy[i] = ((long)AspR * bug.footy[i])/200L;
   }

  for (i = 0; i < 2; i++) /* calculate antenna attachment pts */
   {
    temp2 = bugang + antbang[i];
    bugp.antax[i] = bugx + (int)(((long)antbl * lcos(temp2))/2000L);
    bugp.antay[i] = bugy + (int)(((long)AspR * antbl * lsin(temp2))/200000L);
    bugp.antx[i] = bug.antx[i]/2;
    bugp.anty[i] = ((long)AspR * bug.anty[i])/200L;
   }

  for (i = 0; i < 2; i++) /* calculate cercus attachment pts */
   {
    temp1 = bugang + cerbang[i];
    bugp.cercax[i] = bugx + (int)(((long)cerbl * lcos(temp1))/2000L);
    bugp.cercay[i] = bugy + (int)(((long)AspR * cerbl * lsin(temp1))/200000L);
    bugp.cercx[i] = bug.cercx[i]/2;
    bugp.cercy[i] = ((long)AspR * bug.cercy[i])/200L;
   }

  showbug(bug,col);
  if (recnum)
   { /* record bug info */
    if (bug.mouthst)
     rc[reccnt].mouthfood = rc[reccnt].mouthfood | 1;
    rc[reccnt].energy = energy/10000L;
    for (i=0; i<6; i++)
     if (bug.foot[i])
      rc[reccnt].footst = rc[reccnt].footst | (1<<i);
    bugx = bugp.head[0];
    bugy = bugp.head[1];
    rc[reccnt].x = bugx;
    rc[reccnt].y = bugy;
    for (i=0; i<6; i+=2)
     {
      rc[reccnt].head[i] = bugp.head[i+2] - bugx;
      rc[reccnt].head[i+1] = bugp.head[i+3] - bugy;
     }
    for (i=0; i<12; i+=2)
     {
      rc[reccnt].body[i] = bugp.body[i] - bugx;
      rc[reccnt].body[i+1] = bugp.body[i+1] - bugy;
     }
    for (i=0; i<6; i++)
     {
      rc[reccnt].footx[i] = bugp.footx[i] - bugx;
      rc[reccnt].footy[i] = bugp.footy[i] - bugy;
      rc[reccnt].legx[i] = bugp.legx[i] - bugx;
      rc[reccnt].legy[i] = bugp.legy[i] - bugy;
     }
    for (i=0; i<2; i++)
     {
      rc[reccnt].antx[i] = bugp.antx[i] - bugx;
      rc[reccnt].anty[i] = bugp.anty[i] - bugy;
      rc[reccnt].antax[i] = bugp.antax[i] - bugx;
      rc[reccnt].antay[i] = bugp.antay[i] - bugy;
      rc[reccnt].cercx[i] = bugp.cercx[i] - bugx;
      rc[reccnt].cercy[i] = bugp.cercy[i] - bugy;
      rc[reccnt].cercax[i] = bugp.cercax[i] - bugx;
      rc[reccnt].cercay[i] = bugp.cercay[i] - bugy;
     }
   }
 }


void showbug(struct bug bug,int col)
 {
  int i,poly[10];

  setcolor(col);
  /* draw head */
  for (i=0; i<8; i++)
   poly[i] = bugp.head[i];
  poly[8] = poly[0];
  poly[9] = poly[1];
  drawpoly(5,poly);
  if (bug.mouthst)
   line(bugp.head[0],bugp.head[1],bugp.head[4],bugp.head[5]);

  /* draw body */
  drawpoly(6,bugp.body);

  /* draw antennae */
  for (i=0; i<2; i++)
   {
    line(bugp.antax[i],bugp.antay[i],bugp.antx[i],bugp.anty[i]);
   }
  /* draw cerci */
  for (i=0; i<2; i++)
   line(bugp.cercax[i],bugp.cercay[i],bugp.cercx[i],bugp.cercy[i]);

  /* draw legs & feet */
  for (i=0; i<6; i++)
   {
    line(bugp.legx[i],bugp.legy[i],bugp.footx[i],bugp.footy[i]);
    if (bug.foot[i])
     rectangle(bugp.footx[i]-1,bugp.footy[i]-1,bugp.footx[i]+1,bugp.footy[i]+1);
   }
 }
