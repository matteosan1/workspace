import netsnmp

session = netsnmp.Session(DestHost='192.168.127.253', Version=2, Community='public')

#.1 index
#.2 channel
#.3 Mac Addr
#.4 Signal Strength
#.5 Transimission rate
#.6 SSID
for i in xrange(1, 7):
    vars = netsnmp.VarList(netsnmp.Varbind('.1.3.6.1.4.1.8691.15.70.1.11.17.1.'+str(i)))
    print (session.walk(vars))
