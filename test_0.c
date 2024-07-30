#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "pipex.h"
#include <sys/stat.h>

void file_to_pipe(t_data *info, t_cmd *cmd)
{
    if (pipe(info->pipefd) == -1) {
        perror("PIPE FAILED");
        exit(1);
    }
    
    info->pid = fork();
    if (info->pid == -1) {
        perror("FORK FAILED");
        exit(1);
    }
    
    if (info->pid == 0) {  // Child process
        close(info->pipefd[0]);  // Close unused read end
        
        if (dup2(info->infile, STDIN_FILENO) == -1 || dup2(info->pipefd[1], STDOUT_FILENO) == -1) {
            perror("DUP2 FAILED");
            exit(1);
        }
        
        close(info->infile);
        close(info->pipefd[1]);
        
        execve(cmd->path, cmd->args, NULL);
        perror("EXECVE FAILED");
        exit(1);
    }
    
    // Parent process
    close(info->pipefd[1]);  // Close unused write end
    close(info->infile);
    
    // Save the read end for the next command
    info->keeper = info->pipefd[0];
}

void pipe_to_pipe(t_data *info, t_cmd *cmd)
{
    if (pipe(info->pipefd) == -1) {
        perror("PIPE FAILED");
        exit(1);
    }
    
    info->pid = fork();
    if (info->pid == -1) {
        perror("FORK FAILED");
        exit(1);
    }
    
    if (info->pid == 0) {  // Child process
        close(info->pipefd[0]);  // Close unused read end
        
        if (dup2(info->keeper, STDIN_FILENO) == -1 || 
            dup2(info->pipefd[1], STDOUT_FILENO) == -1) {
            perror("DUP2 FAILED");
            exit(1);
        }
        
        close(info->keeper);
        close(info->pipefd[1]);
        
        execve(cmd->path, cmd->args, NULL);
        perror("EXECVE FAILED");
        exit(1);
    }
    
    // Parent process
    close(info->pipefd[1]);  // Close unused write end
    close(info->keeper);
    
    // Save the read end for the next command
    info->keeper = info->pipefd[0];
}

void pipe_to_file(t_data *info, t_cmd *cmd)
{
    info->pid = fork();
    if (info->pid == -1) {
        perror("FORK FAILED");
        exit(1);
    }
    
    if (info->pid == 0) {  // Child process
        if (dup2(info->keeper, STDIN_FILENO) == -1 || 
            dup2(info->outfile, STDOUT_FILENO) == -1) {
            perror("DUP2 FAILED");
            exit(1);
        }
        
        close(info->keeper);
        close(info->outfile);
        
        execve(cmd->path, cmd->args, NULL);
        perror("EXECVE FAILED");
        exit(1);
    }
    
    // Parent process
    close(info->keeper);
    close(info->outfile);
}

void executions(t_cmd **list, t_data *info)
{
    t_cmd *tail;
    t_cmd *iter;
    int cmd_count = 0;
    pid_t *pids;

    tail = last_node(*list);
    iter = *list;

    // Count commands
    for (t_cmd *tmp = *list; tmp; tmp = tmp->next)
        cmd_count++;

    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids) {
        perror("malloc failed");
        exit(1);
    }

    int i = 0;
    while (iter)
    {
        if (iter == *list)
            file_to_pipe(info, iter);
        else if (iter == tail)
            pipe_to_file(info, iter);
        else
            pipe_to_pipe(info, iter);
        
        pids[i++] = info->pid;
        iter = iter->next;
    }

    // Wait for all child processes
    for (int j = 0; j < cmd_count; j++)
        waitpid(pids[j], NULL, 0);

    free(pids);
}