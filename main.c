#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/vm_sockets.h>

void main(){

  int s = socket(AF_VSOCK, SOCK_STREAM, 0);
  struct sockaddr_vm addr;
  bzero(&addr, sizeof(struct sockaddr_vm));
  addr.svm_family = AF_VSOCK;
  addr.svm_port = 1025;
  addr.svm_cid = VMADDR_CID_HOST;
  if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
    perror("unable to connect to the host");
  }
  for (;;) {
    if (write(s, ".", 1) != 1) {
      perror("unable to write a byte");
    }
    char c;
    if (read(s, &c, 1) != 1) {
      perror("unable to read a byte");
    }
    printf("%c", c);
    fflush(stdout);
  }
}