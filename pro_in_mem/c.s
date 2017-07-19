
c.o:     file format elf32-i386


Disassembly of section .text:

00000000 <fc>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 18             	sub    $0x18,%esp
   6:	c7 44 24 08 1f 00 00 	movl   $0x1f,0x8(%esp)
   d:	00 
   e:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  15:	00 
  16:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
  1d:	e8 fc ff ff ff       	call   1e <fc+0x1e>
  22:	b8 00 00 00 00       	mov    $0x0,%eax
  27:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  2e:	00 
  2f:	89 04 24             	mov    %eax,(%esp)
  32:	e8 fc ff ff ff       	call   33 <fc+0x33>
  37:	b8 00 00 00 00       	mov    $0x0,%eax
  3c:	c9                   	leave  
  3d:	c3                   	ret    
