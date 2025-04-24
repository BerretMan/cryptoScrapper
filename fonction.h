#ifndef FONCTION_H
#define FONCTION_H

#include <stdlib.h>

typedef struct {
	char* html;
	size_t size;
} string;

static size_t WritehtmlCallback(void *contents, size_t size, size_t nmemb, void *userp);

void find_value(char* html,char* buffer,char* type);

char* get_html(char* code);

void remove_space(char* string);


#endif