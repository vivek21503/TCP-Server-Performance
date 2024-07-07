#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define MAX_CONNECTIONS 4001
#define SZ 1024
#define PORT 8080

int control_client(int soc_client,bool a3,int epoll_f) {
    ssize_t bytes_size;
    int a=soc_client;
    char buffer[SZ];
    bool m=true;
    if(a3){
    	bytes_size = recv(a, buffer, sizeof(buffer), 0) ;
	if(bytes_size<=0){
		//printf("disconnect \n");
		a3=false;
		fds_del_ctl1(epoll_f, a,m);
                close(soc_client);
	}
	else if(bytes_size>0){
		buffer[bytes_size] = '\0';
    		printf("received from client %s\n",buffer);
    		send(a, buffer, bytes_size, 0);
		printf("server send :%s\n",buffer);
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
int fds_fd(struct epoll_event arr_events[],int i1){
	if(i1<0 ||i1==-1){
		return -1;
	}
	else{
		return arr_events[i1].data.fd;
	}
}
void fds_ctl(int epoll_f,struct epoll_event event,int soc_servr,bool a2){
	if(a2){
	epoll_ctl(epoll_f, EPOLL_CTL_ADD, soc_servr, &event);
	}
}
void fds_del_ctl1(int epoll_f,int soc_servr,bool a2){
	if(a2){
	epoll_ctl(epoll_f, EPOLL_CTL_DEL, soc_servr,NULL);
	}
}

int main() {
    int soc_server;
    bool a1=true;
    bool a2=true;
    struct epoll_event arr_events[MAX_CONNECTIONS];
    int epoll_fd;
    struct sockaddr * addr_bind;
    int soc_client;
    bool a3=true;
    int n=MAX_CONNECTIONS;

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

    struct epoll_event event;
    epoll_fd = epoll_create1(0);
    int n1=0;
    int n2=-1;
    event.events = EPOLLIN;
    event.data.fd = soc_server;

    if(a2){
    fds_ctl(epoll_fd,event,soc_server,a2);
    }
    

    while (a2) {
        int total_e = epoll_wait(epoll_fd, arr_events, n, n2);
        int i=n1;
	while(a2 && i<total_e){
        	int k1=fds_fd(arr_events,i);
        	bool k2=(k1==soc_server);
        	if(a2 && k2){
        		int m1=accept(soc_server, NULL, NULL);
        		a4=true;
        		 event.events = EPOLLIN | EPOLLET;
        		 int m2=m1;
		        event.data.fd = m2;
		        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, m2, &event);
        		
        	}
        	else{
        		soc_client=fds_fd(arr_events,i);
        		if(a2){
        		int p1=control_client(soc_client,a3,epoll_fd);
        		}
        	}
        	i=next_n(i);
        }
    }

    close(soc_server);

    return 0;
}
