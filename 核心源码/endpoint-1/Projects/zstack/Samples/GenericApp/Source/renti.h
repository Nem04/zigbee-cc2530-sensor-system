#ifndef RENTI_H
#define RENTI_H




#define DATA_PIN_RENTI P0_4                           /* 人体热释放 */

void InitIO_Renti(void);  //初始化引脚

unsigned char read_renti(void);  //获取传感器数据


#endif

