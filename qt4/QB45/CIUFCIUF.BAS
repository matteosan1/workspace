DECLARE SUB ChiusuraLinea ()
DECLARE SUB Stampa ()
DECLARE SUB Rivisualizza (ob!)
DECLARE SUB DisegnaCircoli (x!, y!, r!, rotazione!, apertura!, colore!)
DECLARE FUNCTION rad! (x!)
DECLARE SUB CalcolaInizioInverso (x1, y1, x2, y2, rotax!, r!)
DECLARE SUB Esci ()
DECLARE SUB Intro ()
DECLARE SUB Carica ()
DECLARE SUB Salva ()
DECLARE SUB CalcolaInizio (xf!, yf!, rotax!, x!, y!, tipo!, rotazione!)
DECLARE SUB ZoomOut ()
DECLARE SUB ZoomIn (s)
DECLARE SUB DisegnaTutto ()
DECLARE SUB DisegnaBinario (x, y, tipo!, rotazione!, colore, p, q)

'$dynamic

TYPE binario
        ID AS INTEGER
        posX AS SINGLE
        posY AS SINGLE
        rotazione AS SINGLE
        tipo AS SINGLE
        proxy AS INTEGER
        invproxy AS INTEGER
END TYPE

DIM SHARED nome$(80), raggio(80), angolo(80)
DIM SHARED elemento(2000) AS binario, binari, scala, xmax, xmin, ymax, ymin
DIM SHARED loaded, l$, descrizione$, scartamento, inv
DIM SHARED plastico$(2000), plastico(2000, 3), nplastico, nelementi
DIM cx(2), cy(2)

nbinari = 66: scala = 1: binari = 0: loaded = 0
xmin = 0: xmax = 600: ymin = 0: ymax = 400
altro = 1: nelementi = 0:scartamento = .9: nplastico = 0

CALL Intro
OPEN "binari.dat" FOR INPUT AS #1
        FOR i = 1 TO 79
                INPUT #1, nome$(i)
                INPUT #1, raggio(i)
                INPUT #1, angolo(i)
        NEXT
CLOSE #1
       
SCREEN 12
VIEW (20, 10)-(620, 410), 2, 15
WINDOW (xmax, ymax)-(xmin, ymin)

DO
        LOCATE 27, 74: PRINT USING "1/###"; scala
        LOCATE 27, 3: PRINT descrizione$
        IF altro = 1 THEN LOCATE 28, 1: PRINT "   N nuova_linea  TAB sel.  Z zoom  C elimina  INVIO misura   A altro        "
        IF altro = 2 THEN LOCATE 28, 1: PRINT "   S stampa  L carica_plastico  W salva_plstico  Q esci       A altro        "
        a$ = ""
        DO WHILE a$ = ""
             a$ = INKEY$
        LOOP
        c = ASC(RIGHT$(a$, 1))
        IF a$ = "S" AND altro = 2 THEN CALL Stampa
        IF a$ = "L" AND altro = 2 THEN CALL Carica
        IF a$ = "W" AND altro = 2 THEN CALL Salva
        IF a$ = "Q" AND altro = 2 THEN CALL Esci
        IF a$ = CHR$(13) THEN
                CALL MouseOn
                x = INT((xmax + xmin) / 2)
                y = INT((ymax + ymin) / 2)
                CALL SetMousePos(x, y)
                x1 = 0: x2 = 0: y1 = 0: y2 = 0
                DO
                        CALL GetMousePos(x, y, button)
                        IF button <>0 THEN
                                x = x - 20
                                y = 400 - (y - 10)
                                x = xmin+(xmax-xmin)/600*x
                                y = ymin+(ymax-ymin)/400*y
                                IF button=1 THEN x2 = x: y2 = y
                                if button=2 THEN x1 = x: y1 = y
                        END IF
                        IF button = 3 THEN CALL MouseOff: EXIT DO
                        dist = SQR((x1 - x2) ^ 2 + (y1 - y2) ^ 2)
                        LOCATE 28, 1: PRINT USING " x1: ###.##"; x1; : PRINT USING "     x2: ###.##"; x2;
                        PRINT USING "     y1: ###.##"; y1; : PRINT USING "     y2: ###.##"; y2;
                        PRINT USING "    d: ###.###     "; dist
                LOOP
        END IF
        IF a$ = "A" THEN
                SELECT CASE altro
                        CASE 1
                                altro = 2
                        CASE 2
                                altro = 1
                END SELECT
        END IF
        IF a$ = "C" AND altro = 1 THEN
                cancella = 1
                ob = 0: oob = 0
        END IF
        IF a$ = "N" AND altro = 1 THEN
                nuovo = 1: button = 0
                CALL SetMouseX(20, 620)
                call SetMouseY(10,410)
                CALL MouseOn
                x = INT((xmax + xmin) / 2)
                y = INT((ymax + ymin) / 2)
                CALL SetMousePos(x, y)
        END IF
        IF c = 9 AND altro = 1 THEN
                vecchio = 1
                ob = 1: oob = 0
                inv = 0: a = 0
        END IF
        IF a$ = "Z" AND altro = 1 THEN
                DO
                        lOCATE 28, 1: PRINT "   Sei nella scala 1/"; scala; "  > zoom in  < zoom out, ESC per uscire       "
                        a$ = ""
                        DO WHILE a$ = ""
                             a$ = INKEY$
                        LOOP
                        IF ASC(a$) = 27 THEN EXIT DO
                        IF a$ = ">" AND scala <> 100 THEN
                                IF scala = 1 THEN scala1 = 5
                                IF scala = 5 THEN scala1 = 10
                                IF scala = 10 THEN scala1 = 120
                                CALL ZoomIn(scala1)
                                EXIT DO
                        END IF
                        IF a$ = "<" AND scala <> 1 THEN
                                CALL ZoomOut
                                EXIT DO
                        END IF
                LOOP
                CALL DisegnaTutto
        END IF

        DO WHILE nuovo = 1
                LOCATE 28, 1: PRINT "   con il mouse scegli il punto di partenza, tasto dx scegli, tasto sx esci "
                CALL GetMousePos(x, y, button)
                IF button = 2 THEN CALL MouseOff: nuovo = 0
                IF button = 1 THEN
                        x = x - 20
                        y = 400 - (y - 10)
                        x = xmin+(xmax-xmin)/600*x
                        y = ymin+(ymax-ymin)/400*y
                        CALL MouseOff
                        indice = 1
                        LOCATE 28, 1: PRINT "                                                                           "
                        LOCATE 28, 1: PRINT nome$(indice)
                        LOCATE 28, 20: PRINT "PGUP/PGDN per scegliere binario, invio per confermare"
                        DO
                                a$ = ""
                                DO WHILE a$ = ""
                                     a$ = INKEY$
                                LOOP
                                c = ASC(RIGHT$(a$, 1))
                                IF c = 73 AND indice > 1 THEN indice = indice - 1: LOCATE 28, 1: PRINT "                  "
                                IF c = 81 AND indice < 32 THEN indice = indice + 1: LOCATE 28, 1: PRINT "              "
                                LOCATE 28, 1: PRINT nome$(indice)
                                IF ASC(a$) = 13 THEN EXIT DO
                        LOOP
                        LOCATE 28, 1: PRINT "                  "
                        LOCATE 28, 1: INPUT "Rotazione: ", rotazione
                        LOCATE 28, 1: PRINT "                                            "
                        nplastico = nplastico + 1
                        plastico$(nplastico) = nome$(indice)
                        CALL DisegnaBinario(x, y, indice, rotazione, 0, -1, 1)
                        nuovo = 0
                END IF
        LOOP
       
        DO WHILE cancella = 1
                LOCATE 28, 1: PRINT "   con il TAB seleziona la linea da cancellare, INVIO conferma, ESC esci       "
                a$ = ""
                DO WHILE a$ = ""
                        a$ = INKEY$
                LOOP
                c = ASC(RIGHT$(a$, 1))
                IF ASC(a$) = 27 THEN
                        cancella = 0
                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 0, 0, 0)
                END IF
                DO WHILE c = 9
                        ob = ob + 1
                        IF ob = binari + 1 THEN ob = 1
                        IF elemento(ob).proxy = 0 THEN
                                        CALL Rivisualizza(ob)
                                        IF oob <> 0 THEN CALL DisegnaBinario(elemento(oob).posX, elemento(oob).posY, elemento(oob).tipo, elemento(oob).rotazione, 0, 0, 0)
                                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 4, 0, 0)
                                        oob = ob
                                        EXIT DO
                        END IF
                LOOP
                IF ASC(a$) = 13 THEN
                        i = 0
                        DO WHILE i < nplastico
                                i = i + 1
                                FOR j = 1 TO 3
                                        IF plastico(i, j) = elemento(ob).ID THEN
                                                FOR k = 1 TO binari
                                                        IF elemento(k).ID = plastico(i, 1) THEN
                                                                CALL DisegnaBinario(elemento(k).posX, elemento(k).posY, elemento(k).tipo, elemento(k).rotazione, 2, 0, 0)
                                                                elemento(k).tipo = 0
                                                        END IF
                                                        IF elemento(k).ID = plastico(i, 2) THEN
                                                                CALL DisegnaBinario(elemento(k).posX, elemento(k).posY, elemento(k).tipo, elemento(k).rotazione, 2, 0, 0)
                                                                elemento(k).tipo = 0
                                                        END IF
                                                        IF elemento(k).ID = plastico(i, 3) THEN
                                                                CALL DisegnaBinario(elemento(k).posX, elemento(k).posY, elemento(k).tipo, elemento(k).rotazione, 2, 0, 0)
                                                                elemento(k).tipo = 0
                                                        END IF
                                                NEXT
                                                oob = i
                                                EXIT DO
                                        END IF
                                NEXT
                        LOOP
                        FOR i = 1 TO binari
                                IF elemento(i).proxy = plastico(oob, 1) OR elemento(i).proxy = plastico(oob, 2) OR elemento(i).proxy = plastico(oob, 3) THEN elemento(i).proxy = 0
                                IF elemento(i).invproxy = plastico(oob, 1) OR elemento(i).invproxy = plastico(oob, 2) OR elemento(i).invproxy = plastico(oob, 3) THEN elemento(i).invproxy = 0
                        NEXT
                        i = 0
                        DO WHILE i < binari
                                i = i + 1
                                IF elemento(i).tipo = 0 THEN
                                        FOR j = i TO binari
                                                elemento(j) = elemento(j + 1)
                                        NEXT
                                        binari = binari - 1
                                        i = i - 1
                                END IF
                        LOOP
                        FOR i = oob TO nplastico
                                plastico$(i) = plastico$(i + 1)
                                plastico(i, 1) = plastico(i + 1, 1)
                                plastico(i, 2) = plastico(i + 1, 2)
                                plastico(i, 3) = plastico(i + 1, 3)
                        NEXT
                        nplastico = nplastico - 1
                        cancella = 0
                        CALL DisegnaTutto
                END IF
        LOOP
       
        DO WHILE vecchio = 1
                LOCATE 28, 1: PRINT "   con il TAB seleziona la linea da proseguire, INVIO conferma, ESC esci       "
                a$ = ""
                DO WHILE a$ = ""
                        a$ = INKEY$
                LOOP
                c = ASC(RIGHT$(a$, 1))
                IF ASC(a$) = 27 THEN
                        vecchio = 0
                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 0, 0, 0)
                END IF
                DO WHILE c = 9
                        a = a + 1
                        IF a = 3 THEN a = 1: ob = ob + 1
                        IF ob > binari AND oob = 0 THEN EXIT DO
                        IF ob > binari THEN ob = 1
                        IF a = 1 AND elemento(ob).proxy = 0 THEN
                                        CALL Rivisualizza(ob)
                                        IF oob <> 0 THEN CALL DisegnaBinario(elemento(oob).posX, elemento(oob).posY, elemento(oob).tipo, elemento(oob).rotazione, 0, 0, 0)
                                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 4, 0, 0)
                                        oob = ob
                                        inv = 0
                                        EXIT DO
                        END IF
                        IF a = 2 AND elemento(ob).invproxy = 0 THEN
                                        CALL Rivisualizza(ob)
                                        IF oob <> 0 THEN CALL DisegnaBinario(elemento(oob).posX, elemento(oob).posY, elemento(oob).tipo, elemento(oob).rotazione, 0, 0, 0)
                                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 9, 0, 0)
                                        oob = ob
                                        inv = 1
                                        EXIT DO
                        END IF
                LOOP
                IF ASC(a$) = 13 THEN
                        indice = 1: oindice = 1
                        CALL DisegnaBinario(elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione, 0, 0, 0)
                        IF inv = 0 THEN CALL CalcolaInizio(xf, yf, rotax, elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione)
                        IF inv = 1 THEN CALL CalcolaInizioInverso(xf, yf, rotax, elemento(ob).posX, elemento(ob).posY, elemento(ob).rotazione)
                        LOCATE 28, 1: PRINT "                                                                           "
                        LOCATE 28, 1: PRINT nome$(indice)
                        LOCATE 28, 20: PRINT "   PGUP/PGDN cambia binario,INVIO per confermare"
                        CALL DisegnaBinario(xf, yf, indice, rotax, 4, 0, 0)
                        DO
                                a$ = ""
                                DO WHILE a$ = ""
                                        a$ = INKEY$
                                      LOOP
                                c = ASC(RIGHT$(a$, 1))
                                IF c = 73 AND oindice > 1 THEN oindice = indice: indice = indice - 1: LOCATE 28, 1: PRINT "                      "
                                IF c = 81 AND oindice < nbinari THEN oindice = indice: indice = indice + 1: LOCATE 28, 1: PRINT "                  "
                                LOCATE 28, 1: PRINT nome$(indice)
                                CALL DisegnaBinario(xf, yf, oindice, rotax, 2, 0, 0)
                                CALL DisegnaBinario(xf, yf, indice, rotax, 4, 0, 0)
                                IF ASC(a$) = 13 THEN EXIT DO
                        LOOP
                        nplastico = nplastico + 1
                        plastico$(nplastico) = nome$(indice)
                        t = elemento(ob).ID



                        CALL DisegnaBinario(xf, yf, indice, rotax, 0, t, 1)
                        IF inv = 0 THEN elemento(ob).proxy = elemento(binari).ID
                        IF inv = 1 THEN elemento(ob).invproxy = elemento(binari).ID
                        CALL ChiusuraLinea
                        vecchio = 0
                        CALL DisegnaTutto
                END IF
        LOOP
LOOP
   
' stampa del grafico
' migliorare cancellazione scambi se non vuoti
' migliorare aspetto scambio curvo

SUB CalcolaInizio (xf, yf, rotax, x, y, tipo, rotazione)

IF tipo = 70 OR tipo = 71 THEN
        xf = x + raggio(tipo) * COS(rad(rotazione)) - angolo(tipo) * SIN(rad(rotazione))
        yf = y + raggio(tipo) * SIN(rad(rotazione)) + angolo(tipo) * COS(rad(rotazione))
        rotax = rotazione + SGN(angolo(tipo)) * 42
        IF rotax < 0 THEN rotax = rotax + 360
        IF rotax > 360 THEN rotax = rotax - 360
        EXIT SUB
END IF

IF tipo > 73 THEN
        xf = x + raggio(tipo) * COS(rad(rotazione)) - 1.68 * SGN(angolo(tipo)) * SIN(rad(rotazione))
        yf = y + raggio(tipo) * SIN(rad(rotazione)) + 1.68 * SGN(angolo(tipo)) * COS(rad(rotazione))
        rotax = rotazione + angolo(tipo)
        IF rotax < 0 THEN rotax = rotax + 360
        IF rotax > 360 THEN rotax = rotax - 360
        EXIT SUB
END IF
              
IF angolo(tipo) = 0 THEN
        xf = x + raggio(tipo) * COS(rad(rotazione))
        yf = y + raggio(tipo) * SIN(rad(rotazione))
END IF

IF angolo(tipo) <> 0 THEN
        rx = x + raggio(tipo) * COS(rad(rotazione + 90 * SGN(angolo(tipo))))
        ry = y + raggio(tipo) * SIN(rad(rotazione + 90 * SGN(angolo(tipo))))

        inizio = rotazione - 90 * SGN(angolo(tipo))
        fine = inizio + angolo(tipo)
        IF SGN(angolo(tipo)) < 0 THEN
                xf = rx + raggio(tipo) * COS(rad(fine))
                yf = ry + raggio(tipo) * SIN(rad(fine))
        END IF
        IF SGN(angolo(tipo)) > 0 THEN
                xf = rx + raggio(tipo) * COS(rad(fine))
                yf = ry + raggio(tipo) * SIN(rad(fine))
        END IF
END IF

rotax = rotazione + angolo(tipo)
IF rotax < 0 THEN rotax = rotax + 360
IF rotax > 360 THEN rotax = rotax - 360
END SUB

SUB CalcolaInizioInverso (xf, yf, rotax, x, y, r)
xf = x
yf = y
rotax = r + 180
IF rotax > 360 THEN rotax = rotax - 360
END SUB

SUB Carica
VIEW: CLS
FILES "*.pls"
LOCATE 10, 2: INPUT "Nome del plastico da caricare: ", l$
loaded = 1
OPEN l$ + ".pls" FOR INPUT AS #1
        INPUT #1, descrizione$
        INPUT #1, nelementi
        INPUT #1, binari
        FOR i = 1 TO binari
                INPUT #1, elemento(i).ID
                INPUT #1, elemento(i).posX
                INPUT #1, elemento(i).posY
                INPUT #1, elemento(i).rotazione
                INPUT #1, elemento(i).tipo
                INPUT #1, elemento(i).proxy
                INPUT #1, elemento(i).invproxy
        NEXT
        INPUT #1, nplastico
        FOR i = 1 TO nplastico
                INPUT #1, plastico$(i)
                FOR j = 1 TO 3
                        INPUT #1, plastico(i, j)
                NEXT
        NEXT
CLOSE #1
LOCATE 12, 2: PRINT "   plastico caricato...                          "
sleep 2:cls
CALL ZoomOut
END SUB

SUB ChiusuraLinea
CALL CalcolaInizio(x1, y1, r, elemento(binari).posX, elemento(binari).posY, elemento(binari).tipo, elemento(binari).rotazione)
FOR i = 1 TO binari - 1
        IF elemento(i).proxy = 0 THEN
                CALL CalcolaInizio(x2, y2, r2, elemento(i).posX, elemento(i).posY, elemento(i).tipo, elemento(i).rotazione)
                dist = (x1 - x2) ^ 2 + (y1 - y2) ^ 2
                IF (r - r2) = ABS(180) AND dist < .25 THEN
                        COLOR 4
                        LOCATE 27, 35: PRINT "LINEA CHIUSA": SLEEP 5
                        LOCATE 27, 35: PRINT "            "
                        COLOR 15
                        elemento(i).proxy = elemento(binari).ID
                        elemento(binari).proxy = elemento(i).ID
                END IF
        END IF
        IF elemento(i).invproxy = 0 THEN
                dist = (x1 - elemento(i).posX) ^ 2 + (y1 - elemento(i).posY) ^ 2
                IF r = elemento(i).rotazione AND dist < .25 THEN
                        COLOR 4
                        LOCATE 27, 35: PRINT "LINEA CHIUSA": SLEEP 5
                        LOCATE 27, 35: PRINT "            "
                        COLOR 15
                        elemento(i).invproxy = elemento(binari).ID
                        elemento(binari).proxy = elemento(i).ID
                END IF
        END IF
NEXT
END SUB

SUB DisegnaBinario (x, y, tipo, rotazione, colore, p, q)

IF tipo = 33 OR tipo = 36 OR tipo = 39 OR tipo = 42 OR tipo = 45 OR tipo = 48 THEN
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x, y, angolo(tipo), rotazione, colore, p, q)
        EXIT SUB
END IF

IF tipo = 34 OR tipo = 37 OR tipo = 40 OR tipo = 43 OR tipo = 46 OR tipo = 49 THEN
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        CALL CalcolaInizio(x1, y1, r1, x, y, raggio(tipo), rotazione)
        CALL CalcolaInizioInverso(x2, y2, r2, x1, y1, r1)
        q = q + 1
        CALL DisegnaBinario(x2, y2, angolo(tipo), r2, colore, p, q)
        EXIT SUB
END IF

IF tipo = 35 OR tipo = 38 OR tipo = 41 OR tipo = 44 OR tipo = 47 OR tipo = 50 THEN
        theta1 = rotazione + SGN(angolo(angolo(tipo))) * 90 - angolo(angolo(tipo))
        x1 = x + 1.68 * COS(rad(theta1))
        y1 = y + 1.68 * SIN(rad(theta1))
        theta2 = theta1 - SGN(angolo(angolo(tipo))) * 90
        x2 = x1 + raggio(angolo(tipo)) * COS(rad(theta2))
        y2 = y1 + raggio(angolo(tipo)) * SIN(rad(theta2))
        r = rotazione + 180 - angolo(angolo(tipo))
        IF r > 360 THEN r = r - 360
        CALL DisegnaBinario(x2, y2, (tipo - 2), r, colore, p, q)
        EXIT SUB
END IF

IF tipo = 51 OR tipo = 54 THEN
        CALL DisegnaBinario(x, y, angolo(tipo), rotazione, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        EXIT SUB
END IF

IF tipo = 52 OR tipo = 55 THEN
        CALL DisegnaBinario(x, y, angolo(tipo), rotazione, colore, p, q)
        CALL CalcolaInizio(x1, y1, r1, x, y, angolo(tipo), rotazione)
        CALL CalcolaInizioInverso(x2, y2, r2, x1, y1, r1)
        q = q + 1
        CALL DisegnaBinario(x2, y2, raggio(tipo), r2, colore, p, q)
        EXIT SUB
END IF

IF tipo = 53 OR tipo = 56 THEN
        theta1 = rotazione + SGN(angolo(raggio(tipo))) * 90 - SGN(angolo(raggio(tipo))) * 42
        x1 = x + SGN(angolo(raggio(tipo))) * angolo(raggio(tipo)) * COS(rad(theta1))
        y1 = y + SGN(angolo(raggio(tipo))) * angolo(raggio(tipo)) * SIN(rad(theta1))
        theta2 = theta1 - SGN(angolo(raggio(tipo))) * 90
        x2 = x1 + raggio(raggio(tipo)) * COS(rad(theta2))
        y2 = y1 + raggio(raggio(tipo)) * SIN(rad(theta2))
        r = rotazione + 180 - SGN(angolo(raggio(tipo))) * 42
        IF r > 360 THEN r = r - 360
        CALL DisegnaBinario(x2, y2, angolo(tipo), r, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x2, y2, raggio(tipo), r, colore, p, q)
        EXIT SUB
END IF

IF tipo > 56 AND tipo < 63 THEN
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        x1 = x + ((raggio(raggio(tipo)) / 2) * COS(rad(rotazione)))
        y1 = y + ((raggio(raggio(tipo)) / 2) * SIN(rad(rotazione)))
        rot = (rotazione + 180 - angolo(tipo))
        xf = x1 + ((raggio(raggio(tipo)) / 2) * COS(rad(rot)))
        yf = y1 + ((raggio(raggio(tipo)) / 2) * SIN(rad(rot)))
        rot = (rotazione - angolo(tipo))
        q = q + 1
        if p<>0 then p=-1 else p=0
        CALL DisegnaBinario(xf, yf, raggio(tipo), rot, colore, p, q)
        EXIT SUB
END IF

IF tipo = 63 THEN
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x, y, angolo(tipo), rotazione, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x, y, angolo(tipo) + 1, rotazione, colore, p, q)
        EXIT SUB
END IF

IF tipo = 64 THEN
        CALL DisegnaBinario(x, y, raggio(tipo), rotazione, colore, p, q)
        CALL CalcolaInizio(x1, y1, r1, x, y, raggio(tipo), rotazione)
        CALL CalcolaInizioInverso(x2, y2, r2, x1, y1, r1)
        q = q + 1
        CALL DisegnaBinario(x2, y2, angolo(tipo), r2, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(x2, y2, angolo(tipo) + 1, r2, colore, p, q)
        EXIT SUB
END IF

IF tipo = 65 THEN
        CALL DisegnaBinario(x, y, angolo(tipo), rotazione, colore, p, q)
        CALL CalcolaInizio(xr, yr, r, x, y, angolo(tipo), rotazione)
        CALL CalcolaInizioInverso(xf, yf, rf, xr, yr, r)
        q = q + 1
        CALL DisegnaBinario(xf, yf, angolo(tipo), rf, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(xf, yf, raggio(tipo), rf, colore, p, q)
        EXIT SUB
END IF

IF tipo = 66 THEN
        CALL DisegnaBinario(x, y, angolo(tipo) + 1, rotazione, colore, p, q)
        CALL CalcolaInizio(xr, yr, r, x, y, angolo(tipo) + 1, rotazione)
        CALL CalcolaInizioInverso(xf, yf, rf, xr, yr, r)
        q = q + 1
        CALL DisegnaBinario(xf, yf, angolo(tipo) + 1, rf, colore, p, q)
        q = q + 1
        CALL DisegnaBinario(xf, yf, raggio(tipo), rf, colore, p, q)
        EXIT SUB
END IF

IF tipo > 73 THEN
        xi = x + scartamento / 2 * COS(rad(rotazione + 90 * SGN(angolo(tipo))))
        yi = y + scartamento / 2 * SIN(rad(rotazione + 90 * SGN(angolo(tipo))))
        x1 = raggio(tipo) * COS(rad(rotazione)) - 1.68 * SGN(angolo(tipo)) * SIN(rad(rotazione))
        y1 = raggio(tipo) * SIN(rad(rotazione)) + 1.68 * SGN(angolo(tipo)) * COS(rad(rotazione))
        xc = x + x1
        yc = y + y1
        xa = xc + scartamento / 2 * COS(rad(rotazione + 90 * SGN(angolo(tipo)) + angolo(tipo)))
        ya = yc + scartamento / 2 * SIN(rad(rotazione + 90 * SGN(angolo(tipo)) + angolo(tipo)))
        xb = xc - scartamento / 2 * COS(rad(rotazione + 90 * SGN(angolo(tipo)) + angolo(tipo)))
        yb = yc - scartamento / 2 * SIN(rad(rotazione + 90 * SGN(angolo(tipo)) + angolo(tipo)))
        tan1 = TAN(rad(rotazione))
        tan2 = TAN(rad(rotazione + angolo(tipo)))
        xia = ((yi - ya) + tan2 * xa - tan1 * xi) / (tan2 - tan1)
        IF rotazione + angolo(tipo) = 90 OR rotazione + angolo(tipo) = 270 THEN
                yia = tan1 * (xia - xi) + yi
        ELSE
                yia = tan2 * (xia - xa) + ya
        END IF
        xib = ((yi - yb) + tan2 * xb - tan1 * xi) / (tan2 - tan1)
        IF rotazione + angolo(tipo) = 90 OR rotazione + angolo(tipo) = 270 THEN
                yib = tan1 * (xib - xi) + yi
        ELSE
                yib = tan2 * (xib - xb) + yb
        END IF
        LINE (xia, yia)-(xa, ya), colore
        LINE (xa, ya)-(xb, yb), colore
        LINE (xib, yib)-(xb, yb), colore
        IF p <> 0 THEN
                binari = binari + 1
                nelementi = nelementi + 1
                elemento(binari).ID = nelementi
                elemento(binari).posX = x
                elemento(binari).posY = y
                elemento(binari).rotazione = rotazione
                elemento(binari).tipo = tipo
                elemento(binari).proxy = 0
                elemento(binari).invproxy = p
                plastico(nplastico, q) = nelementi
        END IF
        IF p < 0 THEN elemento(binari).invproxy = 0
        EXIT SUB
END IF

IF (tipo = 71 OR tipo = 70) THEN
        x1 = raggio(tipo) * COS(rad(rotazione)) - angolo(tipo) * SIN(rad(rotazione))
        y1 = raggio(tipo) * SIN(rad(rotazione)) + angolo(tipo) * COS(rad(rotazione))
        xc = x + x1
        yc = y + y1
        xa = xc + scartamento / 2 * COS(rad(rotazione + 132 * SGN(angolo(tipo))))
        ya = yc + scartamento / 2 * SIN(rad(rotazione + 132 * SGN(angolo(tipo))))
        xb = xc - scartamento / 2 * COS(rad(rotazione + 132 * SGN(angolo(tipo))))
        yb = yc - scartamento / 2 * SIN(rad(rotazione + 132 * SGN(angolo(tipo))))
        LINE (xa, ya)-(xb, yb), colore
        r = rotazione + SGN(angolo(tipo)) * 42 + 180
        x1 = 4 * scartamento * COS(rad(r))
        y1 = 4 * scartamento * SIN(rad(r))
        x3 = x + scartamento / 2 * COS(rad(rotazione - 90))
        y3 = y + scartamento / 2 * SIN(rad(rotazione - 90))
        x2 = x + scartamento / 2 * (COS(rad(rotazione + 90)))
        y2 = y + scartamento / 2 * (SIN(rad(rotazione + 90)))
        IF SGN(angolo(tipo)) = 1 THEN SWAP x2, x3: SWAP y2, y3
        LINE (xa, ya)-(xa + x1, ya + y1), colore
        LINE STEP(0, 0)-(x3, y3), colore
        LINE (xb, yb)-(xb + x1, yb + y1), colore
        LINE STEP(0, 0)-(x2, y2), colore
        IF p <> 0 THEN
                binari = binari + 1
                nelementi = nelementi + 1
                elemento(binari).ID = nelementi
                elemento(binari).posX = x
                elemento(binari).posY = y
                elemento(binari).rotazione = rotazione
                elemento(binari).tipo = tipo
                elemento(binari).proxy = 0
                elemento(binari).invproxy = p
                plastico(nplastico, q) = nelementi
        END IF
        IF p < 0 THEN elemento(binari).invproxy = 0
        exit sub
END IF
      
IF tipo < 7 OR (tipo > 66 AND tipo < 70) THEN
        x1 = x + scartamento / 2 * COS(rad(rotazione - 90))
        y1 = y + scartamento / 2 * SIN(rad(rotazione - 90))
        x2 = x + scartamento / 2 * (COS(rad(rotazione + 90)))
        y2 = y + scartamento / 2 * (SIN(rad(rotazione + 90)))
        x3 = raggio(tipo) * COS(rad(rotazione))
        y3 = raggio(tipo) * SIN(rad(rotazione))
        LINE (x1, y1)-(x1 + x3, y1 + y3), colore
        LINE (x2, y2)-(x2 + x3, y2 + y3), colore
        LINE (x3 + x1, y3 + y1)-(x2 + x3, y2 + y3), colore
        IF p <> 0 THEN
                binari = binari + 1
                nelementi = nelementi + 1
                elemento(binari).ID = nelementi
                elemento(binari).posX = x
                elemento(binari).posY = y
                elemento(binari).rotazione = rotazione
                elemento(binari).tipo = tipo
                elemento(binari).proxy = 0
                elemento(binari).invproxy = p
                plastico(nplastico, q) = nelementi
        END IF
        IF p < 0 THEN elemento(binari).invproxy = 0
        exit sub
END IF

IF (ABS(angolo(tipo)) > 0 AND ABS(angolo(tipo)) < 100) THEN
        CALL DisegnaCircoli(x, y, raggio(tipo), rotazione, angolo(tipo), colore)
        IF p <> 0 THEN
                binari = binari + 1
                nelementi = nelementi + 1
                elemento(binari).ID = nelementi
                elemento(binari).posX = x
                elemento(binari).posY = y
                elemento(binari).rotazione = rotazione
                elemento(binari).tipo = tipo
                elemento(binari).proxy = 0
                elemento(binari).invproxy = p
                plastico(nplastico, q) = nelementi
        END IF
        IF p < 0 THEN elemento(binari).invproxy = 0
       
END IF

END SUB

SUB DisegnaCircoli (x, y, r, rotazione, apertura, colore)
rx = x + r * COS(rad(rotazione + 90 * SGN(apertura)))
ry = y + r * SIN(rad(rotazione + 90 * SGN(apertura)))

inizio = rotazione - 90 * SGN(apertura)
fine = inizio + apertura
FOR i = inizio TO fine STEP .01 * SGN(apertura)
        x1 = rx + (r - scartamento / 2) * COS(rad(i))
        y1 = ry + (r - scartamento / 2) * SIN(rad(i))
        PSET (x1, y1), colore
        x2 = rx + (r + scartamento / 2) * COS(rad(i))
        y2 = ry + (r + scartamento / 2) * SIN(rad(i))
        PSET (x2, y2), colore
NEXT
LINE (x1, y1)-(x2, y2), colore

END SUB

SUB DisegnaTutto
FOR i = 1 TO binari
        CALL DisegnaBinario(elemento(i).posX, elemento(i).posY, elemento(i).tipo, elemento(i).rotazione, 0, 0, 0)
NEXT
END SUB

SUB Esci
LOCATE 28, 1: PRINT "   Uscita dal plastico..."
CALL Salva
screen 0
CLS
PRINT "Grazie per aver scelto per l'ennesima volta i prodotti MatteoSoftware."
SLEEP 3
END
END SUB

SUB Intro
CLS
FOR i = 1 TO 14: PRINT : NEXT
PRINT "           ************************************************************ "
PRINT "           *                                                          * "
PRINT "           *                         CIUF CIUF                        * "
PRINT "           *                                                          * "
PRINT "           * Programma di creazione plastici ferroviari scala N 1:160 * "
PRINT "           *                                                          * "
PRINT "           *                 basato sui modelli Roco                  * "
PRINT "           *                                                          * "
PRINT "           *                 v2.00 by MatteoSoftware                  * "
PRINT "           *                                                          * "
PRINT "           ************************************************************ "

SLEEP 6

END SUB

FUNCTION rad (x)
rad = x / 180 * 3.141593
END FUNCTION

SUB Rivisualizza (ob)
quadx = 0: quady = 0
CALL CalcolaInizio(xm, ym, r, elemento(ob).posX, elemento(ob).posY, elemento(ob).tipo, elemento(ob).rotazione)
lx = (xmax - xmin): ly = (ymax - ymin)

IF xm < xmin OR xm > xmax OR ym < ymin OR ym > ymax THEN
       
        IF INT(xm / lx) <> 0 THEN quadx = (xm MOD lx)
        IF INT(ym / ly) <> 0 THEN quady = (ym MOD ly)

        xmin = xm - quadx: ymin = ym - quady
       
        IF INT(xm / lx) = 0 THEN xmin = 0
        IF INT(ym / ly) = 0 THEN ymin = 0

        xmax = xmin + lx: ymax = ymin + ly
       
        VIEW (20, 10)-(620, 410), 2, 15
        WINDOW (xmax, ymax)-(xmin, ymin)

        ' ridisegna binari

        CALL DisegnaTutto
END IF
END SUB

SUB Salva
IF loaded = 1 THEN
        OPEN l$ + ".pls" FOR OUTPUT AS #1
                PRINT #1, descrizione$
                PRINT #1, nelementi
                PRINT #1, binari
                FOR i = 1 TO binari
                        PRINT #1, elemento(i).ID
                        PRINT #1, elemento(i).posX
                        PRINT #1, elemento(i).posY
                        PRINT #1, elemento(i).rotazione
                        PRINT #1, elemento(i).tipo
                        PRINT #1, elemento(i).proxy
                        PRINT #1, elemento(i).invproxy
                NEXT
                PRINT #1, nplastico
                FOR i = 1 TO nplastico
                        PRINT #1, plastico$(i)
                        FOR j = 1 TO 3
                                PRINT #1, plastico(i, j)
                        NEXT
                NEXT
        CLOSE #1
        LOCATE 28, 1: PRINT "   plastico salvato...                          "
END IF
IF loaded = 0 THEN
        VIEW: CLS
        LOCATE 2, 2: INPUT "Descrizione plastico "; descrizione$
        LOCATE 3, 2: INPUT "Nome file .pls "; l$
        OPEN l$ + ".pls" FOR OUTPUT AS #1
                PRINT #1, descrizione$
                PRINT #1, nelementi
                PRINT #1, binari
                FOR i = 1 TO binari
                        PRINT #1, elemento(i).ID
                        PRINT #1, elemento(i).posX
                        PRINT #1, elemento(i).posY
                        PRINT #1, elemento(i).rotazione
                        PRINT #1, elemento(i).tipo
                        PRINT #1, elemento(i).proxy
                        PRINT #1, elemento(i).invproxy
                NEXT
                PRINT #1, nplastico
                FOR i = 1 TO nplastico
                        PRINT #1, plastico$(i)
                        FOR j = 1 TO 3
                                PRINT #1, plastico(i, j)
                        NEXT
                NEXT
        CLOSE #1
        LOCATE 5, 2: PRINT "   plastico salvato...                          "
        loaded=1
END IF
sleep 2:cls
CALL ZoomOut
END SUB

SUB Stampa

redim s(73)

LOCATE 28, 1: PRINT "STAMPA IN CORSO...                                        "

WIDTH LPRINT 80

FOR j = 1 TO 73
        FOR i = 1 TO nplastico
                IF plastico$(i) = nome$(j) THEN s(j) = s(j) + 1
        NEXT
NEXT
lPRINT "ELEMENTI NECESSARI PER IL PLASTICO "; descrizione$
lPRINT
lPRINT
lPRINT "Descrizione                          Qta."
lPRINT
FOR j = 1 TO 73
        if s(j) <> 0 then lPRINT nome$(j); TAB(47); USING "##"; s(j)
NEXT
END SUB

SUB ZoomIn (scala1)
lx = (xmax - xmin) / scala1 * scala
ly = (ymax - ymin) / scala1 * scala
linee = scala1 / scala

FOR i = 1 TO linee
       LINE (xmin + i * lx, ymin)-(xmin + i * lx, ymax), 15
       LINE (xmin, ymin + i * ly)-(xmax, ymin + i * ly), 15
NEXT

LOCATE 28, 1: PRINT "con il mouse scegli il quadrato e conferma con il tasto dx      "

CALL SetMouseX(20, 620)
CALL SetMouseY(10, 410)
CALL MouseOn
DO
        CALL GetMousePos(x, y, button)
        IF button = 1 THEN EXIT DO
LOOP

x = x - 20
y = 400 - (y - 10)

x= xmin+(xmax-xmin)/600*x
y = ymin+(ymax-ymin)/400*y

xmin = x - (x MOD lx)
ymin = y - (y MOD ly)

xmax = xmin + lx: ymax = ymin + ly   

' setta window e view al quadrato scelto

call MouseOff
VIEW (20, 10)-(620, 410), 2, 15
WINDOW (xmax, ymax)-(xmin, ymin)

scala = scala1
call DisegnaTutto

END SUB

SUB ZoomOut
VIEW (20, 10)-(620, 410), 2, 15
xmin = 0: xmax = 600: ymin = 0: ymax = 400
WINDOW (xmax, ymax)-(xmin, ymin)
scala = 1
call DisegnaTutto
END SUB

