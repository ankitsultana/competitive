package main

import (
    "fmt"
    "bufio"
    "os"
)

const LIMIT = 5000003
var t int
var n int
var dp[LIMIT * 4] int
var prefix[LIMIT] int
var ans[LIMIT] int

func rec(n int) int {
    res := 0
    temp := n
    for ; n != 1; {
        if n % 2 == 0 {
            n /= 2
        } else {
            n = 3*n + 1;
        }
        res++
    }
    dp[temp] = res
    return res
}

func main() {
    io := bufio.NewReader(os.Stdin)
    for i := 1; i < LIMIT; i++ {
        rec(i)
        if prefix[i-1] > dp[i] {
            prefix[i] = prefix[i-1]
            ans[i] = ans[i-1]
        } else {
            prefix[i] = dp[i]
            ans[i] = i
        }
    }
    fmt.Fscan(io, &t)
    for i := 0; i < t; i++ {
        fmt.Fscan(io, &n)
        fmt.Println(ans[n])
    }
}
