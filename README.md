# Embeded

### Intermediate techniques for static memory algorithms

The only place I ever saw algorithms used in embedded code was the first place I worked. The person that wrote that code now works for G@@gle. Most embedded code I have had to refactor appears to be written on the level of a intermediate hobbyiest. This includes code in Wind@ws. This is strange since many embedded systems are witten on small microcontrollers with limited resources where a algorithm would help most. **However the difficuty with using an algorithm is if the code is to be maintained by a low experience developer they will have difficutly reading and understanding the code.** Quora indicates that most developers use online searching to find solutions. This is where I am storing my own toolbox of algorithms written specifically for embedded systems eg Arduino, Rasberry Pi, mbed, Maker in exchange for being able to use the storage.

Algorithms are pure computer science methods to do things very efficiently that are not intuitive to beginning coders. The only way to learn something in coding is to write the code, write a throrough set of unit tests (tests to test your code thoroughly). Know how to break your code. After you write the code and tests give it to another coder they will break it in seconds. Go back and write a test that fails like the bug, fix the bug, test should pass.

Algorithms do not look anything like the brute force method (a -> b -> c) to peform a function. Read through write a unit test, use a debugger to walk through each line of code to understand it.

### Static Memory Algorithms

[Moving average](https://github.com/dhiranak/Embeded/tree/master/moving%20average) is a demonstration of a optimized moving average (boxcar) filter.
