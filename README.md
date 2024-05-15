# CS 210

## Program Summary

&ensp; This program utilizes both C++ and Python to track grocery items and their frequency of purchase from an "items.txt" file that lists all items purchased in a given day. This program displays a menu with four user-selectable options until the user decides to exit the program. The first option allows the user to display a list of all items purchased in a given day along with the number of times each item was purchased. The second option allows the user to get the purchase frequency for a specific grocery item. The third option allows the user to display a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased. And finally, the last option allows the user to exit the program.

## Program Usage Preview

#### Option 1
![Option1](https://user-images.githubusercontent.com/111253795/185470125-614a50a9-bf49-4a8f-a8a0-9d093fe5f943.PNG)

#### Option 2
![Option2](https://user-images.githubusercontent.com/111253795/185470205-d0953e30-f195-4088-abbb-62a5b89d2562.PNG)

#### Option 3
![Option3](https://user-images.githubusercontent.com/111253795/185470233-d0256a98-13fb-4fef-ade2-be99ffa60d49.PNG)

#### Option 4
![Option4](https://user-images.githubusercontent.com/111253795/185470262-6ded0fc4-2b00-4112-9c63-9e71b4bd6538.PNG)

## Project Reflection

> What did you do particularly well?

&ensp; The code for this program is organized in such a way for easy readability. My functions are declared before the main program function, and they are defined after the main program function. I believe this helps with readability. I also used industry standard best practices for all function, parameter, and variable naming. Also, the code was properly documented using in-line comments and documentation blocks for functions.

&ensp; I am most proud of the implementation of the histogram. I implemented it in such a way that any string or frequency can be used in the contents of the table, and it will still be organized properly in the console output. The items and frequency characters are also color-coded for better readability. This histogram code can be reused for purposes other than this grocery-tracking program.

> Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

&ensp; There are some changes that I could do to enhance this program code. The first change that I would do is to implement type-checking for the user input. This way if the user accidentally entered something other than an integer, then an error code would be thrown and the program would continue. Another enhancement to the program code would be to implement a Histogram class that displays a formatted histogram for a given data file. There could also be a PrintWordAndFrequency class that would output each word in a given file and the amount of times it appears in the file (such as in Option 1 of this program). This would provide futher code encapsulation, delivering enhanced readability and reusability.

> Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

&ensp; The most difficult code to develop was the formatting of the histogram as it read in the data content from the "frequency.dat" file. I overcame this by carefully planning and implementing a solution to how many spaces to include between the histogram header strings / item strings and the divider lines. If the spaces were not calculated properly, then the table's line dividers would not line up between the different entries in the histogram. Also, the console text color formatting was new to me, so I turned to the Microsoft Docs to get information on how to handle the console output.

> What skills from this project will be particularly transferable to other projects or course work?

&ensp; There were many skills gained from the implementation of this project. The most useful of which is to identify when multiple programming languages could be used in one program. It may be more practical / effecient to use a specific programming language for a specific task in a program. In this grocery-tracking program, it made sense to use Python for its ability to easily read in and parse data from a file, and because of its ability to easily iterate through and manipulate the contents of containers, such as in a dictionary container.

> How did you make this program maintainable, readable, and adaptable?

&ensp; I made this program maintainable by separating out portions of code into functions. For example, there is a function to carry out the task outlined in each option of the user menu, except to exit the program (this is handled by the main program loop as a sentinel value). There are also functions to handle user input and handle the communication between the C++ code and Python code. In doing this encapsulation via functions, there are minimal lines of code in the main program loop. Descriptive funciton names are given as to further improve the readability of the main program loop. Also, all functions are declared before the main program function and defined after the main program function ensuring the main program function is towards the top of the source file. The code is also well-documented so that each portion of code is explained in plain English using in-line comments and documentation blocks for functions.
