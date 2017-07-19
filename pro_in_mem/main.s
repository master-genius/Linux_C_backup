
main.o:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 e4 f0             	and    $0xfffffff0,%esp
   6:	83 ec 30             	sub    $0x30,%esp
   9:	dd 05 10 00 00 00    	fldl   0x10
   f:	dd 5c 24 20          	fstpl  0x20(%esp)
  13:	c7 04 24 0d 00 00 00 	movl   $0xd,(%esp)
  1a:	e8 fc ff ff ff       	call   1b <main+0x1b>
  1f:	89 44 24 28          	mov    %eax,0x28(%esp)
  23:	c7 04 24 0f 00 00 00 	movl   $0xf,(%esp)
  2a:	e8 fc ff ff ff       	call   2b <main+0x2b>
  2f:	89 44 24 2c          	mov    %eax,0x2c(%esp)
  33:	dd 44 24 20          	fldl   0x20(%esp)
  37:	d9 fa                	fsqrt  
  39:	db e8                	fucomi %st(0),%st
  3b:	7a 08                	jp     45 <main+0x45>
  3d:	db e8                	fucomi %st(0),%st
  3f:	74 12                	je     53 <main+0x53>
  41:	dd d8                	fstp   %st(0)
  43:	eb 02                	jmp    47 <main+0x47>
  45:	dd d8                	fstp   %st(0)
  47:	dd 44 24 20          	fldl   0x20(%esp)
  4b:	dd 1c 24             	fstpl  (%esp)
  4e:	e8 fc ff ff ff       	call   4f <main+0x4f>
  53:	dd 5c 24 20          	fstpl  0x20(%esp)
  57:	b8 00 00 00 00       	mov    $0x0,%eax
  5c:	dd 44 24 20          	fldl   0x20(%esp)
  60:	dd 5c 24 0c          	fstpl  0xc(%esp)
  64:	8b 54 24 2c          	mov    0x2c(%esp),%edx
  68:	89 54 24 08          	mov    %edx,0x8(%esp)
  6c:	8b 54 24 28          	mov    0x28(%esp),%edx
  70:	89 54 24 04          	mov    %edx,0x4(%esp)
  74:	89 04 24             	mov    %eax,(%esp)
  77:	e8 fc ff ff ff       	call   78 <main+0x78>
  7c:	e8 fc ff ff ff       	call   7d <main+0x7d>
  81:	b8 00 00 00 00       	mov    $0x0,%eax
  86:	c9                   	leave  
  87:	c3                   	ret    
