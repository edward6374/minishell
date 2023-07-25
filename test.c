/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:00:14 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 13:35:00 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
//#include "readline/library/include/readline/readline.h"
//#include "readline/library/include/readline/history.h"

int main() {
    int pipefd[2]; // Pipe file descriptors
    int child1_pid, child2_pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        return 1;
    }

    // Fork the first child
    child1_pid = fork();
    if (child1_pid == -1) {
        perror("fork failed");
        return 1;
    } else if (child1_pid == 0) {
        // This is the first child (cat command)
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect the write end of the pipe to stdout

        // Now you can execute the cat command (or any other command that generates output)
        execlp("cat", "cat", NULL);
        perror("exec failed"); // If execlp fails, perror will print an error message
        _exit(1); // Exit the child process with an error
    }

    // Fork the second child
    child2_pid = fork();
    if (child2_pid == -1) {
        perror("fork failed");
        return 1;
    } else if (child2_pid == 0) {
        // This is the second child (ls command)
        close(pipefd[1]); // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect the read end of the pipe to stdin

        // Now you can execute the ls command (or any other command that takes input)
        execlp("ls", "ls", NULL);
        perror("exec failed"); // If execlp fails, perror will print an error message
        _exit(1); // Exit the child process with an error
    }

    // This is the parent process
    close(pipefd[0]); // Close the read end of the pipe (parent will not read from it)
    close(pipefd[1]); // Close the write end of the pipe (parent will not write to it)

    // Wait for both child processes to finish
    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    return 0;
}
