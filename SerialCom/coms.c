#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"

#define BUF_SIZE 1024

int main(){
	int i = 0;
	int cport_nr = RS232_GetPortnr("ttyACM0");
	int bdrate = 9600;
	
	char mode[] = {'8', 'N', '1', 0};
	unsigned char str_recv[BUF_SIZE];
	if(RS232_OpenComport(cport_nr, bdrate, mode)){
		printf("Cant open comport\n");
		return(0);
	}

	usleep(2000000);

	
	while(1){
		usleep(1000000);
		int n = RS232_PollComport(cport_nr, str_recv, (int)BUF_SIZE);
		if(n > 0){
			str_recv[n] = 0;
			printf("Received %i bytes: '%s'\n", n, (char *)str_recv);
		}
		i++;
		i%=2;
		
	}
	return(0);
}
