# Skiena path

## 1.7

### Counterexamples 

1-1. a+b < min(a,b).    
        Negative numbers : -1+-2 < min(-1, -2) <=> -3 < -2 .

1-2. a\*b < min(a,b).    
        A negative number : -1\*2 < min(-1, 2) <=> -2 < -1 .
        
1-3. Design/draw a road network with two points a and b such that the fastest route between a and b is not the shortest route.    
        The road network could be a right isosceles triangle with a and b as hypotenuse vertices, but with a limit of speed twice as smaller than the other route (by *legs* or catheti). Let d1 be the distance between a and b and d2 the distance of one leg (so the total distance between a and b using this route is `2*d2`). From the Pythagorean theorem, we have `d1^2 = 2*d2^2` so `d2 = d1/sqrt(2)`. Now, `t2 = 2*d2/v2 = 2*d1/(sqrt(2)*2*v1) = t1/sqrt(2)`. As sqrt(2) > 1, the fastest route is by the longest route, namely the legs of our triangle and not the hypotenuse.

1-4. Design/draw a road network with two points a and b such that the shortest route between a and b is not the route with the fewest turns.    
        We take the previous right isosceles triangle, we remove the hypotenuse and we replace it with an arc circle with the center in the middle of the (remove) hypotenuse. The arc circle has no turns, the triangle has one turn, but the shortest route is the triangle's catheti, not the arc circle. Let's prove it: let d1 be the distance by the circle and d2 the one by triangle. `d1 = 2*PI*R/2 = PI*R = PI*(d/2) = (PI/2) * d` . `d2 = 2*d/sqrt(2)= sqrt(2)*d` (see 1-3). `d1 > d2 <=> (PI/2)*d > sqrt(2)*d <=> PI > 2*sqrt(2) <=> PI^2 > 8 <=> 9,86 > 8` . QED.
 
# Help
- `GitHub` uses its own *md* format, but try to stick to the standard!
- use \\ to encode (escape) special characters.

# Reference
- Markdown (*md*) quick help: https://guides.github.com/features/mastering-markdown/
- https://stackoverflow.com/questions/5112057/where-can-i-find-the-solutions-to-the-algorithm-design-manual
- (the precedent goes to) http://www.algorist.com/algowiki/index.php/The_Algorithms_Design_Manual_(Second_Edition)
