#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

char *itoa(int num, char *out){
	int neg = 0;
	int count = 0;

	if (num < 0) {	
		neg = 1;
		num = 0 - num;
	}

	do{
		*out = (num % 10) + '0';
		num /= 10;
		out++;
		count++;
	} while (num != 0);

	if (neg == 1){
		*out = '-';
		out++;
		count++;
	}

	reverse(out-count, count);

	*out = '\0';
	return out-count;
}

// is_allocated: 0 for dont free, 1 for free
void parse_format(const char **fmt, va_list *vlist, char **out, int *is_allocated) {
	if (**fmt == '%') {
		*fmt = *fmt + 1;
		*is_allocated = 0;
		switch (**fmt) {
			case 's':
				*out = va_arg(vlist, char *);
				break;
			case 'd':
				*out = calloc(65, sizeof(char));
				*is_allocated = 1;
				int num = va_arg(vlist, int);
				itoa(num, *out);
				break;
			case '%':
				*out = calloc(2, sizeof(char));
				*is_allocated = 1;
				
				**out = '%';
				break;
			default:
				fprintf(stderr, "Invalid format!\n");
				*out = calloc(3, sizeof(char));
				*is_allocated = 1;
				
				**out = '%';
				*(*out+1) = **fmt;
				break;
		}

	}
	*fmt = *fmt + 1;
}

int my_sprintf(char *out, const char *fmt, ...) {
	va_list vlist;
	int count = 0;

	va_start(vlist, fmt);

	// fmt always point to next char to be processed
	// out always point to next char available
	while(*fmt != '\0') {
		if (*fmt != '%') {
			*out = *fmt;
			out++;
			count++;
			fmt++;
		} else {
			char *str;
			int is_allocated = 0;
			parse_format(&fmt, &vlist, &str, &is_allocated);
			char *to_free = str;

			while (*str != '\0') {
				*out = *str;
				out++;
				str++;
				count++;
			}

			if (is_allocated == 1) {
				free(to_free);
			}
		}
	}
	*out = '\0';

	va_end(vlist);

	return count;
}	

int my_snprintf(char *out, unsigned int n, const char *fmt, ...) {
	va_list vlist;
	int count = 0;

	va_start(vlist, fmt);

	// fmt always point to next char to be processed
	// out always point to next char available
	while(*fmt != '\0') {
		if (*fmt != '%') {
			if (count + 1 < n){
				*out = *fmt;
				out++;
			}
			count++;
			fmt++;
		} else {
			char *str;
			int is_allocated = 0;
			parse_format(&fmt, &vlist, &str, &is_allocated);
			char *to_free = str;

			while (*str != '\0') {
				if (count + 1 < n){
					*out = *str;
					out++;
				}
				str++;
				count++;
			}

			if (is_allocated == 1) {
				free(to_free);
			}
		}
	}
	*out = '\0';

	va_end(vlist);

	return count;
}

int main(void) {
	int count = 0;
	char *buff = malloc(sizeof(char) * 512);

	count = my_sprintf(buff, "hello %s, its been %d days.", "kevin", -29);

	printf("%s\n%d\n", buff, count);

	count = sprintf(buff, "hello %s, its been %d days.", "kevin", -29);

	printf("%s\n%d\n", buff, count);

	// snprintf

	count = my_snprintf(buff, 32, "hello %s, its been %d days.", "kevin", -29);

	printf("%s\n%d\n", buff, count);

	count = snprintf(buff, 32, "hello %s, its been %d days.", "kevin", -29);

	printf("%s\n%d\n", buff, count);

	free(buff);

	return 0;
}