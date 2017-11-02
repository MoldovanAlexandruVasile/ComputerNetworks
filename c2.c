#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
       int c;
       struct sockaddr_in server;
       uint16_t a, b, suma;
 
       c = socket(AF_INET, SOCK_STREAM, 0);
       if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
       }
       memset(&server, 0, sizeof(server));
       server.sin_port = htons(1234);
       server.sin_family = AF_INET;
       server.sin_addr.s_addr = inet_addr("127.0.0.1");

       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server\n");
                return 1;
       }
       int n;
       printf("n = ");
       scanf("%hu", &n);
       int v[100];
       n = htons(n);
       send(c, &n, sizeof(int), 0);
       n = ntohs(n);
       for(int i = 0; i < n; i++)
       {
                int x;
                printf("v[%hu] = ",i);
                scanf("%hu", &x);
                v[i] = x;
       }
       send(c, &v, sizeof(int)*n, 0);
       recv(c, &suma, sizeof(suma), 0);
       suma = ntohs(suma);
       printf("Suma este %hu\n", suma);
       close(c);
}
