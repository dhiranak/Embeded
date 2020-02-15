# Embeded
Intermediate techniques for static memory algorithms 


Moving average is a demonstration of a optimized moving average (boxcar) filter. The brute force method would be to have a static circular buffer, add a element to the buffer over writing the last value, add all of the elements in the buffer
then divide the sum with the number of elements in the buffer. This has a complexity of O(n) for each processing frame. The optimized function caches the int values, adding the new value, subtracting the oldest value, then divides by the window size. The new value is written over the older value in the buffer and the pointer is advanced. the complexity of the optimized version is O(3) with a memory complexity of O(n). The circular buffer is simplified by just overwriting the oldest value and advancing the pointer using a modulus function to roll over to the start of the buffer. 
