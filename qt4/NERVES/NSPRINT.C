#include "defn.h"
#define EXTERN
#include "nsdata.c"

void main(int argc,char *argv[])
 {
  int i,j;
  struct neuron *np;
  struct Iint *ip;
  struct con *cp;
  char str[20];
  FILE *file;

  if (argc != 2)
   return;

  ns = calloc(150,sizeof(struct neuron));
  Iinta = calloc(75,sizeof(struct Iint));
  cona = calloc(300,sizeof(struct con));

  file = fopen(argv[1],"rb");
  if (file == NULL)
   return;
  fread(&nn,2,1,file);
  for (np=ns, j=0; j<nn; np++, j++)
   fread(np,sizeof(struct neuron)-22,1,file);
  fread(&ni,2,1,file);
  for (ip=Iinta, j=0; j<ni; ip++, j++)
   fread(ip,40,1,file);
  fread(&nc,2,1,file);
  for (cp=cona, j=0; j<nc; cp++, j++)
   fread(cp,sizeof(struct con)-4,1,file);
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

  /* print file */
  printf("Prepare printer (LPT1) and press any key\n");
  bioskey(0);
  fprintf(stdprn,"%s\n\n",argv[1]);
  for (i=0, np=ns; i<nn; i++, np++)
   {
    if (np->name[0])
     {
      fprintf(stdprn,"%s\n",np->name);
      fprintf(stdprn,"  Gmem   Cmem   Vt     Fmin   Gain\n");
      fprintf(stdprn,"  %-6.1f %-6.1f %-6.1f %-6.1f %-6.1f\n\n",
	      1e6*np->Gmem,1e9*np->Cmem,1e3*np->Vt,
	      np->Fmin,1e-3*np->Gain);
      if (np->Iint == NULL)
       fprintf(stdprn,"  Iint\n  NONE\n\n");
      else
       {
	ip = np->Iint;
	if (ip->type == 0)
	 {
	  fprintf(stdprn,"  Iint       IL     Vthr   Base   Mult   IL     Duration\n");
	  fprintf(stdprn,"  NON-RANDOM %-6.1f %-6.1f %-6.1f %-6.2f %-6.1f %-6.1f\n\n",
		  1e9*ip->IL,1e3*ip->pL[0],1e3*ip->pL[1],ip->pL[2],
		  1e9*ip->IL,1e3*ip->pH[0]);
	 }
	else
	 {
	  fprintf(stdprn,"  Iint       IL     Min    Max    IL     Min    Max\n");
	  fprintf(stdprn,"  RANDOM     %-6.1f %-6.1f %-6.1f %-6.1f %-6.1f %-6.1f\n\n",
		  1e9*ip->IL,1e3*ip->pL[0],1e3*ip->pL[1],
		  1e9*ip->IH,1e3*ip->pH[0],1e3*ip->pH[0]);
	 }
       }
      if (!np->Isens)
       {
	fprintf(stdprn,"  Sensory-function\n");
	fprintf(stdprn,"  NONE\n\n");
       }
      else
       if (np->Isens == OS)
	{
	 fprintf(stdprn,"  Sensory-function Param-1    Param-2\n");
	 fprintf(stdprn,"  ODOR STRENGTH    %-9.4f  %-9.4f\n\n",
		 1e9*np->pI[0],1e9*np->pI[1]);
	}
       else
	{
	 fprintf(stdprn,"  Sensory-function    Param\n");
	 switch (np->Isens)
	  {
	   case LAF:
	    strcpy(str,"LEG ANGLE FORWARD");
	    break;
	   case LAB:
	    strcpy(str,"LEG ANGLE BACKWARD");
	    break;
	   case AC:
	    strcpy(str,"ANTENNA CONTACT");
	    break;
	   case EC:
	    strcpy(str,"ENERGY CAPACITY");
	    break;
	   case MC:
	    strcpy(str,"MOUTH CONTACT");
	    break;
	   default:
	    str[0] = 0;
	  }
	 fprintf(stdprn,"  %-19s %-6.1f\n\n",str,1e9*np->pI[0]);
	}
      if (!np->mtype)
       fprintf(stdprn,"  Motor-output\n  NONE\n\n");
      else
       {
	fprintf(stdprn,"  Motor-output  Type    Param\n");
	if (np->mtype == 1)
	 {
	  if (np->mname == 0)
	   strcpy(str,"FORWARD");
	  else
	   if (np->mname == 1)
	    strcpy(str,"BACKWARD");
	   else
	    strcpy(str,"LATERAL");
	  fprintf(stdprn,"  FORCE         %-5s %-6.1f\n\n",str,np->mconst);
	 }
	else
	 {
	  if (np->mname == 0)
	   strcpy(str,"FOOT");
	  else
	   strcpy(str,"MOUTH");
	  fprintf(stdprn,"  STATE         %-5s %-6.1f\n\n",str,np->mconst);
	 }
       }
      fprintf(stdprn,"  CONNECTIONS:\n");
      if (np->con)
       {
	fprintf(stdprn,"  Sending   Current   Type      Compound  Current   State\n");
	for (cp=np->con; cp!=NULL; cp=cp->next)
	 {
	  if (cp->ctype == 0)
	   fprintf(stdprn,"  %-6s    %-6.1f    DIRECT\n",cp->sname,cp->Isr*1e9);
	  else
	   if (cp->ctype == 1)
	    fprintf(stdprn,"  %-6s    %-6.1f    GATED     %-6s    %-6.1f    %d\n",
		    cp->sname,cp->Isr*1e9,cp->cname,cp->Icr*1e9,cp->U);
	   else
	    fprintf(stdprn,"  %-6s    %-6.1f    MODULATED %-6s    %-6.1f\n",
		    cp->sname,cp->Isr*1e9,cp->cname,cp->Icr*1e9);
	 }
       }
      fprintf(stdprn,"\n\n");
     }
   }
 }