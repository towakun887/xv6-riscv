#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char*
getrwx(short m){
  static char rwx[4];
  rwx[0] = ((m >> 2) & 1) == 1 ? 'r' : '-';
  rwx[1] = ((m >> 1) & 1) == 1 ? 'w' : '-';
  rwx[2] = (m & 1) == 1 ? 'x' : '-';
  rwx[3] = '\0';
  return rwx;
}

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

  //chache previous mode
  int fd;
  struct stat st;
  short befmod = 0;
  if(!((fd = open(argv[2],0))<0)){ //if file open success
    if(!(fstat(fd,&st)<0)){ //if stat open success
      befmod = st.mod;
    }
  }

  //MAIN
  if(chmod(argv[2],atoi(argv[1]))<0){
    printf("chmod: failed\n");

  //checking result
  }else{
    if(fd<0){ //if file open failed in ago
      if((fd = open(argv[2],0))<0){ //retry
        printf("chmod: executed but checking failed: file not found.\n");
        exit(0);
      }
      //if success, continue to get stat
    }

    if(fstat(fd,&st)<0){ //re-get stat
      printf("chmod: executed but checking failed: cannot open stat\n");
      exit(0);
    }

    //common message
    printf("chmod: success: mode of %s has been changed to %s",argv[2],getrwx(st.mod));
    if(befmod != 0){ //if there is chached old mode
      printf(" from %s\n",getrwx(befmod));
    }else{
      printf("\n");
    }
  }
}
