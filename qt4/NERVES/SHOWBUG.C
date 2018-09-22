#include "defn.h"
#include "playdata.c"
#include "playproto.h"


void showbug(struct recbug *rc,int col)
 {
  int i,x,y,t1,t2,poly[12];

  setcolor(col);

  x = rc->x;
  y = rc->y;

  /* draw head */
  poly[0] = x;
  poly[1] = y;
  for (i=0; i<6; i+=2)
   {
    poly[i+2] = rc->head[i] + x;
    poly[i+3] = rc->head[i+1] + y;
   }
  poly[8] = poly[0];
  poly[9] = poly[1];
  drawpoly(5,poly);
  if (rc->mouthfood & 1)
   line(poly[0],poly[1],poly[4],poly[5]);

  /* draw body */
  for (i=0; i<12; i+=2)
   {
    poly[i] = rc->body[i] + x;
    poly[i+1] = rc->body[i+1] + y;
   }
  drawpoly(6,poly);

  /* draw antennae */
  for (i=0; i<2; i++)
   {
    line(rc->antax[i]+x,rc->antay[i]+y,rc->antx[i]+x,rc->anty[i]+y);
   }

  /* draw cerci */
  for (i=0; i<2; i++)
   line(rc->cercax[i]+x,rc->cercay[i]+y,rc->cercx[i]+x,rc->cercy[i]+y);

  /* draw legs & feet */
  for (i=0; i<6; i++)
   {
    t1 = rc->footx[i] + x;
    t2 = rc->footy[i] + y;
    line(rc->legx[i]+x,rc->legy[i]+y,t1,t2);
    if (rc->footst & (1<<i))
     rectangle(t1-1,t2-1,t1+1,t2+1);
   }
 }