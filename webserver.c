#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int serverSocked, newServerSocket, portNumber, client;
    char buffer[256];
    struct sockaddr_in serv_addr, client_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"Keine Portnummer übergeben.");
        exit(1);
    }
    serverSocked = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocked < 0) {
        perror("Fehler beim erstellen des Socket.");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portNumber = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);

    if (bind(serverSocked, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        perror("Fehler beim binden mit Client.");
        exit(1);
    }
    listen(serverSocked, 5);
    client = sizeof(client_addr);
    newServerSocket = accept(serverSocked,
                             (struct sockaddr *) &client_addr,
                             &client);
    if (newServerSocket < 0) {
        perror("Fehler beim Akzeptieren.");
        exit(1);
    }
    bzero(buffer,256);
    n = read(newServerSocket, buffer, 255);
    if (n < 0) {
        perror("Fehler beim lesen vom Socket.");
        exit(1);
    }
    printf("Die erhaltene Nachricht ist: %s",buffer);

    n = write(newServerSocket, "Reply", 5);
    if (n < 0) {
        perror("Fehler beim Antworten.");
        exit(1);
    }
    return 0;
}
