#include <Arduino.h>
#include <Wire.h>
#include "acelerometro.h"


void inicializacion_acel(byte address){
	direccion = address;
	//Paso a modo standby para poder cambiar el rango dinamico
	standby_mode();
	//Imposicion de limites de aceleracion
	IIC_RegWrite(XYZ_DATA_CFG_REG, (IIC_RegRead(XYZ_DATA_CFG_REG) & ~(0x03)));
	IIC_RegWrite(XYZ_DATA_CFG_REG, (IIC_RegRead(XYZ_DATA_CFG_REG) | g_Range));
	//Activamos el modo
	active_mode();
}

void standby_mode(){ 
	Wire.beginTransmission(direccion);
	wire.write(CTRL_REG1);
	 //Wire.endTransmission(false);
	Wire.requestFrom(direccion,1);
	
	 while(!Wire.available()) ;  //tiempo de espera hasta que llega el registro del acelerometro
	byte registro_control = Wire.read();
	
	//Configuracion del registro CTRL_REG1 del acelerometro
	Wire.write (CTRL_REG1);
	Wire.write (registro_control & ~(0x01));
	
	Wire.endTransmission();
	
}

void active_mode(){
	Wire.beginTransmission(direccion);
	wire.write(CTRL_REG1);
	 //Wire.endTransmission(false);
	Wire.requestFrom(direccion,1);
	
	 while(!Wire.available()) ;  //tiempo de espera hasta que llega el registro del acelerometro
	byte registro_control = Wire.read();
	
	//Configuracion del registro CTRL_REG1 del acelerometro
	Wire.write (CTRL_REG1);
	Wire.write (registro_control | (0x01));
	
	Wire.endTransmission();
	
	
	
	//IIC_RegWrite(CTRL_REG1, (IIC_RegRead(CTRL_REG1) | (0x01)) );
}

void lectura_datos (int *xyz_datos){
	bytes xyz_datos_separados[6];
	Wire beginTransmission(direccion); //Inicio de la transmision
	Wire.requestFrom(direccion, 6); //Se solicitan 6 bytes al esclavo
	while(Wire.available() < 6);	//Tiempo de espera hasta que son mandados
	
	for(int x = 0 ; x < 6 ; x++){	//Lectura de los 6 bytes mandados por el esclavo
		xyz_datos_separados[x] = Wire.read();
	}
	
	for(int x = 0 ; x < 3 ; x++){
		xyz_datos[x]= (xyz_datos_separados[2*x] << 8) |   xyz_datos_separados[2*x +1];
	}	
	
	
	
}