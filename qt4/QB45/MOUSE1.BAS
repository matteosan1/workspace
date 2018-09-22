DECLARE SUB MouseOn ()
DECLARE SUB SetMouseCursor (x!, y!,v())
'$INCLUDE: 'qb.bi'

DIM SHARED inregs AS RegTypeX, outregs AS RegTypeX
dim v(32) as single

FOR i = 1 TO 32
        READ v(i)
NEXT


SCREEN 12
line(0,0)-(100,100),15,bf

CALL SetMouseCursor(7, 7,v())
CALL MouseOn
DO
	a$ = INKEY$
	IF a$ = "q" THEN EXIT DO
LOOP
END

data &Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff
data &Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff,&Hffff

data &H0000,&H0100,&H0100,&H0100,&H0fe0,&H0100,&H0100,&H0100
data &H0000,&H0000,&H0000,&H0000,&H0000,&H0000,&H0000,&H0000
 
'DATA 65087,65087,65087,65087,65087,65087,32768
'DATA 32896,32768,65087,65087,65087,65087,65087,65087,65535
'DATA 0,128,128,128,128,128,0
'DATA 15934,0,128,128,128,128,128,0,0

      





SUB GetMousePos (x, y, button)
inregs.ax = 3
CALL INTERRUPTX(51, inregs, outregs)
x = outregs.cx
y = outregs.dx
button = outregs.bx
END SUB

SUB MouseOff
inregs.ax = 2
CALL INTERRUPTX(51, inregs, outregs)
END SUB

SUB MouseOn
inregs.ax = 0
CALL INTERRUPTX(51, inregs, outregs)
inregs.ax = 1
CALL INTERRUPTX(51, inregs, outregs)
END SUB

SUB SetMouseCursor (x, y,v())
def seg = varseg(v(1))
inregs.ax = 9
inregs.bx = x
inregs.cx = y
inregs.es = VARseg(v(1))
inregs.dx = VARptr(v(1))
CALL INTERRUPTX(51, inregs, outregs)
END SUB

SUB SetMousePos (x, y)
inregs.ax = 4
inregs.cx = x
inregs.dx = y
CALL INTERRUPTX(51, inregs, outregs)
END SUB

SUB SetMouseX (xmin, xmax)
inregs.ax = 7
inregs.cx = xmin
inregs.dx = xmax
CALL INTERRUPTX(51, inregs, outregs)
END SUB

SUB SetMouseY (ymin, ymax)
inregs.ax = 8
inregs.cx = ymin
inregs.dx = ymax
CALL INTERRUPTX(51, inregs, outregs)
END SUB

