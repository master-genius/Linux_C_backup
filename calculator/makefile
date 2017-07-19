all = test.o bw_add.o chadd.o crnm.o nmop.o bw_mis.o chmis.o chmul.o bw_mul.o mvbits.o bw_div.o chdiv.o

calt: $(all)
	gcc -o calt $(all) -O2

$(all): fdef.h ddef.h

clean:
	rm $(all) calt

