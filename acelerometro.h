
#define CTRL_REG1 0x2A 
#define XYZ_DATA_CFG 0x0E
#define  g_Range 0x01  // 2g=0x00 4g=0x01 8g=0x02


class acelerometro{
public : 

	byte direccion;
//extern void inicializacion_acel(void);
void inicializacion_acel(byte direccion);
void lectura_datos (int *xyz_datos);
};