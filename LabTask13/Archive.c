//----Archive
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

//--------------------------------------------------------------------------------------------------
//----Main function
int main(int argc, char *argv[]) {

  //----Check if user has provided a file name as an argument
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    exit(1);
  }

  //----Get current time
  time_t now = time(NULL);

  //----Get the file's modification time
  struct stat file_stat;
  if (stat(argv[1], &file_stat) != 0) {
    perror("Error getting file status");
    exit(1);
  }

  //----Calculate the difference between the current time and modification time
  time_t difference = now - file_stat.st_mtime;

  //----Check if the file has not been modified for 4 weeks
  //----4*7*24*60*60 to calculate amount of seconds in 4 weeks
  //----Set the file to read-only if modification time is over 4 weeks ago
  if (difference > 2419200) {
    mode_t permissions = file_stat.st_mode & ~S_IWOTH & ~S_IWGRP & ~S_IWUSR;
    if (chmod(argv[1], permissions) < 0) {
      perror("Error setting new permissions");
      return 1;
    }
  }

  return EXIT_SUCCESS;
}
