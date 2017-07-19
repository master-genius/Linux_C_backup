
m:     file format elf32-i386


Disassembly of section .init:

08048340 <_init>:
 8048340:	53                   	push   %ebx
 8048341:	83 ec 08             	sub    $0x8,%esp
 8048344:	e8 00 00 00 00       	call   8048349 <_init+0x9>
 8048349:	5b                   	pop    %ebx
 804834a:	81 c3 ab 1c 00 00    	add    $0x1cab,%ebx
 8048350:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048356:	85 c0                	test   %eax,%eax
 8048358:	74 05                	je     804835f <_init+0x1f>
 804835a:	e8 41 00 00 00       	call   80483a0 <__gmon_start__@plt>
 804835f:	e8 fc 00 00 00       	call   8048460 <frame_dummy>
 8048364:	e8 97 02 00 00       	call   8048600 <__do_global_ctors_aux>
 8048369:	83 c4 08             	add    $0x8,%esp
 804836c:	5b                   	pop    %ebx
 804836d:	c3                   	ret    

Disassembly of section .plt:

08048370 <read@plt-0x10>:
 8048370:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 8048376:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 804837c:	00 00                	add    %al,(%eax)
	...

08048380 <read@plt>:
 8048380:	ff 25 00 a0 04 08    	jmp    *0x804a000
 8048386:	68 00 00 00 00       	push   $0x0
 804838b:	e9 e0 ff ff ff       	jmp    8048370 <_init+0x30>

08048390 <printf@plt>:
 8048390:	ff 25 04 a0 04 08    	jmp    *0x804a004
 8048396:	68 08 00 00 00       	push   $0x8
 804839b:	e9 d0 ff ff ff       	jmp    8048370 <_init+0x30>

080483a0 <__gmon_start__@plt>:
 80483a0:	ff 25 08 a0 04 08    	jmp    *0x804a008
 80483a6:	68 10 00 00 00       	push   $0x10
 80483ab:	e9 c0 ff ff ff       	jmp    8048370 <_init+0x30>

080483b0 <__libc_start_main@plt>:
 80483b0:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 80483b6:	68 18 00 00 00       	push   $0x18
 80483bb:	e9 b0 ff ff ff       	jmp    8048370 <_init+0x30>

080483c0 <sqrt@plt>:
 80483c0:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483c6:	68 20 00 00 00       	push   $0x20
 80483cb:	e9 a0 ff ff ff       	jmp    8048370 <_init+0x30>

Disassembly of section .text:

080483d0 <_start>:
 80483d0:	31 ed                	xor    %ebp,%ebp
 80483d2:	5e                   	pop    %esi
 80483d3:	89 e1                	mov    %esp,%ecx
 80483d5:	83 e4 f0             	and    $0xfffffff0,%esp
 80483d8:	50                   	push   %eax
 80483d9:	54                   	push   %esp
 80483da:	52                   	push   %edx
 80483db:	68 f0 85 04 08       	push   $0x80485f0
 80483e0:	68 80 85 04 08       	push   $0x8048580
 80483e5:	51                   	push   %ecx
 80483e6:	56                   	push   %esi
 80483e7:	68 84 84 04 08       	push   $0x8048484
 80483ec:	e8 bf ff ff ff       	call   80483b0 <__libc_start_main@plt>
 80483f1:	f4                   	hlt    
 80483f2:	90                   	nop
 80483f3:	90                   	nop
 80483f4:	90                   	nop
 80483f5:	90                   	nop
 80483f6:	90                   	nop
 80483f7:	90                   	nop
 80483f8:	90                   	nop
 80483f9:	90                   	nop
 80483fa:	90                   	nop
 80483fb:	90                   	nop
 80483fc:	90                   	nop
 80483fd:	90                   	nop
 80483fe:	90                   	nop
 80483ff:	90                   	nop

08048400 <__do_global_dtors_aux>:
 8048400:	55                   	push   %ebp
 8048401:	89 e5                	mov    %esp,%ebp
 8048403:	53                   	push   %ebx
 8048404:	83 ec 04             	sub    $0x4,%esp
 8048407:	80 3d 60 a0 04 08 00 	cmpb   $0x0,0x804a060
 804840e:	75 3f                	jne    804844f <__do_global_dtors_aux+0x4f>
 8048410:	a1 64 a0 04 08       	mov    0x804a064,%eax
 8048415:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 804841a:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 8048420:	c1 fb 02             	sar    $0x2,%ebx
 8048423:	83 eb 01             	sub    $0x1,%ebx
 8048426:	39 d8                	cmp    %ebx,%eax
 8048428:	73 1e                	jae    8048448 <__do_global_dtors_aux+0x48>
 804842a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048430:	83 c0 01             	add    $0x1,%eax
 8048433:	a3 64 a0 04 08       	mov    %eax,0x804a064
 8048438:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 804843f:	a1 64 a0 04 08       	mov    0x804a064,%eax
 8048444:	39 d8                	cmp    %ebx,%eax
 8048446:	72 e8                	jb     8048430 <__do_global_dtors_aux+0x30>
 8048448:	c6 05 60 a0 04 08 01 	movb   $0x1,0x804a060
 804844f:	83 c4 04             	add    $0x4,%esp
 8048452:	5b                   	pop    %ebx
 8048453:	5d                   	pop    %ebp
 8048454:	c3                   	ret    
 8048455:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048459:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048460 <frame_dummy>:
 8048460:	55                   	push   %ebp
 8048461:	89 e5                	mov    %esp,%ebp
 8048463:	83 ec 18             	sub    $0x18,%esp
 8048466:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 804846b:	85 c0                	test   %eax,%eax
 804846d:	74 12                	je     8048481 <frame_dummy+0x21>
 804846f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048474:	85 c0                	test   %eax,%eax
 8048476:	74 09                	je     8048481 <frame_dummy+0x21>
 8048478:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 804847f:	ff d0                	call   *%eax
 8048481:	c9                   	leave  
 8048482:	c3                   	ret    
 8048483:	90                   	nop

08048484 <main>:
 8048484:	55                   	push   %ebp
 8048485:	89 e5                	mov    %esp,%ebp
 8048487:	83 e4 f0             	and    $0xfffffff0,%esp
 804848a:	83 ec 30             	sub    $0x30,%esp
 804848d:	dd 05 60 86 04 08    	fldl   0x8048660
 8048493:	dd 5c 24 20          	fstpl  0x20(%esp)
 8048497:	c7 04 24 0d 00 00 00 	movl   $0xd,(%esp)
 804849e:	e8 69 00 00 00       	call   804850c <fa>
 80484a3:	89 44 24 28          	mov    %eax,0x28(%esp)
 80484a7:	c7 04 24 0f 00 00 00 	movl   $0xf,(%esp)
 80484ae:	e8 65 00 00 00       	call   8048518 <fb>
 80484b3:	89 44 24 2c          	mov    %eax,0x2c(%esp)
 80484b7:	dd 44 24 20          	fldl   0x20(%esp)
 80484bb:	d9 fa                	fsqrt  
 80484bd:	db e8                	fucomi %st(0),%st
 80484bf:	7a 08                	jp     80484c9 <main+0x45>
 80484c1:	db e8                	fucomi %st(0),%st
 80484c3:	74 12                	je     80484d7 <main+0x53>
 80484c5:	dd d8                	fstp   %st(0)
 80484c7:	eb 02                	jmp    80484cb <main+0x47>
 80484c9:	dd d8                	fstp   %st(0)
 80484cb:	dd 44 24 20          	fldl   0x20(%esp)
 80484cf:	dd 1c 24             	fstpl  (%esp)
 80484d2:	e8 e9 fe ff ff       	call   80483c0 <sqrt@plt>
 80484d7:	dd 5c 24 20          	fstpl  0x20(%esp)
 80484db:	b8 50 86 04 08       	mov    $0x8048650,%eax
 80484e0:	dd 44 24 20          	fldl   0x20(%esp)
 80484e4:	dd 5c 24 0c          	fstpl  0xc(%esp)
 80484e8:	8b 54 24 2c          	mov    0x2c(%esp),%edx
 80484ec:	89 54 24 08          	mov    %edx,0x8(%esp)
 80484f0:	8b 54 24 28          	mov    0x28(%esp),%edx
 80484f4:	89 54 24 04          	mov    %edx,0x4(%esp)
 80484f8:	89 04 24             	mov    %eax,(%esp)
 80484fb:	e8 90 fe ff ff       	call   8048390 <printf@plt>
 8048500:	e8 33 00 00 00       	call   8048538 <fc>
 8048505:	b8 00 00 00 00       	mov    $0x0,%eax
 804850a:	c9                   	leave  
 804850b:	c3                   	ret    

0804850c <fa>:
 804850c:	55                   	push   %ebp
 804850d:	89 e5                	mov    %esp,%ebp
 804850f:	8b 45 08             	mov    0x8(%ebp),%eax
 8048512:	0f af 45 08          	imul   0x8(%ebp),%eax
 8048516:	5d                   	pop    %ebp
 8048517:	c3                   	ret    

08048518 <fb>:
 8048518:	55                   	push   %ebp
 8048519:	89 e5                	mov    %esp,%ebp
 804851b:	83 ec 28             	sub    $0x28,%esp
 804851e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048521:	89 04 24             	mov    %eax,(%esp)
 8048524:	e8 e3 ff ff ff       	call   804850c <fa>
 8048529:	89 45 f4             	mov    %eax,-0xc(%ebp)
 804852c:	8b 45 f4             	mov    -0xc(%ebp),%eax
 804852f:	0f af 45 f4          	imul   -0xc(%ebp),%eax
 8048533:	c9                   	leave  
 8048534:	c3                   	ret    
 8048535:	90                   	nop
 8048536:	90                   	nop
 8048537:	90                   	nop

08048538 <fc>:
 8048538:	55                   	push   %ebp
 8048539:	89 e5                	mov    %esp,%ebp
 804853b:	83 ec 18             	sub    $0x18,%esp
 804853e:	c7 44 24 08 1f 00 00 	movl   $0x1f,0x8(%esp)
 8048545:	00 
 8048546:	c7 44 24 04 40 a0 04 	movl   $0x804a040,0x4(%esp)
 804854d:	08 
 804854e:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048555:	e8 26 fe ff ff       	call   8048380 <read@plt>
 804855a:	b8 68 86 04 08       	mov    $0x8048668,%eax
 804855f:	c7 44 24 04 40 a0 04 	movl   $0x804a040,0x4(%esp)
 8048566:	08 
 8048567:	89 04 24             	mov    %eax,(%esp)
 804856a:	e8 21 fe ff ff       	call   8048390 <printf@plt>
 804856f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048574:	c9                   	leave  
 8048575:	c3                   	ret    
 8048576:	90                   	nop
 8048577:	90                   	nop
 8048578:	90                   	nop
 8048579:	90                   	nop
 804857a:	90                   	nop
 804857b:	90                   	nop
 804857c:	90                   	nop
 804857d:	90                   	nop
 804857e:	90                   	nop
 804857f:	90                   	nop

08048580 <__libc_csu_init>:
 8048580:	55                   	push   %ebp
 8048581:	57                   	push   %edi
 8048582:	56                   	push   %esi
 8048583:	53                   	push   %ebx
 8048584:	e8 69 00 00 00       	call   80485f2 <__i686.get_pc_thunk.bx>
 8048589:	81 c3 6b 1a 00 00    	add    $0x1a6b,%ebx
 804858f:	83 ec 1c             	sub    $0x1c,%esp
 8048592:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 8048596:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 804859c:	e8 9f fd ff ff       	call   8048340 <_init>
 80485a1:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 80485a7:	29 c7                	sub    %eax,%edi
 80485a9:	c1 ff 02             	sar    $0x2,%edi
 80485ac:	85 ff                	test   %edi,%edi
 80485ae:	74 29                	je     80485d9 <__libc_csu_init+0x59>
 80485b0:	31 f6                	xor    %esi,%esi
 80485b2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80485b8:	8b 44 24 38          	mov    0x38(%esp),%eax
 80485bc:	89 2c 24             	mov    %ebp,(%esp)
 80485bf:	89 44 24 08          	mov    %eax,0x8(%esp)
 80485c3:	8b 44 24 34          	mov    0x34(%esp),%eax
 80485c7:	89 44 24 04          	mov    %eax,0x4(%esp)
 80485cb:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 80485d2:	83 c6 01             	add    $0x1,%esi
 80485d5:	39 fe                	cmp    %edi,%esi
 80485d7:	75 df                	jne    80485b8 <__libc_csu_init+0x38>
 80485d9:	83 c4 1c             	add    $0x1c,%esp
 80485dc:	5b                   	pop    %ebx
 80485dd:	5e                   	pop    %esi
 80485de:	5f                   	pop    %edi
 80485df:	5d                   	pop    %ebp
 80485e0:	c3                   	ret    
 80485e1:	eb 0d                	jmp    80485f0 <__libc_csu_fini>
 80485e3:	90                   	nop
 80485e4:	90                   	nop
 80485e5:	90                   	nop
 80485e6:	90                   	nop
 80485e7:	90                   	nop
 80485e8:	90                   	nop
 80485e9:	90                   	nop
 80485ea:	90                   	nop
 80485eb:	90                   	nop
 80485ec:	90                   	nop
 80485ed:	90                   	nop
 80485ee:	90                   	nop
 80485ef:	90                   	nop

080485f0 <__libc_csu_fini>:
 80485f0:	f3 c3                	repz ret 

080485f2 <__i686.get_pc_thunk.bx>:
 80485f2:	8b 1c 24             	mov    (%esp),%ebx
 80485f5:	c3                   	ret    
 80485f6:	90                   	nop
 80485f7:	90                   	nop
 80485f8:	90                   	nop
 80485f9:	90                   	nop
 80485fa:	90                   	nop
 80485fb:	90                   	nop
 80485fc:	90                   	nop
 80485fd:	90                   	nop
 80485fe:	90                   	nop
 80485ff:	90                   	nop

08048600 <__do_global_ctors_aux>:
 8048600:	55                   	push   %ebp
 8048601:	89 e5                	mov    %esp,%ebp
 8048603:	53                   	push   %ebx
 8048604:	83 ec 04             	sub    $0x4,%esp
 8048607:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 804860c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804860f:	74 13                	je     8048624 <__do_global_ctors_aux+0x24>
 8048611:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048616:	66 90                	xchg   %ax,%ax
 8048618:	83 eb 04             	sub    $0x4,%ebx
 804861b:	ff d0                	call   *%eax
 804861d:	8b 03                	mov    (%ebx),%eax
 804861f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048622:	75 f4                	jne    8048618 <__do_global_ctors_aux+0x18>
 8048624:	83 c4 04             	add    $0x4,%esp
 8048627:	5b                   	pop    %ebx
 8048628:	5d                   	pop    %ebp
 8048629:	c3                   	ret    
 804862a:	90                   	nop
 804862b:	90                   	nop

Disassembly of section .fini:

0804862c <_fini>:
 804862c:	53                   	push   %ebx
 804862d:	83 ec 08             	sub    $0x8,%esp
 8048630:	e8 00 00 00 00       	call   8048635 <_fini+0x9>
 8048635:	5b                   	pop    %ebx
 8048636:	81 c3 bf 19 00 00    	add    $0x19bf,%ebx
 804863c:	e8 bf fd ff ff       	call   8048400 <__do_global_dtors_aux>
 8048641:	83 c4 08             	add    $0x8,%esp
 8048644:	5b                   	pop    %ebx
 8048645:	c3                   	ret    
