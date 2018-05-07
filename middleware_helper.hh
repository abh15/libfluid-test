// Added khaarde.rohan@yahoo.com
// IEEE P1930
#ifndef __MIDDLEWARE_HELPER__
#define __MIDDLEWARE_HELPER__
#include <unistd.h>  
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT_DST 6653 //OF_port
#define PORT_SRC 6657
#include "libfluid_base/fluid/base/of.hh"

class middleware_helper
{
	public :
        // 
    void send_to_absL(void* msg_data, const char *msg_target)
    {    
           if (msg_target == "m-NBI")
            { 
              printf(" m-SBI message received at absL \n");
              //Abstract here for m-NBI message format // To Do
              send_to_mNBI(msg_data);  
            }
           else if (msg_target == "m-SBI")
            {
              printf(" m-NBI message received at absL \n");
              //Abstract here for m-SBI message format // To Do
              send_to_mNBI(msg_data);
            }
           printf(" \n\n Openflow Version is %u \n",(((uint8_t*) msg_data)[0]));
                      
    }

        // This funtion forwards (or abstract and forwards) Openflow controller plugin message to abstraction layer. 
    int init_mNBI_Listener()
    {
    	//Run this function as a seprate thread to listen mNBI message and make callback to send_to_absL().
        printf("Started mNBI_Listener() as thread \n");
        int valread, sock = 0;
        struct sockaddr_in serv_addr;
        char msg_data[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)   
            {
              printf("\n m-NBI Socket creation error \n");
              return -1;
            }
        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT_SRC);
             // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "192.168.0.14", &serv_addr.sin_addr)<=0) 
            {
                printf("\nInvalid address/ Address not supported \n");
                return -1;
            }
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            { 
                printf("\n m-NBI Connection Failed \n");
                return -1;
            }        
        printf("mNBI_Listener()-->> Listening for m-NBI messages \n");
        while(1)
        {
        valread = read( sock , msg_data, 1024);
        printf("mNBI_Listener()-->> Received %s\n",atoi(msg_data) );
         }

        return 0;
    }
    
    int send_to_mNBI (void* data)
    {
            // absL to mNBI (SDN_CTL)
        printf(" absL message received at m-NBI \n");
        int sock = 0,msg_lenght,valread;
       // printf("  Openflow Version is %u \n",(((uint8_t*) data)[0]));
       // msg_lenght = (((uint8_t*) data)[2]);
           /* struct ofp_header msg;
            msg.version = ((uint8_t*) data)[0];
            msg.type = OFPT_HELLO;
            msg.length = htons(8);
            msg.xid = ((uint32_t*) data)[1];*/
        struct sockaddr_in address;
        struct sockaddr_in serv_addr;
        uint8_t data1[] = {0x01, 0x00, 0x00, 0x08, 0x14, 0x78, 0xf0, 0x90};

        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)   
            {
              printf("\n m-NBI Socket creation error \n");
              return -1;
            }
        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT_DST);
             // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "192.168.0.14", &serv_addr.sin_addr)<=0) 
            {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
            }
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            { 
            printf("\n m-NBI Connection Failed \n");
            return -1;
            }
        
        valread = read( sock , buffer, 1024);
        printf("%s\n",atoi(buffer));
        
        send(sock ,(char*)&data1, sizeof(data1), 0);
        printf("Message sent on m-NBI \n");
        //sleep(4);
       // send(sock ,(char*)&data1, sizeof(data1), 0);

        while(1)
        { valread = read( sock , buffer, 1024);
        printf("%s\n",atoi(buffer));
        }
       
            return 0;
    }

    int send_to_mSBI (void* data)
    {
     // absL to mSBI (SDN_BS)
    }
};
#endif