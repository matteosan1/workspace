/*
 * NAME: lcos(irad)
 *
 * FUNCTION: lcos returns by table lookup the cos of irad (radx1000)
 */

int lcos(irad)
  int irad;
 {
  while (irad < 0)
   irad += TWOPI;
  while (irad >= TWOPI)
   irad -= TWOPI;
  return(icos[(irad+1)/2]);
 }