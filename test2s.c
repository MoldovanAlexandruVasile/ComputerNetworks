#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
       int s;
       struct sockaddr_in server, client;
       int c, l;

       s = socket(AF_INET, SOCK_STREAM, 0);
       if (s < 0) {
              printf("Eroare la crearea socketului server\n");
              return 1;
       }

       memset(&server, 0, sizeof(server));
       server.sin_port = htons(1234);
       server.sin_family = AF_INET;
       server.sin_addr.s_addr = INADDR_ANY;

       if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
              printf("Eroare la bind\n");
              return 1;
       }

       listen(s, 5);
       l = sizeof(client);
       memset(&client, 0, sizeof(client));

       while (1) {
              uint16_t length, b, suma;
	      char caracter;
              c = accept(s, (struct sockaddr *) &client, &l);
              printf("S-a conectat un client.\n");
              // deservirea clientului
              recv(c, &length, sizeof(int), MSG_WAITALL);
	      length = ntohs(length);
	      char string[100];
              recv(c, &string, sizeof(char)*length, MSG_WAITALL);
	      recv(c, &caracter, sizeof(char), MSG_WAITALL);
              int lastpos = 0;
	      for (int i = 0 ; i < length; i++)
		  if (string[i] == caracter)
			lastpos = i;
	      lastpos = htons(lastpos);
	      send(c, &lastpos, sizeof(int), 0);
              lastpos = ntohs(lastpos);
	      send(c, &string, sizeof(char)*lastpos, 0);
              close(c);
       }
}
