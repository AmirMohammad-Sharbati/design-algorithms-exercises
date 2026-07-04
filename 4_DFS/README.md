## ASSIGNMENT 2: second question

in this algorithm we try to write the brute force algorithm. because of small inputs, it will be accepted.
I use DFS like algorithm. for what? for generating all non descentent sequences which are between 1 and m (bound = m) and their length is n. 

I write the recursive function which generates all sequences
after that we should check all constraints for all sequnces and print the most value which is passed constraints.


### Time complexity:
what is the count of non descentent sequences with n numbers which are from 1 to m?
we can compute it as this:
see it as difference between numbers that their sum should be less or equal to m-1.
so we should solve this equation:
x1 + ... xn <= m-1  | xi >= 0  => xi is the difference beween ai and ai-1 (a0 = 1)
so the count is this:
x1 + ... xn + xn+1 = m-1  =>  combination (n+m-1, n) choose n from n+m-1
suppose that maximum m and n is 10. so the count of sequences is less than 1e5.
for each one we should check all constraints which is at most q = 50.
so brute force algorithm works for these m, n, q well.

### 
we have python, cpp and java implementations for this question.
