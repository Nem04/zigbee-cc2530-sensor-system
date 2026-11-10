#include "iocc2530.h"
#include "OnBoard.h"
#include "renti.h"




void InitIO_Renti(void)
{

	P0SEL &= ~0x10;                 //设置P0.4为普通IO口
  	P0DIR &= ~0x10;                 //P0.4定义为输入口
}

unsigned char read_renti(void)
{
	int		i	= 0;
	static uint8	record	= 0;
	uint8		state	= 0;
	if ( DATA_PIN_RENTI == 1 )
	{
		state = 1;                      /*有人进入 */
	}else {
		for ( i = 0; i < 5; i++ )
		{
			if ( DATA_PIN_RENTI == 1 )
			{
				state = 1;      /*有人进入 */
				break;
			}
			MicroWait( 10000 );     /* Wait 10ms */
		}
	}

	if ( state == 1 )
	{
		record = ( (record << 1) | 0x01);
	}else {
		record = ( (record << 1) & (~0x01) );
	}

	if ( (record & 0x1f) == 0 )
	{
		return (0);
	}else {
		return (1);
	}


}