#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>
#include "fonction.h"


//https://curl.se/libcurl/c/getinmemory.html
static size_t WritehtmlCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  string* mem = (string*)userp;
 
  char *ptr = realloc(mem->html, mem->size + realsize + 1);

  mem->html = ptr;
  memcpy(&(mem->html[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->html[mem->size] = 0;
 
  return realsize;
}
 
void find_value(char* html,char* buffer,char* type) {
	regex_t regex;
	regmatch_t matches[2];
	const char* pattern;
    if (!strcmp(type,"valeur")){pattern="<span class=\"sc-65e7f566-0 WXGwg base-text\"[^>]*>([^<]*)</span>";}
    if (!strcmp(type,"variation")){pattern = "<div class=\"sc-65e7f566-0 enCfYh\"><div data-role=\"percentage-value\"[^>]*><p[^>]*><svg[^>]*><path[^>]*><\\/path><\\/svg>([0-9]+\\.[0-9]+)%"; }
	if (!strcmp(type,"couleur")){pattern="<div class=\"sc-65e7f566-0 enCfYh\">.*?<p color=\"([^\"]+)";}
	if (regcomp(&regex, pattern, REG_EXTENDED)!=0) {

		printf("error: compilation of regex failed!");
		return;
	}

	if (regexec(&regex, html,2,matches,0)==0) {
		int debut = matches[1].rm_so;
        int fin = matches[1].rm_eo;
        snprintf(buffer, fin - debut + 1, "%s", html + debut);
	} else {
		printf("%s\n",pattern);
		printf("ERROR: Unfind value, verify the crypto-currency.");
		buffer="";
		return;
	}
	regfree(&regex);
}
char* get_html(char* code) {
	CURL* curl=curl_easy_init();
	CURLcode res;
	char* url=malloc(64);
	if (!strcmp(code,"eth")) {url="https://coinmarketcap.com/fr/currencies/ethereum/";}
	else if (!strcmp(code,"btc")) {url="https://coinmarketcap.com/fr/currencies/bitcoin/";}
	else if (!strcmp(code,"sol")) {url="https://coinmarketcap.com/fr/currencies/solana/";}
	else if (!strcmp(code,"doge")) {url="https://coinmarketcap.com/fr/currencies/dogecoin/";}
	else {snprintf(url,60,"%s%s%s","https://coinmarketcap.com/fr/currencies/",code,"/");}
	string chunk;
	chunk.html = malloc(1);
	chunk.size=0;

	curl_global_init(CURL_GLOBAL_ALL);

	
	curl_easy_setopt(curl, CURLOPT_URL, url);
 
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WritehtmlCallback);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	 
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	res = curl_easy_perform(curl);

	return chunk.html;	

/*
    if(!strcmp(type,"whales")) {
        find_value(chunk.html,buffer,"whales");
        return buffer;
    }
	free(chunk.html);
	free(url);
	return 0;	*/
}


void remove_space(char* string) {
	int i=0;int j=0;
	string[strlen(string)-5]= '\0';

	while (string[i] != '\0') {

		if (!((unsigned char)string[i] == 0xE2 || (unsigned char)string[i+1] == 0x80 || (unsigned char)string[i+2] == 0xAF)) {
			string[j++]=string[i];
		}else {
			i+=2;
		}
		i++;

		if(string[i]==',') {
			string[i]='.';
		}
	}
	string[j]='\0';
}