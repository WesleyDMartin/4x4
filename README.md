# 4x4 Spastic Motion Interpret
## Conestoga College 4x4 - 2017

#### Wesley Martin, Ricardo Mohammed, Felipe Flor, Kalvin Stares

# Summary
This project will allow people with minimal or zero fine motor control interact with devices 
that would ordinarily require more controlled hand or arm gestures. By simulating motions such
as swipe right, swipe left, push down, or pull up, the program can interpret very inconsistent 
or shaky movements as a single command. Because the movements do not require force, the program 
can also be used to simulate button presses for those who otherwise lack the arm strength to activate 
buttons which require pressure.

# Moving Forward
Moving forward, there are two areas of research and improvement that would be required before this 
project would be testable in a real world situation. The first is the interaction between the
reader program operating on the host device and any API’s on that device that would be required 
to translate input commands to generic control functions. For example, translating the swipe right 
or swipe left to a forward or backward in a PowerPoint presentation. To make this project fully 
unctional, we would also need to alter the program to operate at a much faster sample rate, and 
with more sensors. The current limitations of the default teensy setup limit us to four samples 
per second. But with more optimized hardware and software, our design and setup is capable of 
getting close to twenty sets of data reads per second from four different sensors. Once we are 
able to implement those optimizations, we believe that this system is very capable of interpreting 
spastic gestures with a high degree of accuracy.
