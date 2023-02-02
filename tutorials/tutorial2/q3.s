0000000 30 f4 30 00 00 00 00 00 00 00 80 20 00 00 00 00	| 
0000010 00 00 00 30 f2 0a 00 00 00 00 00 00 00 00 00 00	|  
0000020 90 20 23 

30 f4 30 00 00 00 00 00 00 00 
80 20 00 00 00 00 00 00 00 
30 f2 0a 00 00 00 00 00 00 00 00 00 
00	 
90 
20 23 

Address   Labels
0x20      proc
0x30      stack

irmovq $3, %rsp
call proc
irmovq 0x0a, %rdx
halt

.pos 0x20:
proc:
    ret                 # return immediately
    rrmovq %rdx, %rbx   # not executed

.pos 0x30
stack: