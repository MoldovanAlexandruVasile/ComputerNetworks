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
       char string[100];
       printf("String: ");
       fgets(string, 100, stdin);
       char caracter;
       printf("Caracter: ");
       scanf(" %c", &caracter);
       getchar();
       int length = strlen(string);
       length = htons(length);
       send(c, &length, sizeof(int), 0);
       length = ntohs(length);
       send(c, &string, sizeof(char)*length, 0);
       send(c, &caracter, sizeof(char), 0);


       int length2;
       char string2[100];
       recv(c, &length2, sizeof(int), 0);
       length2 = ntohs(length2);
       recv(c, &string2, sizeof(char)*length2, 0);
	printf("The received string: ");
       for(int i = 0; i < length2; i++)
       	printf("%c", string2[i]);
	printf("\n");
       close(c);
}
