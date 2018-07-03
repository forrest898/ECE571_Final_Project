#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_RLEN 50
#define BENCH 250


//char *compress(char *str) ;
char *encode(char *src, uint32_t size);

int main(int argc, char **argv) {

    int fd = 1;
    int i = 0;
    char *result;


    int j = 0;
    //char * ptr;
    uint32_t fileSize, bytesRead;
    fd = open("/usr/share/dict/american-english", O_RDONLY);
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
    result = (char *)calloc((fileSize*2 + 1), sizeof(char));

    for(j = 0; j < BENCH; j++) {

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
      result = encode(c, bytesRead);
    //c = &c[0];
//      printf("%s\n", result);
      memset(result, 0, (fileSize*2 + 1)*sizeof(char));
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
  int rLen;
  char count[MAX_RLEN];
  int len = strlen(src);
  //printf("%d\n", len);

  /* If all characters in the source string are different,
    then size of destination string would be twice of input string.
    For example if the src is "abcd", then dest would be "a1b1c1d1"
    For other inputs, size would be less than twice.  */

  char *dest = (char *)malloc(sizeof(char)*(size*2 + 1));

  int i, j = 0, k;

  /* traverse the input string one by one */
  for(i = 0; i < len; i++)
  {

    /* Copy the first occurrence of the new character */
    if(src[i] == '\n')
      continue;
    dest[j++] = src[i];

    /* Count the number of occurrences of the new character */
    rLen = 1;
    while(i + 1 < len && src[i] == src[i+1])
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
  //printf("%d\n", j);
  return dest;

}
