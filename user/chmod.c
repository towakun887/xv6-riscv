#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage: chmod <char*:path> <int:mode>\n");
    exit(0);
  }

  if(chmod(argv[1],atoi(argv[2]))<0){
    printf("chmod: failed\n");
  }else{
    printf("chmod: sucess: mode of %s is changed to %s\n",argv[1],argv[2]);
  }
}
