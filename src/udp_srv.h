#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512
#define PORT 9930

struct sockaddr_in si_me, si_other;
int s, i;
socklen_t slen=sizeof(si_other);
char buf[BUFLEN];

void diep(char *s){
  perror(s);
  exit(1);
}

void bsock(){
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
  diep("socket");

  memset((char *) &si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me))==-1)
  diep("bind");
}

void pdata(){
  recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
}
