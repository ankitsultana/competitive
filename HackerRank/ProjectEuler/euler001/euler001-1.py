def s(n): return (n*(n+1))/2
def alpha(n): return (3*s(n/3))+(5*s(n/5))-(15*s(n/15))
print '\n'.join((str(alpha((int(raw_input()))-1))) for tc in xrange(int(raw_input())))
