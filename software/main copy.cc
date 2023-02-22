
#define LINUX 1

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include <string.h>
#include <time.h>
#endif

#ifndef LINUX

#endif

void welcome()
{
  printf("welcome\n");
}
void term_mainloop();



int main()
{

    printf("start engine\n");
    welcome();
    term_mainloop();
    
    return 0;
}


#include "readline.h"
char chbuf[100];
static char* readline(char* prtstr)
{
    
    char ch;
    printf("%s", prtstr);
    int i = 0;
    while(ch != '\n')
    {
      
      ch = getchar();
      chbuf[i] = ch;
      i++;

    }
    chbuf[i - 1] = '\0';
    return chbuf;
}


/* We use the `readline' library to provide more flexibility to read from stdin. */


//执行到结束
static int cmd_h(char *args) {//cpu执行
  printf("hello world!\n");
  return 0;
}


static uint32_t res[100] = {};
uint32_t fib(uint32_t n)
{
    if(n == 1 || n == 2) 
        return 1;
    if(res[n])
        return res[n];
    res[n] = fib(n - 1) + fib(n - 2);
    return res[n];
}


static int cmd_t(char *args) {
  printf("time : %d\n", time(NULL));
  return 0;
}

//打印内存
static int cmd_f(char *args) {
  if(args == NULL)
  {
    printf("arguments??? \n");
    return 0;
  }  
  uint32_t N = atoi(args);//字节数
  // printf("N=%d\n",N);
  printf("%d\n", fib(N));
  return 0;
}



static struct {//命令
  const char *name;
  const char *description;
    int (*handler) (char *);//函数指针,指针名为handler，参数是*char，返回值是int
} cmd_table [] = {
  { "hello", "helloworld", cmd_h },
  { "fib", "Exit NEMU", cmd_f },
  { "time", "step instruction", cmd_t },
  //命令 描述 函数

};

#define NR_CMD ARRLEN(cmd_table)//array length????
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))

void term_mainloop() {


  //用str接受终端输入的一行信息
  for (char *str; (str = readline(">>>")) != NULL; ) 
  {
    char *str_end = str + strlen(str);//指向字符串末尾指针

    /* extract the first token as the command */
    //第一个空格之前的视为命令,存入cmd
    //strtok(处理的字符串，分割符)
    char *cmd = strtok(str, " ");//cmd指向第一个字符，下次调用从第一个空格之后开始

    //如果什么也不输入，则默认进行si 
    if (cmd == NULL) 
    { 
      printf("no command\n");
      continue;
    }
    
    //命令之后的字符视为参数
    char *args = cmd + strlen(cmd) + 1;//指向参数的第一个字符
    if (args >= str_end) {
      args = NULL;
    }

    //对命令进行分拣，执行cmd对应的函数
    int i;
    for (i = 0; i < NR_CMD; i++) {//扫描是否是某个命令
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        //当执行函数的返回值小于0时终止，否则再次请求输入
        if (cmd_table[i].handler(args) < 0)
          { return; }//执行命令
        break;
      }
    }
    //不匹配任何已知命令
    if (i == NR_CMD)
      { printf("Unknown command '%s'\n", cmd); }
  }

}

