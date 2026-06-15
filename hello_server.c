#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int
main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in addr;
	char *msg = "Hello from the server!\n";

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind (server_fd,(struct sockaddr *)&addr, sizeof(addr));

	listen(server_fd, 1);

	printf("Waiting for a connection on port 5000...\n");
	
	client_fd = accept(server_fd, NULL, NULL);

	write(client_fd, msg, strlen(msg));

	close(client_fd);
	close(server_fd);

	return 0;

}


