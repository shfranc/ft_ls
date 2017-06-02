# ft_ls
Command LS, which list files in Mac operating systems, sort by lexicographic order.

### Required options
-R : search through folders recursively  
-l : display long format, with detailed information about the file  
-t : sort by modification time  
-a : include hidden files  
-r : reverse sorting  

### Others options
-G : colors, 11 colors for types, permissions or user  
-S : sort by size  
-u : display or sort by last access time with -l and -t, no effect otherwise  
-U : display or sort by birth time with -l and -t, no effect otherwise  
-f : no acsii sorting + option 'a' active  
-1 : display in a single column (default is in column)  

### Optimisation
All sorts are executed with a merge sort algorithm on linked lists.
