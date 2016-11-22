#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

// swap and reverse should go into their own utility file
void swap(char *a, char *b){
	char temp = *a;
	*a = *b;
	*b = temp;
}

void reverse(char *str, int size){
	int start = 0;
	int end = size - 1;

	while (start < end){
		swap(str+start, str+end);
		start++;
		end--;
	}
	return;
}

// Default base 10, will add support for other bases later
// will have to be single digit under base, or will take the least
// significant digit under base (default 10)
char digit_to_char(int num, int base) {
	int digit = num;

	if (digit >= base){
		digit = digit % base; 
	}

	return digit + '0';
}

char hex_to_char(int num) {
	char result = 0;

	if (num < 10) {
		result = num + '0';
	} else {
		result = (num - 10) + 'A';
	}

	return result;
}

int char_to_hex(char c) {
	int result = 0;

	if (c >= 'A') {
		result = (c - 'A') + 10;
	} else {
		result = c - '0';
	}

	return result;
}

int char_to_digit(char c) {
	return c - '0';
}

char *itoa(int num, char *out, int base){
	int neg = 0;
	int count = 0;
	int digit_mask = 15;

	switch (base) {
		case 10: {
			if (num < 0) {	
				neg = 1;
				num = 0 - num;
			}

			do{
				*out = digit_to_char(num, base);
				num /= base;
				out++;
				count++;
			} while (num != 0);

			if (neg == 1){
				*out = '-';
				out++;
				count++;
			}
			break;
		}
		case 16: {
			unsigned int u_num = (unsigned int) num;
			int digit;

			do {
				digit = u_num & digit_mask;
				u_num = u_num >> 4;
				*out = hex_to_char(digit);
				out++;
				count++;
			} while (u_num != 0);
			
			*out = 'x';
			out++;
			count++;
			*out = 'O';
			out++;
			count++;

			break;
		}
		default:
			break;
	}

	reverse(out-count, count);

	*out = '\0';
	return out-count;
}

// default base 10
int a_to_i(char *str, int base) {
	int result = 0;
	int neg = FALSE;

	switch (base) {
		case 10: {
			while(*str != '\0') {
				if (*str == '-') {
					neg = TRUE;
				} else {
					result = (result * 10) + char_to_digit(*str);
				}
				str++;
			}

			if (neg == TRUE) {
				result = - result;
			}
			break;
		}
		case 16: {
			// we skip the Ox prefix
			str += 2;

			while (*str != '\0') {
				result = (result << 4) | char_to_hex(*str);
				str++;
			}
		}
	}

	return result;
}

int main() {
	int a = -128333;
	int b = 199022;

	char *buffer_a = calloc(65, sizeof(char));
	char *buffer_b = calloc(65, sizeof(char));

	printf("a: %s\n", itoa(a, buffer_a, 16));
	printf("b: %s\n", itoa(b, buffer_b, 16));

	int c = a_to_i(buffer_a, 16);
	int d = a_to_i(buffer_b, 16);

	printf("c: %d\n", c);
	printf("d: %d\n", d);

	free(buffer_a);
	free(buffer_b);

	return 0;
}