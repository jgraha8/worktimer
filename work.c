#include <stdio.h>
#include <string.h>
#include <time.h>
#include "work.h"

FILE *sessfile;
time_t total_time;

void print_usage() {
  printf("Usage: ./work [-f logfile.txt], type h for command help.\n"); 
}

void print_commands() {
  printf("Commands: s[tatus], l{og} [message], r[eset]\n");
}

void end_session(int print_file){
  time_t now;
  time(&now);
  double time_diff = difftime(now, total_time);
  printf("Elapsed Time: ");
  if ((int)time_diff/60/60 > 0){
    printf("%i:", (int)time_diff/60/60);
  }
  printf("%i:%i on %s", ((int)time_diff/60)%60, (int)time_diff%60, ctime(&total_time));
  if (print_file){
    fprintf(sessfile, "%i:%i:%i - %s", (int)time_diff/60/60, ((int)time_diff/60)%60, (int)time_diff%60, ctime(&total_time));
  }
}

int process_input(void){
  char input[MAX_INPUT]; 
  char *inputp = input; char *newstr;
  if (fgets(input, MAX_INPUT, stdin) != NULL){
    if (input[0] == 'g' || input[0] == 's'){
      end_session(0);
      printf("\n");
    } else if (input[0] == 'l' || input[0] == 'f'){
      end_session(1);
      if (strlen(input) > 3){
        newstr = strstr(input, "l ");
        if (newstr == NULL){
          newstr = strstr(input, "f ");
        }
        if (newstr == NULL){ return 0; }
        strncpy(newstr, "# ", 2);
        fputs(newstr, sessfile);
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
}

int main(int argc, char **argv){
  int worktype = 0;
  char *file_name;
  int c; char act;

  time(&total_time);
  
  if (argc == 2 && (strstr(argv[1], "--help") != NULL || strstr(argv[1], "-h") != NULL)){
    print_usage();
    return 0;
  }

  if (argc == 3 && (argv[1][1] == 'f' || argv[1][2] == 'f')){
    file_name = argv[2];
  } else {
    file_name = "hours.txt";
  }
  printf("Using logfile %s, type h for help.\n", file_name);

  sessfile = fopen(file_name, "a+");

  while(process_input()){  };
  
  fclose(sessfile);

}

