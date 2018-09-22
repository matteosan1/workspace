'$INCLUDE: 'qb.bi'

DIM SHARED inregs AS RegTypeX, outregs AS RegTypeX

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

