from PIL import Image
from glob import iglob
from base64 import b64encode
from base64 import b64decode
from io import BytesIO
def bfs(q,tab,im):
    newimg=im.copy()
    tab2=newimg.load()
    black = 255
    for i in range(im.size[0]):
        for j in range(im.size[1]):
            tab2[i,j]=(0,0,0,0)
    pic=im.load()
    i=0
    mi=q[0][0]
    mj=q[0][1]
    while len(q)>i:
        tmp=q[i]
        i=i+1
        if tmp[0]<mi:
            mi=tmp[0]
        if tmp[1]<mj:
            mj=tmp[1]
        if tmp[0]-1>=0 and tab[tmp[0]-1][tmp[1]] and pic[tmp[0]-1,tmp[1]][3]==black:
            q.append((tmp[0]-1,tmp[1]))
            tab[tmp[0]-1][tmp[1]]=0
        if tmp[1]-1>=0 and tab[tmp[0]][tmp[1]-1] and pic[tmp[0],tmp[1]-1][3]==black:
            q.append((tmp[0],tmp[1]-1))
            tab[tmp[0]][tmp[1]-1]=0
        if tmp[0]+1<im.size[0] and tab[tmp[0]+1][tmp[1]] and pic[tmp[0]+1,tmp[1]][3]==black:
            q.append((tmp[0]+1,tmp[1]))
            tab[tmp[0]+1][tmp[1]]=0
        if tmp[1]+1<im.size[1] and tab[tmp[0]][tmp[1]+1] and pic[tmp[0],tmp[1]+1][3]==black:
            q.append((tmp[0]-1,tmp[1]+1))
            tab[tmp[0]-1][tmp[1]+1]=0
    for j in q:
        tab2[j[0]-mi,j[1]-mj]=(0,0,0,black)
    q[:]=[]
    b=BytesIO()
    newimg.save(b,"png")
    return str(b64encode(b.getvalue()))

def separate(data):
    im=Image.open(BytesIO(b64decode(data)))
    black = 255
    pic=im.load()
    q=[]
    ta=[]
    tab=[[1 for i in range(im.size[1])] for i in range(im.size[0])]
    for i in range(im.size[0]):
        for j in range(im.size[1]):
            if tab[i][j]==1 and pic[i,j][3]==black:
                q.append((i,j))
                ne=bfs(q,tab,im)
                ta.append(ne)
    return ta

