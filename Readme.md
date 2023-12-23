# Bignum Data Type

In C++ programming language, there is a restriction on the size of the integers you can define and work. The largest integer you can represent in C++ is 2^64 in long data type.

You may need to work with much larger integers. Because I've been required to use large integers frequently, I decided to write a class for them so that it would not be necessary to implement it every time.

I implemented some basic operations for this class, Bignum, like summation, subtraction, etc. But I should mention that it is very slow, so it is not efficient to do lots of calculations on them. I implement each operation the way we naturally do; for instance, I implemented summation like we sum two numbers on the paper, summing every two digits from right to left of the number. Thus, it is straightforward to read.

I represent each number in an array, and each element shows a digit of the number.

There are lots of improvements that you can make to this code. For example, each element of the array can show more than a digit because a digit size is less than 4 bits, but each element has a size of 4 bytes. Another thing you can do is use the binary search algorithm in the part of the code where I tried to find a digit that meets the algorithm's needs by looping (in the division and finding the 2nd root). Of course, other improvements can be made.