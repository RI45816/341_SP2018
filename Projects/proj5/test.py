import re, sys, random

w = open("input.txt","r+")
r = w.read()
w.write("\n")

s=sys.argv[1:]
if (len(s)) > 2:
	w.write("\n".join([f"{i} " + f" {i} ".join(str(x) for x in random.sample(range(*[int(i) for i in s[:2]]),len(range(*[int(i) for i in s[:2]])))) for i in s[2:]]))
else:
	n = max([int(i[2]) for i in [*{*re.findall(r'(^|(?<=z ))(\d+) (\d+)',r)}]])
	w.write("\n"+re.sub(r'(^|(?<=z ))(\d+) (%i)' % n,lambda x:"%s %s" % (x[2],str(int(x[3])+1)),r,0))
w.write("\n")