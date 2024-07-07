#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <arpa/inet.h>

#define MAX_CONNECTIONS 4001
#define PORT 4444
#define SZ 1024
int control_client(int soc_client,bool a3) {
    ssize_t bytes_size;
    int a=soc_client;
    char buffer[SZ];
    if(a3){
    	bytes_size = recv(a, buffer, sizeof(buffer), 0) ;
	if(bytes_size<=0){
		//printf(" disconnect \n");
		a3=false;
		return 0;
	}
	else if(bytes_size>0){
    		printf("received from client %s\n",buffer);
    		send(a, buffer, bytes_size, 0);
		printf("server send :%s\n",buffer);
		return 1;
	}
    		
    }
    return 1;

}
bool check_bind(int b1,bool s2){
	if(s2){
	
	if (b1<0 && s2){
		perror("error");
		return false;
	}
	else{
		return true;
	}
	}
	return true;
}

bool check_accept(int k1,bool s2){
	if(s2){
	if(k1<0 || k1==-1){
		return true;
	}
	else{
		return false;
	}
	}
	return true;
}
bool check_listen(int l1,bool s2){
	if(s2){
	if(l1<0){
		perror("error");
		return false;
	}
	else if(l1==-1){
		perror("error");
		return false;
	}
	else{
		return true;
	}
	}
	return true;
}

int next_n(int n11){
	return n11+1;
}
short fds_revent(struct pollfd fds[],int k1){
	int n11=k1;
	return fds[n11].revents;
	

}
int fds_fd(struct pollfd fds[],int k1){
	int n11=k1;
	return fds[n11].fd;
}
short fds_event(struct pollfd fds[],int k1){
	int n11=k1;
	return fds[n11].events;
}

int main() {

    struct pollfd fds[MAX_CONNECTIONS];
    int soc_server;
    int n1=0;
    struct sockaddr_in  client_addr;
    bool a1=true;
    bool a2=true;
    struct sockaddr * addr_bind;
    int soc_client;
    bool a3=true;
    socklen_t client_addr_len = sizeof(client_addr);
    int n = 0;
    int n2=-1;

    // Create a server socket
    soc_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bool a4=true;
    
    addr_bind=(struct sockaddr*)&server_addr;
    socklen_t len_server_addr=sizeof(server_addr);
    
    int b1=bind(soc_server,addr_bind,len_server_addr);
    bool b2=check_bind(b1,a4);
    if(b2==false && a2){
    	a1=false;
    	exit(1);
    }
    int l1=listen(soc_server,MAX_CONNECTIONS);
    bool l2;
    l2=check_listen(l1,a4);
    if(l2==false && a2){
    	a1=false;
    	exit(1);
    }
    printf("Server on port %d\n", PORT);

    fds[0].fd = soc_server;
    short k2 =fds_event(fds,0);
    fds[0].events = POLLIN;

    while (a2) {
    	n1=next_n(n);
        
       	poll(fds, n1, n2);
	if(a3){
	int n4=0;
	short r1=fds_revent(fds,n4);
        if (a2 && (r1 & POLLIN)) {
            int n3=MAX_CONNECTIONS;
            n3=n3-1;
            struct sockaddr * accept_client_addr;
            accept_client_addr=(struct sockaddr*)&client_addr;
            soc_client = accept(soc_server,accept_client_addr, &client_addr_len);
            bool s1=check_accept(soc_client,a4);
            bool j1=(n<n3);
            if(s1==false && j1){
            	int p1=next_n(n);
            	fds[p1+n4].fd=soc_client;
            	fds[p1+ n4].events = POLLIN;
            	n=next_n(n);
            	
            	
            }
        }
        }

        int i1=1;
        while(i1<=n && a2){
        	short r2=fds_revent(fds,i1);
        	if (a2 && (r2 & POLLIN)) {
        	int f1=fds_fd(fds,i1);
                soc_client =f1;
                int m2=control_client(soc_client,a3);
                if(a3 && m2==0){
                	close(soc_client);
                	fds[i1].fd=n2;
                }
            }
            i1++;
        	
        }

        
    }

    close(soc_server);
    return 0;
}

