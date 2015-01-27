/*
 * mystrcpy.cpp
 *
 *  Created on: 2009-12-7
 *      Author: kwarph
 */

#include <iostream>

/**
 * @brief Copies the string pointed to by src, including the
 *        terminating null byte ('\0'), to the buffer pointed
 *        to by dest
 * @param src – source string
 * @param dest – destination string
 * @return destination string
 */
char* mystrcpy(char* dest, const char* src) {
	char* tmp = dest;
	while (*tmp++ = *src++)
		;

	return dest;
}

int main() {
	char ca[32];
	mystrcpy(ca, "hello, world!");

	std::cout << ca << '\n';
}
