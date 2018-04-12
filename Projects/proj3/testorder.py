import re

textfile = open("input.txt","r")
matches = re.findall("\\ba\\b -?\d+",textfile.read())
# print (matches)
textfile = open("input.txt","w")
# print(" ".join(["f " + str(i) for i in range(len(matches))]))
textfile.write("%s\n%s\n%s\nz 0"  % (" ".join(matches), " ".join(["fa " + str(i) for i in range(len(matches))]), " ".join(["f " + i[2:] for i in matches])))
# a 0 a 1 a 2 a 3 a -1 a 2
