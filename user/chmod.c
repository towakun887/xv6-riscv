#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage: chmod <int:mode> <char*:path>\n");
    exit(0);
  }

  int mode = atoi(argv[1]);
  if(mode < 4 || 7 < mode){
    printf("chmod: Invalid file mode: %d\n",mode);
    exit(0);
  }

  if(chmod(argv[2],atoi(argv[1]))<0){
    printf("chmod: failed\n");
  }else{
    int fd;
    struct stat st;
    if((fd = open(argv[2],0))<0){
      printf("chmod: executed but checking failed: file not found.\n");
      exit(0);
    }
    if(fstat(fd,&st)<0){
      printf("chmod: executed but checking failed: cannot open stat\n");
      exit(0);
    }
    printf("chmod: sucess: mode of %s is changed to %d\n",argv[2],st.mod);
  }
}
