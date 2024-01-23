# clang demo

## REF

https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html

``` shell
gcc -c -Wall -Werror -fpic a.c -I.
gcc -c -Wall -Werror -fpic b.c -I.

gcc -shared -o liba.so a.o
gcc -shared -o libb.so b.o

export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
gcc -L/home/evan/repos/golang_invoke_so_file_demo/c_demo -Wall -o test main.c -I.

# 这个不对，不需要强行引用a.so
gcc -L/home/evan/repos/golang_invoke_so_file_demo/c_demo -Wall -o test main.c -la -I.
```