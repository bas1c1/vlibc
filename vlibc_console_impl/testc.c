#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

int main(int argc, char *argv[]) {
  printf("%.15f", vlibc_log(5));
}