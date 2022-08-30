void    execute_line(t_node *line, t_envp *env)
{
    int save_fd[2];
    if (check_builtin(line))
    {
        save_fd[0] = dup(STDIN_FILENO);
        save_fd[1] = dup(STDOUT_FILENO);
        if (line->left)
            check_redirection(line->left, env);
        if (line->right)
        run_builtin(line->right, env);
        dup2(save_fd[0], STDIN_FILENO);
        dup2(save_fd[1], STDOUT_FILENO);
        close(save_fd[0]);
        close(save_fd[1]);
    }
    else
    {
        pid_t pid;
        int status;
        pid = fork();
        if(pid)
        {
            waitpid(pid, &status, 0);
            update_exitcode(status, env);
        }
        else
        {
            if (line->left)
                check_redirection(line->left, env);
            if (line->right)
                execute(line->right, env);
        }
    }
}

void	make_process(t_node *line, t_envp *env)
//line이 루트노드일때, 
//실행을 담당하는 함수.
//1.빌트인인지 확인해
//빌트인이면 리다이렉션 할 때 메인을 유지하기 위한 fd를 저장해줘.(dup(0), dup(1)하고 저장)
//빌트인 바로실행
//끝나면, fd복원
//2. 나머지는 모두 포크가능
//리다이렉션 해주고, 실행

void	execute_pipe(t_node *root, t_envp *env)
{
    int **fd;
    pid_t *pid;
    int status;
    int process;
    int temp_fd[2];
    int i;
    t_node *line;

    process = count_process(root);
	if (initial_pipe(process, &fd, &pid))
		return ;
    i = 0;
    while (root->type == PIPE)
    {
        temp_fd[0] = fd[i][FD_WRITE];
        temp_fd[1] = fd[i+1][FD_READ];
        pipe(temp_fd);
        pid[i] = fork();
        if (pid[i] < 0)
		{
			printf("error\n");
			return ;
		}
        else if (pid[i])
        {
            if (i != 0)
				close(fd[i][FD_READ]);
            if (i != process - 1)
				close(fd[i][FD_WRITE]);
            if (root->right)
                root = root->right;
            i += 1;
            if (i == process -1)
            {
                i = 0;
				while (i < process)
				{
					waitpid(pid[i], &status, 0);
					i += 1;
				}
				if (update_exitcode(status, env))
					return ;
            }
        }
        else
        {
            if (i == process -1)
                //마지막 라인이라는 뜻 : root->right에 대해서 진행
            {
                if (root->right == LINE)
                {
                    line = root->right;
                    //내부를 함수로 빼면 밑에 root->left와 합치기 가능할지도
                    if (line->left)
                    check_redirection(line->left, env);
                    dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                    close(fd[i - 1][FD_READ]);
                    dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                    if (line->right)
                        execute(line, env);
                }

            }
            if (root->left == LINE)
            {
                line = root->left;
                if (line->left)
                    check_redirection(line->left, env);
                if (i != 0)
                {
                    dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                    close(fd[i - 1][FD_READ]);
                }
                dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                close(fd[i][FD_WRITE]);
                close(fd[i + 1][FD_READ]);
                close(fd[process -1][FD_WRITE]);
                if (line->right)
                    execute(line, env);
            }
        }
    }
}
//만약 pipe가 루트노드이면, 
//실행을 담당하는 함수
//파이프 연결해
//1. 포크해.
//2. 리다이렉션해
//나머지 필요없는 파이프 제거해
//마지막, root->right 에 대해서 pipe, fork, redirection, execute 진행
// if (i != 0)
			    // {
			    // 	dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                //     close(fd[i - 1][FD_READ]);
		    	// }
			    // dup2(fd[i][FD_WRITE], STDOUT_FILENO);
    			// close(fd[i][FD_WRITE]);
                // if (i != process - 1)
    	    	// {
                //     close(fd[i + 1][FD_READ]);
    		    // 	close(fd[process -1][FD_WRITE]);
                // } ??
//3. 실행해.
