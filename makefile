all: cryptoScrapper

cryptoScrapper: cryptoScrapper.o fonction.o
	gcc -o cryptoScrapper cryptoScrapper.o fonction.o -lcurl

fonction.o: fonction.c
	gcc -c fonction.c

cryptoScrapper.o: cryptoScrapper.c
	gcc -c cryptoScrapper.c

clean:
	rm -f cryptoScrapper *.o