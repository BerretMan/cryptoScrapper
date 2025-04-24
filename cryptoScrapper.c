#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>
#include "fonction.h"


#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define RESET "\x1B[0m"

int main(int argc, char** argv) {
	char* valeur=malloc(64);
	char* buffer=malloc(64);
	char* logo;
	int trouve=0;

	char* prompt=malloc(128);
	char* option_v=malloc(16);
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
		{"dogecoin","󰩃"},
		{"doge","󰩃"}
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
	snprintf(prompt, 128,"%s  %s %s %s",logo,valeur,option_v,option_w);
	printf("%s\n",prompt);

	free(buffer);
	free(valeur);
	free(option_v);
	free(html);
	free(prompt);
	return 0;
}
