# Embeded

### Embedded development

Embedded can be a place to obtain a saturation of knowledge of computer systems. Similar to desktop or mobile development it is possible for a developer to muddle along with remedial coding techniques and devices will work... mostly. Since most devices are lightweight a single developer can work on all aspects of code including operating systems all the way down to the "metal". Without a big picture understanding of things debugging is difficult to impossible since every system interacts with several others. A developer will either take the vertical learning curve as a challenge and step up and become the next level developer or they will only ever see whole systems as one of the black arts reserved for the anonymous master programmer in some abstract other place. 

### Intermediate techniques for static memory algorithms

The only place I ever saw algorithms used in embedded code was the first place I worked. The person that wrote that code now works for G@@gle. Most embedded code I have had to refactor appears to be written on the level of an intermediate hobbyist. This includes code in Wind@ws. This is strange since many embedded systems are written on small microcontrollers with limited resources where an algorithm would help most. **However the difficulty with using an algorithm is if the code is to be maintained by a low experience developer they will have difficultly reading and understanding the code.** Quora indicates that most developers use online searching to find solutions. This is where I am storing my own toolbox of algorithms written specifically for embedded systems eg Arduino, Raspberry Pi, mbed, Maker in exchange for being able to use the storage.

Algorithms are pure computer science methods to do things very efficiently that are not intuitive to beginning coders. Algorithms do not look anything like the brute force method (a -> b -> c) to perform a function. The only way to learn the algorithms is to write the code, write a thorough set of unit tests (tests to test your code thoroughly). Know how to break your code. After you write the code and tests give it to another coder they will break it in seconds. Go back and write a test that fails like the bug, fix the bug, test should pass.

### Static Memory Algorithms

[Moving average](https://github.com/dhiranak/Embeded/tree/master/moving%20average) is a demonstration of a optimized moving average (boxcar) filter.

[Static circular queue](https://github.com/dhiranak/Embeded/tree/master/Static_Queue) is a circular queue in its most basic form to store integers or indices for an array of pointers to data structures to manage the pool of elements.

[Static Linked List](https://github.com/dhiranak/Embeded/tree/master/Linked%20List) uses a queue to manage an array of list nodes. Included in the functions is a function to test for a cycle. This shows the basics of algorithms using static memory. 

[Static Binary Tree](https://github.com/dhiranak/Embeded/tree/master/Binary%20Tree) uses a queue to manage an array of binary tree nodes. The nodes class uses a singleton pattern to insure that only one instanced of a tree uses the same nodes in the class.  
