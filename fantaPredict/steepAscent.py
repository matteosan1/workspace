import math, sys, array
import extractResults
import ROOT

def correlation(x, y, ah, bh, aa, ba, g, r):
    tau = 1.

    l = (ah*ba*g)
    m = (aa*bh)

    #print l, m, r
    if (r < max(-1/l, -1/m)):
        r = max(-1/l, -1/m)

    if (r > min(1/(l*m), 1)):
        r = min(1/(l*m), 1)
    #print x, y
    if (x == 0 and x == y):
        tau = 1 - l*m*r
    elif (x == 0 and y == 1):
        tau = 1 + l*r
    elif (x == 1 and y == 0):
        tau = 1 + m*r
    elif (x == 1 and x == y):
        tau = 1 - r
    else:
        tau = 1
    #print tau  
    if (tau < 1.):
        tau = 1.

    return tau

def derivativeCorrelation(x, y, ah, bh, aa, ba, g, r):
    dtau = 1.
    if (x == 0 and x == y):
        dtau = - (ah*ba*g)*(aa*bh)
    elif (x == 0 and y == 1):
        dtau = ah*ba*g
    elif (x == 1 and y == 0):
        dtau = aa*bh
    elif (x == 1 and x == y):
        dtau = -1
    else:
        dtau = 0
        
    return dtau/correlation(x, y, ah, bh, aa, ba, g, r)

def pdf(x, y, ah, bh, aa, ba, g, r):
    l = ah*ba*g
    m = aa*bh
    pr = correlation(x, y, ah, bh, aa, ba, g, r)*math.pow(l, x)*math.exp(-l)/math.factorial(x)*math.pow(m, y)*math.exp(-m)/math.factorial(y)
    #pr = math.pow(l, x)*math.exp(-l)/math.factorial(x)*math.pow(m, y)*math.exp(-m)/math.factorial(y)
    
    return pr

def probHomeWin(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    for i in xrange(10):
        for j in xrange(10):
            if (i > j):
                pr = pr + pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)

    return pr

def probAwayWin(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    for i in xrange(10):
        for j in xrange(10):
            if (i < j):
                pr = pr + pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)

    return pr

def highestProbAwayWin(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    ris1 = -1
    ris2 = -1
    for i in xrange(10):
        for j in xrange(10):
            if (i < j):
                temp = pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)
                if (pr < temp):
                    pr = temp
                    ris1 = i
                    ris2 = j

    print "Vittoria: %d - %d (prob. %1.2f)" % (ris1, ris2, pr)

def highestProbHomeWin(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    ris1 = -1
    ris2 = -1
    for i in xrange(10):
        for j in xrange(10):
            if (i > j):
                temp = pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)
                if (pr < temp):
                    pr = temp
                    ris1 = i
                    ris2 = j

    print "Vittoria: %d - %d (prob. %1.2f)" % (ris1, ris2, pr)

def highestProbDraw(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    ris = -1
    for i in xrange(10):
        for j in xrange(10):
            if (i == j):
                temp = pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)
                if (pr < temp):
                    pr = temp
                    ris = i
    print "Pareggio: %d - %d (prob. %1.2f)" % (ris, ris, pr)

def probDraw(indexH, indexA, ah, bh, aa, ba, g, r):
    pr = 0.
    for i in xrange(10):
        for j in xrange(10):
            if (i == j):
                pr = pr + pdf(i, j, ah[indexH], bh[indexH], aa[indexA], ba[indexA], g, r)

    return pr

def likelihoodTerm(x, y, ah, bh, aa, ba, g, r, t):
    #print "ecco1"
    #print math.exp(-0.0065*t), correlation(x, y, ah, bh, aa, ba, g, r), x*math.log(ah), x*math.log(ba), x*math.log(g), (ah*ba*g), y*math.log(aa), y*math.log(bh), (aa*bh)
    #print "ecco2"
    
    L_i = math.exp(-0.0065*t)*(math.log(correlation(x, y, ah, bh, aa, ba, g, r)) + x*math.log(ah) + x*math.log(ba) + x*math.log(g) - (ah*ba*g) + y*math.log(aa) + y*math.log(bh) -(aa*bh))
    #L_i = math.exp(-0.065*t)*(x*math.log(ah) + x*math.log(ba) + x*math.log(g) - (ah*ba*g) + y*math.log(aa) + y*math.log(bh) -(aa*bh))

    return L_i

def derivativeTerm(param, x, y, ah, bh, aa, ba, g, r, t):
    d=0 
    if (param == 0):
        d = x/ah - ba*g
    elif (param == 1):
        d = y/bh - aa    
    elif (param == 2):
        d = y/aa - bh    
    elif (param == 3):
        d = x/ba - ah*g
    elif (param == 4):
        d = x/g - ah*ba
    elif (param == 5):
        d = derivativeCorrelation(x, y, ah, bh, aa, ba, g, r)
    
    return d*math.exp(-0.065*t)
    
def likelihood(matches, ah, bh, aa, ba, g, r):
    l = 0.
    for t, m in enumerate(matches):
        l = l + likelihoodTerm(m[1], m[3], ah[m[0]], bh[m[0]], aa[m[2]], ba[m[2]], g, r, (t-len(matches))/10)

    return l

def updateParameters(index, alpha, matches, ah, bh, aa, ba, g, r):
    for param in xrange(6):
        d = 0.
        for t, m in enumerate(matches):
            if (param == 0 or param == 1):
                if (m[0] == index):
                    d = d + derivativeTerm(param, m[1], m[3], ah[m[0]], bh[m[0]], aa[m[2]], ba[m[2]], g[0], r[0], (t-len(matches))/10)
            elif (param == 2 or param == 3):
                if (m[2] == index):
                    d = d + derivativeTerm(param, m[1], m[3], ah[m[0]], bh[m[0]], aa[m[2]], ba[m[2]], g[0], r[0], (t-len(matches))/10.)
            elif (param == 4 or param == 5):
                d = d + derivativeTerm(param, m[1], m[3], ah[m[0]], bh[m[0]], aa[m[2]], ba[m[2]], g[0], r[0], (t-len(matches))/10)
                          
        if (param == 0):
            ah[index] = ah[index]+alpha*d
        elif (param == 1):
            bh[index] = bh[index]+alpha*d
        elif (param == 2):
            aa[index] = aa[index]+alpha*d
        elif (param == 3):
            ba[index] = ba[index]+alpha*d
        elif (param == 4):
            g[0] = g[0]+alpha*d
        elif (param == 5):
            r[0] = r[0]+alpha*d                    

def steepAscent(alpha, iterations, minDL, matches, ah, bh, aa, ba, g, r):
    
    iteration = 0
    L = likelihood(matches, ah, bh, aa, ba, g[0], r[0])
    L_old = 999.

    while ((L-L_old) > minDL or iteration == 0):
        L_old = L
        for i in xrange(len(ah)):
            updateParameters(i, alpha, matches, ah, bh, aa, ba, g, r)

        L = likelihood(matches, ah, bh, aa, ba, g[0], r[0])
        iteration += 1
        if (iteration % 100 == 0):
            print "Iteration: %d L: %f" %(iteration, L)

        if (iteration == iterations):
            break

    print "Iteration: %d L: %f" %(iteration, L)

if __name__ == "__main__":
    teamMap = {'ATALANTA':0, 'LAZIO':1, 'CHIEVO':2, 'BOLOGNA':3, 'FIORENTINA':4, 'UDINESE':5,'GENOA':6, 'CAGLIARI':7,'JUVENTUS':8, 'PARMA':9,'MILAN':10, 'SAMPDORIA':11,'PALERMO':12, 'NAPOLI':13,'PESCARA':14, 'INTER':15,'ROMA':16, 'CATANIA':17,'SIENA':18, 'TORINO':19}

    matches = extractResults.extract(teamMap)
    
    r = [0]
    g = [1]
    ah = [1 for i in xrange(20)]
    aa = [1 for i in xrange(20)]
    bh = [1 for i in xrange(20)]
    ba = [1 for i in xrange(20)]

    steepAscent(0.001, 10000, 0.001, matches, ah, bh, aa, ba, g, r)
    print "--------------------------"
    for t in teamMap.keys():
        print "%10s\t %1.3f %1.3f  %1.3f %1.3f" % (t, ah[teamMap[t]], bh[teamMap[t]], aa[teamMap[t]], ba[teamMap[t]])
    print "Coefficiente casalingo: %1.3f" % (g[0])
    
    print "--------------------------"
    #nextRound = [('BOLOGNA', 'PALERMO'), ('CATANIA', 'CHIEVO'), ('FIORENTINA', 'ATALANTA'), ('INTER', 'CAGLIARI'), ('JUVENTUS', 'LAZIO'), ('NAPOLI', 'MILAN'), ('ROMA', 'TORINO'), ('SAMPDORIA', 'GENOA'), ('SIENA', 'PESCARA'), ('UDINESE', 'PARMA')]
    #nextRound = [('ATALANTA','GENOA'),('CAGLIARI','NAPOLI'),('CHIEVO','SIENA'),('LAZIO','UDINESE'),('MILAN','JUVENTUS'),('PALERMO','CATANIA'),('PARMA','INTER'),('PESCARA','ROMA'),('SAMPDORIA','BOLOGNA'),('TORINO','FIORENTINA')]
    nextRound = [('BOLOGNA', 'ATALANTA'),('CATANIA', 'MILAN'),('FIORENTINA', 'SAMPDORIA'),('GENOA', 'CHIEVO'),('INTER', 'PALERMO'),('JUVENTUS', 'TORINO'),('LAZIO', 'PARMA'),('NAPOLI', 'PESCARA'),('SIENA', 'ROMA'),('UDINESE', 'CAGLIARI')]

#16 Giornata-09/12/2012 15.00.00
#ATALANTA-PARMA	-(- )
#BOLOGNA-LAZIO	-(- )
#CAGLIARI-CHIEVO	-(- )
#INTER-NAPOLI	-(- )
#PALERMO-JUVENTUS	-(- )
#PESCARA-GENOA	-(- )
#ROMA-FIORENTINA	-(- )
#SAMPDORIA-UDINESE	-(- )
#SIENA-CATANIA	-(- )
#TORINO-MILAN	-(- )
#17 Giornata-16/12/2012 15.00.00
#CATANIA-SAMPDORIA	-(- )
#CHIEVO-ROMA	-(- )
#FIORENTINA-SIENA	-(- )
#GENOA-TORINO	-(- )
#JUVENTUS-ATALANTA	-(- )
#LAZIO-INTER	-(- )
#MILAN-PESCARA	-(- )
#NAPOLI-BOLOGNA	-(- )
#PARMA-CAGLIARI	-(- )
#UDINESE-PALERMO	-(- )
#18 Giornata-22/12/2012 15.00.00
#ATALANTA-UDINESE	-(- )
#BOLOGNA-PARMA	-(- )
#CAGLIARI-JUVENTUS	-(- )
#INTER-GENOA	-(- )
#PALERMO-FIORENTINA	-(- )
#PESCARA-CATANIA	-(- )
#ROMA-MILAN	-(- )
#SAMPDORIA-LAZIO	-(- )
#SIENA-NAPOLI	-(- )
#TORINO-CHIEVO	-(- )
#19 Giornata-06/01/2013 15.00.00
#CATANIA-TORINO	-(- )
#CHIEVO-ATALANTA	-(- )
#FIORENTINA-PESCARA	-(- )
#GENOA-BOLOGNA	-(- )
#JUVENTUS-SAMPDORIA	-(- )
#LAZIO-CAGLIARI	-(- )
#MILAN-SIENA	-(- )
#NAPOLI-ROMA	-(- )
#PARMA-PALERMO	-(- )
#UDINESE-INTER	-(- )
#20 Giornata-13/01/2013 15.00.00
#LAZIO-ATALANTA	-(- )
#BOLOGNA-CHIEVO	-(- )
#UDINESE-FIORENTINA	-(- )
#CAGLIARI-GENOA	-(- )
#PARMA-JUVENTUS	-(- )
#SAMPDORIA-MILAN	-(- )
#NAPOLI-PALERMO	-(- )
#INTER-PESCARA	-(- )
#CATANIA-ROMA	-(- )
#TORINO-SIENA	-(- )
#21 Giornata-20/01/2013 15.00.00
#MILAN-BOLOGNA	-(- )
#ATALANTA-CAGLIARI	-(- )
#GENOA-CATANIA	-(- )
#ROMA-INTER	-(- )
#PALERMO-LAZIO	-(- )
#FIORENTINA-NAPOLI	-(- )
#CHIEVO-PARMA	-(- )
#SIENA-SAMPDORIA	-(- )
#PESCARA-TORINO	-(- )
#JUVENTUS-UDINESE	-(- )
#22 Giornata-27/01/2013 15.00.00
#LAZIO-CHIEVO	-(- )
#CATANIA-FIORENTINA	-(- )
#JUVENTUS-GENOA	-(- )
#ATALANTA-MILAN	-(- )
#PARMA-NAPOLI	-(- )
#CAGLIARI-PALERMO	-(- )
#SAMPDORIA-PESCARA	-(- )
#BOLOGNA-ROMA	-(- )
#UDINESE-SIENA	-(- )
#INTER-TORINO	-(- )
#23 Giornata-03/02/2013 15.00.00
#PALERMO-ATALANTA	-(- )
#PESCARA-BOLOGNA	-(- )
#ROMA-CAGLIARI	-(- )
#NAPOLI-CATANIA	-(- )
#SIENA-INTER	-(- )
#CHIEVO-JUVENTUS	-(- )
#GENOA-LAZIO	-(- )
#FIORENTINA-PARMA	-(- )
#TORINO-SAMPDORIA	-(- )
#MILAN-UDINESE	-(- )
#24 Giornata-10/02/2013 15.00.00
#ATALANTA-CATANIA	-(- )
#INTER-CHIEVO	-(- )
#JUVENTUS-FIORENTINA	-(- )
#PARMA-GENOA	-(- )
#CAGLIARI-MILAN	-(- )
#LAZIO-NAPOLI	-(- )
#PALERMO-PESCARA	-(- )
#SAMPDORIA-ROMA	-(- )
#BOLOGNA-SIENA	-(- )
#UDINESE-TORINO	-(- )
#25 Giornata-17/02/2013 15.00.00
#TORINO-ATALANTA	-(- )
#CATANIA-BOLOGNA	-(- )
#PESCARA-CAGLIARI	-(- )
#FIORENTINA-INTER	-(- )
#ROMA-JUVENTUS	-(- )
#SIENA-LAZIO	-(- )
#CHIEVO-PALERMO	-(- )
#MILAN-PARMA	-(- )
#NAPOLI-SAMPDORIA	-(- )
#GENOA-UDINESE	-(- )
#26 Giornata-24/02/2013 15.00.00
#PARMA-CATANIA	-(- )
#SAMPDORIA-CHIEVO	-(- )
#BOLOGNA-FIORENTINA	-(- )
#PALERMO-GENOA	-(- )
#INTER-MILAN	-(- )
#UDINESE-NAPOLI	-(- )
#LAZIO-PESCARA	-(- )
#ATALANTA-ROMA	-(- )
#JUVENTUS-SIENA	-(- )
#CAGLIARI-TORINO	-(- )
#27 Giornata-03/03/2013 15.00.00
#SIENA-ATALANTA	-(- )
#BOLOGNA-CAGLIARI	-(- )
#FIORENTINA-CHIEVO	-(- )
#ROMA-GENOA	-(- )
#CATANIA-INTER	-(- )
#NAPOLI-JUVENTUS	-(- )
#MILAN-LAZIO	-(- )
#TORINO-PALERMO	-(- )
#SAMPDORIA-PARMA	-(- )
#PESCARA-UDINESE	-(- )
#28 Giornata-10/03/2013 15.00.00
#INTER-BOLOGNA	-(- )
#JUVENTUS-CATANIA	-(- )
#LAZIO-FIORENTINA	-(- )
#GENOA-MILAN	-(- )
#CHIEVO-NAPOLI	-(- )
#ATALANTA-PESCARA	-(- )
#UDINESE-ROMA	-(- )
#CAGLIARI-SAMPDORIA	-(- )
#PALERMO-SIENA	-(- )
#PARMA-TORINO	-(- )
#29 Giornata-17/03/2013 15.00.00
#NAPOLI-ATALANTA	-(- )
#SIENA-CAGLIARI	-(- )
#PESCARA-CHIEVO	-(- )
#FIORENTINA-GENOA	-(- )
#SAMPDORIA-INTER	-(- )
#BOLOGNA-JUVENTUS	-(- )
#TORINO-LAZIO	-(- )
#MILAN-PALERMO	-(- )
#ROMA-PARMA	-(- )
#CATANIA-UDINESE	-(- )
#30 Giornata-30/03/2013 15.00.00
#UDINESE-BOLOGNA	-(- )
#LAZIO-CATANIA	-(- )
#CAGLIARI-FIORENTINA	-(- )
#INTER-JUVENTUS	-(- )
#CHIEVO-MILAN	-(- )
#TORINO-NAPOLI	-(- )
#PARMA-PESCARA	-(- )
#PALERMO-ROMA	-(- )
#ATALANTA-SAMPDORIA	-(- )
#GENOA-SIENA	-(- )
#31 Giornata-07/04/2013 15.00.00
#INTER-ATALANTA	-(- )
#CATANIA-CAGLIARI	-(- )
#UDINESE-CHIEVO	-(- )
#NAPOLI-GENOA	-(- )
#ROMA-LAZIO	-(- )
#FIORENTINA-MILAN	-(- )
#SAMPDORIA-PALERMO	-(- )
#SIENA-PARMA	-(- )
#JUVENTUS-PESCARA	-(- )
#BOLOGNA-TORINO	-(- )
#32 Giornata-14/04/2013 15.00.00
#PALERMO-BOLOGNA	-(- )
#CHIEVO-CATANIA	-(- )
#ATALANTA-FIORENTINA	-(- )
#CAGLIARI-INTER	-(- )
#LAZIO-JUVENTUS	-(- )
#MILAN-NAPOLI	-(- )
#TORINO-ROMA	-(- )
#GENOA-SAMPDORIA	-(- )
#PESCARA-SIENA	-(- )
#PARMA-UDINESE	-(- )
#33 Giornata-21/04/2013 15.00.00
#GENOA-ATALANTA	-(- )
#NAPOLI-CAGLIARI	-(- )
#SIENA-CHIEVO	-(- )
#UDINESE-LAZIO	-(- )
#JUVENTUS-MILAN	-(- )
#CATANIA-PALERMO	-(- )
#INTER-PARMA	-(- )
#ROMA-PESCARA	-(- )
#BOLOGNA-SAMPDORIA	-(- )
#FIORENTINA-TORINO	-(- )
#34 Giornata-28/04/2013 15.00.00
#ATALANTA-BOLOGNA	-(- )
#MILAN-CATANIA	-(- )
#SAMPDORIA-FIORENTINA	-(- )
#CHIEVO-GENOA	-(- )
#PALERMO-INTER	-(- )
#TORINO-JUVENTUS	-(- )
#PARMA-LAZIO	-(- )
#PESCARA-NAPOLI	-(- )
#ROMA-SIENA	-(- )
#CAGLIARI-UDINESE	-(- )
#35 Giornata-05/05/2013 15.00.00
#PARMA-ATALANTA	-(- )
#LAZIO-BOLOGNA	-(- )
#CHIEVO-CAGLIARI	-(- )
#NAPOLI-INTER	-(- )
#JUVENTUS-PALERMO	-(- )
#GENOA-PESCARA	-(- )
#FIORENTINA-ROMA	-(- )
#UDINESE-SAMPDORIA	-(- )
#CATANIA-SIENA	-(- )
#MILAN-TORINO	-(- )
#36 Giornata-08/05/2013 15.00.00
#SAMPDORIA-CATANIA	-(- )
#ROMA-CHIEVO	-(- )
#SIENA-FIORENTINA	-(- )
#TORINO-GENOA	-(- )
#ATALANTA-JUVENTUS	-(- )
#INTER-LAZIO	-(- )
#PESCARA-MILAN	-(- )
#BOLOGNA-NAPOLI	-(- )
#CAGLIARI-PARMA	-(- )
#PALERMO-UDINESE	-(- )
#37 Giornata-12/05/2013 15.00.00
#UDINESE-ATALANTA	-(- )
#PARMA-BOLOGNA	-(- )
#JUVENTUS-CAGLIARI	-(- )
#GENOA-INTER	-(- )
#FIORENTINA-PALERMO	-(- )
#CATANIA-PESCARA	-(- )
#MILAN-ROMA	-(- )
#LAZIO-SAMPDORIA	-(- )
#NAPOLI-SIENA	-(- )
#CHIEVO-TORINO	-(- )
#38 Giornata-19/05/2013 15.00.00
#TORINO-CATANIA	-(- )
#ATALANTA-CHIEVO	-(- )
#PESCARA-FIORENTINA	-(- )
#BOLOGNA-GENOA	-(- )
#SAMPDORIA-JUVENTUS	-(- )
#CAGLIARI-LAZIO	-(- )
#SIENA-MILAN	-(- )
#ROMA-NAPOLI	-(- )
#PALERMO-PARMA	-(- )
#INTER-UDINESE	-(- )
#
    for p in nextRound:
        w = probHomeWin(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])
        d = probDraw(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])
        l = probAwayWin(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])        
        guess = ""
        if (w > 0.25):
            guess = guess + "1 "
        if (d > 0.25):
            guess = guess + "X "
        if (l > 0.25):
            guess = guess + "2 "

        print "%10s %10s: %1.3f %1.3f %1.3f %s" %(p[0], p[1], w, d, l, guess)
        highestProbHomeWin(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])
        highestProbDraw(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])
        highestProbAwayWin(teamMap[p[0]], teamMap[p[1]], ah, bh, aa, ba, g[0], r[0])

    if (int(sys.argv[1]) != 0):
        tree_t = array.array('i', [13])
        tree_r = array.array('f', r)
        tree_g = array.array('f', g)
        tree_ah = array.array('f', ah)
        tree_aa = array.array('f', aa)
        tree_bh = array.array('f', bh)
        tree_ba = array.array('f', ba)
        
        file = ROOT.TFile("coeff.root", "update")
        tree = file.Get("coeff")
        if (tree == None):
            tree = ROOT.TTree("coeff", "coeff")

        tree.Branch("t", tree_t, "t/I")
        tree.Branch("aHome", tree_ah, "aHome[20]/F")
        tree.Branch("aAway", tree_aa, "aAway[20]/F")
        tree.Branch("bHome", tree_bh, "bHome[20]/F")
        tree.Branch("bAway", tree_ba, "bAway[20]/F")
        tree.Branch("g", tree_g, "g/F")
        tree.Branch("r", tree_r, "r/F")
        
        tree.Fill()
        tree.Write()
        
        file.Close()
