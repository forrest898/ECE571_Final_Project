#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "PAPI_sample.h"
#include <papi.h>
#include <perfmon/perf_event.h>
#include <stdlib.h>

#define MAX_RLEN 50
#define BENCH 20


//char *compress(char *str) ;
char *encode(char *src, uint32_t size);

int main(int argc, char **argv) {


    int ret, i;
	char* ev = "MEM_INST_RETIRED:SPLIT_LOADS";
	char* filename = "hungry";
	int sample_type=PERF_SAMPLE_IP | PERF_SAMPLE_TID | PERF_SAMPLE_TIME |
		PERF_SAMPLE_ADDR | PERF_SAMPLE_READ | PERF_SAMPLE_CALLCHAIN |
		PERF_SAMPLE_ID | PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD |
		PERF_SAMPLE_STREAM_ID | PERF_SAMPLE_RAW |
		PERF_SAMPLE_DATA_SRC ;

	ret = PAPI_sample_init(1, ev, 1, sample_type, 100000, filename);
	if(ret != PAPI_OK) {
		printf("PANIC\n");
		exit(1);
	}

	printf("At least I started\n");

	ret = PAPI_sample_start(1);
	if(ret != PAPI_OK) {
		printf("PANIC\n");
		exit(1);
	}

    int fd = 1;
    //int i = 0;
    char *result;


    int zz = 0;
    //char * ptr;
    uint32_t fileSize, bytesRead;
    //fd = open("/usr/share/dict/american-english", O_RDONLY);
        fd = open("image.jpg", O_RDONLY);

    if(fd < 0) {
      printf("Failed to open file for compression\n");
      return 1;
    }
    fileSize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    printf("Filesize: %u\n", fileSize);
    char *c = (char *) calloc(fileSize, sizeof(char));
    bytesRead = read(fd, c, fileSize);
    printf("I read %d bytes\n", bytesRead);
    //result = (char *)calloc((fileSize*2 + 1), sizeof(char));
    char *dest = (char *)malloc(sizeof(char)*(fileSize*2 + 1));

    int rLen;
    char count[MAX_RLEN];
    int len = fileSize;

    for(zz = 0; zz < BENCH; zz++) {

    //printf("File is %d big \n",fileSize);

//	printf("%d\n",j);
    //ptr = &(*c);
    //printf("%c", *c);
    /*
    while(*(c) != EOF) {
      //printf("%d", i);
      i++;c++;
    }
    */
    //printf("i is %d, and I made it\n", i);

    //printf("%d\n", len);

    /* If all characters in the source string are different,
      then size of destination string would be twice of input string.
      For example if the src is "abcd", then dest would be "a1b1c1d1"
      For other inputs, size would be less than twice.  */


    //char *dest = (char *)malloc(sizeof(char)*(size*2 + 1));

    int i, j = 0, k;

    /* traverse the input string one by one */
    for(i = 0; i < len; i++)
    {

      /* Copy the first occurrence of the new character */
      if(c[i] == '\n')
        continue;
      dest[j++] = c[i];

      /* Count the number of occurrences of the new character */
      rLen = 1;
      while(i + 1 < len && c[i] == c[i+1])
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
    dest[j] = '\0';
    //c = &c[0];
//      printf("%s\n", result);
      memset(dest, 0, (fileSize*2 + 1)*sizeof(char));
      memset(count, 0, sizeof(char)*50);
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

    		ret = PAPI_sample_stop(1, 1);
		if(ret != PAPI_OK) {
			printf("PANIC\n");
			exit(1);
		}

}
/*
char *compress(char *str) {
    char *start = str;
    char *c_first = str;
    char *c_last = str;
    char *c_write = str;
    int run_len = 0;
    while (*str) {
        ++c_last;
        ++run_len;
        if (!(*c_last) || *c_last != *c_first || run_len == 9) {
            // end of run
            *(c_write++) = *c_first;
            if (run_len > 1)
                *(c_write++) = '0' + run_len;
            // start next run
            run_len = 0;
            c_first = c_last;
        }
        ++str;
    }
    *c_write = 0;
    return start;
}
*/
/* Returns the Run Length Encoded string for the
   source string src */


char *encode(char *src, uint32_t size)
{
  char * dest;
  //printf("%d\n", j);
  return dest;

}