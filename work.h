#define MAX_INPUT 80
#define LOGFILE "worktimer.log"

void print_usage(void);
void print_command(void);
void print_log_header(void);
void end_session(int);
int process_input(void);

FILE *logfile;
time_t total_time;
char *task;
