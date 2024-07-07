#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 4444
#define MAX_CONNECTIONS 4001
#define SZ 1024

void *control_client(void *arg) {
    char buffer[SZ];
    int soc_client = *((int *)arg);
    int a1=soc_client;
    bool a4=true;
    int b_size=SZ;
    ssize_t bytes_size;

    while (a4 && (bytes_size = recv(a1, buffer, SZ, 0)) > 0) {
    	if(bytes_size<=0){
    		a4=false;
    	}
        printf("Received from client: %s\n", buffer);
        send(soc_client, buffer, bytes_size, 0);
        printf("send to client %s\n",buffer);
    }

    close(soc_client);
    free(arg);
    pthread_exit(NULL);
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
int main() {
    int soc_server;
    struct sockaddr_in client_addr;
    struct sockaddr* addr_bind;
    bool a1=true;
    bool a2=true;
    pthread_t thr_id;
    int soc_client;
    socklen_t client_addr_len = sizeof(client_addr);

    soc_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    addr_bind=(struct sockaddr*)&server_addr;
    socklen_t len_server_addr=sizeof(server_addr);
    bool a4=true;
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
        	int *soc_client_p = malloc(sizeof(int));
		*soc_client_p = soc_client;
		if(a2){

		pthread_create(&thr_id, NULL, control_client, (void *)soc_client_p);
		}
        	
        }
    	
    	
    	
        /*soc_client = accept(soc_server, (struct sockaddr*)&client_addr, &client_addr_len);
        if (soc_client == -1) continue;
        */

        /*int *soc_client_ptr = malloc(sizeof(int));
        *soc_client_ptr = soc_client;

        pthread_create(&thread_id, NULL, handle_client, (void *)soc_client_ptr);
        */
    }
    close(soc_server);
    return 0;
}
