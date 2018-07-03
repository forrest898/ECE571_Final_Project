#include <stddef.h>
#include <stdint.h>


#define BENCH_SIZE (16*1024*1024)
#define BENCH_ITERATIONS 1024

static uint8_t __attribute__((aligned(64))) benchmark[BENCH_SIZE+16];

#define OFFSET 0


#ifdef VMWOS
#include "syscalls.h"
#include "vlibc.h"
#include "vmwos.h"


static int64_t get_time_us(void) {

	int64_t value;
	struct timespec t;

	clock_gettime(CLOCK_REALTIME,&t);

	value=(t.tv_sec*1000000ULL)+t.tv_nsec/1000;

	return value;
}

#else

#include <stdio.h>
#include <time.h>


static int64_t get_time_us(void) {

	int64_t value;

	struct timespec t;

	clock_gettime(CLOCK_REALTIME,&t);

	value=(t.tv_sec*1000000ULL)+t.tv_nsec/1000;

	return value;
}

#endif






void *memset_byte(void *s, int c, uint32_t n) {

	uint32_t i;
	char *b;

	b=(char *)s;

	for(i=0;i<n;i++) b[i]=c;

	return s;
}


void *memset_4byte(void *s, int c, uint32_t n) {

	uint32_t i;
	uint32_t *b;
	uint8_t *ch;
	uint32_t pattern;
	uint32_t offset;
	uint32_t count;


	pattern=(c&0xff);
	pattern=pattern|(pattern<<8)|(pattern<<16)|(pattern<<24);

	//printk("Writing %x (4 x %x)\n",pattern,c);

	offset=((uint32_t)s)%4;

	ch=(uint8_t *)s;

	/* Do leading edge if unaligned */
	if (offset) {
		for(i=0;i<(4-offset);i++) ch[i]=c;
		b=(uint32_t *)(ch+(4-offset));
		count=n-1;
	}
	else {
		b=(uint32_t *)s;
		count=n;
	}

	/* Do 4-byte chunks */
	for(i=0;i<(count/4);i++) b[i]=pattern;

	/* Do trailing edge if unaligned */
	for(i=0;i<offset;i++) {
//		printk("Tail: setting offset %d\n",(n-offset)+i);
		ch[(n-offset)+i]=c;
	}

	return s;
}

void *memset_custom(void *s, int c, uint32_t n) {

	// The larger the block size the more the loops can be unrolled for speed
	uint32_t numblocks = n / 512;
	uint32_t leftovers = n % 512;
	uint8_t *dat = (uint8_t*)s;

	// Write large blocks at a time
	// Compiler should optimize this into a single list of 512 operations, but we force it to do 8 at once to ensure speed
	int i,j;
	for(i = 0; i < numblocks; i++){
		for(j = 0; j < 512/8; j++){
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
			*dat = c;
			dat++;
		}
	}

	// Handle the leftovers
	for(i = 0; i < leftovers; i++){
		*dat = c;
		dat++;
	}

	return s;
}


/* Test to be sure correct value was written */
static void memset_test(void *addr, int value, int size) {

	int i,errors=0;
	char *b;
	b=(char *)addr;

	printf("\tTesting: ");
	for(i=0;i<size;i++) {
		if (b[i]!=value) {
			printf("Not match at offset %d (%x!=%x)!\n",
				i,b[i],value);
			errors++;
			if (errors>20) break;
		}
	}

	if (b[size+1]==value) {
		errors++;
		printf("Value after the end has wrong value!\n");
	}

	if (errors) printf("Failed!\n");
	else printf("Passed!\n");

}


/* Test setting per-byte memory set */
static void run_memory_benchmark8(int32_t reps) {

	int i;
	uint64_t before,after;
	uint32_t diff;

	before=get_time_us();

	for(i=0;i<reps;i++) {
		memset_byte(benchmark+OFFSET,0xfe,BENCH_SIZE);
	}

	after=get_time_us();

	diff=after-before;

	printf("\tMEMSPEED: %d MB took %dus = %dMB/s\n",
		(BENCH_SIZE*reps)/1024/1024,
		(diff),
		(BENCH_SIZE*reps)/(diff));

	memset_test(benchmark+OFFSET,0xfe,BENCH_SIZE);

}

static void run_memory_benchmark32(int32_t reps) {

	int i;
	uint64_t before,after;
	uint32_t diff;

	before=get_time_us();

	for(i=0;i<reps;i++) {
		memset_4byte(benchmark+OFFSET,0xa5,BENCH_SIZE);
	}

	after=get_time_us();

	diff=after-before;

	printf("\tMEMSPEED: %d MB took %dus = %dMB/s\n",
		(BENCH_SIZE*reps)/1024/1024,
		(diff),
		(BENCH_SIZE*reps)/diff);

	memset_test(benchmark+OFFSET,0xa5,BENCH_SIZE);
}

static void run_memory_benchmark_custom(int32_t reps) {

	int i;
	uint64_t before,after;
	uint32_t diff;

	before=get_time_us();

	for(i=0;i<reps;i++) {
		memset_custom(benchmark+OFFSET,0x78,BENCH_SIZE);
	}

	after=get_time_us();

	diff=after-before;
	//thing = ((uint64_t)(BENCH_SIZE*reps))/(diff)

	printf("\tMEMSPEED: %d MB took %dus =  %dMB/s\n",
		(BENCH_SIZE*reps)/1024/1024,
		(diff),
		(BENCH_SIZE*reps)/(diff));

	memset_test(benchmark+OFFSET,0x78,BENCH_SIZE);
}

static void memset_benchmark(int32_t reps) {

	/* Naive version */
	//printf("8-bit memset\n");
	//run_memory_benchmark8(reps);

	/* 32-bit version */
	//printf("32-bit memset\n");
	//run_memory_benchmark32(reps);

	/* custom version */
	printf("Custom memset\n");
	run_memory_benchmark_custom(reps);

}


int main(int argc, char **argv) {

	int32_t reps;

	if (argc>1) {
		reps=atoi(argv[1]);
	}
	else {
		reps=BENCH_ITERATIONS;
	}

	memset_benchmark(reps);

	return 0;
}
