# The way of Skiena

## 1.7

### Counterexamples 

1. (1-1). a+b < min(a,b).    
        Negative numbers : -1+-2 < min(-1, -2) <=> -3 < -2 .

2. (1-2). a\*b < min(a,b).    
        A negative number : -1\*2 < min(-1, 2) <=> -2 < -1 .
        
3. (1-3). Design/draw a road network with two points a and b such that the fastest route between a and b is not the shortest route.     


The road network could be a right isosceles triangle with a and b as hypotenuse vertices, but with a limit of speed twice as smaller than the other route (by *legs* or catheti). Let d1 be the distance between a and b and d2 the distance of one leg (so the total distance between a and b using this route is `2*d2`). From the Pythagorean theorem, we have `d1^2 = 2*d2^2` so `d2 = d1/sqrt(2)`. Now, `t2 = 2*d2/v2 = 2*d1/(sqrt(2)*2*v1) = t1/sqrt(2)`. As sqrt(2) > 1, the fastest route is by the longest route, namely the legs of our triangle and not the hypotenuse.

4. (1-4). Design/draw a road network with two points a and b such that the shortest route between a and b is not the route with the fewest turns.    

We take the previous right isosceles triangle, we remove the hypotenuse and we replace it with an arc circle with the center in the middle of the (remove) hypotenuse. The arc circle has no turns, the triangle has one turn, but the shortest route is the triangle's catheti, not the arc circle. Let's prove it: let d1 be the distance by the circle and d2 the one by triangle. `d1 = 2*PI*R/2 = PI*R = PI*(d/2) = (PI/2) * d` . `d2 = 2*d/sqrt(2)= sqrt(2)*d` (see 1-3). `d1 > d2 <=> (PI/2)*d > sqrt(2)*d <=> PI > 2*sqrt(2) <=> PI^2 > 8 <=> 9,86 > 8` . QED.

5. (1-5). The knapsack problem: S = set, T = target.    
  - Put the elements of S in the knapsack in left to right order if they fit, i.e. the first-fit algorithm.    
        {3, 2, 2}, T = 4. Result is {3} instead of {2, 2}.
  - Put the elements of S in the knapsack from smallest to largest, i.e. the best-fit algorithm.    
        {3, 2, 1}, T = 2. Result is {1} instead of {2}.
  - Put the elements of S in the knapsack from largest to smallest.    
        {3, 2, 2}, T = 4. Result is {3} instead of {2, 2}.

6. (1-6). The cover set problem: U = {1, .., n}. Find a counterexample for the following algorithm: Select the largest subset for the cover, and then delete all its elements from the universal set. Repeat by adding the subset containing the largest number of uncovered elements until all are covered.

Naming conventions: SL is the largest set, while S1 ... Sm are the other sets. `len(SL) > len(Sk) for k=1..n`.   
Algorithm: U = SL + S1 + ... Sm. Let's find a counterexample U = S1 + ... Sm so that adding SL is useless, increasing the number of subsets, thus not the smallest cover set.

Let us try the smallest subset, m=1. In this case U = SL + S1, but also U = S1 which is contradiction because SL is larger than S1.
For m=2, let us find S1 and S2 so that

        U = SL + S1 + S2    (property 1)
        U = S1 + S2         (property 2)

We can suppose n is pair for our counterexample.
A winning case seems to be:

        SL = {1, ..., n/2-1, n/2+2, ..., n}
        S1 = {1, ..., n/2}
        S2 = {n/2+1, ..., n}

It is obvious that `U = S1 + S2` (property 1), so `U = SL + S1 + S2` (property 2). `len(S1) = len(S2) = n/2 < len(SL) = n-2 <=> 4 < n` . For 6 we have: {1, 2, 5, 6}, {1, 2, 3}, {4, 5, 6}.

Thus, a counterexample is, for U = {1 .. 6} :  **{1, 2, 5, 6}**, **{1, 2, 3}**, **{4, 5, 6}**.
 
# Help
- `GitHub` uses its own *md* format, but try to stick to the standard!
- use \\ to encode (escape) special characters.

# Reference
- Markdown (*md*) quick help: https://guides.github.com/features/mastering-markdown/. (tag_md)
- https://stackoverflow.com/questions/5112057/where-can-i-find-the-solutions-to-the-algorithm-design-manual
- (the precedent goes to) http://www.algorist.com/algowiki/index.php/The_Algorithms_Design_Manual_(Second_Edition)
