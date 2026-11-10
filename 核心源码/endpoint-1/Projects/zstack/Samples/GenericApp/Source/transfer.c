#include "ringbuffer.h"
#include "transfer.h"


static struct transfer_operation  transfer_operation_new ;
static unsigned char data_buffer_send[TRANSMISSION_CACHE_LEN];
static unsigned char data_buffer_recv[TRANSMISSION_CACHE_LEN];


static RingBuffer rb_sensor_send ;
static RingBuffer rb_sensor_recv ;

static unsigned char ringbuff_data_send[TRANSMISSION_CACHE_LEN];
static unsigned char ringbuff_data_recv[TRANSMISSION_CACHE_LEN];

void transfer_init(struct transfer_operation * trans)
{
    transfer_operation_new = *trans ;
  
    rb_new(&rb_sensor_send,ringbuff_data_send,TRANSMISSION_CACHE_LEN);
    rb_new(&rb_sensor_recv,ringbuff_data_recv,TRANSMISSION_CACHE_LEN);
}



void transfer_send_to_cache(unsigned char * buff ,unsigned int len)
{
  int rb_len;

  if(len==0) return ;

  rb_len = rb_can_write(&rb_sensor_send);

  len = rb_len>len ? len : rb_len;

  rb_write(&rb_sensor_send, buff, len);
    
}



void transfer_send_sync(void)
{
    int rb_len ;
    
    rb_len = rb_can_read(&rb_sensor_send);

    rb_len = rb_read(&rb_sensor_send,data_buffer_send,rb_len);

  if (rb_len > 0) {
    if (transfer_operation_new.device_send_function != 0)
      transfer_operation_new.device_send_function(data_buffer_send, rb_len);
  }
}


void transfer_recv_to_cache(unsigned char * buff ,unsigned int len)
{

  int rb_len;

  if(len==0) return ;

  rb_len = rb_can_write(&rb_sensor_recv);

  len = rb_len>len ? len : rb_len;

  rb_write(&rb_sensor_recv, buff, len);

}



void transfer_recv_sync(void)
{
  int rb_len ;
    
    rb_len = rb_can_read(&rb_sensor_recv);

    rb_len = rb_read(&rb_sensor_recv,data_buffer_recv,rb_len);

  if (rb_len > 0)
  {
    if (transfer_operation_new.user_recv_callback != 0)
      transfer_operation_new.user_recv_callback(data_buffer_recv, rb_len);
  }
}


