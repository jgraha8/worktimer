#define MAX_INPUT 80
#define LOGFILE "worktimer.log"

void print_usage();
void print_command();
void print_prompt();
void print_log_header();
void session_status(int);
int process_input();

FILE *logfile;
time_t total_time;
