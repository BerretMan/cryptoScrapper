all: cryptoScrapper clean

cryptoScrapper: cryptoScrapper.o
	gcc -o cryptoScrapper cryptoScrapper.o -lcurl

cryptoScrapper.o: cryptoScrapper.c
	gcc -c cryptoScrapper.c

clean:
	rm -f prog *.o