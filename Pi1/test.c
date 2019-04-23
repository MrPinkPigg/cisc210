/*
#include <stdio.h>
#include <time.h>

#define SECOND 1
#define MINUTE 60
#define HOUR 3600

int diff = 0;

void show(int unit, char end);

main() {
    time_t start = time(0), now = time(0);

    while (1) {
        diff = (now - start);
        show(SECOND, ' ');
        show(MINUTE, ' ');
        show(HOUR, '\n');
        now = time(0);
    }
}

void show(int unit, char end) {
    int i, secs = (diff/unit) % 60;
    for (i = 6; i >= 0; --i) {
        if (secs & (1 << i))
            putchar('+');
        else
            putchar('-');
    }
    putchar(end);
}
*/

/* localtime example */
#include <stdio.h>
#include <time.h>

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  while(1){
   time (&rawtime);
   timeinfo = localtime(&rawtime);

   int hours = timeinfo->tm_hour;
   int mins = timeinfo->tm_min;
   int secs = timeinfo->tm_sec;

	 printf ( "%02d:%02d:%02d\n", hours, mins, secs);
  }
  return 0;
}
