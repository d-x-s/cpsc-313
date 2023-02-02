0x000: 30f46000000000000000	|   irmovq Stack, %rsp
0x0??: 30f00380000000000000	|   irmovq rtnp,%rax
0x014: a00f                	|   pushq %rax       
0x016: 6300                	|   xorq %rax,%rax   
0x018: 742c00000000000000   |   jne target       
0x0??: 30f00100000000000000	|   irmovq $1,%rax 
0x02b: 00                  	|   halt

0x02c: 90                 	|   target: ret
0x0??: 30f30200000000000000	|   irmovq $2,%rbx
0x037: 00                  	|   halt

0x038: 30f23000000000000000	|   rtnp: irmovq $3,%rdx
0x0??: 00                	|   halt

0x0??: ????????????????????	|   .pos 0x60 (we don't know this)
0x060: ????????????????????	|   Stack:    (we don't know this)
