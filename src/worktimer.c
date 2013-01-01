#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "worktimer.h"
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


void print_version() {
  printf("worktimer version %s\n", VERSION);
}

void print_usage() {
  printf("Usage: worktimer [-v] [-f logfile.txt], type h for command help.\n"); 
}

void print_commands() {
  printf("Commands: s[tatus], l[og] <message>, r[eset], q[uit]\n");
}

void print_prompt() {
  printf("command> ");
}

void print_log_header() {
  fprintf(logfile, "         Start Time         Work Time            Log Message      \n");
  fprintf(logfile, "========================== =========== ===========================\n");
}

void session_status(int print_file){
  time_t now;
  time(&now);
  double time_diff = difftime(now, total_time);

  int hours = (int)time_diff/60/60;
  int minutes = ((int)time_diff/60)%60;
  int seconds = (int)time_diff%60;

  // Getting the starting time and strip newline character
  char *start_time = (char *)ctime(&total_time); 
  size_t len = strlen(start_time);
  start_time[len-1]='\0';

  char work_time[8];
  sprintf(work_time, "%2.2i:%2.2i:%2.2i", hours, minutes, seconds);

  printf("Elapsed Time: %s", work_time);
  if (print_file){
    printf("\n");
    fprintf(logfile, " %s   %8s    ", start_time, work_time);
  }
}

int process_input() {
  char input[MAX_INPUT]; 
  char *newstr;
  char *logmesg;

  if (fgets(input, MAX_INPUT, stdin) != NULL){

    if (input[0] == 's'){

      session_status(0);
      printf("\n");

    } else if (input[0] == 'l'){

      if (strlen(input) > 3){
        newstr = strstr(input, "l ");
	logmesg = &newstr[2];
	if (newstr == NULL){ return 0; }
	session_status(1);
        fprintf(logfile,"%s", logmesg);
	// Reset the time
	time(&total_time);

      } else {					
	printf("No log message specified.\n");
	//fprintf(logfile,"\n");
      }   
      print_prompt();
      return 1;

    } else if (input[0] == 'r'){
      printf("Resetting time\n");
      time(&total_time);
    } else if (input[0] == 'q'){
      return 0;
    } else if (input[0] == 'h'){
      print_commands(); 
    } else {
      print_commands();
    }
    print_prompt();
    return 1;

  }
  return 0;
}

int main(int argc, char **argv){

  char *file_name;
  time(&total_time);

  if (argc == 2 && (strstr(argv[1], "-v") != NULL ) ) {
    print_version();
    return 0;
  }
  
  if (argc == 2 && (strstr(argv[1], "--help") != NULL || strstr(argv[1], "-h") != NULL)){
    print_usage();
    return 0;
  }

  if (argc == 3 && (argv[1][1] == 'f' || argv[1][2] == 'f')){
    file_name = argv[2];
  } else {
    file_name = LOGFILE;
  }

  if( access( file_name, F_OK ) != -1 ) {
    // Log file exist
    logfile = fopen(file_name, "a+");
  } else {
    // Log file does not exist
    logfile = fopen(file_name, "w");
    print_log_header();
  }
  
  printf("Using logfile %s, type h for help.\n", file_name);
  print_prompt();
  while(process_input()){  };
  
  fclose(logfile);
  return 0;
}

