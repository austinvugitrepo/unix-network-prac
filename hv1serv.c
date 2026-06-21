/* Today I learned these headers are in /usr/include/. 
 * I should probably reference them if im borrowing going forward.
 */

#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
	int serv_fd, client_fd;
	
	/* man inet */
	struct sockaddr_in a;

	char *msg = "Hola!\n";

	/* man socket */
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);

	/* man memset */
	memset(&a, 0, sizeof(a));

	/* man netintro */
	a.sin_family = AF_INET;

	/* man htons */
	a.sin_port = htons(6767);
	
	a.sin_addr.s_addr = INADDR_ANY;

	/* man bind */
	bind(serv_fd, (struct sockaddr *)&a, sizeof(a));

	/* man listen */
	listen(serv_fd, 1);

	printf("Waiting for a connection on port 6767...\n");

	/* man accept */
	client_fd = accept(serv_fd, NULL, NULL);

	/* man write */
	write(client_fd, msg, strlen(msg));
	
	/* man close */
	close(client_fd);
	close(serv_fd);

	return 0;

}

