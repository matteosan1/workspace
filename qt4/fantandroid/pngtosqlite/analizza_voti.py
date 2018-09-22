import sys, os

filename = ""
theRound = -1
if (len(sys.argv) == 1):
    filename = raw_input("input file: ")
    theRound = raw_input("Giornata:")
else:
    filename = sys.argv[1]
    theRound = int(sys.argv[2])

file = open(filename)
lines = file.readlines()
file.close()

id = 0
name = ""
playedRole = -1
scored = 0
conceded = 0
assist = 0
yellowCard = 0
redCard = 0
kickedPenalty = 0
savedPenalty = 0
failedPenalty = 0
ownGoal = 0
vote = 0

file  = open("sqlCommands_"+str(theRound), "w")
file2 = open("voti_"+str(theRound)+".csv", "w") 

i = 0
for l in lines:
    if (l[0] == " " or l == ""):
        continue
    #print l
    if (i == 0):
        temp = l.split(" ")
        id = int(temp[0])
        name = " ".join(temp[1:]).upper().split("\n")[0]

    if (i == 1):
        playedRole = l.split("\n")[0]

    if (i == 2):
        temp = l.split("\n")[0]
        if (temp != "-"):
            vote = float(temp)
        else:
            vote = 0

    if (i == 3):
        temp = l.split("\n")[0]
        if (temp == "-"):
            scored = 0
            conceded = 0
        elif (int(temp) > 0):
            scored = int(temp)
            conceded = 0
        elif (int(temp) < 0):
            conceded = abs(int(temp))
            scored = 0

    if (i == 4):
        temp = l.split("\n")[0]
        if (temp != "-"):
            assist = int(temp)
        else:
            assist = 0

    if (i == 5):
        temp = l.split("\n")[0]
        if (playedRole == "Por"):
            if (temp != "-"):
                savedPenalty  = int(temp)
            else:
                savedPenalty = 0
        else:
            if (temp != "-"):
                kickedPenalty  = int(temp)
            else:
                kickedPenalty = 0
                
    if (i == 6):
        temp = l.split("\n")[0]
        if (temp != "-"):
            failedPenalty = int(temp)
        else:
            failedPenalty = 0

    if (i == 8):
        temp = l.split("\n")[0]
        if (temp != "-"):
            yellowCard = int(temp)
        else:
            yellowCard = 0

    if (i == 9):
        temp = l.split("\n")[0]
        if (temp != "-"):
            redCard = int(temp)
        else:
            redCard = 0

    if (i == 7):
        temp = l.split("\n")[0]
        if (temp != "-"):
            ownGoal = int(temp)
        else:
            ownGoal = 0
        
    i += 1

    if (i == 11):
        file.write("INSERT INTO playerStats (id, name, playedRole, round, scored, conceded, assist, yellowCard, redCard, kickedPenalty, savedPenalty, failedPenalty, ownGoal, vote) VALUES (")
        file.write(str(id)+",'" + name + "'," + str(-1) + "," + str(theRound) + "," + str(scored) + "," + str(conceded) + "," + str(assist) + "," + str(yellowCard) + "," + str(redCard) + "," + str(kickedPenalty) + "," + str(savedPenalty) + "," + str(failedPenalty) + "," + str(ownGoal) + "," +str(vote) + ");")
        file.write("\n")

        file2.write(name + ";" + str(playedRole) + ";-999;" + str(scored) + ";" + str(conceded) + ";" + str(assist) + ";" + str(yellowCard) + ";" + str(redCard) + ";" + str(savedPenalty) + ";" + str(failedPenalty) + ";" + str(ownGoal) + ";" +str(vote) + "\n")

        i = 0

file.close()
file2.close()    

file = open("dbUpdater.sh", "w")
file.write("#!/bin/bash\n")
file.write("sqlite3 prova.sqlite < sqlCommands_"+str(theRound)+"\n")
file.close()
#os.chmod("dbUpdater.sh", 777)
