/*
 * NAME: lsin(irad)
 *
 * FUNCTION: lsin returns by table lookup the sin of irad (1000xradians)
 */

int lsin(irad)
  int irad;
 {
  while (irad < 0)
   irad += TWOPI;
  while (irad > TWOPI)
   irad -= TWOPI;
  return(isin[(irad+1)/2]);
 }