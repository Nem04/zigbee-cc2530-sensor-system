#include "protocol.h"

#include "OSAL.h"
#include "transfer.h"




static unsigned char send_one_pack_start = 0;
static unsigned char send_one_pack_first = 0;



void  GetPack(struct protocol_info * info, const unsigned char * src, unsigned int len)
{


	int loop = 0;

	for (loop = 0; loop < len; loop++)
	{
		if (src[loop] == '{')
		{
			info->flag_is_get_head = 1;
			info->pack_idx = 0;
			//flag_is_get_tail = 0;

			info->buff[info->pack_idx++] = src[loop];

			continue;
		}
		else if (src[loop] == '}')
		{
			if (info->flag_is_get_head)
			{
				info->buff[info->pack_idx++] = src[loop];
				info->buff[info->pack_idx] = 0;
				info->pack_callback(info->buff, info->pack_idx);
				info->pack_idx = 0;
				info->flag_is_get_head = 0;
			}
			else
			{
				info->pack_idx = 0;
			}
		}
		else
		{
			if (info->flag_is_get_head && info->pack_idx < info->buff_max_len - 2)
			{
				info->buff[info->pack_idx++] = src[loop];
			}
		}
	}
}




unsigned char  Get_id_value(struct protocol_info * info, char * src, char * id, char * value)
{

	if (info->complete)
	{
		info->complete = 0;

		info->flag_get_start = 0;
		info->flag_get_symbel = 0;
		info->flag_get_end = 0;
		info->id_idx_last = 0;
		info->id_idx_now = 0;

		return 0;
	}

	do
	{
		if (src[info->id_idx_now] == '{')
		{
			info->flag_get_start = info->id_idx_now + 1;
		}
		else if (src[info->id_idx_now] == ':')
		{
			info->flag_get_symbel = info->id_idx_now;
		}
		else if (src[info->id_idx_now] == '}' || src[info->id_idx_now] == ',')
		{

			info->flag_get_end = info->id_idx_now;

			if (info->flag_get_symbel - info->flag_get_start > 1 && info->flag_get_end - info->flag_get_symbel > 1 && info->id_idx_last < info->flag_get_start
				&& info->flag_get_symbel - info->flag_get_start < 30 && info->flag_get_end - info->flag_get_symbel <50)
			{

				//osal_memcpy(id, &src[info->flag_get_start], info->flag_get_symbel - info->flag_get_start);
				//*(id + info->flag_get_symbel - info->flag_get_start ) = 0;

				

				if (src[info->flag_get_start] == '\"' && src[info->flag_get_symbel - 1] == '\"')
				{
					memcpy(id, &src[info->flag_get_start + 1], info->flag_get_symbel - info->flag_get_start - 2);
					*(id + info->flag_get_symbel - info->flag_get_start - 2) = 0;
				}
				else
				{
					memcpy(id, &src[info->flag_get_start], info->flag_get_symbel - info->flag_get_start );
					*(id + info->flag_get_symbel - info->flag_get_start ) = 0;
				}

				//osal_memcpy(value, &src[info->flag_get_symbel + 1], info->flag_get_end - info->flag_get_symbel - 1);
				//*(value + info->flag_get_end - info->flag_get_symbel - 1) = 0;


				if (src[info->flag_get_symbel + 1] == '\"' && src[info->flag_get_end - 1] == '\"')
				{
					memcpy(value, &src[info->flag_get_symbel + 2], info->flag_get_end - info->flag_get_symbel - 3);
					*(value + info->flag_get_end - info->flag_get_symbel - 3) = 0;
				}
				else
				{
					memcpy(value, &src[info->flag_get_symbel + 1], info->flag_get_end - info->flag_get_symbel - 1);
					*(value + info->flag_get_end - info->flag_get_symbel - 1) = 0;
				}

				if (src[info->id_idx_now] == '}')
				{
					info->complete = 1;
					return 1;
				}
				else
				{
					info->id_idx_last = info->id_idx_now;
					info->flag_get_start = info->id_idx_now + 1;
					return 1;
				}
			}

			if (src[info->id_idx_now] == ',')
			{
				info->id_idx_last = info->id_idx_now;
				info->flag_get_start = info->id_idx_now + 1;
			}
			else if (src[info->id_idx_now] == '}')
			{
				info->complete = 0;

				info->flag_get_start = 0;
				info->flag_get_symbel = 0;
				info->flag_get_end = 0;
				info->id_idx_last = 0;
				info->id_idx_now = 0;

				return 0;
			}

			else
			{
				return 0;
			}

			

		}
	} while (info->id_idx_now++ < (info->buff_max_len - 2));


	info->flag_get_start = 0;
	info->flag_get_symbel = 0;
	info->flag_get_end = 0;
	info->id_idx_last = 0;
	info->id_idx_now = 0;

	return 0;
}


unsigned char  Set_id_value_str(char * id, char * value)
{
  char out[30];
  unsigned char len = 0 ;
  if (send_one_pack_start)
  {
    if (!send_one_pack_first)
    {
      len = sprintf(out, "\"%s\":\"%s\"", id, value);
      send_one_pack_first = 1;
    }
    else
    {
      len = sprintf(out, ",\"%s\":\"%s\"", id, value);
    }
  }

  transfer_send_to_cache(out, len);

  return len;
}



unsigned char  Set_id_value_int(char * id, int value)
{
  char out[30];
  unsigned char len ;


  if (send_one_pack_start)
  {
    if (!send_one_pack_first)
    {
      len = sprintf(out, "\"%s\":%d", id, value);
      send_one_pack_first = 1;
    }
    else
    {
      len = sprintf(out, ",\"%s\":%d", id, value);
    }
  }

  transfer_send_to_cache(out, len);

  return len;
}




void  Set_debug_info(char * info)
{
  transfer_send_to_cache("{",1);
  transfer_send_to_cache(info,osal_strlen(info));
  transfer_send_to_cache("}",1);
}


void Start_send_pack(void)
{

  transfer_send_to_cache("{", 1);
  send_one_pack_start = 1;

}



void Complete_send_pack(void)
{
  transfer_send_to_cache("}", 1);
  send_one_pack_start = 0;
  send_one_pack_first = 0;

  transfer_send_sync();
}






















