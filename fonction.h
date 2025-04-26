#ifndef FONCTION_H
#define FONCTION_H

#include <stdlib.h>

typedef struct {
	char* html;
	size_t size;
} string;

/**
 * @brief  Shows how the write callback function can be used to download data into a
 * chunk of memory instead of storing it in a file.
   @author https://curl.se/libcurl/c/getinmemory.html
 */
static size_t WritehtmlCallback(void *contents, size_t size, size_t nmemb, void *userp);

/**
 * @brief use regex to find a specific value in html
 * 
 * @param html 
 * @param buffer string which contains the final output
 * @param type specify a key-word for each regex
 */
void find_value(char* html,char* buffer,char* type);

/**
 * @brief Get the coinmarketpage of the cryto
 * @author BerretMan
 * 
 * @param code name or code of the crypto
 * @return char* html
 */
char* get_html(char* code);

/**
 * @brief Remove space(U+202F) from a string
 * @author BerretMan
 * 
 * @param string 
 */
void remove_space(char* string);

/**
 * @brief Transform string to the lowercase version
 * @author BerretMan
 * @param string 
 */
void lower_string(char* string);


#endif