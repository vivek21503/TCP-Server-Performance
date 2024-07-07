#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 4444
#define MAX_CONNECTIONS 4000
#define SZ 4096

int control_client(int soc_client,bool a3,int arr[],int i1) {
    ssize_t bytes_size;
    int a=soc_client;
    char buffer[SZ];
    if(a3){
    	bytes_size = recv(a, buffer, sizeof(buffer), 0) ;
	if(bytes_size<=0){
		//printf("disconnect \n");
		a3=false;
		close(a);
                arr[i1] = 0;
	}
	else if(bytes_size>0){
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
bool check_accept(int k1,bool s2){
	if(s2){
	if(k1<0 || k1==-1){
		printf("error");
		return true;
	}
	else{
		return false;
	}
	}
	return true;
}
void buffer_intial(int n1,int arr[],int val){
	int val1=val;
	for(int i=0;i<n1;i++){
		arr[i]=val1;
	}
}
int find_max_fd(fd_set * r_fds,bool a2,int arr[],int n1,int *fd_max){
	int s1=n1;
	int i1=0;
	while(i1<n1 && a2){
		int a=arr[i1];
		bool a1=(a2 && (a>0));
		if (a2 && a1==true) {
                	FD_SET(a, r_fds);
		 }
		if (a2 && (a > *fd_max)) {
			a2=true;
			*fd_max = a;
		  }
		i1++;
	}
	return 1;
}
int next_val(int n1){
	return n1+1;
}
void update_fd(int arr[],int n1,int v2){
	int i1=0;
	int n11=n1;
	while(i1<n11){
		bool k2=(arr[i1]==0);
		if (k2==true) {
                    arr[i1] = v2;
                    break;
                }
                i1=i1+1;
		
	}
}
int main() {
    int soc_server;
    struct sockaddr_in  client_addr;
    fd_set r_fds;
    bool a1=true;
    bool a2=true;
    struct sockaddr * addr_bind;
    int soc_client[MAX_CONNECTIONS];
    int n=MAX_CONNECTIONS;
    
    bool a3=true;
    int n1=0;
    buffer_intial(MAX_CONNECTIONS,soc_client,n1);
    socklen_t client_addr_len = sizeof(client_addr);
    

    soc_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int n2=-1;
    
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

    printf("Server listening on port %d\n", PORT);

    int fd_max;
    while (a2) {
        FD_ZERO(&r_fds);
        FD_SET(soc_server, &r_fds);
        int m1;
        fd_max = soc_server;
        m1=find_max_fd(&r_fds,a2,soc_client,n,&fd_max);

        int m2=next_val(fd_max);

         select(m2, &r_fds, NULL, NULL, NULL);
        

        if (a2 && FD_ISSET(soc_server, &r_fds)) {
            struct sockaddr * accept_client_addr;
            accept_client_addr=(struct sockaddr*)&client_addr;
            int soc1_client = accept(soc_server, accept_client_addr, &client_addr_len);
            bool s1=check_accept(soc1_client,a4);
            
            
            update_fd(soc_client,n,soc1_client);
        }
        int i1=0;
        while(a2 && i1<n){
            int fd = soc_client[i1];
            if (a2 && FD_ISSET(fd, &r_fds)) {
            	if(a2){
            	int i2=control_client(fd,a3,soc_client,i1);
            	}
            }
                i1=next_val(i1);
        }
    }

    close(soc_server);
    return 0;
}
