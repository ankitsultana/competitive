def max(a, b):
    if(a > b):
        return a
    return b

t = int(input())
prime = [None]*41
for i in range(41):
    prime[i] = 0

for i in range(2,41):
    if (prime[i] == 0):
        j = i*i
        while(j < 41):
            prime[j] = 1
            j += i
            
prime[0] = 1
prime[1] = 1

for tc in range(t):
    l = [None]*41
    for i in range(41):
        l[i] = 0
    n = int(input())
    for j in range(2,n+1):
        for i in range(2, j+1):
            power = 0
            temp = j
            while (prime[i] == 0 and temp % i == 0):
                power = power+1
                l[i] = max(l[i], power)
                temp /= i
                
    res = 1
    for i in range(2, n+1):
        while (l[i] != 0):
            res = res*i
            l[i] = l[i]-1
    print (res)
