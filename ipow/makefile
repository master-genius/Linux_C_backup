all = test.o crnm.o nmop.o mvbits.o bw_div.o chdiv.o chmis.o dgdiv.o bw_mul.o chmul.o chadd.o bw_ipow.o

test: $(all)
	gcc -o test $(all)

$(all): fdef.h ddef.h


clean:
	rm $(all) test

