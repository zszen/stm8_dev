   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.8 - 03 Dec 2008
2455                     ; 7 main()
2455                     ; 8 {
2457                     	switch	.text
2458  0000               _main:
2462                     ; 9 	PA_DDR = 0xff;
2464  0000 35ff5002      	mov	_PA_DDR,#255
2465                     ; 10 	PA_ODR = 0xff;
2467  0004 35ff5000      	mov	_PA_ODR,#255
2468                     ; 11 	PD_DDR = 0xff;
2470  0008 35ff5011      	mov	_PD_DDR,#255
2471                     ; 12 	PD_ODR = 0xff;
2473  000c 35ff500f      	mov	_PD_ODR,#255
2474  0010               L1061:
2475                     ; 13 	while (1);
2477  0010 20fe          	jra	L1061
2490                     	xdef	_main
2509                     	end
