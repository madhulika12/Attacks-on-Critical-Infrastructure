#define FORLINUX

#include "modbus.h"
#include "modbus_attack.h"

int main(int argc, char *argv[]){

  unsigned char addr, fc, data[256], crc[2];
  int datalen;
  char inport[100], outport[100];
  int i, j, len, err;
  int port;
  struct modbus_pdu *pdu;
  int cnt = 0x0;
  
  strcpy(inport, "/dev/ttyUSB0");
  strcpy(outport, "/dev/ttyUSB2");
  
  for(i=1; i<argc; i++){
    if(strcmp(argv[i], "-inport") == 0){
      len = strlen(argv[i+1]);
      if(len > 100){
        printf("Error: Port name must be less than 100 characters long.\n");
        return(-1);
      }
      strncpy(inport, argv[i+1], len);
      i++;
      printf("INFO: Input port = %s\n", inport);
    } else if(strcmp(argv[i], "-outport") == 0){
      len = strlen(argv[i+1]);
      if(len > 100){
        printf("Error: Port name must be less than 100 characters long.\n");
        return(-1);
      }
      strncpy(outport, argv[i+1],len);
      i++;      
    }else{
      printf("ERROR: Illegal arguments (%s)\n", argv[i]);
      printf("Usage: %s -inport /dev/ttyXX -outport /dev/ttyYY\n", argv[0]);
      return (-1);
    }
  }
   
  port = openport(outport);
  if(port < 0)
    return (port);
  printf("open %s ok port = %d\n", outport, port);
  
  char *str;
  unsigned char lrc, top, bottom;
  addr = (unsigned char) 0x4; 

  //fc =0x01 read coil, not implement excode = 01
  for(cnt=0x0; cnt<0x14; cnt++){
  fc = (unsigned char)cnt;
  datalen = 4;
  data[0] = 0x0b;
  data[1] = 0xb7;
  data[2] = 0x00;
  data[3] = 0x09;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);     
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  sendmodbus_ascii(port, pdu);
  freepdu(pdu);
  printf("number is %d\n", cnt);
  sleep(5);
}
  //fc = 0x02 Read Discrete Inputs, not implement excode = 01
/*  fc = 0x02;
  datalen = 4;
  data[0] = 0x0b;
  data[1] = 0xb7;
  data[2] = 0x00;
  data[3] = 0x09;
  
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  freepdu(pdu);
  printf("number is %d\n", cnt++);
  usleep(10000);
  
  //fc = 0x03 Read Holding Registers, not implement excode = 01
  fc = 0x03;
  datalen = 4;
  data[0] = 0x0b;
  data[1] = 0xb7;
  data[2] = 0x00;
  data[3] = 0x09;

  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;
  
  pdu = mkpdu(addr, fc, data, datalen, crc);
  freepdu(pdu);
  printf("numb is %d\n", cnt++);
  usleep(10000);

  //fc = 0x04 Read Input Registers, not implement excode = 01
  fc = 0x04;
  datalen = 4;
  data[0] = 0x0b;
  data[1] = 0xb7;
  data[2] = 0x00;
  data[3] = 0x09;
  
  str = malloc(datalen+2);
  str[0] = addr;
  str[1] = fc;
  memcpy(str+2, data, datalen);
  lrc = LRC(str, datalen+2);
  free(str);
  byte2ascii(lrc, &top, &bottom);
  crc[0] = top;
  crc[1] = bottom;

  pdu = mkpdu(addr, fc, data, datalen, crc);
  freepdu(pdu);
  printf("number is %d\n", cnt++);
  usleep(10000);

  //fc = 0x05 
  */ 
}
