#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__



struct protocol_info
{
	//get pack
	unsigned char * buff;
	unsigned int  buff_max_len;
	unsigned char flag_is_get_head;
	int pack_idx;
	void(*pack_callback)(unsigned char * a, int b);

	//get id
	int id_idx_now;
	int id_idx_last;
	unsigned char flag_get_start;
	unsigned char flag_get_symbel;
	unsigned char flag_get_end;
	unsigned char complete;

	//set id - value
	unsigned char send_one_pack_start;
	unsigned char send_one_pack_first;
};





void  GetPack(struct protocol_info * info, const unsigned char * src, unsigned int len);

unsigned char   Get_id_value(struct protocol_info * info, char * src, char * id, char * value);



void Start_send_pack(void);

void Complete_send_pack(void);

unsigned char  Set_id_value_str(char * id, char * value);

unsigned char  Set_id_value_int( char * id, int value);

void  Set_debug_info(char * info);



#endif
