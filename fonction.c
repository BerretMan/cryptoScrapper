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
    if (!strcmp(type,"whales")){pattern = "<div class=\"sc-65e7f566-0 enCfYh\"><div data-role=\"percentage-value\"[^>]*><p[^>]*><svg[^>]*><path[^>]*><\\/path><\\/svg>([0-9]+\\.[0-9]+)%"; }

	

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
char* get_value(char* code,char* type) {
	CURL* curl=curl_easy_init();
	CURLcode res;
	char* url=malloc(64);
	if (!strcmp(code,"eth")) {url="https://coinmarketcap.com/fr/currencies/ethereum/";}
	else if (!strcmp(code,"btc")) {url="https://coinmarketcap.com/fr/currencies/bitcoin/";}
	else if (!strcmp(code,"sol")) {url="https://coinmarketcap.com/fr/currencies/solana/";}
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
	char* buffer = malloc(256); 
    if(!strcmp(type,"valeur")) {
        find_value(chunk.html,buffer,"valeur");
        return buffer;
    }

    if(!strcmp(type,"whales")) {
        find_value(chunk.html,buffer,"whales");
        return buffer;
    }
	free(chunk.html);
	free(url);
	return 0;	
}