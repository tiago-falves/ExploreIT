file1 = open('time', 'r') 

sum=0
i =0.0
for line in file1:
	sum += float(line)
	i+=1.0

print sum/i
print sum
