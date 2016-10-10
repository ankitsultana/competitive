t=0
n=0
read t
tc=0
res=0
while [ $tc -lt $t ]; do
	read n
	res=$(((n*n*(n+1)*(n+1))/4))
	res=$((res-(n*(n+1)*(2*n+1)/6)))
	echo $res
	tc=$((tc+1))
done
