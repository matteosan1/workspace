DECLARE SUB playSound (object AS ANY, freq AS INTEGER)
DECLARE SUB intro (fileName AS STRING)
DECLARE SUB mouseStatus (m AS ANY)
DECLARE SUB mouseGet ()
DECLARE SUB MouseDriver (AX%, bx%, CX%, dx%)
DECLARE SUB cameraView (objects() AS ANY, camera AS ANY, xOff AS INTEGER, yOff AS INTEGER)
DECLARE SUB printFX (text AS STRING)
DECLARE SUB centerPrint (text AS STRING, yOff AS INTEGER)
DECLARE SUB followObject (object AS ANY, tx AS INTEGER, ty AS INTEGER, mode AS INTEGER)
DECLARE SUB moveHunter (object AS ANY, tx AS INTEGER, ty AS INTEGER)
DECLARE SUB followTargets (object AS ANY)
DECLARE SUB light (value AS INTEGER)
DECLARE SUB killObject (object AS ANY, x AS INTEGER, y AS INTEGER)
DECLARE SUB setSoundFX ()
DECLARE SUB playSFX (blasterNum AS INTEGER)
DECLARE SUB touch (spx AS INTEGER, spy AS INTEGER, objNum AS INTEGER)
DECLARE SUB moveCamera (camera AS ANY, target AS ANY)
DECLARE SUB putObj (number AS INTEGER, way AS STRING, px AS INTEGER, py AS INTEGER)
DECLARE SUB initPlan (world() AS ANY, effect() AS INTEGER, anim() AS ANY, fileName AS INTEGER)
DECLARE SUB putEnv (number AS INTEGER, px AS INTEGER, py AS INTEGER)
DECLARE SUB changeOptions (options AS ANY, choice AS STRING)
DECLARE SUB setPal (fileName AS STRING)
DECLARE SUB replace (object AS ANY)
DECLARE SUB moveBullet (object AS ANY)
DECLARE SUB moveCoin (object AS ANY)
DECLARE SUB action (object AS ANY)
DECLARE SUB moveBox (object AS ANY)
DECLARE SUB moveBeing (object AS ANY)
DECLARE SUB newCell (object AS ANY, cellMax AS INTEGER)
DECLARE SUB objectMove (object AS ANY, wx AS INTEGER, wy AS INTEGER)
DECLARE SUB movePlayer (object AS ANY)
DECLARE SUB initObject (objects() AS ANY, fileName AS INTEGER)
DECLARE SUB move (objects() AS ANY)
DECLARE FUNCTION form$ (number AS INTEGER)
DECLARE FUNCTION cameraChange% (x AS INTEGER, y AS INTEGER, Nobj AS INTEGER, Nspr AS INTEGER, cam AS INTEGER)
DECLARE FUNCTION shootBullet% (indoor AS INTEGER, x AS INTEGER, y AS INTEGER, dx AS INTEGER, dy AS INTEGER, number AS INTEGER)
DECLARE FUNCTION getChoice% (request AS STRING, choice1 AS STRING, choice2 AS STRING)
DECLARE FUNCTION count% (counter AS INTEGER, counterMax AS INTEGER)
DECLARE FUNCTION checkAnim% (tileNenv AS INTEGER, counterAct AS INTEGER)

CONST false = 0, true = NOT false
CONST limX = 319, limY = 199
CONST byte = 255, colMax = byte, atbMax = 63, palMax = 215
CONST tileSize = 17, pSize = 170
CONST midX = limX \ 2 - tileSize \ 2, midY = limY \ 2 - tileSize \ 2
CONST worldX = 50, worldY = 50
CONST effectMax = 7, bulletmax = 10
CONST envMax = 157, objMax = 87 + 2 + bulletmax
CONST mouseArea = 10
CONST root = "" '"c:\main\sprache\qb45\mine\new\"

TYPE sprite
  status AS INTEGER ' type of object
  nrg    AS INTEGER ' energy
  x      AS INTEGER ' position
  y      AS INTEGER ' ...
  sx     AS INTEGER ' speed
  sy     AS INTEGER ' ...
  body   AS INTEGER ' appearance
  stage  AS INTEGER ' animation cell
  dx     AS INTEGER ' direction
  dy     AS INTEGER ' ...
  td     AS INTEGER ' target direction
  tx0    AS INTEGER ' target
  ty0    AS INTEGER ' ...
  tx1    AS INTEGER ' ...
  ty1    AS INTEGER ' ...
  indoor AS INTEGER '
  number AS INTEGER ' for cell (/ event)
END TYPE

TYPE tile
  env AS STRING * 1 ' environment
  ind AS STRING * 1 ' indoor
  obj AS STRING * 1 ' object
END TYPE

TYPE gameSetting
  soundFX  AS INTEGER
  finish   AS INTEGER
  SBlaster AS INTEGER
  cheat    AS INTEGER
  win      AS INTEGER
  two      AS INTEGER
  mouse    AS INTEGER
  level    AS INTEGER
END TYPE

TYPE animation
  link  AS INTEGER
  speed AS INTEGER
END TYPE

TYPE pal
  red   AS INTEGER
  green AS INTEGER
  blue  AS INTEGER
END TYPE

TYPE playerStats
  gun     AS INTEGER
  coins   AS INTEGER
END TYPE

TYPE mouseType
  left    AS INTEGER
  middle  AS INTEGER
  right   AS INTEGER
  x       AS INTEGER
  y       AS INTEGER
  visible AS INTEGER
END TYPE

DIM blaster(25) AS STRING
DIM channel(8) AS STRING
DIM options AS gameSetting
DIM keyboard AS STRING
DIM player(1) AS playerStats
DIM clock AS SINGLE
DIM clearBuf AS STRING
DIM SHARED none AS STRING * 1
DIM SHARED viewX AS INTEGER
DIM SHARED viewY AS INTEGER
DIM SHARED mouseDat AS STRING

options.soundFX = true
options.SBlaster = true
options.level = 1

SCREEN 13
RANDOMIZE TIMER
setSoundFX
SLEEP 1
playSFX 6
printFX ">Robot Plague"
centerPrint "Copyright (C) 1997 by Philipp Lenssen", 1
centerPrint "Press i for info", 2
SLEEP 1

DO
 
  IF options.two THEN
    player(0).gun = false
    player(1).gun = false
    viewX = 4
    viewY = 4
  ELSE
    player(0).gun = false
    viewX = 7
    viewY = 5
  END IF
 
  ' $STATIC
  REDIM world(-worldX TO worldX, -worldY TO worldY) AS tile
  REDIM objects(1 TO objMax) AS sprite
  REDIM effect(envMax) AS INTEGER
  REDIM anim(envMax) AS animation
  REDIM objPic(objMax) AS STRING
  ' $DYNAMIC
  REDIM map(-viewX TO viewX, -viewY TO viewY, 1) AS INTEGER
  REDIM buf(-viewX TO viewX, -viewY TO viewY, 1) AS STRING
 
  initPlan world(), effect(), anim(), options.level
  initObject objects(), options.level
  setPal "colors"
  CLS

  DO
    clock = TIMER
    keyboard = INKEY$
    clearBuf = INKEY$
    move objects()
    IF options.two THEN
      cameraView objects(), objects(2), -80, 0
      cameraView objects(), objects(objMax - 0 - bulletmax), 80, 0
    ELSE
      cameraView objects(), objects(2), 0, 0
    END IF
    changeOptions options, keyboard
    DO UNTIL clock + .001 - TIMER <= 0
    LOOP
  LOOP UNTIL options.finish
  
  SLEEP 1
  light -12
  playSFX 5
  IF options.win THEN
    printFX "Well done"
    options.win = false
  ELSE
    printFX "Game over"
  END IF
  SLEEP 2
  CLS
  IF getChoice%("Play again", "y", "n") THEN options.finish = false
 
LOOP UNTIL options.finish
END

REM $STATIC
SUB action (object AS sprite)
 
  SHARED world() AS tile, effect() AS INTEGER
  DIM tileEffect AS INTEGER
  IF object.indoor THEN
    tileEffect = effect(ASC(world(object.x, object.y).ind))
  ELSE
    tileEffect = effect(ASC(world(object.x, object.y).env))
  END IF
  SELECT CASE tileEffect
    CASE 2 ' danger
      playSound object, 0
      object.nrg = object.nrg - 10
    CASE 4 ' next
      IF RND * 40 < 5 THEN
        IF object.indoor THEN
          world(object.x, object.y).ind = CHR$(ASC(world(object.x, object.y).ind) + 1)
        ELSE
          world(object.x, object.y).env = CHR$(ASC(world(object.x, object.y).env) + 1)
        END IF
      END IF
    CASE 5 ' before
      IF RND * 40 < 5 THEN
        IF object.indoor THEN
          world(object.x, object.y).ind = CHR$(ASC(world(object.x, object.y).ind) - 1)
        ELSE
          world(object.x, object.y).env = CHR$(ASC(world(object.x, object.y).env) - 1)
        END IF
      END IF
    CASE 7 ' door
      SELECT CASE none
        CASE world(object.x - 1, object.y).ind
          object.sx = -1
          object.sy = 0
        CASE world(object.x + 1, object.y).ind
          object.sx = 1
          object.sy = 0
        CASE world(object.x, object.y - 1).ind
          object.sx = 0
          object.sy = -1
        CASE world(object.x, object.y + 1).ind
          object.sx = 0
          object.sy = 1
      END SELECT
      IF object.indoor = false THEN
        object.sx = object.sx * -1
        object.sy = object.sy * -1
      END IF
      world(object.x, object.y).obj = none
      object.indoor = NOT object.indoor
  END SELECT
  IF ASC(world(object.x + object.sx, object.y + object.sy).obj) = 0 THEN
    IF object.indoor THEN
      tileEffect = effect(ASC(world(object.x + object.sx, object.y + object.sy).ind))
    ELSE
      tileEffect = effect(ASC(world(object.x + object.sx, object.y + object.sy).env))
    END IF
    SELECT CASE tileEffect
      CASE 0 ' ground
        replace object '##
        playSound object, 2
      CASE 1 ' barrier
        object.sx = 0
        object.sy = 0
        playSound object, 1
      CASE 2 ' danger
        replace object
        world(object.x, object.y).obj = none
      CASE 3 ' above ' never used ##
        replace object
        world(object.x, object.y).obj = none
        playSound object, 2
      CASE 4, 5 ' next, before
        replace object
        playSound object, 2
      CASE 6 ' next b
        IF object.indoor THEN
          world(object.x + object.sx, object.y + object.sy).ind = CHR$(ASC(world(object.x + object.sx, object.y + object.sy).ind) + 1)
        ELSE
          world(object.x + object.sx, object.y + object.sy).env = CHR$(ASC(world(object.x + object.sx, object.y + object.sy).env) + 1)
        END IF
        playSound object, 8
      CASE 7
        IF object.status <> 4 AND object.status <> 6 THEN
          replace object
          playSound object, 2
        END IF
    END SELECT
  ELSE
    IF ABS(object.sx) + ABS(object.sy) > 0 THEN
      touch object.sx, object.sy, ASC(world(object.x + object.sx, object.y + object.sy).obj)
      IF object.status = 5 THEN
        playSound object, 14
      ELSE
        playSound object, 17
      END IF
      object.sx = 0 '#?!
      object.sy = 0
    END IF
  END IF
  IF object.nrg <= 0 THEN world(object.x, object.y).obj = none

END SUB

FUNCTION cameraChange% (x AS INTEGER, y AS INTEGER, Nobj AS INTEGER, Nspr AS INTEGER, cam AS INTEGER)

  SHARED objPic() AS STRING, map() AS INTEGER, buf() AS STRING

  IF map(x, y, cam) <> Nobj OR objPic(Nspr) <> buf(x, y, cam) THEN
    cameraChange% = true
  ELSE
    cameraChange% = false
  END IF
  map(x, y, cam) = Nobj
  buf(x, y, cam) = objPic(Nspr)

END FUNCTION

SUB cameraView (objects() AS sprite, camera AS sprite, xOff AS INTEGER, yOff AS INTEGER)

  SHARED world() AS tile, anim() AS animation
  DIM x AS INTEGER, y AS INTEGER, px AS INTEGER, py AS INTEGER
  DIM tileNenv AS INTEGER, tileNobj AS INTEGER
  DIM cam AS INTEGER
  STATIC counter AS INTEGER

  IF camera.nrg = 0 THEN EXIT SUB
  IF camera.number = 2 THEN
    cam = 0
  ELSE
    cam = 1
  END IF

  FOR x = -viewX TO viewX
    FOR y = -viewY TO viewY
      IF camera.indoor THEN
        tileNenv = ASC(world(x + camera.x, y + camera.y).ind)
      ELSE
        tileNenv = ASC(world(x + camera.x, y + camera.y).env)
      END IF
      tileNobj = ASC(world(x + camera.x, y + camera.y).obj)
      IF tileNobj > 0 THEN
        IF objects(tileNobj).indoor <> camera.indoor THEN tileNobj = 0
      END IF
      IF checkAnim%(tileNenv, count%(counter, 50)) THEN
        IF camera.indoor THEN
          world(x + camera.x, y + camera.y).ind = CHR$(anim(tileNenv).link)
        ELSE
          world(x + camera.x, y + camera.y).env = CHR$(anim(tileNenv).link)
        END IF
        tileNenv = anim(tileNenv).link
      END IF
      IF cameraChange%(x, y, tileNenv, tileNobj, cam) THEN
        px = midX + x * tileSize + xOff
        py = midY + y * tileSize + yOff
        IF tileNenv > 0 THEN
          putEnv tileNenv, px, py
        ELSE
          LINE (px, py)-STEP(tileSize - 1, tileSize - 1), 0, BF
        END IF
        IF tileNobj > 0 THEN
          putObj tileNobj, "m", px, py
          putObj tileNobj, "o", px, py
        END IF
      END IF
    NEXT
  NEXT

END SUB

SUB centerPrint (text AS STRING, yOff AS INTEGER)

  COLOR 245
  LOCATE 14 + yOff, 20 - LEN(text) \ 2
  PRINT text;

END SUB

SUB changeOptions (options AS gameSetting, choice AS STRING)

  SELECT CASE choice
    CASE "i"
      intro "readme"
    CASE "2"
      options.two = NOT options.two
      options.finish = true
    CASE "m"
      options.mouse = NOT options.mouse
      IF options.mouse THEN mouseGet
    CASE "s"
      options.soundFX = NOT options.soundFX
    CASE "b"
      options.SBlaster = NOT options.SBlaster
    CASE "p"
      DO UNTIL INKEY$ = "p"
      LOOP
    CASE CHR$(27)
      options.finish = true
  END SELECT

END SUB

FUNCTION checkAnim% (tileNenv AS INTEGER, counterAct AS INTEGER)
     
  SHARED anim() AS animation
  'checkAnim% = false
  IF anim(tileNenv).link > 0 THEN
    SELECT CASE anim(tileNenv).speed
      CASE 0 ' flicker
        IF RND * 500 < 5 THEN checkAnim% = true
      CASE 1 ' trigger
        IF RND * 2000 < 5 THEN checkAnim% = true
      CASE 2 ' smooth
        IF counterAct THEN checkAnim% = true
    END SELECT
  END IF

END FUNCTION

FUNCTION count% (counter AS INTEGER, counterMax AS INTEGER)

  IF counter < counterMax THEN
    counter = counter + 1
    count% = false
  ELSE
    counter = 0
    count% = true
  END IF
  
END FUNCTION

SUB followObject (object AS sprite, tx AS INTEGER, ty AS INTEGER, mode AS INTEGER)
 
  STATIC firstCordX AS INTEGER
  IF RND * 30 < 5 THEN firstCordX = NOT firstCordX
 
  IF mode = -1 THEN
    
    IF firstCordX THEN
      IF object.x = tx THEN
        IF INT(RND * 2) = 1 THEN
          objectMove object, 1, 0
        ELSE
          objectMove object, -1, 0
        END IF
        EXIT SUB
      ELSEIF object.y = ty THEN
        IF INT(RND * 2) = 1 THEN
          objectMove object, 0, 1
        ELSE
          objectMove object, 0, -1
        END IF
        EXIT SUB
      END IF
    ELSE
      IF object.y = ty THEN
        IF INT(RND * 2) = 1 THEN
          objectMove object, 0, 1
        ELSE
          objectMove object, 0, -1
        END IF
        EXIT SUB
      ELSEIF object.x = tx THEN
        IF INT(RND * 2) = 1 THEN
          objectMove object, 1, 0
        ELSE
          objectMove object, -1, 0
        END IF
        EXIT SUB
      END IF
    END IF

  END IF
 
  IF firstCordX THEN
    IF object.x > tx THEN
      objectMove object, -1 * mode, 0
    ELSEIF object.x < tx THEN
      objectMove object, 1 * mode, 0
    ELSEIF object.y > ty THEN
      objectMove object, 0, -1 * mode
    ELSEIF object.y < ty THEN
      objectMove object, 0, 1 * mode
    END IF
  ELSE
    IF object.y > ty THEN
      objectMove object, 0, -1 * mode
    ELSEIF object.y < ty THEN
      objectMove object, 0, 1 * mode
    ELSEIF object.x > tx THEN
      objectMove object, -1 * mode, 0
    ELSEIF object.x < tx THEN
      objectMove object, 1 * mode, 0
    END IF
  END IF

END SUB

SUB followTargets (object AS sprite)
 
  IF NOT (object.tx0 = object.tx1 AND object.ty0 = object.ty1) THEN
    IF object.td = 0 THEN
      IF object.x < object.tx0 THEN
        objectMove object, 1, 0
      ELSEIF object.x > object.tx0 THEN
        objectMove object, -1, 0
      ELSEIF object.y < object.ty0 THEN
        objectMove object, 0, 1
      ELSEIF object.y > object.ty0 THEN
        objectMove object, 0, -1
      ELSE
        object.td = 1
        object.dx = 1
        object.dy = 0 '#
      END IF
    ELSE
      IF object.x < object.tx1 THEN
        objectMove object, 1, 0
      ELSEIF object.x > object.tx1 THEN
        objectMove object, -1, 0
      ELSEIF object.y < object.ty1 THEN
        objectMove object, 0, 1
      ELSEIF object.y > object.ty1 THEN
        objectMove object, 0, -1
      ELSE
        object.td = 0
        object.dx = 1
        object.dy = 0
      END IF
    END IF
  END IF

END SUB

FUNCTION form$ (number AS INTEGER)

  form$ = LTRIM$(STR$(number))

END FUNCTION

FUNCTION getChoice% (request AS STRING, choice1 AS STRING, choice2 AS STRING)

  DIM choice AS STRING
  centerPrint request + " (" + choice1 + "/" + choice2 + ")?", 0
  DO
    choice = INKEY$
  LOOP UNTIL choice = choice1 OR choice = choice2
  IF choice = choice1 THEN
    getChoice% = true
  ELSE
    getChoice% = false
  END IF

END FUNCTION

SUB initObject (objects() AS sprite, fileName AS INTEGER)

  SHARED options AS gameSetting
  DIM n AS INTEGER
  OPEN root + "lvl\obj" + form$(fileName) + ".dat" FOR BINARY AS #1
    FOR n = 1 TO objMax - 2 - bulletmax
      GET #1, , objects(n)
    NEXT
    IF options.two THEN
      objects(objMax - 1 - bulletmax) = objects(1)
      objects(objMax - 1 - bulletmax).x = objects(objMax - 1 - bulletmax).x + 2
      objects(objMax - 1 - bulletmax).number = objMax - 1 - bulletmax
      objects(objMax - 0 - bulletmax) = objects(2)
      objects(objMax - 0 - bulletmax).x = objects(objMax - 0 - bulletmax).x + 1
      objects(objMax - 0 - bulletmax).td = objects(objMax - 1 - bulletmax).number
      objects(objMax - 0 - bulletmax).number = objMax - 0 - bulletmax
    END IF
    FOR n = objMax - bulletmax + 1 TO objMax
      objects(n).status = 7
      objects(n).body = 8
      objects(n).number = n
    NEXT
  CLOSE #1
 
END SUB

SUB initPlan (world() AS tile, effect() AS INTEGER, anim() AS animation, fileName AS INTEGER)

  DIM x AS INTEGER, y AS INTEGER, n AS INTEGER
 
  OPEN root + "lvl\plan" + form$(fileName) + ".dat" FOR BINARY AS #1
    FOR x = -worldX TO worldX
      FOR y = -worldY TO worldY
        GET #1, , world(x, y).env
      NEXT
    NEXT
  CLOSE
  OPEN root + "lvl\indoor" + form$(fileName) + ".dat" FOR BINARY AS #1
    FOR x = -worldX TO worldX
      FOR y = -worldY TO worldY
        GET #1, , world(x, y).ind
      NEXT
    NEXT
  CLOSE
  OPEN root + "lvl\effect" + form$(fileName) + ".dat" FOR BINARY AS #1
    FOR n = 0 TO envMax
      GET #1, , effect(n)
    NEXT
  CLOSE
  OPEN root + "lvl\anim" + form$(fileName) + ".dat" FOR BINARY AS #1
    FOR n = 0 TO envMax
      GET #1, , anim(n)
    NEXT
  CLOSE

END SUB

SUB intro (fileName AS STRING)

  DIM text AS STRING, n AS INTEGER, keyb AS STRING
  SHARED map() AS INTEGER, buf() AS STRING
  REDIM map(-viewX TO viewX, -viewY TO viewY, 1) AS INTEGER
  REDIM buf(-viewX TO viewX, -viewY TO viewY, 1) AS STRING
  PALETTE
  CLS
  LOCATE 1
  OPEN root + fileName + ".txt" FOR INPUT AS #1
    WHILE NOT EOF(1)
      LINE INPUT #1, text
      COLOR 15
      PRINT text
      IF CSRLIN >= 20 THEN
        COLOR 7
        PRINT CHR$(13) + "(Press any key to continue and escape to skip)"
        LOCATE 1
        DO: keyb = INKEY$: LOOP UNTIL keyb <> ""
        IF keyb = CHR$(27) THEN
          CLS
          CLOSE #1
          EXIT SUB
        END IF
        CLS
      END IF
    WEND
  CLOSE #1
  COLOR 7
  PRINT CHR$(13) + "(Press any key to continue)"
  DO: LOOP UNTIL INKEY$ <> ""
  setPal "colors"
  CLS

END SUB

SUB killObject (object AS sprite, x AS INTEGER, y AS INTEGER)
 
  SHARED world() AS tile, effect() AS INTEGER, objects() AS sprite
  SHARED options AS gameSetting
  DIM number AS INTEGER
  number = ASC(world(x, y).obj)
  IF number > 0 THEN
    IF NOT objects(number).status = 7 THEN
      objects(number).nrg = objects(number).nrg - 1
      IF objects(number).status = 5 THEN objects(number).td = object.td
      IF objects(number).nrg <= 0 THEN
        object.sx = 0
        object.sy = 0
        IF objects(number).status = 3 THEN
          options.finish = true
        END IF
      END IF
      action objects(number)
    END IF
  END IF
 
END SUB

SUB light (value AS INTEGER)

 DIM I AS INTEGER, n AS INTEGER, col AS pal
 DIM clock AS SINGLE
 
 IF SGN(value) = -1 THEN
  FOR n = 0 TO ABS(value)
    FOR I = 0 TO palMax
      OUT &H3C7, I
        col.red = INP(&H3C9)
        col.green = INP(&H3C9)
        col.blue = INP(&H3C9)
        OUT &H3C8, I
        OUT &H3C9, .9 * col.red
        OUT &H3C9, .9 * col.green
        OUT &H3C9, .9 * col.blue
      NEXT
      clock = TIMER
      DO UNTIL clock + .001 - TIMER <= 0
      LOOP
    NEXT
  ELSE '## never used
    FOR n = 0 TO value
      FOR I = 0 TO palMax
        OUT &H3C7, I
        col.red = INP(&H3C9)
        col.green = INP(&H3C9)
        col.blue = INP(&H3C9)
        OUT &H3C8, I
        OUT &H3C9, col.red / .9
        OUT &H3C9, col.green / .9
        OUT &H3C9, col.blue / .9
      NEXT
      clock = TIMER
      DO UNTIL clock + .001 - TIMER <= 0
      LOOP
    NEXT
  END IF

END SUB

SUB MouseDriver (AX%, bx%, CX%, dx%)
 
  DEF SEG = VARSEG(mouseDat)
  mouse% = SADD(mouseDat)
  CALL Absolute(AX%, bx%, CX%, dx%, mouse%)

END SUB

SUB mouseGet

  mouseDat = SPACE$(57)
  OPEN root + "mousedat.dat" FOR INPUT AS #1
    FOR I% = 1 TO 57
      INPUT #1, A$
      H$ = CHR$(VAL("&H" + A$))
      MID$(mouseDat, I%, 1) = H$
    NEXT
  CLOSE #1

END SUB

SUB MousePut
 
  AX% = 4
  CX% = x%
  dx% = y%
  MouseDriver AX%, 0, CX%, dx%

END SUB

SUB mouseStatus (m AS mouseType)
 
  lb% = m.left
  RB% = m.right
  xMouse% = m.x
  yMouse% = m.y
  AX% = 3
  MouseDriver AX%, bx%, CX%, dx%
  lb% = ((bx% AND 1) <> 0)
  RB% = ((bx% AND 2) <> 0)
  xMouse% = CX%
  yMouse% = dx%
  m.left = ABS(lb%)
  m.right = ABS(RB%)
  m.x = xMouse%
  m.y = yMouse%

END SUB

SUB move (objects() AS sprite)

  SHARED options AS gameSetting
  DIM nr AS INTEGER, hunters AS INTEGER, players AS INTEGER
 
  FOR nr = LBOUND(objects) TO UBOUND(objects)
    IF objects(nr).nrg > 0 THEN
      SELECT CASE objects(nr).status
        CASE 1
          movePlayer objects(nr)
          IF players = false THEN players = true
        CASE 2
          moveCamera objects(nr), objects(objects(nr).td)
        CASE 3
          IF RND * 40 < 5 THEN moveBeing objects(nr)
        CASE 4
          moveBox objects(nr)
        CASE 5
          IF RND * 20 < 5 THEN
            IF objects(nr).td >= 1 THEN
              moveHunter objects(nr), objects(objects(nr).td).x, objects(objects(nr).td).y
            ELSE
              moveHunter objects(nr), 0, 0
            END IF
          END IF
          IF hunters = false THEN hunters = true
        CASE 6
          moveCoin objects(nr)
        CASE 7
          moveBullet objects(nr)
      END SELECT
    END IF
  NEXT
 
  IF hunters = false THEN
    options.finish = true
    options.win = true
  ELSEIF players = false THEN
    options.finish = true
    options.win = false
  END IF
 
END SUB

SUB moveBeing (object AS sprite)

  followTargets object
  action object
  newCell object, 1
  object.sx = 0
  object.sy = 0
 
END SUB

SUB moveBox (object AS sprite)

  action object
  newCell object, 0
  object.sx = 0
  object.sy = 0
 
END SUB

SUB moveBullet (object AS sprite)
 
  IF object.nrg = 4 THEN killObject object, object.x + object.dx, object.y + object.dy
  IF ABS(object.sx) + ABS(object.sy) = 0 THEN
    IF object.nrg = 4 OR RND * 10 < 5 THEN
      object.nrg = object.nrg - 1
    END IF
  END IF
  action object
 
  IF object.nrg = 4 THEN
    object.stage = 0
    newCell object, 0
  ELSE
    object.body = 11
    object.dx = 0
    object.dy = 0
    IF RND * 8 < 5 THEN object.sx = 1 '##
    object.sy = 0
    newCell object, 3 ' explosion
    object.sx = 0
  END IF

END SUB

SUB moveCamera (camera AS sprite, target AS sprite)

  STATIC counter AS INTEGER, camMode AS INTEGER

  camera.sx = 0
  camera.sy = 0
 
  camera.indoor = target.indoor
  'camera.nrg = target.nrg
 
  IF ABS(target.tx0) + ABS(target.ty0) > 0 THEN ' ###
    camMode = 0 ' following
    counter = 0
  ELSEIF camMode = 0 THEN
    IF count%(counter, 30) THEN
      camMode = 1 ' leading
      target.stage = 1 ' #
    END IF
  END IF
 
  IF camMode = 0 THEN
    IF camera.x - viewX \ 2 > target.x THEN
      camera.sx = -1
    ELSEIF camera.x + viewX \ 2 < target.x THEN
      camera.sx = 1
    END IF
    IF camera.y - viewY \ 2 > target.y THEN
      camera.sy = -1
    ELSEIF camera.y + viewY \ 2 < target.y THEN
      camera.sy = 1
    END IF
  ELSE
    IF camera.x > target.x + (target.dx * (viewX \ 2)) THEN
      camera.sx = -1
    ELSEIF camera.x < target.x + (target.dx * (viewX \ 2)) THEN
      camera.sx = 1
    END IF
    IF camera.y > target.y + (target.dy * (viewY \ 2)) THEN
      camera.sy = -1
    ELSEIF camera.y < target.y + (target.dy * (viewY \ 2)) THEN
      camera.sy = 1
    END IF
  END IF

  IF ABS(camera.x + camera.sx) + viewX <= worldX THEN
    camera.x = camera.x + camera.sx
  END IF
  IF ABS(camera.y + camera.sy) + viewY <= worldY THEN
    camera.y = camera.y + camera.sy
  END IF
 
END SUB

SUB moveCoin (object AS sprite)
 
  SHARED world() AS tile, player() AS playerStats
  SHARED objects() AS sprite
  DIM playNum AS INTEGER, rNum AS INTEGER
 
  IF ASC(world(object.x - object.sx, object.y - object.sy).obj) = 1 THEN
    playNum = 0
  ELSEIF ASC(world(object.x - object.sx, object.y - object.sy).obj) = objMax - bulletmax - 1 THEN
    playNum = 1
  ELSE
    playNum = -1
  END IF
 
  IF playNum = 0 OR playNum = 1 THEN
    IF object.body = 10 THEN
      IF player(playNum).gun = 0 THEN
        player(playNum).gun = 30
        object.nrg = 0
        object.sx = 0
        object.sy = 0
      END IF
    ELSEIF object.body = 13 THEN
      rNum = ASC(world(object.x - object.sx, object.y - object.sy).obj)
      IF objects(rNum).nrg < 5 THEN
        objects(rNum).nrg = 5
        playSound object, 22
        object.nrg = 0
        object.sx = 0
        object.sy = 0
      END IF
    ELSE
      playSound object, 15
      player(playNum).coins = player(playNum).coins + 1
      object.nrg = 0
      object.sx = 0
      object.sy = 0
    END IF
  END IF

  action object
  newCell object, 0
  object.sx = 0
  object.sy = 0
 
END SUB

SUB moveHunter (object AS sprite, tx AS INTEGER, ty AS INTEGER)

  IF object.nrg < 10 AND object.x - (viewX + viewX \ 2) <= tx AND object.x + (viewX + viewX \ 2) >= tx AND object.y - (viewY + viewY \ 2) <= ty AND object.y + (viewY + viewY \ 2) >= ty THEN
    IF object.nrg < 5 THEN
      followObject object, tx, ty, -1
    ELSE
      followObject object, tx, ty, 1
      IF (SGN(object.dx) = -1 AND object.x > tx AND object.y = ty) XOR (SGN(object.dx) = 1 AND object.x < tx AND object.y = ty) XOR (SGN(object.dy) = -1 AND object.y > ty AND object.x = tx) XOR (SGN(object.dy) = 1 AND object.y < ty AND object.x = tx _
) THEN
        IF RND * (object.nrg * 5) < 5 THEN
          IF shootBullet%(object.indoor, object.x, object.y, object.dx, object.dy, object.number) THEN
            object.sx = object.dx * -1
            object.sy = object.dy * -1
          END IF
        END IF
      END IF
    END IF
  ELSE
    followTargets object
  END IF
 
  IF RND * 100 < 5 AND object.nrg >= 5 AND object.nrg < 10 THEN
    object.nrg = object.nrg + 1
    IF object.nrg = 10 THEN object.td = 0
  END IF

  IF ABS(object.sx) + ABS(object.sy) > 0 THEN
    killObject object, object.x + object.dx, object.y + object.dy
  END IF
 
  IF object.nrg < 5 THEN
    object.body = 12
  END IF
  action object
  newCell object, 1
  object.sx = 0
  object.sy = 0

END SUB

SUB movePlayer (object AS sprite)

  SHARED keyboard AS STRING, player() AS playerStats
  SHARED options AS gameSetting
  STATIC reload0 AS INTEGER, reload1 AS INTEGER
  STATIC mouse AS mouseType, oldMouse AS mouseType
  DIM keyb AS STRING

  IF object.number = 1 THEN
    SELECT CASE keyboard
      CASE CHR$(0) + "K"
        objectMove object, -1, 0
      CASE CHR$(0) + "M"
        objectMove object, 1, 0
      CASE CHR$(0) + "H"
        objectMove object, 0, -1
      CASE CHR$(0) + "P"
        objectMove object, 0, 1
      CASE CHR$(13)
        IF reload0 = 0 THEN
          IF player(0).gun > 0 THEN
            IF shootBullet%(object.indoor, object.x, object.y, object.dx, object.dy, object.number) THEN
              object.sx = object.dx * -1
              object.sy = object.dy * -1
              reload0 = 10
              player(0).gun = player(0).gun - 1
            END IF
          END IF
        END IF
    END SELECT
    IF reload0 > 0 THEN reload0 = reload0 - 1
    IF player(0).gun THEN
      object.body = 9
    ELSE
      object.body = 1
    END IF
  ELSE
    IF options.mouse THEN
      mouseStatus mouse
      mouse.x = mouse.x \ 2
      IF mouse.x < oldMouse.x - mouseArea OR mouse.x < mouseArea THEN
        keyb = "f"
      ELSEIF mouse.x > oldMouse.x + mouseArea OR mouse.x > limX - mouseArea THEN
        keyb = "h"
      ELSEIF mouse.y < oldMouse.y - mouseArea OR mouse.y < mouseArea THEN
        keyb = "t"
      ELSEIF mouse.y > oldMouse.y + mouseArea OR mouse.y > limY - mouseArea THEN
        keyb = "g"
      END IF
      oldMouse = mouse
      IF mouse.left = 1 THEN keyb = " "
    ELSE
      keyb = keyboard
    END IF
   
    SELECT CASE keyb
      CASE "f"
        objectMove object, -1, 0
      CASE "h"
        objectMove object, 1, 0
      CASE "t"
        objectMove object, 0, -1
      CASE "g"
        objectMove object, 0, 1
      CASE " "
        IF reload1 = 0 THEN
          IF player(1).gun > 0 THEN
            IF shootBullet%(object.indoor, object.x, object.y, object.dx, object.dy, object.number) THEN
              object.sx = object.dx * -1
              object.sy = object.dy * -1
              reload1 = 10
              player(1).gun = player(1).gun - 1
            END IF
          END IF
        END IF
    END SELECT
    IF reload1 > 0 THEN reload1 = reload1 - 1
    IF player(1).gun THEN
      object.body = 9
    ELSE
      object.body = 1
    END IF
   
    IF reload1 > 0 THEN reload1 = reload1 - 1
    IF player(1).gun THEN
      object.body = 9
    ELSE
      object.body = 1
    END IF
  END IF

  action object
  newCell object, 3
  object.tx0 = object.sx '##!
  object.ty0 = object.sy '##!
  object.sx = 0
  object.sy = 0
 
END SUB

SUB newCell (object AS sprite, cellMax AS INTEGER)
 
  SHARED objPic() AS STRING
  IF ABS(object.sx) + ABS(object.sy) > 0 THEN
    IF object.stage < cellMax THEN
      object.stage = object.stage + 1
    ELSE
      object.stage = 0
    END IF
  END IF
  objPic(object.number) = form$(object.body) + "_"
  IF object.dx = -1 THEN
    objPic(object.number) = objPic(object.number) + "4"
  ELSEIF object.dx = 1 THEN
    objPic(object.number) = objPic(object.number) + "6"
  ELSEIF object.dy = -1 THEN
    objPic(object.number) = objPic(object.number) + "8"
  ELSEIF object.dy = 1 THEN
    objPic(object.number) = objPic(object.number) + "2"
  ELSE
    objPic(object.number) = objPic(object.number) + "5"
  END IF
  SELECT CASE object.stage
    CASE 0
      objPic(object.number) = objPic(object.number) + "a"
    CASE 1, 3
      objPic(object.number) = objPic(object.number) + "b"
    CASE 2
      objPic(object.number) = objPic(object.number) + "c"
  END SELECT

END SUB

SUB objectMove (object AS sprite, wx AS INTEGER, wy AS INTEGER)

  IF object.dx = wx AND object.dy = wy THEN
    object.sx = wx
    object.sy = wy
  ELSE
    object.dx = wx
    object.dy = wy
  END IF

END SUB

SUB playSFX (blasterNum AS INTEGER)

  SHARED channel() AS STRING, blaster() AS STRING, options AS gameSetting
  DIM chanIndex AS INTEGER, in AS INTEGER, d AS INTEGER, B AS INTEGER
  DIM reg AS STRING, regX AS INTEGER
  DIM dat AS STRING, datX AS INTEGER
 
  IF options.soundFX = false THEN EXIT SUB
  chanIndex = VAL(MID$(blaster(blasterNum), 61, 4))
  FOR in = 1 TO 60 STEP 4
    reg = MID$(channel(chanIndex), in, 4)
    regX = VAL(reg)
    dat = MID$(blaster(blasterNum), in, 4)
    datX = VAL(dat)
    OUT &H388, regX
    FOR d = 1 TO 6
      B = INP(&H388)
    NEXT
    OUT &H389, datX
    FOR d = 1 TO 35
      B = INP(&H388)
    NEXT
  NEXT
 
END SUB

SUB playSound (object AS sprite, freq AS INTEGER)

  SHARED options AS gameSetting, objects() AS sprite
  DIM n AS INTEGER, I AS INTEGER, iMax AS INTEGER
  IF options.two THEN
    iMax = 2
  ELSE
    iMax = 1
  END IF
  FOR I = 1 TO iMax
    IF I = 1 THEN
      n = 2
    ELSE
      n = objMax - 0 - bulletmax
    END IF
    IF object.x >= objects(n).x - viewX AND object.x <= objects(n).x + viewX THEN
      IF object.y >= objects(n).y - viewY AND object.y <= objects(n).y + viewY THEN
        IF object.indoor = objects(n).indoor THEN
          IF options.SBlaster AND freq <> 2 THEN
            playSFX freq
          ELSEIF options.soundFX THEN
            SOUND 100 + freq * 100, .03
          END IF
        END IF
      END IF
    END IF
  NEXT
 
END SUB

SUB printFX (text AS STRING)

  DIM x AS INTEGER, y AS INTEGER
  DIM zoom AS SINGLE, I AS INTEGER, clock AS SINGLE
  DIM xOff AS INTEGER, yOff AS INTEGER, colr AS INTEGER
  DIM textLen AS INTEGER, banner AS INTEGER
 
  IF LEFT$(text, 1) = ">" THEN
    text = RIGHT$(text, LEN(text) - 1)
    banner = 40
  END IF

  PALETTE 1, 0
  COLOR 1
  LOCATE 1, 1
  PRINT text
 
  textLen = LEN(text) * 8 - 3
  DIM pic(textLen, 7) AS INTEGER
 
  FOR x = 0 TO textLen
    FOR y = 0 TO 7
      IF POINT(x, y) = 1 THEN pic(x, y) = true
    NEXT
  NEXT
  CLS
 
  FOR I = 0 TO 35
    OUT 968, I + palMax + 1
    OUT 969, I + 15
    OUT 969, I + 15
    OUT 969, I + 15
  NEXT
  IF banner > 0 THEN
    FOR I = 0 TO 35
      OUT 968, I + banner + 1
      OUT 969, I + 15
      OUT 969, (I + 1) \ 4
      OUT 969, (I + 1) \ 4
    NEXT
  END IF

  FOR zoom = .2 TO 3.3 STEP .2
    xOff = midX - (textLen * zoom) \ 2 + zoom
    yOff = midY - (7 * zoom) \ 2 + zoom
    colr = palMax + 1 + zoom * 9 + zoom
    bancol = (banner + 1 + zoom * 9 + zoom) * SGN(banner)
    FOR x = 0 TO textLen
      FOR y = 0 TO 7
        IF pic(x, y) THEN
          LINE (xOff + x * zoom, yOff + y * zoom)-STEP(zoom, zoom), colr, BF
        ELSE
          LINE (xOff + x * zoom, yOff + y * zoom)-STEP(zoom, zoom), bancol, BF
        END IF
      NEXT
    NEXT
    clock = TIMER
    DO UNTIL clock + .001 - TIMER <= 0
    LOOP
  NEXT

END SUB

SUB putEnv (number AS INTEGER, px AS INTEGER, py AS INTEGER) STATIC

  DIM buffer(1 TO 21) AS INTEGER
  DIM n AS INTEGER, index AS INTEGER, newPic AS INTEGER, offset AS INTEGER
  DIM pic1(pSize) AS INTEGER, pic2(pSize) AS INTEGER, pic3(pSize) AS INTEGER
  DIM pic4(pSize) AS INTEGER, pic5(pSize) AS INTEGER, pic6(pSize) AS INTEGER
  DIM pic7(pSize) AS INTEGER, pic8(pSize) AS INTEGER, pic9(pSize) AS INTEGER
  DIM pic10(pSize) AS INTEGER, pic11(pSize) AS INTEGER, pic12(pSize) AS INTEGER
  DIM pic13(pSize) AS INTEGER, pic14(pSize) AS INTEGER, pic15(pSize) AS INTEGER
  DIM pic16(pSize) AS INTEGER, pic17(pSize) AS INTEGER, pic18(pSize) AS INTEGER
  DIM pic19(pSize) AS INTEGER, pic20(pSize) AS INTEGER, pic21(pSize) AS INTEGER
 
  index = 0
  FOR n = 0 TO -20 STEP -1 ' searching from newest to oldest picture
    offset = newPic + n
    IF offset < LBOUND(buffer) THEN offset = UBOUND(buffer) + offset
    IF buffer(offset) = number THEN
      index = offset
      EXIT FOR
    END IF
  NEXT
 
  IF index = 0 THEN
    IF newPic < UBOUND(buffer) THEN
      newPic = newPic + 1
    ELSE
      newPic = LBOUND(buffer)
    END IF
    index = newPic
    SELECT CASE index
      CASE 1: DEF SEG = VARSEG(pic1(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic1(0))
      CASE 2: DEF SEG = VARSEG(pic2(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic2(0))
      CASE 3: DEF SEG = VARSEG(pic3(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic3(0))
      CASE 4: DEF SEG = VARSEG(pic4(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic4(0))
      CASE 5: DEF SEG = VARSEG(pic5(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic5(0))
      CASE 6: DEF SEG = VARSEG(pic6(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic6(0))
      CASE 7: DEF SEG = VARSEG(pic7(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic7(0))
      CASE 8: DEF SEG = VARSEG(pic8(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic8(0))
      CASE 9: DEF SEG = VARSEG(pic9(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic9(0))
      CASE 10: DEF SEG = VARSEG(pic10(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic10(0))
      CASE 11: DEF SEG = VARSEG(pic11(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic11(0))
      CASE 12: DEF SEG = VARSEG(pic12(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic12(0))
      CASE 13: DEF SEG = VARSEG(pic13(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic13(0))
      CASE 14: DEF SEG = VARSEG(pic14(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic14(0))
      CASE 15: DEF SEG = VARSEG(pic15(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic15(0))
      CASE 16: DEF SEG = VARSEG(pic16(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic16(0))
      CASE 17: DEF SEG = VARSEG(pic17(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic17(0))
      CASE 18: DEF SEG = VARSEG(pic18(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic18(0))
      CASE 19: DEF SEG = VARSEG(pic19(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic19(0))
      CASE 20: DEF SEG = VARSEG(pic20(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic20(0))
      CASE 21: DEF SEG = VARSEG(pic21(0)): BLOAD root + "env\" + form$(number) + ".GRH", VARPTR(pic21(0))
    END SELECT
    DEF SEG
    buffer(index) = number
  END IF

  SELECT CASE index
    CASE 1: PUT (px, py), pic1, PSET
    CASE 2: PUT (px, py), pic2, PSET
    CASE 3: PUT (px, py), pic3, PSET
    CASE 4: PUT (px, py), pic4, PSET
    CASE 5: PUT (px, py), pic5, PSET
    CASE 6: PUT (px, py), pic6, PSET
    CASE 7: PUT (px, py), pic7, PSET
    CASE 8: PUT (px, py), pic8, PSET
    CASE 9: PUT (px, py), pic9, PSET
    CASE 10: PUT (px, py), pic10, PSET
    CASE 11: PUT (px, py), pic11, PSET
    CASE 12: PUT (px, py), pic12, PSET
    CASE 13: PUT (px, py), pic13, PSET
    CASE 14: PUT (px, py), pic14, PSET
    CASE 15: PUT (px, py), pic15, PSET
    CASE 16: PUT (px, py), pic16, PSET
    CASE 17: PUT (px, py), pic17, PSET
    CASE 18: PUT (px, py), pic18, PSET
    CASE 19: PUT (px, py), pic19, PSET
    CASE 20: PUT (px, py), pic20, PSET
    CASE 21: PUT (px, py), pic21, PSET
  END SELECT

END SUB

SUB putObj (number AS INTEGER, way AS STRING, px AS INTEGER, py AS INTEGER) STATIC

  SHARED objPic() AS STRING
  DIM buffer(1 TO 21) AS STRING
  DIM n AS INTEGER, index AS INTEGER, newPic AS INTEGER, offset AS INTEGER
  DIM pic1(pSize) AS INTEGER, pic2(pSize) AS INTEGER, pic3(pSize) AS INTEGER
  DIM pic4(pSize) AS INTEGER, pic5(pSize) AS INTEGER, pic6(pSize) AS INTEGER
  DIM pic7(pSize) AS INTEGER, pic8(pSize) AS INTEGER, pic9(pSize) AS INTEGER
  DIM pic10(pSize) AS INTEGER, pic11(pSize) AS INTEGER, pic12(pSize) AS INTEGER
  DIM pic13(pSize) AS INTEGER, pic14(pSize) AS INTEGER, pic15(pSize) AS INTEGER
  DIM pic16(pSize) AS INTEGER, pic17(pSize) AS INTEGER, pic18(pSize) AS INTEGER
  DIM pic19(pSize) AS INTEGER, pic20(pSize) AS INTEGER, pic21(pSize) AS INTEGER
 
  index = 0
  FOR n = 0 TO -20 STEP -1 ' searching from newest to oldest picture
    offset = newPic + n
    IF offset < LBOUND(buffer) THEN offset = UBOUND(buffer) + offset
    IF buffer(offset) = objPic(number) + way THEN
      index = offset
      EXIT FOR
    END IF
  NEXT
 
  IF index = 0 THEN
    IF newPic < UBOUND(buffer) THEN
      newPic = newPic + 1
    ELSE
      newPic = LBOUND(buffer)
    END IF
    index = newPic
    SELECT CASE index
      CASE 1: DEF SEG = VARSEG(pic1(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic1(0))
      CASE 2: DEF SEG = VARSEG(pic2(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic2(0))
      CASE 3: DEF SEG = VARSEG(pic3(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic3(0))
      CASE 4: DEF SEG = VARSEG(pic4(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic4(0))
      CASE 5: DEF SEG = VARSEG(pic5(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic5(0))
      CASE 6: DEF SEG = VARSEG(pic6(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic6(0))
      CASE 7: DEF SEG = VARSEG(pic7(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic7(0))
      CASE 8: DEF SEG = VARSEG(pic8(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic8(0))
      CASE 9: DEF SEG = VARSEG(pic9(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic9(0))
      CASE 10: DEF SEG = VARSEG(pic10(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic10(0))
      CASE 11: DEF SEG = VARSEG(pic11(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic11(0))
      CASE 12: DEF SEG = VARSEG(pic12(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic12(0))
      CASE 13: DEF SEG = VARSEG(pic13(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic13(0))
      CASE 14: DEF SEG = VARSEG(pic14(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic14(0))
      CASE 15: DEF SEG = VARSEG(pic15(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic15(0))
      CASE 16: DEF SEG = VARSEG(pic16(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic16(0))
      CASE 17: DEF SEG = VARSEG(pic17(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic17(0))
      CASE 18: DEF SEG = VARSEG(pic18(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic18(0))
      CASE 19: DEF SEG = VARSEG(pic19(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic19(0))
      CASE 20: DEF SEG = VARSEG(pic20(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic20(0))
      CASE 21: DEF SEG = VARSEG(pic21(0)): BLOAD root + "obj\" + objPic(number) + way + ".GRH", VARPTR(pic21(0))
    END SELECT
    DEF SEG
    buffer(index) = objPic(number) + way
  END IF

  IF way = "m" THEN
    SELECT CASE index
      CASE 1: PUT (px, py), pic1, AND
      CASE 2: PUT (px, py), pic2, AND
      CASE 3: PUT (px, py), pic3, AND
      CASE 4: PUT (px, py), pic4, AND
      CASE 5: PUT (px, py), pic5, AND
      CASE 6: PUT (px, py), pic6, AND
      CASE 7: PUT (px, py), pic7, AND
      CASE 8: PUT (px, py), pic8, AND
      CASE 9: PUT (px, py), pic9, AND
      CASE 10: PUT (px, py), pic10, AND
      CASE 11: PUT (px, py), pic11, AND
      CASE 12: PUT (px, py), pic12, AND
      CASE 13: PUT (px, py), pic13, AND
      CASE 14: PUT (px, py), pic14, AND
      CASE 15: PUT (px, py), pic15, AND
      CASE 16: PUT (px, py), pic16, AND
      CASE 17: PUT (px, py), pic17, AND
      CASE 18: PUT (px, py), pic18, AND
      CASE 19: PUT (px, py), pic19, AND
      CASE 20: PUT (px, py), pic20, AND
      CASE 21: PUT (px, py), pic21, AND
    END SELECT
  ELSE
    SELECT CASE index
      CASE 1: PUT (px, py), pic1, OR
      CASE 2: PUT (px, py), pic2, OR
      CASE 3: PUT (px, py), pic3, OR
      CASE 4: PUT (px, py), pic4, OR
      CASE 5: PUT (px, py), pic5, OR
      CASE 6: PUT (px, py), pic6, OR
      CASE 7: PUT (px, py), pic7, OR
      CASE 8: PUT (px, py), pic8, OR
      CASE 9: PUT (px, py), pic9, OR
      CASE 10: PUT (px, py), pic10, OR
      CASE 11: PUT (px, py), pic11, OR
      CASE 12: PUT (px, py), pic12, OR
      CASE 13: PUT (px, py), pic13, OR
      CASE 14: PUT (px, py), pic14, OR
      CASE 15: PUT (px, py), pic15, OR
      CASE 16: PUT (px, py), pic16, OR
      CASE 17: PUT (px, py), pic17, OR
      CASE 18: PUT (px, py), pic18, OR
      CASE 19: PUT (px, py), pic19, OR
      CASE 20: PUT (px, py), pic20, OR
      CASE 21: PUT (px, py), pic21, OR
    END SELECT
  END IF

END SUB

SUB replace (object AS sprite)

  SHARED world() AS tile
  world(object.x, object.y).obj = none
  object.x = object.x + object.sx
  object.y = object.y + object.sy
  world(object.x, object.y).obj = CHR$(object.number)

END SUB

SUB setPal (fileName AS STRING)
 
  DIM col AS pal, I AS INTEGER
  OPEN root + fileName + ".pal" FOR BINARY AS #1
    FOR I = 0 TO palMax
      GET #1, , col
      OUT 968, I
      OUT 969, col.red
      OUT 969, col.green
      OUT 969, col.blue
    NEXT
  CLOSE #1

END SUB

SUB setSoundFX

  SHARED channel() AS STRING, blaster() AS STRING
  DIM I AS INTEGER
  OPEN root + "sound\channels.dat" FOR INPUT AS #1
    FOR I = 0 TO 8
      INPUT #1, channel(I)
    NEXT
  CLOSE #1
  OPEN root + "sound\various.sfx" FOR INPUT AS #1
    FOR I = 0 TO 25
      INPUT #1, blaster(I)
    NEXT
  CLOSE #1
 
END SUB

FUNCTION shootBullet% (indoor AS INTEGER, x AS INTEGER, y AS INTEGER, dx AS INTEGER, dy AS INTEGER, number AS INTEGER)

  SHARED objects() AS sprite
  DIM n AS INTEGER
  shootBullet% = false
  FOR n = objMax - bulletmax + 1 TO objMax
    IF objects(n).nrg <= 0 THEN
      objects(n).nrg = 4
      objects(n).x = x
      objects(n).y = y
      objects(n).sx = dx
      objects(n).sy = dy
      objects(n).dx = dx
      objects(n).dy = dy
      objects(n).body = 8
      objects(n).indoor = indoor
      objects(n).td = number
      playSound objects(n), 13
      shootBullet% = true
      EXIT FOR
    END IF
  NEXT
 
END FUNCTION

SUB touch (spx AS INTEGER, spy AS INTEGER, objNum AS INTEGER)

  SHARED objects() AS sprite
  IF NOT objects(objNum).status = 7 THEN ' bullet
    objects(objNum).sx = spx
    objects(objNum).sy = spy
  END IF

END SUB

