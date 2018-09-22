import ROOT
import math
import extractResults
from array import array;

homeIndex = []
awayIndex = []
nmatches = 0

def fcn(npar, gin, f, par, iflag):
   global nmatches
   global xArray
   global yArray
   global homeIndex
   global awayIndex

   # calculate chisquare
   likelihood = 1.
   for i in range(nmatches):       
       parMatch = [par[homeIndex[i]*4], par[homeIndex[i]*4+2], par[awayIndex[i]*4+1], par[awayIndex[i]*4+3], par[8]]
       #print parMatch
       likelihhod = likelihood * myFunc(xArray[i], yArray[i], parMatch)
       
   #print likelihood
   f[0] = likelihood
   #ncount += 1

def myFunc(x, y, par):
    la = par[0]*par[3]*par[4]
    mu = par[2]*par[1]
    #print math.exp(-la), math.pow(la, x), math.exp(-mu), math.pow(mu, y)

    L = math.exp(-la)*math.pow(la, x)*math.exp(-mu)*math.pow(mu, y)
    
    f(a,b,c)*f(b)*g(a)*g(b)
    

    #print "L", L
    return L


teamMap = {'ATALANTA':0, 'LAZIO':1, 'CHIEVO':2, 'BOLOGNA':3, 'FIORENTINA':4, 'UDINESE':5,'GENOA':6, 'CAGLIARI':7,'JUVENTUS':8, 'PARMA':9,'MILAN':10, 'SAMPDORIA':11,'PALERMO':12, 'NAPOLI':13,'PESCARA':14, 'INTER':15,'ROMA':16, 'CATANIA':17,'SIENA':18, 'TORINO':19}

matches = extractResults.extract(teamMap)


x = []
y = []

for k, m in enumerate(matches):
    homeIndex.append(teamMap[m[0]])
    x.append(m[1])
    awayIndex.append(teamMap[m[2]])
    y.append(m[3])

xArray = array('f', x)
yArray = array('f', y)

minimizer = ROOT.TFitter(9)

p1 = array('d', [-1])
#minimizer.ExecuteCommand("SET PRINTOUT", p1, 1);

minimizer.SetFCN(fcn)

## Set starting values and step sizes for parameters
vstart = array('d', [1])
step   = array('d', [0.01])

for i in xrange(20):
    minimizer.SetParameter(i*4,   "ah"+str(i), vstart[0], step[0], 0, 10)
    minimizer.SetParameter(i*4+1, "aa"+str(i), vstart[0], step[0], 0, 10)
    #minimizer.SetParameter(i*4+2, "bh"+str(i), vstart[0], step[0], 0, 10)
    #minimizer.SetParameter(i*4+3, "ba"+str(i), vstart[0], step[0], 0, 10)
minimizer.SetParameter(9, "g", 1, 0.01, -10, 10)

arglist = array('d', [0])
#  minimizer->ExecuteCommand("SIMPLEX", 0, 0);
#arglist[0] = 9
minimizer.ExecuteCommand("MIGRAD", arglist, 0)
  
#  //double e1, e2, e3, e4;
#  //minimizer->GetErrors(0, e1, e2, e3, e4);
#  //std::cout << e1 << " " << e2 << " " << e3 << " " << e4 << std::endl;
#minimizer.mnmigr();
#  //double p[2] = {0, 1};
#  //minimizer->ExecuteCommand("CONTOUR", &p[0], (int)2);
#
minimizer.ExecuteCommand("HESSE", arglist, 0)
#    













#if __name__ == '__main__':
#   testfit()
