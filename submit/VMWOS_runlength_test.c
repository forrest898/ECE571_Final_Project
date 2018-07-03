/* Prints B for 5s */
/* Half of the traditional duo used to show multi-tasking is working */

#include <stddef.h>
#include <stdint.h>
#include "syscalls.h"
#include "vlibc.h"

#define MAX_RLEN 50
#define BENCH 250
#define DICT_BYTES 938848

int main(int argc, char **argv) {
	//printf("HERE");
	int fd = 1;

	int z = 0;
	//char * ptr;
	uint32_t bytesRead;

	fd = open("/home/american-english", O_RDONLY, 0);
	if(fd < 0) {
		printf("Failed to open file for compression\n");
		return 1;
	}
	//printf("here1\n");

  int rLen;
	char *count;
	count = vmwos_malloc(MAX_RLEN);
  printf("Memsetting %p for count\n", count);
	memset(count, 0, MAX_RLEN);

	char *dest;
	dest=vmwos_malloc((DICT_BYTES*2+1));
  printf("Memsetting %p for destination string\n",dest);
	memset(dest, 0, (DICT_BYTES*2+1));
	//printf("here3\n");

	//fileSize = lseek(fd, 0, SEEK_END);
	char *c;
	c=vmwos_malloc(DICT_BYTES);

	printf("Memsetting for dictionary%p\n",c);
	memset(c,0,800*600*3);

	//memset(c, 0, DICT_BYTES*sizeof(char));
	//printf("here2\n");

	bytesRead = read(fd, c, DICT_BYTES);
	//printf("here3\n");
	printf("I read %d bytes\n", bytesRead);


	int i, j = 0, k;

	for(z = 0; z < BENCH; z++) {
		//lseek(fd, 0, SEEK_SET);
	//printf("File is %d big \n",fileSize);


	//ptr = &(*c);
	//printf("%c", *c);

		j	= 0;
		rLen = 0;
  //printf("%d\n", len);
		//printf("here3\n");

  /* If all characters in the source string are different,
    then size of destination string would be twice of input string.
    For example if the src is "abcd", then dest would be "a1b1c1d1"
    For other inputs, size would be less than twice.  *


  /* traverse the input string one by one */
  	for(i = 0; i < DICT_BYTES; i++)
  	{

    /* Copy the first occurrence of the new character */
    	if(c[i] == '\n')
      	continue;
    	dest[j++] = c[i];

    /* Count the number of occurrences of the new character */
    	rLen = 1;
    	while(i + 1 < DICT_BYTES && c[i] == c[i+1])
    	{
      	rLen++;
      	i++;
    	}

    /* Store rLen in a character array count[] */
    	sprintf(count, "%d", rLen);

    /* Copy the count[] to destination */
    	for(k = 0; *(count+k); k++, j++)
    	{
      	dest[j] = count[k];
    	}
  	}

  /*terminate the destination string */
  	dest[j] = '\0'; /*
	while(*(c) != EOF) {
		//printf("%d", i);
		i++;c++
	}
	*/
	//printf("i is %d, and I made it\n", i);

		//printf("here4\n");
	//c = &c[0];
		//printf("%d\n", j);
		//printf("Byte %c, next byte %c\n",dest[5000], dest[5001]);
		memset(dest, 0, (DICT_BYTES*2 + 1));
		memset(count, 0, MAX_RLEN);
	//  if(result[0] == -1)
	//    printf("How though?\n");
	//while(*result != '\0') {
		//printf("%d\n", i);
	//  i++;result++;
	//}
	}

	//  printf("i is %d, and I made it twice\n", i);
	if(close(fd) < 0) {
		printf("Error closing compressed file\n");
		return 1;
	}

	return 0;

}
