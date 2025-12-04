## Question 2 of Assignment 1 : 3D dominance counting

In this question we have n points in the input. we should compute the `ans` for each point:
```
ansi​=​{(xj​,yj​,zj​) ∣ xj​<xi​ and yj​<yi​ and zj​<zi​}
```
It is the count of points which have less coordinates.


### solution: divide and conqure

we should solve this problem with O(n log^2 n).
The brute force algorithm which is very easy to implement is O(n^2). We can compare each two points' coordinates and simply calculate the `ans` of each point.  
But it isn't the best algorithm. we should solve it more efficient.  
what is the idea? We should know about BIT (binary indexed tree) or also called fenwick tree:

#### What is Fenwick tree:  
--- explanation of this data structure and its application (sum of range of numbers in the array)  
(You can see good and complete explanations in this link:  
```
https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.youtube.com/watch%3Fv%3DuSFzHCZ4E-8&ved=2ahUKEwizjOCE5KORAxWY0QIHHVOrEQ8QkPEHegQIGRAB&usg=AOvVaw0WY_BHKWkAdJGwRZpGcNUu
```
)


OK, what should we do in this problem?
at first we sort points based on x. then we divide it into two parts, called left half and right half.  We know that the right one has bigger x, so the problem reduced to (y, z) problem (2D dominance counting).  

In each half we sort the y. Now, we iterate from left to right in each part. For each y in right side we know what points have less x and less y. now what should we do for z?

The most difficult part of algorithm is this: how to find the count of points in the left side that have less z from current point's z?

Problem reduced to this. we have two arrays of numbers (each one has M/2 numbers). their names are right and left. (adapt with the computing current z's less numbers in left side) Total numbers are from 1 to M. for each number in right, we should find how many numbers in the left side's sub array are less than this nubmer. what is the sub array of left side? In the main problem we specify it with ys, but for this reduced problem think it that it can be subarray from first index to k < M/2 and k grows by growing the z in the right array.

so we should use BIT for this. for each index we insert 1 if we see it in left sub array. we should find the count of indexes that are 1 and are less than z. how? 

We declare `seen_less_numbers` array. seen_less_numbers[i] is the state of seeing or not seeing the number i. for current z we should compute the sum of numbers in this array from first until index z. how to compute it because seen_less_numbers will change by iterating in left side?

we use BIT! ok, we have numbers and should sum over them in each query. and this is the exact application of BIT.

after that, we have the correct ans for each point. :)