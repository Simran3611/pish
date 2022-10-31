
This is the creation of the shell. Most of the commands do work. Here is an example of commands to try in order to check if it works or not.

cat pish.c < inputRedir.txt //input redirect does not work
cat pish.c > outputRedir.txt
cat pish.c >> outputAppend.txt
ls | tee list
ls
rm inputRedir.txt
rm outputRedir.txt
rm outputAppend.txt
rm | tee list
ls
clear
cd //changes to home directory. Unable to change it to the directory specified

Sometimes the prompt might not be printed, regardless, input your command and it will still get executed.
Also sometimes when exiting or performing a task, the shell might print out multiple times that you have exited the shell.

The following signals are handled
- ctrl z
- ctrl c
- ctrl /

The parsing of spaces works however when we parse the command does not get executed.

Dup2 was used to write to files and strtok used to parse the strings.

