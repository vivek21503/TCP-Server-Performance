#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 4444
#define MAX_CONNECTIONS 301
#define SZ 1028

void control_client(int soc_client,bool a3) {
    ssize_t bytes_size;
    int a=soc_client;
    char buffer[SZ];
    if(a3){
    	while(a3 && (bytes_size = recv(a, buffer, sizeof(buffer), 0)) > 0){
    		if(bytes_size<=0){
    			a3=false;
    		}
    		printf("received from client %s\n",buffer);
    		send(a, buffer, bytes_size, 0);
        	printf("server send :%s\n",buffer);
    		
    		
    	}
    	
    }


    close(soc_client);
    exit(0);
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
		return true;
	}
	else{
		return false;
	}
	}
	return true;
}
int check_fork(pid_t a,bool s2){
	if (a==0 && s2){
	   return 1;
	}
	else if(a>0 && s2){
		return 2;
	}
	else{
		printf("error");
		return -1;
	}
}
int main() {
    int soc_server;
    struct sockaddr_in  client_addr;
    bool a1=true;
    bool a2=true;
    struct sockaddr * addr_bind;
    int soc_client;
    bool a3=true;
    socklen_t client_addr_len = sizeof(client_addr);

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
    
	
    while (a2) {
        struct sockaddr * accept_client_addr;
        accept_client_addr=(struct sockaddr*)&client_addr;
        soc_client = accept(soc_server, accept_client_addr, &client_addr_len);
        bool s1=check_accept(soc_client,a4);
        if(s1==false && a2){
        	pid_t child_pid = fork();
        	int p=check_fork(child_pid,a4);
		if (p==1 && a2) {
            		close(soc_server);
            		control_client(soc_client,a3);
		} else if (p==2 && a2) {
		    close(soc_client);
		}
        	
        	

        		
        }
        
        
    }

    close(soc_server);
    return 0;
}
