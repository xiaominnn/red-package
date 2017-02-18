#include "CTcpServer.h"

int main()
{
    CTcpServer *ctcpServer = new CTcpServer("127.0.0.1", 9999);
    int listenfd = ctcpServer->get_listenfd();
    struct sockaddr_in cliaddr;
    char buf[1024];
    int connfd, childpid;
    socklen_t clilen = 0;
	for ( ; ; ) 
    {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		if ( (childpid = fork()) == 0) 
        {	/* child process */
			close(listenfd);	/* close listening socket */
            int num = 0;
            while((num = read(connfd, buf, 1024)) > 0)
            {
                write(connfd, buf, num);
            }
			exit(0);
		}
		close(connfd);			/* parent closes connected socket */
    }
    return 0;
}
