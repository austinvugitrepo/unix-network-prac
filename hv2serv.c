#include <sys/socket.h>
#include <netinet/in.h>

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Simple TCP server that exits after client connects via port 6000.
 * This server only responds to IPv4 and is tested using localhost.
 */

int
main(void)
{
	int serv_fd, cli_fd;
	char *mesg = "Hello client!\n";
	

	/* using IPv4: */
	struct sockaddr_in addr;

	if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		err(1, NULL);

	/* cleaning the struct: */
	memset(&addr, 0, sizeof(addr));

	/* filling the struct: */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serv_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		err(1, NULL);
	 
	if (listen(serv_fd, 1) == -1)
		err(1, NULL);
	
	printf("Waiting on port 6000...\n");

	for (;;) {
		if ((cli_fd = accept(serv_fd, NULL, NULL)) == -1)
			err(1, NULL);

		if (write(cli_fd, mesg, strlen(mesg)) == -1)
			err(1, NULL);

		if (close(cli_fd) == -1)
			err(1, NULL);
	}

	return 0;

} 
