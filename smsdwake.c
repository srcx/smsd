/*
 * smsdwake
 * (c)2002,2003 Stepan Roh
 */
 
/* $Id: smsdwake.c,v 1.2 2003/01/29 19:49:36 stepan Exp $ */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

#define SMSD_PID_FILE	"/var/run/smsd.pid"

int main () {

  FILE *f;
  char buf[65];
  pid_t pid;
  
  memset (buf, 0, 65);
  
  f = fopen (SMSD_PID_FILE, "r");
  if (f == NULL) {
    return 2;
  }
  fread (buf, 1, 64, f);
  fclose (f);

  pid = atoi (buf);
  if (pid <= 0) {
    return 3;
  }  

  return -kill (pid, SIGUSR1);
}
