
def extract(teamMap):

    file = open("risultati.txt")
    lines = file.readlines()
    file.close()
    
    matches = []

    for l in lines:
        if (l == "\n"):
            continue
        l = l.split("\n")[0]
        items = l.split(" ")
        s = items[0].split("-")
        g = items[1].split("-")
        
        matches.append((teamMap[s[0]], float(g[0]), teamMap[s[1]], float(g[1])))

    return matches

