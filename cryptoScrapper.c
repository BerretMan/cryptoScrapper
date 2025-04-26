#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>
#include "fonction.h"


#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"

int main(int argc, char** argv) {
	char* valeur=malloc(64);
	char* buffer=malloc(64);
	char* logo;
	int trouve=0;

	char* prompt=malloc(128);
	char* option_v=malloc(16);

	char* bitcoin_logo="\x1B[33m\x1B[0m";
	char* ethereum_logo="\x1B[35m\x1B[0m";
	char* solana_logo="\x1B[35m󰰢\x1B[0m";
	char* dogecoin_logo="\x1B[33m󰩃\x1B[0m";

	struct {
        char *coin;
        char *logo;
    } coin_hashmap[] = {
		{"eth",ethereum_logo},
		{"ethereum",ethereum_logo},
		{"btc",bitcoin_logo},
		{"bitcoin",bitcoin_logo},
		{"sol",solana_logo},
		{"solana",solana_logo},
		{"dogecoin",dogecoin_logo},
		{"doge",dogecoin_logo}
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

		if (!trouve) {
			logo="";
		}
		
	} 
	
	char* html=get_html(argv[1]);
	
    find_value(html,valeur,"valeur");

	char* color=malloc(16);
	for (int i=2;i<argc;i++) {

		if(!strcmp(argv[i],"-o")) {

			remove_space(valeur);
			printf("%s",valeur);	
			return 0;
		}

		if (!strcmp(argv[i],"-$")) {


			remove_space(valeur);
			double v=atof(valeur);

			char* prix_du_dollar=malloc(16);
			char* html_usdt=get_html("tether");
			find_value(html_usdt,prix_du_dollar,"valeur");
			remove_space(prix_du_dollar);
			double usdt=atof(prix_du_dollar);

			snprintf(valeur, 64,"%.2f $", v/usdt);


		}

		if(!strcmp(argv[i],"-v")) {

		 	find_value(html,buffer,"variation");
			find_value(html,color,"couleur");

			if (!strcmp(color,"red")) {
				snprintf(option_v, 64,"%s -%s%% (1d) %s", RED, buffer, RESET);
			} else {
				snprintf(option_v, 64,"%s +%s%% (1d) %s", GREEN, buffer, RESET);
			}
		}

	}
	snprintf(prompt, 128,"%s %s%s",logo,valeur,option_v);
	printf("%s\n",prompt);

	free(buffer);
	free(valeur);
	free(option_v);
	free(html);
	free(prompt);
	return 0;
}
