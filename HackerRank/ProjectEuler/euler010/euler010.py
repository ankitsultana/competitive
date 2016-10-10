t = int(raw_input())

MAXN = 1000001
isPrime = list(True for i in xrange(MAXN))
isPrime[0] = False
isPrime[1] = False

for i in xrange(MAXN):
    if i*i > MAXN:  
        break
    if not isPrime[i]:
        continue
    j = i*i
    while j < MAXN:
        isPrime[j] = False
        j += i

prefixSum = list(i if isPrime[i] else 0 for i in xrange(0, MAXN, 1))
for i in xrange(1, MAXN, 1):
    prefixSum[i] += prefixSum[i-1]

for tc in xrange(t):
    n = int(raw_input())
    print prefixSum[n]
