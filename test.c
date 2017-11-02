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
       server.sin_port = htons(54321);
       server.sin_family = AF_INET;
       server.sin_addr.s_addr = inet_addr("172.30.113.3");

       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
              printf("Eroare la conectarea la server\n");
              return 1;
       }
	while(1)
	{
       		char string[100];
       		char string2[200];
		printf("\nString: ");
      		fgets(string, 100, stdin);
       		int length = strlen(string);
       		send(c, &string, sizeof(char)*length, 0);
       		recv(c, &string2, sizeof(char)*200, 0);
       		printf("String-ul primit: ");
		for(int i = 0; i < strlen(string2); i++)
			if (string2[i] == '\n')
				break;
			else printf("%c", string2[i]);
       }
       close(c);
}
