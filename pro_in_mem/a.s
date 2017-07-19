
a.o:     file format elf32-i386


Disassembly of section .text:

00000000 <fa>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 45 08             	mov    0x8(%ebp),%eax
   6:	0f af 45 08          	imul   0x8(%ebp),%eax
   a:	5d                   	pop    %ebp
   b:	c3                   	ret    
