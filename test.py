from separator import separate
import sys
def getcap(data,unk,database):
    o=[]
    ta=separate(data)
    for i in ta:
        si=str(i)
        for j in range(10):
            if si in database[j]:
                o.append(j)
                break
        else:
            unk.write(i[2:-1]+"\n")
    return o
database=open(sys.argv[0][:-7]+"database.txt","rb")
unk=open(sys.argv[0][:-7]+"unk.txt","w")
tab=[[] for i in range(10)]
for line in database.readlines():
    tab[int(line[0:1])].append(str(line[4:-3]))
if len(sys.argv)==1:
    for line in open("suminputs.txt").readlines():
        print(getcap(line,unk,tab))

elif len(sys.argv)==2:
    x=getcap(sys.argv[1],unk,tab)
    if len(x)==3:
        sys.exit(x[0]*100+x[1]*10+x[2])
    else:
        sys.exit(-1)


unk.close()
