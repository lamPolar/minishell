MINISHELL
---
### made by [sojoo](https://github.com/zoovely) && [heeskim](https://github.com/lamPolar)
  Welcome to KINDERshell๐ฅ
  [์ฌ์ง ์ฝ์ ์์ ]
  ๊ฐ๋ฐ ๊ธฐ๊ฐ : 8/24 ~ 


### 1. Introduction
> *The objective of this project is for you to **create a simple shell**. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.*
>
> With Minishell, youโll be able to travel through time and come back to problems people faced when Windows didnโt exist.



### 2. Instructions : Write a shell

- ์ธํฐํ๋ฆฌํฐ๋ ๋ช๋ น ํ๋กฌํํธ(`$> `)๋ฅผ ๋์์ผํ๋ค.
  - ์ฌ์ฉ์๊ฐ enter ํค๋ฅผ ๋๋ฌ ๋ช๋ น์ค(command line)์ ์๋ ฅํ  ๋ ๊น์ง ๊ธฐ๋ค๋ ค์ผ ํ๋ค.
  - ํ๋กฌํํธ๋ ๋ช๋ น์ด ์์ ํ ์คํ๋ ํ์๋ง ๋ค์ ํ์๋๋ค.

- ํ๊ฒฝ๋ณ์ PATH์ ์๋๊ฒฝ๋ก, ์ ๋ ๊ฒฝ๋ก์ ๋ฐ๋ผ ์คํ ํ์ผ(The executable)์ ์ฐพ๊ณ  ์คํํ๋ค.
  - ์คํ ํ์ผ์ ์ฐพ์ ์ ์๋ ๊ฒฝ์ฐ ์ค๋ฅ ๋ฉ์์ง๋ฅผ ํ์ํ๊ณ  ํ๋กฌํํธ๋ฅผ ๋ค์ ํ์ํ๋ค.

- Working History๋ฅผ ๋ณด์ฌ์ค๋ค.

- ์ ์ญ๋ณ์๋ 1๊ฐ๊น์ง๋ง ํ์ฉํ๋ค.

- ๋ซํ์ง ์์ ๋ฐ์ดํ๋, \, ;, . ๊ฐ์ ํน์๋ฌธ์์ ๋ํด์ ํด์ํ์ง ์์๋ ๋๋ค.

- ๋ค์๊ณผ ๊ฐ์ ์ ๋ด์ฅ ํจ์๋ฅผ ๊ตฌํํ๋ค. (Builtin directory)
  - `echo` (`-n` option only)
  - `cd` (์๋๊ฒฝ๋ก, ์ ๋๊ฒฝ๋ก๋ง)
  - `pwd` (option์ ์ธ)
  - `export`(option ์ ์ธ)
  - `unset`(option ์ ์ธ)
  - `env` (option, argument์ ์ธ)
  - `exit` (option ์ ์ธ))

- ๋ค์์ ๊ธฐ๋ฅ๋ค์ Bash shell์ ์ ์ฌํ๊ฒ ๋์ํด์ผํ๋๋ก ๊ตฌํํ๋ค.
  - `'` , `"`
  - file redirection (`<<`, `<`, `>`, `>>`)
  - ํ์ดํ(`|`) 
  - ํ๊ฒฝ๋ณ์(`$`์ดํ์ ๋ณ์ ex)$HOME )
  - `$?`(exit code)
  - `ctrl-C`, `ctrl-D`, `ctrl-\`

- ์ด์ธ์ ์ ์๋์ง ์์ ์ฌํญ๋ค์ ๋ฌด์๋์ด๋ ์ข๋ค.
- ๋ชจ๋  ์ฌํญ์์ Bash๋ฅผ ์ฐธ๊ณ ํ๊ธธ ์ถ์ฒํ๋ค.
  

### 3. Allowed Functions

- malloc, free
- read, write, open, close
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve, wait, waitpid, wait3, wait4
- signal, kill, exit
- strerror, errno
- dup, dup2, pipe



