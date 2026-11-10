#ifndef _TRANSFER_H_
#define _TRANSFER_H_


#define TRANSMISSION_CACHE_LEN 200

struct transfer_operation{
    void(*user_recv_callback)(unsigned char * buff, unsigned int len);
	void(*device_send_function)(unsigned char * buff, unsigned int len);
};


void transfer_init(struct transfer_operation * trans);

void transfer_send_to_cache(unsigned char * buff ,unsigned int len);

void transfer_send_sync(void);

void transfer_recv_to_cache(unsigned char * buff ,unsigned int len);

void transfer_recv_sync(void);


#endif 