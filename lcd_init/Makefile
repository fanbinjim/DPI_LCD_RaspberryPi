cc = gcc
target = lcd_init
object = lcd_init.o
lib = bcm2835
$(target) : $(object)
	cc -o $(target) $(object) -L. -l $(lib)

clean :
	rm -rf *.o $(target)