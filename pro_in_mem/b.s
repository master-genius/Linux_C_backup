
b.o:     file format elf32-i386


Disassembly of section .text:

00000000 <fb>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 28             	sub    $0x28,%esp
   6:	8b 45 08             	mov    0x8(%ebp),%eax
   9:	89 04 24             	mov    %eax,(%esp)
   c:	e8 fc ff ff ff       	call   d <fb+0xd>
  11:	89 45 f4             	mov    %eax,-0xc(%ebp)
  14:	8b 45 f4             	mov    -0xc(%ebp),%eax
  17:	0f af 45 f4          	imul   -0xc(%ebp),%eax
  1b:	c9                   	leave  
  1c:	c3                   	ret    
