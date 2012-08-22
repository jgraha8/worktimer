#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "work.h"

void print_usage(void) {
  printf("Usage: ./work [-f logfile.txt], type h for command help.\n"); 
}

void print_commands(void) {
  printf("Commands: s[tatus], l{og} [message], r[eset]\n");
}

void print_log_header(void) {
  fprintf(logfile, "         Start Time         Work Time            Log Message      \n");
  fprintf(logfile, "========================== =========== ===========================\n");
}

void end_session(int print_file){
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
  sprintf(work_time, "%i:%i:%i", hours, minutes, seconds);

  printf("Elapsed Time: %s", work_time);
  if (print_file){
    printf("\n");
    fprintf(logfile, " %s   %8s    ", start_time, work_time);
  }
}

int process_input(void){
  char input[MAX_INPUT]; 
  char *newstr;
  char *logmesg;

  if (fgets(input, MAX_INPUT, stdin) != NULL){

    if (input[0] == 'g' || input[0] == 's'){

      end_session(0);
      printf("\n");

    } else if (input[0] == 'l' || input[0] == 'f'){

      end_session(1);

      if (strlen(input) > 3){
        newstr = strstr(input, "l ");
	logmesg = &newstr[2];
        if (newstr == NULL){
          newstr = strstr(input, "f ");
        }
        if (newstr == NULL){ return 0; }
        //strncpy(newstr, "# ", 2);
        //fputs(newstr, logfile);
	fprintf(logfile,"%s", logmesg);
      } else {
	  fprintf(logfile,"\n");
      }

      return 0;

    } else if (input[0] == 'r'){
      time(&total_time);
      printf("Resetting time");
    } else if (input[0] == 'h'){
      print_commands();    
    } else {
      print_commands();
    }

    return 1;

  }
  return 0;
}

int main(int argc, char **argv){

  char *file_name;
  time(&total_time);
  
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

  while(process_input()){  };
  
  fclose(logfile);
  return 0;
}

