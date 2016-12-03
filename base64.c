#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

const char base64_map[] =
        	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
       		"abcdefghijklmnopqrstuvwxyz"
      		"0123456789+/";

size_t b64_length(size_t len){
	if (len % 3 != 0) {
		return ((len / 3) + 1) * 4;
	} else {
		return (len / 3) * 4;
	}
}

void b64_encode(const void * src, size_t len, void * dst){
	unsigned int bit_mask = 63;
	const unsigned char *source = (const unsigned char *) src;
	char *dest = (char *) dst;
	char buff[4];
	unsigned int bit_data = 0;

	for(int j = 0; j < (len/3); j++) {
		bit_data = source[0] << 16 | source[1] << 8 | source[2];

		for (int i = 1; i <= 4; i++) {
			buff[4 - i] = base64_map[bit_data & bit_mask];
			bit_data = bit_data >> 6;
		}

		for (int i = 0; i < 4; i++) {
			*dest = buff[i];
			dest++;
		}

		source += 3;
	}

	// assume padding at end
	if (len % 3 != 0) {
		int left_over_bytes = len % 3;
		int padded_bits = (3 - left_over_bytes) * 8;

		for (int i = 0; i < 3; i++){
			if (i < left_over_bytes) {
				bit_data = (bit_data << 8) | source[i];
			} else {
				bit_data = (bit_data << 8);
			}
		}

		for (int i = 1; i <= 4; i++){
			if(padded_bits >= 6) {
				padded_bits -= 6;
				buff[4 - i] = '=';
				bit_data = bit_data >> 6;
			} else {
				buff[4 - i] = base64_map[bit_data & bit_mask];
				bit_data = bit_data >> 6;
			}
		}

		for (int i = 0; i < 4; i++) {
			*dest = buff[i];
			dest++;
		}

		source += 3;
	}

	return;
}

int main() {
	char src[] = {0, 69, 242, 1, 69, 242, 2, 69, 242, 4, 69};
	char *dest = calloc(b64_length(sizeof(src)/sizeof(char)), 8);

	b64_encode(src, sizeof(src)/sizeof(char), dest);

	for (int i = 0; i < b64_length(sizeof(src)/sizeof(char)); i++) {
		printf("%c", dest[i]);
	}

	printf("\n");

	return 0;
}