# DATA_STRUCTURES_PROJECT2
Chip operations. The code will use chips to perform operation on different sets of numbers. The results and sequences of operations will be displayed.

Description: Imagine you have a collection of specialized computing chips designed to perform a specific elementary arithmetic operation. These operations include addition, subtraction, multiplication, negation, and division. Each chip, except for the negation chip, requires two input values and produces a single output value. Due to the nature of its operation, the negation chip only needs one input and generates one output.
Among these chips, there is a unique type called the output chip. This chip has one input and no output, as its sole function is to display the value it receives through its input line. For instance, if an output chip labeled O50 receives a value of 987.2, it will display a message like: “I am output chip number 50, and the value I received is 987.2.”
In addition to the output chip, an input chip is designed to provide values to the computing system. This input chip feeds a value into the circuit, acting as a data source for the calculations performed by the other chips.
Consider a configuration where four chips are connected in sequence to perform a series of operations. These chips are as follows:

1.
A100 (Addition Chip): This chip adds two input values. It is connected to two input chips labeled I1 and I2. These input chips supply the values to be added.

2.
N110 (Negation Chip): The output from the addition chip A100 is sent to the input of the negation chip N110. The negation chip takes this input value and negates it, producing a single output that is the negative of the input value.

3.
M120 (Multiplication Chip): This chip requires two inputs to perform multiplication. One of its inputs is connected to the output of the negation chip N110, while the other input comes from the output of another input chip labeled I3.

4.
S130 (Subtraction Chip): The output from the multiplication chip M120 is fed into one of the inputs of the subtraction chip S130. The other input to this chip comes from the output of an additional input chip labeled I4. The subtraction chip then subtracts the second input from the first and produces an output.

Finally, the output from the subtraction chip S130 is connected to the input of the output chip, labeled O50. This output chip, O50, receives and prints the final computed value from the sequence of operations. For instance, if the final value is 42.0, it would display: “I am output chip number 50, and the value I received is 42.0.”

In summary, the configuration of these chips allows a series of arithmetic operations to be performed in sequence, where each chip's output is passed as an input to the next chip in the chain. The entire process culminates in the output chip, which displays the final result of the computations.
The input to your program will have the following format for the above. First, we build the circuit. Note that the first character is to add a chip to our circuit with a single letter A.

![image](https://github.com/user-attachments/assets/c652f146-432a-40df-ac3f-06c9e888a1dc)

After you build the circuit, you give input values, let the circuit execute, and produce an answer. The input is shown below. Note that the first character is an I, which tells us we are feeding some values into the input chips. You will also see that the first character is an O, which tells us we are asking the output chip to give us the output.

I I1 5
I I2 10
I I3 5
I I4 10
O O50

Now consider a much more elaborate circuit, as shown pictorially below.

![image](https://github.com/user-attachments/assets/1fd5acdd-786f-4078-815b-de1541e5bd80)

The input for building the above circuit will be as follows:
13. <- Number of chips in our circuit
I1
I2
I3
I4
I5
I6
O50
A100
Page 4 of 7
S200
M300
N400
D500
S600
19 <- Number of commands including input command and the output command
A I1 A100
A I2 A100
A I3 S200
A I4 S200
A A100 M300
A S200 M300
A M300 N400
A N400 D500
A I5 D500
A D500 S600
A I6 S600
A S600 O50
Once you provide input values for I1, I2, I3, I4, I5, and I6, as below, you should produce the correct output.
I I1 5
I I2 10
I I3 3
I I4 1
I I5 4
I I6 2
O O50

Your Project Implementation: As part of this project, you will create the CHIP class as described below.
Programming Objectives:
1.
All code must be in C++.You will create a class given below with appropriate fields.

2.
The class will have several methods whose prototypes are provided to you.

3.
All input will be read via redirected input. That is, you will not open a file inside the program.

4.
The class structure is shown below (you are responsible for fixing any syntax errors).

5.
The structure for your main program is also provided. You will use that for your project.

Program Structure:
You will have the following class structure. You have to ensure that all methods and appropriate additional fields are added.


