import random

def create(filename, t, n, m):
    f = open(filename, 'wb')
    f.write(str(t) + '\n')
    for x in xrange(t):
        f.write(str(n) + ' ' + str(m) + '\n')
        for i in xrange(n):
            f.write(str(random.randint(1, 1)) + ' ')
        f.write('\n')
        for j in xrange(m):
            f.write(str(random.randint(1, 1)) + ' ')
        f.write('\n')
    f.close()

create('big.in', 125, 50, 50)
