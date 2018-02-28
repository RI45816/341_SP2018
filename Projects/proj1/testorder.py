import re

textfile = open("input.txt","r+")
matches = re.findall("\d+",list(textfile)[0])
#print(" ".join(["f " + str(i) for i in range(len(matches))]))
textfile.write("\n" +" ".join(["fa " + str(i) for i in range(len(matches))]))
textfile.write("\n" +" ".join(["f " + i for i in matches]))