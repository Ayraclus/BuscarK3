from random import randint,shuffle

n = int(raw_input('Cantidad de Vertices \n'))
d = float(raw_input('Densidad de artistas (Recomendado < 0.1, cantidad de ejes en el Kn = '+ str( n * (n-1) / 2) + ')\n'))
m = int(n*(n-1)/2*d)
t = 1

for i in xrange(t):
  f = open('N'+str(n)+'M'+str(m),'w')
  
  mat = [[0 for x in xrange(n)] for y in xrange(n)]
  
  cnt = 0
  
  while(cnt<m):
    a = randint(0,n-1)
    b = filter(lambda x: mat[a][x] == 0 and a!=x ,xrange(n))
    shuffle(b)
    b = b[0]

    can = True
    for c in xrange(n):
      if c==a: continue
      if c==b: continue
      if mat[a][c]==1 and mat[b][c]==1: can = False
    
    if can:
      mat[a][b] = 1
      mat[b][a] = 1
      cnt+=1
      print (cnt)

  print>>f, n
  for a in xrange(n):
    for b in xrange(a+1,n):
      if mat[a][b]==1:
        print>>f, a,b
  
  f.close()
