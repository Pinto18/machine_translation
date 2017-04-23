# 3 Metrics and Hypotheses
## Introduction
Our application will have similar algorithms written in both Javascript and C++. The application can be broken down into three main sections: file I/O, string manipulation, and floating point arithmetic. Performance for our application will be based on these three sections. We will perform a side by side comparison of both implementations to test their performance. 
## Metrics
### File I/O
The first metric is file I/O. C++ is a compiled language, while Javascript is an interpreted language. Because of this, C++ usually runs much faster than Javascript. Because both languages have implementations for file I/O, we believe that C++ will execute the file I/O portion of the code faster than Javascript.
> https://developer.mozilla.org/en-US/Add-ons/Code_snippets/File_I_O
> http://www.cplusplus.com/reference/fstream/ifstream/ 
### String Manipulation
The second metric is string manipulation. Javascript contains multiple methods for manipulating string. C++ on the other hand does not. Functions such as ‘lowercase’ are already implemented in Javascript but have to be implemented by the programmer in C++. This may result in more inefficient code in C++. Because of this, we believe that Javascript will execute the string manipulation portion of the code faster than C++.
> https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String \
> http://www.cplusplus.com/reference/string/string/ 
### Floating-Point Arithmetic
The third and final metric is floating point arithmetic. Fbench is a trigonometry intense floating-point benchmark. It determine the execution speed of a floating point application and checks the accuracy of the algorithm. With C as the baseline of 1, Javascript recieved a relative time of 27.6 on a Linux machine. Because of this, we believe that C++ will execute the floating point math portion of the code faster than Javascript.
> https://www.fourmilab.ch/fbench/fbench.html
