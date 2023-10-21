# Grading System
## General Information
this project is
The program is an automated checking system of code program outputs made in c. the program contain two parts
part 1: checking the relation between two files.
part 2: checking the relation between output of c program to the desire output. 
### part A (ex21)
this program accepts paths to two files as arguments to main, and checks whether the two files
Identical/similar/different.
### definitions
##### identical- two files are identical if all characters in them are equal
##### similar-Similar files are files that are not identical, but contain the same text, and there is a difference in usage In lower or uppercase letters, space and/or line breaks
##### different-different files are files that are not identical or similar.

for example: all the next files are similar
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
2. eneter to Linux terminal and enter to following command: ``` gcc ex21.c -o comp.out  ``` 
3. enter the 2 files that you want to check with their absolute  path ``` ./comp.out <path A> <path B>  ```  for example ```./comp.out /home/os2021/code/1.txt /home/os2021/code/2.txt```
3. write ```echo $?```

* if the output is 1 -**the files are identical**
* if the output is 2 **they are different**  
* if the output is 3 -**the files are similar**

### part B (ex22)
this program accepts  a path to a configuration file as an argument to the main.

The configuration file contains 3 lines:
Line 1: path to the folder containing subfolders. On the first level (one inside), each folder
represents a user, and should contain a c file.
Line 2: Path to the file containing input.
Line 3: Path to the file containing the correct output for the input file from line 2
<br>
the  program enter  into all subfolders and ignore other non-folder files if any inside the folder from row 1.
search in each of its subfolders and not at deeper levels for a c file and compile it.
 then ,the resulting executable file  run with the input that appears in the file in the location in row 2.afterwards,
The output of the program  compared with the desired output file, whose location comes from line 3.
At the end ,the  program  create a file (in the folder from which your program was run) named results.csv
which contains for each username (the name of the subfolder) its score (between 0 and 100) and the reason for the grade.
<br>
* NO_C_FILE : if in the directory there isn't a file that end with .c **grade 0** 
* COMPILATION_ERROR: if the file can't compile **grade 10**
* TIMOUT: the time to compile the file is more than 5 seconds. **grade 20**
* WRONG: if the output is different than the desire output **grade 50**
* SIMILAR: if the output  is different than the desire output but similar **grade 75**
* EXCELLENT: the output is identical **grade 100** 

### examples 
##### example for the results.csv
```
Monica,100,EXCELLENT
Phoebe,0,NO_C_FILE
Rachel,20,TIMEOUT
Ross,10,COMPILATION_ERROR
Joey,50,WRONG
Chandler,75,SIMILAR
```
##### example for the configuration file 
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
##### Example of output file content
```
Please enter an operation
Please enter two numbers
```
## Setup for part B
1. Clone the repository:
```
https://github.com/EtaiWil/ASS02Better.git
```
2. eneter to Linux terminal and enter to following command: ``` gcc ex22.c   ```
3. enter the configuration file that you want to check with absolute  path ``` ./a.out <path A>   ```  for example ```./a.out /home/os2021/conf.txt```
4. see the results in results.csv

## Built With

- C


## Author

**Etai Wilentzik**

- [Profile](https://github.com/EtaiWil )
- [Email](mailto:etaiwil2000@gmail.com?subject=Hi "Hi!")
- [LinkedIn](https://www.linkedin.com/in/etai-wilentzik-b5a106212/ "Welcome")

## Support 🤝

Contributions, issues, and feature requests are welcome!

Give a ⭐️ if you like this project!


