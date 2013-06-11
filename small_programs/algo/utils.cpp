#include <random>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

// initialize random number generator with seed as
// current time.
void random_init()
{
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);
}

/* This function will be called by child proces */
void displayGraph(const char *filename)
{
  char psfile[256];
  char psfile1[256];
  char path[255];
  int pid;
  int status;

  sprintf(psfile,"%s.ps", filename);
  if (pid = fork()) {
    waitpid(pid, &status, 0);
    if (psfile[0] != '/') {
      getcwd(path, 255);
      sprintf(psfile1, "%s/%s", path, psfile);
      strcpy(psfile, psfile1);
    }
    sleep(1);
    execl("/usr/bin/gv", "gv", psfile, NULL);
  }
  else {
    execl("/usr/bin/dot", "dot" , "-Tps", "-o", psfile, filename, NULL);
  }
}
