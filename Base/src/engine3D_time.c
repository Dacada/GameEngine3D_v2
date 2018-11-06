#include <engine3D_time.h>

#ifdef _WIN32
#include <Windows.h>

const double engine3D_timer_second = 1;

static double frequency;
static LARGE_INTEGER start;

void engine3D_timer_init(void) {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	frequency = 1.0 / freq.QuadPart;
	QueryPerformanceCounter(&start);
}

double engine3D_timer_getTime(void) {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	LONGLONG cycles = current.QuadPart - start.QuadPart;
	return cycles * frequency;
}

void engine3D_time_sleep(const double t) {
	Sleep((DWORD)(t * 1000.0));
}
#endif

#ifdef __unix__
#include "engine3D_util.h"
#include <stdio.h>
#include <errno.h>
#include <time.h>

const double engine3D_timer_second = 1000000.0;

static struct timespec start;

void engine3D_timer_init(void) {
	if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
		perror("clock_gettime");
		engine3D_util_bail("CLOCK_MONOTONIC failed");
	}
}

double engine3D_timer_getTime(void) {
	struct timespec tp;
	if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1) {
		perror("clock_gettime");
		engine3D_util_bail("CLOCK_MONOTONIC failed");
	}
	return ((double)(tp.tv_nsec - start.tv_nsec))/1000.0 + ((double)(tp.tv_sec - start.tv_sec))*1000000.0;
}

void engine3D_time_sleep(const double t) {
	struct timespec tp, currentTime;
	long t_long = (long)t;

	if (clock_gettime(CLOCK_MONOTONIC, &currentTime) == -1) {
		perror("clock_gettime");
		engine3D_util_bail("CLOCK_MONOTONIC failed");
	}

	long realns = currentTime.tv_nsec + (t_long % 1000000) * 1000;
	tp.tv_nsec = realns % 1000000000;
	tp.tv_sec = realns / 1000000000 + currentTime.tv_sec + t_long / 1000000;

	int err = EINTR;
	while (err == EINTR) {
		err = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tp, NULL);
	}

	if (err != 0) {
		perror("clock_nanosleep");
		engine3D_util_bail("CLOCK_MONOTONIC nanosleep failed");
	}
}
#endif

static double delta;

double engine3D_time_getDelta(void) {
	return delta;
}

void engine3D_time_setDelta(const double d) {
	delta = d;
}
