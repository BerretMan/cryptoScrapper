#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

typedef struct {
	char* html;
	size_t size;
} string;

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
 
void find_value(char* html,char* buffer) {
	regex_t regex;
	regmatch_t matches[2];
	const char* pattern=malloc(256);
	pattern="<span class=\"sc-65e7f566-0 WXGwg base-text\"[^>]*>([^<]*)</span>";

	if (regcomp(&regex, pattern, REG_EXTENDED)!=0) {
		printf("error: compilation of regex failed!");
		return;
	}

	if (regexec(&regex, html,2,matches,0)==0) {
		int debut = matches[0].rm_so;
        int fin = matches[0].rm_eo;
        snprintf(buffer, fin - debut + 1, "%s", html + debut);
	} else {
		printf("ERROR: unfind value, regex error");
	}
	regfree(&regex);
}


void cut_span(char* buffer) {
	int debut=0;int fin=0;
	int i=0;
	int bool_debut=0;

	while(fin==0){
		if (buffer[i]=='>') {
			debut=i+1;
			bool_debut=1;
		}
		if (buffer[i]=='<' && bool_debut == 1) {
			fin=i;
		}
		i++;
	}
	int len =fin-debut;
	buffer[len]='\0';
	strncpy(buffer, buffer+debut, len);


}


char* get_value(char* code) {
	CURL* curl=curl_easy_init();
	CURLcode res;
	char* url=malloc(64);
	if (!strcmp(code,"eth")) {url="https://coinmarketcap.com/fr/currencies/ethereum/";}
	if (!strcmp(code,"btc")) {url="https://coinmarketcap.com/fr/currencies/bitcoin/";}
	if (!strcmp(code,"sol")) {url="https://coinmarketcap.com/fr/currencies/solana/";}

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
	find_value(chunk.html,buffer);

	cut_span(buffer);
	return buffer;

	free(chunk.html);
	free(url);
	return 0;	
}

int main(int argc, char** argv) {
	char* buffer=malloc(64);
	if (argc==2) {
		if (!strcmp(argv[1],"eth") || !strcmp(argv[1],"ethereum")) {
			buffer=get_value("eth");
			printf(" %s",buffer);
		}
		if (!strcmp(argv[1],"btc") || !strcmp(argv[1],"bitcoin")) {
			buffer=get_value("btc");
			printf(" %s",buffer);
			
		}
		if (!strcmp(argv[1],"sol") || !strcmp(argv[1], "solana")) {
			buffer=get_value("sol");
			printf("🟣 %s",buffer);
		}

	}
	printf("\n");
	free(buffer);
	return 0;

}
