using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zigbee_wifi
{
    public interface Protocol_interface
    {
        void protocaol_callback(byte[] buff, int len);
    }


    public class Protocol
    {
        byte[] buff = new byte[256];
        int buff_max_len = 256;
        int flag_is_get_head;
        int pack_idx;
        Protocol_interface local_interface;

        //get id
        int id_idx_now;
        int id_idx_last;
        int flag_get_start;
        int flag_get_symbel;
        int flag_get_end;
        int complete;


        public Protocol(Protocol_interface interface_arg)
        {
            local_interface = interface_arg;
        }


        public void GetPack(byte[] src, int len)
        {
            int loop = 0;

            for (loop = 0; loop < len; loop++)
            {
                if (src[loop] == '{')
                {
                    flag_is_get_head = 1;
                    pack_idx = 0;
                    //flag_is_get_tail = 0;

                    buff[pack_idx++] = src[loop];

                    continue;
                }
                else if (src[loop] == '}')
                {
                    if (flag_is_get_head == 1)
                    {
                        buff[pack_idx++] = src[loop];
                        buff[pack_idx] = 0;
                        local_interface.protocaol_callback(buff, pack_idx);
                        pack_idx = 0;
                        flag_is_get_head = 0;
                    }
                    else
                    {
                        pack_idx = 0;
                    }
                }
                else
                {
                    if (flag_is_get_head == 1 && pack_idx < buff_max_len - 2)
                    {
                        buff[pack_idx++] = src[loop];
                    }
                }
            }

        }



        public int Get_id_value(byte[] src, ref string id, ref string value)
        {

            if (complete == 1)
            {
                complete = 0;

                flag_get_start = 0;
                flag_get_symbel = 0;
                flag_get_end = 0;
                id_idx_last = 0;
                id_idx_now = 0;

                return 0;
            }

            do
            {
                if (src[id_idx_now] == '{')
                {
                    flag_get_start = id_idx_now + 1;
                }
                else if (src[id_idx_now] == ':')
                {
                    flag_get_symbel = id_idx_now;
                }
                else if (src[id_idx_now] == '}' || src[id_idx_now] == ',')
                {

                    flag_get_end = id_idx_now;

                    if (flag_get_symbel - flag_get_start > 1 && flag_get_end - flag_get_symbel > 1 && id_idx_last < flag_get_start
                      && flag_get_symbel - flag_get_start < 30 && flag_get_end - flag_get_symbel < 30)
                    {

                        //osal_memcpy(id, &src[ flag_get_start],  flag_get_symbel -  flag_get_start);
                        //*(id +  flag_get_symbel -  flag_get_start ) = 0;



                        if (src[flag_get_start] == '\"' && src[flag_get_symbel - 1] == '\"')
                        {
                            byte[] temp = new byte[256];

                            Array.Clear(temp, 0, 256);

                            for (int i = 0; i < flag_get_symbel - flag_get_start - 2; i++)
                            {
                                temp[i] = src[flag_get_start + 1 + i];
                            }

                            temp[flag_get_symbel - flag_get_start - 2] = 0;


                            string str = System.Text.Encoding.ASCII.GetString(temp);

                            str = str.TrimEnd('\0');

                            id = str;
                        }
                        else
                        {
                            byte[] temp = new byte[256];

                            Array.Clear(temp, 0, 256);

                            for (int i = 0; i < flag_get_symbel - flag_get_start; i++)
                            {
                                temp[i] = src[flag_get_start + i];
                            }
                            temp[flag_get_symbel - flag_get_start] = 0;


                            string str = System.Text.Encoding.ASCII.GetString(temp);
                            str = str.TrimEnd('\0');

                            id = str;

                        }

                        //osal_memcpy(value, &src[ flag_get_symbel + 1],  flag_get_end -  flag_get_symbel - 1);
                        //*(value +  flag_get_end -  flag_get_symbel - 1) = 0;


                        if (src[flag_get_symbel + 1] == '\"' && src[flag_get_end - 1] == '\"')
                        {

                            byte[] temp = new byte[256];

                            Array.Clear(temp, 0, 256);

                            for (int i = 0; i < flag_get_end - flag_get_symbel - 3; i++)
                            {
                                temp[i] = src[flag_get_symbel + 2 + i];
                            }

                            temp[flag_get_end - flag_get_symbel - 3] = 0;


                            string str = System.Text.Encoding.ASCII.GetString(temp);
                            str = str.TrimEnd('\0');

                            value = str;

                        }
                        else
                        {
                            byte[] temp = new byte[256];

                            Array.Clear(temp, 0, 256);

                            for (int i = 0; i < flag_get_end - flag_get_symbel - 1; i++)
                            {
                                temp[i] = src[flag_get_symbel + 1 + i];
                            }
                            temp[flag_get_end - flag_get_symbel - 1] = 0;


                            string str = System.Text.Encoding.ASCII.GetString(temp);
                            str = str.TrimEnd('\0');

                            value = str;

                        }

                        if (src[id_idx_now] == '}')
                        {
                            complete = 1;
                            return 1;
                        }
                        else
                        {
                            id_idx_last = id_idx_now;
                            flag_get_start = id_idx_now + 1;
                            return 1;
                        }
                    }

                    if (src[id_idx_now] == ',')
                    {
                        id_idx_last = id_idx_now;
                        flag_get_start = id_idx_now + 1;
                    }
                    else if (src[id_idx_now] == '}')
                    {
                        complete = 0;

                        flag_get_start = 0;
                        flag_get_symbel = 0;
                        flag_get_end = 0;
                        id_idx_last = 0;
                        id_idx_now = 0;

                        return 0;
                    }

                    else
                    {
                        return 0;
                    }



                }
            } while (id_idx_now++ < (buff_max_len - 2));


            flag_get_start = 0;
            flag_get_symbel = 0;
            flag_get_end = 0;
            id_idx_last = 0;
            id_idx_now = 0;

            return 0;
        }


    }
}
