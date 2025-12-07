## Question 1 of Assignment 1 : DP algorithm question


In this question we have n numbers in input (actualy first number is n and after that we expect n numbers) called them ai (not AI, a with index i :)))  
We should generate the output for each sequence of numbers from 1 to k (for all k between 1 to n) We should maximize the result of sum(aibi) for 1<= i <= k. The constrain of problem is that b1 and bk should be 0, -1 or 1 and all numbers should have difference 1 or 0 from previous number. for example -1, 0, 1, 2, 1 is correct sequence but -1, 0 , 2, 3, 2, 1 isn't correct because the difference of 0 and 2 is bigger than 1.

https://en.wikipedia.org/wiki/Lipschitz_continuity

So for each number we should generate the result of this maximum sum of (aibi) for each i from 1 to k.

## What is the algorithm?
The algorithm is **Dynamic Programming**. we should solve the problem by solving some sub problems. we should see the question as recursive question. and in each step we should save the previous result to achieve the goal of DP and good performance in quesiton.

The idea is that result[k, t] (means that the result for numbers till k and it can be between -t and t) is this:
```
result[k, t] = max((ak*t + result[k-1, t-1]), (ak*t + result[k-1, t]), (ak*t + result[k-1, t+1])
                , (ak*t-1 + result[k-1, t-1]) ,...)
```

what?? t is between k and -k, so we should solve 3*2k sub problem. this is very bad. beside bad time complexity, the problem is space complexity.
we should make it better.
the main result for each k is for t = 1, -1, 0. for k+1 this number can be -2, -1, 0, 1, 2. but because of previous step we know that between numbers -1, 0, 1 what makes the result bigger, so we need only previous one, -2 and 2.
so in each step we need max of three calculation.
and so we need to save three number for each step for each i between 1 to n: the biggest of previous step and +-(k-i+1)
but, it still isn't perfect, it seems that in this algorithm we could achieve to O(n^2) time complexity (of course space complexity is O(n) and it is efficient) 


### The most difficult part of algorithm: How to achieve to n log n or n from previous algorithm?
The main point of question is that Fk(x) is concave. we define it as followed:
Fk(x) = best sum (aibi) 1 <= i <= k as bk = x.
because in step k we need this: what is the best total value if last b = x?
so the recursive function is this:
F(k+1)(y) = a(k+1) * y + max (Fk(y), Fk (y-1), Fk (y+1))
so the final result for each step is this:
Ans[k] = max (Fk(-1), Fk(0), Fk(1))

We should use concativity of F to store good points to show its total behaviour with a few points...
