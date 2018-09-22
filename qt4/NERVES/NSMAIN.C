#include "defn.h"
#define EXTERN
#include "nsdata.c"
#include "proto.h"

void main(void)
 {
  FILE *file;

  ns = calloc(150,sizeof(struct neuron));
  nsc = calloc(150,sizeof(struct neurcalc));
  Iinta = calloc(75,sizeof(struct Iint));
  cona = calloc(300,sizeof(struct con));
  neurfname[0] = 0;
  envfname[0] = 0;
  recpath[0] = 0;
  recnum = 0;
  AspR = 100./1.37 + .5;  /* x100 to make integer */
  drawmult = 2;
  Iextgr = -1;
  energy = 9990000L;

  /* read in integer sin & cos tables */
  file = fopen("sincos.tab","rb");
  if (file == NULL)
   {
    printf("File SINCOS.TAB not found, exiting\n");
    exit(0);
   }
  fread(isin,2,TWOPI/2+1,file);
  fread(icos,2,TWOPI/2+1,file);

  /* initialize leg constants */
  maxlegang[3] = PI - PI/5;
  minlegang[3] = PI;
  maxlegang[4] = PI - PI/12;
  minlegang[4] = PI + PI/12;
  maxlegang[5] = PI - PI/12;
  minlegang[5] = PI + PI/8;
  maxlegang[0] = PI/5;
  minlegang[0] = 0;
  maxlegang[1] = PI/12;
  minlegang[1] = -PI/12;
  maxlegang[2] = PI/12;
  minlegang[2] = -PI/8;
  attang[0] = atan2(15,8)*1000.;
  attang[1] = 0;
  attang[2] = atan2(-23,9)*1000.;
  attang[3] = atan2(15,-8)*1000.;
  attang[4] = PI;
  attang[5] = 2*PI + atan2(-23,-9)*1000.;
  attl[0] = sqrt(8*8 + 15*15);
  attl[1] = 12;
  attl[2] = sqrt(9*9 + 23*23);
  attl[3] = attl[0];
  attl[4] = 12;
  attl[5] = attl[2];
  legl[0] = 17;
  legl[1] = 15;
  legl[2] = 17;
  legl[3] = 17;
  legl[4] = 15;
  legl[5] = 17;
  hdsang[0] = atan2(22,11)*1000.;
  hdsang[1] = atan2(22,-11)*1000.;
  hdsl = sqrt(11*11 + 22*22);
  hdtang = PI/2;
  hdtl = 29;
  hdbang = PI/2;
  hdbl = 14;
  btang[0] = atan2(18,6)*1000.;
  btang[1] = atan2(18,-6)*1000.;
  btl = sqrt(6*6 + 18*18);
  bmang[0] = 0.;
  bmang[1] = PI;
  bml = 12;
  bbang[0] = atan2(-30,6)*1000.;
  bbang[1] = atan2(-30,-6)*1000.;
  bbl = sqrt(6*6 + 30*30);
  cerbang[0] = atan2(-30,2)*1000.;
  cerbang[1] = atan2(-30,-2)*1000.;
  cerbl = sqrt(2*2 + 30*30);
  antbang[0] = atan2(26,6)*1000.;
  antbang[1] = atan2(26,-6)*1000.;
  antbl = sqrt(6*6 + 26*26);

  /* initialize antenna and cercus constants */
  antang[0] = atan2(65,30)*1000.;
  antang[1] = atan2(65,-30)*1000.;
  antl = sqrt(30*30 + 65*65);
  cercang[0] = atan2(-34,8)*1000.;
  cercang[1] = atan2(-34,-8)*1000.;
  cercl = sqrt(34*34 + 8*8);

  bug.x = 500000L;
  bug.y = 500000L;

  plottype = 0; /* start with graphs plotted */

  randomize(); /* initialize random number generator */

  nn = 0;
  ni = 0;
  nc = 0;
  DT = 5;

  nsmenu();
  clrscr();
 }
