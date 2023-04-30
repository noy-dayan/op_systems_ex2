#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAX_ARGS 10
#define MAX_COMMAND_LENGTH 1024

void handle_signal(int signal);

int main() {
    int i;
    char *argv[MAX_ARGS];
    char command[MAX_COMMAND_LENGTH];
    char *token;
    int output_mode = 0;
    int output_file;
    int input_mode = 0;
    int input_file;
    int pipe_mode = 0;
    int pipe_fd[2];
    pid_t pid;

    // set signal handler for SIGINT
    signal(SIGINT, handle_signal);

    while (1) {
        // print shell prompt
        printf("stshell: ");

        // read command from user
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // replace newline character with null terminator 
        command[strlen(command) - 1] = '\0';

        // check for empty command 
        if (command[0] == '\0') {
            continue;
        }

        // parse command line 
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            if (strcmp(token, ">") == 0) {
                // output redirection 
                output_mode = 1;
                token = strtok(NULL, " ");
                output_file = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_file == -1) {
                    perror("open");
                    break;
                }
            } else if (strcmp(token, ">>") == 0) {
                // append output redirection 
                output_mode = 1;
                token = strtok(NULL, " ");
                output_file = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (output_file == -1) {
                    perror("open");
                    break;
                }
            } else if (strcmp(token, "<") == 0) {
                // input redirection 
                input_mode = 1;
                token = strtok(NULL, " ");
                input_file = open(token, O_RDONLY);
                if (input_file == -1) {
                    perror("open");
                    break;
                }
            } else if (strcmp(token, "|") == 0) {
                // pipe 
                pipe_mode = 1;
                if (pipe(pipe_fd) == -1) {
                    perror("pipe");
                    break;
                }
                // execute left-hand command 
                argv[i] = NULL;
                pid = fork();
                if (pid == 0) {
                    if (output_mode) {
                        close(STDOUT_FILENO);
                        dup2(output_file, STDOUT_FILENO);
                    }
                    if (input_mode) {
                        close(STDIN_FILENO);
                        dup2(input_file, STDIN_FILENO);
                    }
                    close(pipe_fd[0]);
                    dup2(pipe_fd[1], STDOUT_FILENO);
                    execvp(argv[0], argv);
                    perror("execvp");
                    exit(EXIT_FAILURE);

                } else if (pid == -1) {
                    perror("fork");
                    break;
                }
                // set up for executing right-hand command 
                close(pipe_fd[1]);
                input_mode = 1;
                input_file = pipe_fd[0];
                i = 0;
                token = strtok(NULL, " ");

            } else {
                // normal argument 
                argv[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
       
		}

		// End of argument list 
		argv[i] = NULL;

		// Check for exit command 
		if (strcmp(argv[0], "exit") == 0) {
			break;
		}

		// Execute command 
		pid = fork();
		if (pid == 0) {
			if (output_mode) {
				close(STDOUT_FILENO);
				dup2(output_file, STDOUT_FILENO);
			}
			if (input_mode) {
				close(STDIN_FILENO);
				dup2(input_file, STDIN_FILENO);
			}
			execvp(argv[0], argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else if (pid == -1) {
			perror("fork");
		} else {
			wait(NULL);
			if (output_mode) {
				close(output_file);
				output_mode = 0;
			}
			if (input_mode) {
				close(input_file);
				input_mode = 0;
			}
			if (pipe_mode) {
				close(pipe_fd[0]);
				pipe_mode = 0;
			}
		}
	}

	return 0;
}

void handle_signal(int signal) {
    // do nothing
    return;
}