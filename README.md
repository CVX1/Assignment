# Assignment 4 : Adding redirection to your rShell
## Author:   Mike   Izbicki
### Github Setup

The first part of assignment to is to update your github ‘Projects’. You will add a new project, call it ‘Assn 4 -- Redirection’ with the same 3 columns, ‘Backlog’, ‘In Progress’, and ‘To Deploy’. 

Now, after reading the assignment specifications, create manageable sized u ser stories . Each of these user stories should be logged as an issue on github, labeled as an enhancement. 
They should start in the ‘Backlog’ column. 
You then want to assign the first 2 or 3 user stories to each of the group members. 
```
Note: you can assign issues to contributors . 
```
The first issue each member decides to work on should be moved to the ‘In Progress’ column. Each user will want to track their work through the ‘Projects’ Kanban board and resolve the issue when they complete it. After completing all their assigned user stories they can assign themselves new ones and begin working on them. 


### Coding Requirements 

Extend your rshell program so that it properly handles 
* input redirection - "<" 
* output redirection - ">" (replacing)
* output redirection - ">>" (adding)
* piping - "|"

This will require using the Unix functions dup and pipe . You can find help on how to use these functions in the man pages. As an example, after this assignment, your program should be able to successfully handle the following command: 
```
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2 
```
IMPORTANT : This is a necessary but not sufficient test case. You must come up with others on your own. Bash has an extensive syntax for redirection, and you are not required to implement all of it. But if you're curious, see the [linux documentation project's bash io-redirection tutorial for details](http://www.tldp.org/LDP/abs/html/io-redirection.html).




