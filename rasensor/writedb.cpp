#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <mysql/mysql.h>

#include <time.h>
#include <math.h>

#define CS_MCP3208  8        // BCM_GPIO_8

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000   // 1MHz

#define VCC         4.8       // Supply Voltage

#define DBHOST "라즈베리파이IP"
#define DBUSER "root"
#define DBPASS "디비비번"
#define DBNAME "디비이름"

MYSQL *connector;
MYSQL_RES *result;
MYSQL_ROW row;

int read_mcp3208_adc(unsigned char adcChannel)
{
  unsigned char buff[3];
  int adcValue = 0;

  buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
  buff[1] = ((adcChannel & 0x07) << 6);
  buff[2] = 0x00;

  digitalWrite(CS_MCP3208, 0);  // Low : CS Active

  wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

  buff[1] = 0x0F & buff[1];
  adcValue = ( buff[1] << 8) | buff[2];

  digitalWrite(CS_MCP3208, 1);  // High : CS Inactive

  return adcValue;
}


int main (void)
{
  int adcChannel  = 0;
  int adcValue[8] = {0};

  if(wiringPiSetupGpio() == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    return 1 ;
  }

  if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
  {
    fprintf (stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));
    return 1 ;
  }

  pinMode(CS_MCP3208, OUTPUT);

  // MySQL connection
  connector = mysql_init(NULL);
  if (!mysql_real_connect(connector, DBHOST, DBUSER, DBPASS, DBNAME, 3306, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(connector));
    return 0;
  }

  printf("MySQL(rpidb) opened.\n");

  while(1)
  {
    char query[1024];

    adcValue[0] = read_mcp3208_adc(0); // Temperature Sensor
    adcValue[0] = ((adcValue[0] * VCC / 4095 - (0.1 * VCC))/(0.8 * VCC)) * 200 - 50;

    adcValue[1] = read_mcp3208_adc(1); // Humidity Sensor
    adcValue[1] = ((adcValue[1] * VCC / 4095 - (0.1 * VCC))/(0.8 * VCC)) * 100;

    adcValue[2] = read_mcp3208_adc(2); // Illuminance Sensor
    adcValue[3] = read_mcp3208_adc(3); // Mic Sensor
    adcValue[4] = read_mcp3208_adc(4); // Flame Sensor
    adcValue[5] = read_mcp3208_adc(5); // Acceleration Sensor (Z-Axis)
    adcValue[6] = read_mcp3208_adc(6); // Gas Sensor
    adcValue[7] = read_mcp3208_adc(7); // Distace Sensor
    adcValue[7] = 27*pow((double)(adcValue[7]*VCC/4095), -1.10);

    sprintf(query,"insert into envdata values (now(),%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
      adcValue[0],adcValue[1],adcValue[2],adcValue[3],adcValue[4],
      0,0,adcValue[5],adcValue[6],adcValue[7],0);

    if(mysql_query(connector, query))
    {
      fprintf(stderr, "%s\n", mysql_error(connector));
      printf("Write DB error\n");
    }

    delay(1000); //1sec delay
  }

  mysql_close(connector);

  return 0;
}
