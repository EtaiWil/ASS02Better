# Grading System
## General Information
The program is an automated checking system of code program outputs made in c.<br>
The program contains two parts part 1: checking the relation between two files.Part 2: checking the relation between the output of the C program to the desired output. 
### part A (ex21)
This program accepts paths to two files as arguments to the main and checks whether the two files are identical/similar/different.
### definitions
##### Identical- two files are identical if all characters in them are equal.
##### Similar-Similar files are files that are not identical but contain the same text, and there is a difference in usage In lower or uppercase letters, space, and/or line breaks.
##### Different-different files are files that are not identical or similar.

For example: all the next files are similar:
```
File A:
12ab23
File B:
12Ab23
File C:
12aB23
File D:
12AB23
File E:
12 aB 23
File F:
12
ab2
3
```

## Setup for part A
1. Clone the repository:

```
https://github.com/EtaiWil/ASS02Better.git
```
2. Enter to Linux terminal and enter the following command: ``` gcc ex21.c -o comp.out  ``` 
3. Enter the 2 files that you want to check with their absolute  path ``` ./comp.out <path A> <path B>  ```  for example ```./comp.out /home/os2021/code/1.txt /home/os2021/code/2.txt```
3. Write ```echo $?```

* If the output is 1 -**the files are identical**
* If the output is 2 **the files are different**  
* If the output is 3 -**the files are similar**

### Part B (ex22)
This program accepts a path to a configuration file as an argument to the main. The configuration file contains 3 lines: <br>
Line 1: path to the folder containing subfolders. On the first level (one inside), each folder represents a user and should contain a c file.<br>
Line 2: Path to the file containing input.<br>
Line 3: Path to the file containing the correct output for the input file from line 2
The program enters into all subfolders and ignores other non-folder files if any inside the folder from row 1.Search in each of its subfolders and not at deeper levels for a c file and compile it. Then, the resulting executable file runs with the input that appears in the file in the location in row 2.<br>
Afterward, The output of the program is compared with the desired output file, whose location comes from line 3.<br>
In the end, the program creates a file (in the folder from which your program was run) named results.csv which contains each username (the name of the subfolder) its score (between 0 and 100), and the reason for the grade.
<br>
* NO_C_FILE : if in the directory there isn't a file that end with .c **grade 0** 
* COMPILATION_ERROR: if the file can't compile **grade 10**
* TIMOUT: the time to compile the file is more than 5 seconds. **grade 20**
* WRONG: if the output is different than the desire output **grade 50**
* SIMILAR: if the output  is different than the desire output but similar **grade 75**
* EXCELLENT: the output is identical **grade 100** 

### Examples 
##### Example for the results.csv:
```
Monica,100,EXCELLENT
Phoebe,0,NO_C_FILE
Rachel,20,TIMEOUT
Ross,10,COMPILATION_ERROR
Joey,50,WRONG
Chandler,75,SIMILAR
```
##### Example for the configuration file: 
```
/home/os2021/students
/home/os2021/io/input.txt
/home/os2021/io/output.txt

```
##### Example of input file content
```
1
5 4
4
```
##### Example of output file content:
```
Please enter an operation
Please enter two numbers
```
## Setup for part B
1. Clone the repository:
```
https://github.com/EtaiWil/ASS02Better.git
```
2.Enter to Linux terminal and enter to the following command:``` gcc ex22.c   ``` <br>
3.Enter the configuration file that you want to check with absolute  path ``` ./a.out <path A>   ```  for example ```./a.out /home/os2021/conf.txt```
4.See the results in results.csv

## Built with

- C


## Author

**Etai Wilentzik**

- [Profile](https://github.com/EtaiWilentzik )
- [LinkedIn]( https://www.linkedin.com/in/etai-wilentzik/ "Welcome")


## Support 🤝

Contributions, issues, and feature requests are welcome!

Give a ⭐️ if you like this project!


