f = open("nodes.txt", "w")
i=0
f.write("10000\n");
for c1 in range(100):
	for c2 in range(100):
		sttmp = "("+str(i)+", "+str(c1*37)+", "+str(c2*37)+")\n"
		f.write(sttmp)
		i+=1

f.close()
f = open("edges.txt", "w")
i=0
for c1 in range(100):
	for c2 in range(100):
		if(i>999):
			f.write("("+str(i-1000)+", "+str(i)+")\n")
		if(i<9000):
			f.write("("+str(i+1000)+", "+str(i)+")\n")
		if(i%1000!=0):
			f.write("("+str(i-1)+", "+str(i)+")\n")
		if(i%999!=0):
			f.write("("+str(i+1)+", "+str(i)+")\n")
		i+=1
f.close()
