REM 3D program with rotation
REM from http://www.bath.ac.uk/~cs1ars
REM email alexslack56@hotmail.com
REM program dated 29 june 2000, although it must of been written before then.

SCREEN 9, 1, 0
DIM n, nos, a, b, vx, vy, te, pe AS INTEGER
nos = 8: n = nos
DIM x(n), y(n), x, y, z, d AS INTEGER
DIM t(n), ref(n), p(n), r(n), z(n)
DIM c(8)
RANDOMIZE TIMER / 3
ap% = 1
col% = (RND * 1024)

REM spherical polar co-ordinate starfield
REM variables x,y,z are 3d cartesian star location
REM r is its roh or radius from origin
REM t is its angle from y axis
REM ref is used to create sine wave star movements (6.28 corrosponds to 1750)
REM oy, ox are old 2d locations (for erasing)
REM expanded 10-5-00 : crosses instead of dots

FOR n = 1 TO nos
ref(n) = (RND * 6.28)
r(n) = 50 * SIN(ref(n))
t(n) = (RND * 6.28)
p(n) = (RND * 6.28)
NEXT n


vz = -100
pe = 1: te = -1: re = -1
LOCATE 1, 1
PRINT "   vx="; vx; "vy="; vy; "vz= "; vz; "     "
PRINT " te="; te; " pe="; pe; " re="; re
10
FOR n = 1 TO nos

IF te = -1 THEN GOTO 12
IF t(n) > 6.28 THEN t(n) = 0 ELSE t(n) = t(n) + .03
12

IF pe = -1 THEN GOTO 14
IF p(n) > 6.28 THEN p(n) = 0 ELSE p(n) = p(n) + .03
14

IF re = -1 THEN GOTO 16
IF ref(n) > 6.28 THEN ref(n) = 0
r(n) = 50 * SIN(ref(n))
ref(n) = ref(n) + .03
16

REM *************** tpr > xyz bit ***************
x(n) = COS(p(n)) * r(n) * SIN(t(n))
y(n) = COS(p(n)) * r(n) * COS(t(n))
z(n) = SIN(p(n)) * r(n)
REM ************ end of tpr > xyz bit ****************


i$ = LCASE$(INKEY$)
IF i$ = "f" THEN vz = vz + 2
IF i$ = "v" THEN vz = vz - 2
IF i$ = "d" THEN vy = vy - 1
IF i$ = "c" THEN vy = vy + 1
IF i$ = "z" THEN vx = vx - 1
IF i$ = "x" THEN vx = vx + 1
IF i$ = "t" THEN te = -te
IF i$ = "p" THEN pe = -pe
IF i$ = "r" THEN re = -re

IF i$ = "" THEN GOTO 20

REM **************** start of pp bit *************
20

az = z(n) - vz
IF az <= 10 THEN GOTO 30
az = az / 300
z1 = (z(n) - 5) - vz: z1 = z1 / 300
z2 = (z(n) + 5) - vz: z2 = z2 / 300

xx = x(n) - vx: yy = y(n) - vy

a = xx / az + 320
b = yy / az + 175


c(1) = (xx - 5) / az + 320 '     x, use c(1),b
c(2) = (xx + 5) / az + 320 '     x, use c(2),b
c(3) = (yy - 5) / az + 175 '     y, use a,c(3)
c(4) = (yy + 5) / az + 175 '     y, use a,c(4)
c(5) = xx / z1 + 320 '     x, use c(5),c(6)
c(6) = yy / z1 + 175 '     y, use c(5),c(6)
c(7) = xx / z2 + 320 '     x, use c(7),c(8)
c(8) = yy / z2 + 175 '     y, use c(7),c(8)

COLOR ((n + col%) MOD 15) + 1
GOSUB 1000

REM ***************** end of pp bit *****************
30
                     
NEXT n
REM ******screen update routine***********
IF ap% = 1 THEN ap% = 0 ELSE ap% = 1
WAIT &H3DA, 8      'important! wait for vertical retrace
SCREEN 9, , ap%, 1 - ap%
CLS
LOCATE 1, 1: COLOR 15
PRINT "   vx="; vx; "vy="; vy; "vz= "; vz; "     "
PRINT " te="; te; " pe="; pe; " re="; re
REM *********back to start************
GOTO 10


1000 REM **** sub one - wireframe models ****

REM ****** keep for reference ****
'LINE (c(1), b)-(c(2), b)      'left x, right x
'LINE (a, c(3))-(a, c(4))      'down y, up y
'LINE (c(5), c(6))-(c(7), c(8))       'close z, far z
'a = centre x, b = centre y, (together make centre z?)
REM ******************************

LINE (c(1), b)-(c(5), c(6))
LINE (c(5), c(6))-(c(2), b)
LINE (c(2), b)-(c(7), c(8))
LINE (c(7), c(8))-(c(1), b)

LINE (c(1), b)-(a, c(4))
LINE (a, c(4))-(c(2), b)
LINE (c(2), b)-(a, c(3))
LINE (a, c(3))-(c(1), b)

LINE (a, c(4))-(c(5), c(6))
LINE (c(5), c(6))-(a, c(3))
LINE (a, c(3))-(c(7), c(8))
LINE (c(7), c(8))-(a, c(4))




RETURN

