#ifndef ENGINE3D_TIME_H
#define ENGINE3D_TIME_H

// Initialize timer
void engine3D_timer_init(void);

// Get time since an unspecified moment.
// The units are seconds
double engine3D_timer_getTime(void);

// Sleep the current thread for the given length of time
// Time is in seconds
void engine3D_time_sleep(const double t);

#endif /* ENGINE3D_TIME_H */
