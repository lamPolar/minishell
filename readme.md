## 1. Introduction
> *The objective of this project is for you to **create a simple shell**. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.*
>
> With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.



## 2. Instructions : Write a shell

- 인터프리터는 명령 프롬프트(`$> `)를 띄워야한다.
  - 사용자가 enter 키를 눌러 명령줄(command line)을 입력할 때 까지 기다려야 한다.
  - 프롬프트는 명령이 완전히 실행된 후에만 다시 표시된다.

- 환경변수 PATH와 상대경로, 절대 경로에 따라 실행 파일(The executable)을 찾고 실행한다.
  - 실행 파일을 찾을 수 없는 경우 오류 메시지를 표시하고 프롬프트를 다시 표시한다.

- Working History를 보여준다.

- 전역변수는 1개까지만 허용한다.

- 닫히지 않은 따옴표나, \, ;, . 같은 특수문자에 대해서 해석하지 않아도 된다.

- 다음과 같은 쉘 내장 함수를 구현한다. (Builtin directory)
  - `echo` (`-n` option only)
  - `cd` (상대경로, 절대경로만)
  - `pwd` (option제외)
  - `export`(option 제외)
  - `unset`(option 제외)
  - `env` (option, argument제외)
  - `exit` (option 제외))

- 다음의 기능들을 Bash shell와 유사하게 동작해야하도록 구현한다.
  - `'` , `"`
  - file redirection (`<<`, `<`, `>`, `>>`)
  - 파이프(`|`) 
  - 환경변수(`$`이후의 변수 ex)$HOME )
  - `$?`(exit code)
  - `ctrl-C`, `ctrl-D`, `ctrl-\`

- 이외의 제시되지 않은 사항들은 무시되어도 좋다.
- 모든 사항에서 Bash를 참고하길 추천한다.
  

## 3. Allowed Functions

- malloc, free
- read, write, open, close
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve, wait, waitpid, wait3, wait4
- signal, kill, exit
- strerror, errno
- dup, dup2, pipe



