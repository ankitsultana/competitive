# Enter your code here. Read input from STDIN. Print output to STDOUT
t = Integer(gets.chomp)
tc = 0
for tc in 1..t do
    n = Integer(gets.chomp)
    res = n*n*(n+1)*(n+1)/4
    res = res-(n*(n+1)*(2*n+1)/6)
    puts (res)
end
