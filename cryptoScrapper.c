#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>
#include "fonction.h"


int main(int argc, char** argv) {
	char* buffer=malloc(64);
	char* logo;
	int trouve=0;

	char* prompt=malloc(128);
	char* option_w=malloc(16);


	struct {
        char *coin;
        char *logo;
    } coin_hashmap[] = {
		{"eth",""},
		{"ethereum",""},
		{"btc",""},
		{"bitcoin",""},
		{"sol","🟣"},
		{"solana","🟣"},
	};

	int len_coin_hashmap=sizeof(coin_hashmap)/sizeof(coin_hashmap[0]);

	if (argc==1) {
		printf("Format: ./cryptoScrapper {coin}");
		return 1;
	}

	if (argc>=2) {

		int i=0;
		while(!trouve && i<len_coin_hashmap) {
			if (!strcmp(argv[1],coin_hashmap[i].coin)) {

				logo=coin_hashmap[i].logo;
				trouve=1;
			}
			i++;
		} 
		buffer=get_value(argv[1],"valeur");
		if (!trouve) {
			logo="";
		}

	} 
	
	for (int i=2;i<argc;i++) {
		if(!strcmp(argv[i],"-w")) {
			option_w=get_value(argv[1],"whales");
		}
	}
	snprintf(prompt, 128,"%s  %s  %s",logo,buffer,option_w);
	printf("%s\n",prompt);

	free(buffer);
	free(prompt);
	return 0;
}
