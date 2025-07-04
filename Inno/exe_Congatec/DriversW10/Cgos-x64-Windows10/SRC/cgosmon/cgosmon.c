// cgosmon.c : Defines the entry point for the console application.
//
// Project: 		cgosmon
// Description:	display of CGOS sensor values (temperature, fan, voltage)
// Author:			Michael Schanz
// Date:				04-05-2006
//
// $Id: cgosmon.c,v 1.2 2006/04/10 08:23:59 sml Exp $
#include "OsAL.h"
#include <stdio.h>

#include "Cgos.h"

char buf[512];

#undef TEXT

#ifndef TEXT
#define TEXT(s) s
#endif

void report(char *s)
{
  __report("%s",s);
}

struct sensor {
	char name[32];
	unsigned long value;
};


struct sensor temp_values[8] =
{
	{"CPU temperature" , CGOS_TEMP_CPU },
	{"Box temperature" , CGOS_TEMP_BOX },
	{"Environment temperature" , CGOS_TEMP_ENV },
	{"Board temperature" , CGOS_TEMP_BOARD },
	{"Backplane temperature" , CGOS_TEMP_BACKPLANE },
	{"Chipset temperature" , CGOS_TEMP_CHIPSETS },
	{"Unknown temperature" , CGOS_TEMP_OTHER },
	{"", 0 }
};

struct sensor voltage_values[14] =
{
	{"CPU voltage" , CGOS_VOLTAGE_CPU },
	{"DC  voltage" , CGOS_VOLTAGE_DC },
	{"standby  voltage" , CGOS_VOLTAGE_DC_STANDBY },
	{"battery  voltage" , CGOS_VOLTAGE_BAT_CMOS },
	{"battery  power voltage" , CGOS_VOLTAGE_BAT_POWER },
	{"AC voltage" , CGOS_VOLTAGE_AC },
	{"unknown" , CGOS_VOLTAGE_OTHER },
	{"5V supply voltage (5V_S0)" , CGOS_VOLTAGE_5V_S0 },
	{"5V standby voltage (5V_S5)" , CGOS_VOLTAGE_5V_S5 },
	{"3.3V supply voltage (3V_S0)" , CGOS_VOLTAGE_33V_S0 },
	{"3.3V standby voltage (3V_S5)" , CGOS_VOLTAGE_33V_S5 },
	{"core A voltage" , CGOS_VOLTAGE_VCOREA },
	{"core B voltage" , CGOS_VOLTAGE_VCOREB },
	{"", 0 }
};

struct sensor fan_values[7] =
{
	{"CPU fan" , CGOS_FAN_CPU },
	{"Box fan" , CGOS_FAN_BOX },
	{"Environment fan" , CGOS_FAN_ENV },
	{"Chipset fan" , CGOS_FAN_CHIPSET },
	{"Video fan" , CGOS_FAN_VIDEO },
	{"Unknown fan" , CGOS_FAN_OTHER },
	{"", 0 }
};

int main(int argc, char* argv[])
{
	HCGOS hCgos = 0;
	static CGOSTEMPERATUREINFO temperatureInfo = {0};
	static CGOSVOLTAGEINFO voltageInfo = {0};
	static CGOSFANINFO fanInfo = {0};
	unsigned long dwUnit, setting, status, monCount = 0;
	unsigned long dwLibVersion, dwDrvVersion;
	int i;
	unsigned int val_hi, val_lo;

	// install the library
	if (!CgosLibInitialize())
	{
		if (!CgosLibInstall(1))
		{
			// error: can't install cgos library
			report(TEXT("Error: can't install CGOS library\n"));
			return (-1);
		}
    report(TEXT("The driver has been installed.\n"));
    if (!CgosLibInitialize()) {
      report(TEXT("Still could not open driver, a reboot might be required!\n"));
      return (-1);
      }		
	}
	
	//check library version
	dwLibVersion = CgosLibGetVersion();
	dwDrvVersion = CgosLibGetDrvVersion();
	
	if ( dwLibVersion < 0x0102000A || dwDrvVersion < 0x0102000A )
	{
		sprintf(buf,
		  TEXT("Error: outdated CGOS Library/Driver version.\n")
			TEXT("detected library version: 0x%08lx\n")
			TEXT("required library version: 0x0102000A\n")
			TEXT("detected driver  version: 0x%08lx\n")
			TEXT("required driver  version: 0x0102000A\n"),
			dwLibVersion,
			dwDrvVersion
			);
		report(buf);
	  CgosBoardClose(hCgos);
	  return(-1);
	}  

	
    // open the cgos board
    if (CgosBoardOpen(0,0,0,&hCgos))
    {
	    report(TEXT("Temperature sensors\n"));
			report(TEXT("===================\n"));

			temperatureInfo.dwSize = sizeof (temperatureInfo);
			monCount = CgosTemperatureCount(hCgos);

			if(monCount != 0)
  	  	{
    	  for(dwUnit = 0; dwUnit < monCount; dwUnit++)
      	  {
            if(CgosTemperatureGetInfo(hCgos, dwUnit, &temperatureInfo))
            {
            	 if(CgosTemperatureGetCurrent(hCgos, dwUnit, &setting, &status))
            	 {
					//scan type
					i=0;
					while (temp_values[i].value !=0)
					{
						if (temperatureInfo.dwType == temp_values[i].value)
							break;
						i++;
					}

					temperatureInfo.dwMin = (long) temperatureInfo.dwMin / 1000;
					temperatureInfo.dwMax /= 1000L;
					setting = (long) setting / 1000;

					sprintf(buf,TEXT("Type of sensor:      %s\n"),temp_values[i].name); report(buf);				
	 				sprintf(buf,TEXT("Unit number:         %d\n"),dwUnit); report(buf);
	 				sprintf(buf,TEXT("Resolution:          %d\n"),temperatureInfo.dwRes); report(buf);
	 				sprintf(buf,TEXT("Minimum temperature: %d degrees centigrade\n"),temperatureInfo.dwMin); report(buf);
	 				sprintf(buf,TEXT("Maximum temperature: %d degrees centigrade\n"),temperatureInfo.dwMax); report(buf);
	 				sprintf(buf,TEXT("Current temperature: %d degrees centigrade\n"),setting); report(buf);
	 				getchar();
                 }
            }
          }          
    	  }

		report(TEXT("\n"));
		report(TEXT("Voltage sensors\n"));
		report(TEXT("===============\n"));

		voltageInfo.dwSize = sizeof (voltageInfo);
		monCount = CgosVoltageCount(hCgos);

		if(monCount != 0)
  	  	{
    	  for(dwUnit = 0; dwUnit < monCount; dwUnit++)
      	  {
            if(CgosVoltageGetInfo(hCgos, dwUnit, &voltageInfo))
            {
            	 if(CgosVoltageGetCurrent(hCgos, dwUnit, &setting, &status))
            	 {
					//scan type
					i=0;
					while (voltage_values[i].value !=0)
					{
						if (voltageInfo.dwType == voltage_values[i].value)
							break;
						i++;
					}

					sprintf(buf,TEXT("Type of sensor:      %s\n"),voltage_values[i].name); report(buf);	
	 				sprintf(buf,TEXT("Unit number:         %d\n"),dwUnit); report(buf);
	 				sprintf(buf,TEXT("Resolution:          %d\n"),voltageInfo.dwRes); report(buf);

					if ( voltageInfo.dwNom == -1)
		 				report(TEXT("Nominal voltage:     -1\n"));
					else
					{
						val_hi = voltageInfo.dwNom / 1000;
						val_lo = voltageInfo.dwNom % 1000;
	 					sprintf(buf,TEXT("Nominal voltage:     %d.%d V\n"),val_hi,val_lo); report(buf);
					}

					val_hi = voltageInfo.dwMin / 1000;
					val_lo = voltageInfo.dwMin % 1000;
	 				sprintf(buf,TEXT("Minimum voltage:     %d.%d V\n"),val_hi,val_lo); report(buf);

					val_hi = voltageInfo.dwMax / 1000;
					val_lo = voltageInfo.dwMax % 1000;
	 				sprintf(buf,TEXT("Maximum voltage:     %d.%d V\n"),val_hi,val_lo); report(buf);

					val_hi = setting / 1000;
					val_lo = setting % 1000;
	 				sprintf(buf,TEXT("Current voltage:     %d.%d V\n"),val_hi,val_lo); report(buf);
	 				getchar();
                 }
            }
          }          
    	  }

		report(TEXT("\n"));
		report(TEXT("Fan sensors\n"));
		report(TEXT("===========\n"));

		fanInfo.dwSize = sizeof (fanInfo);
		monCount = CgosFanCount(hCgos);

		if(monCount != 0)
  	  	{
    	  for(dwUnit = 0; dwUnit < monCount; dwUnit++)
      	  {
            if(CgosFanGetInfo(hCgos, dwUnit, &fanInfo))
            {
            	 if(CgosFanGetCurrent(hCgos, dwUnit, &setting, &status))
            	 {
					//scan type
					i=0;
					while (fan_values[i].value !=0)
					{
						if (fanInfo.dwType == fan_values[i].value)
							break;
						i++;
					}

					sprintf(buf,TEXT("Type of sensor:      %s\n"),fan_values[i].name); report(buf);
	 				sprintf(buf,TEXT("Unit number:         %d\n"),dwUnit); report(buf);

					if ( fanInfo.dwSpeedNom == -1)
		 				sprintf(buf,TEXT("Nominal speed:       -1\n"));
					else
						sprintf(buf,TEXT("Nominal speed:       %d rpm\n"),fanInfo.dwSpeedNom);
					report(buf);

	 				sprintf(buf,TEXT("Minimum speed:       %d rpm\n"),fanInfo.dwMin); report(buf);
	 				sprintf(buf,TEXT("Maximum speed:       %d rpm\n"),fanInfo.dwMax); report(buf);
	 				sprintf(buf,TEXT("Current speed:       %d rpm\n"),setting); report(buf);
	 				getchar();
                 }
            }
          }          
    	  }

  }
  else
  {
	// error: can't open board
	report(TEXT("Error: can't open CGOS board\n"));
	return (-1);
  }	
	   
  CgosBoardClose(hCgos);

  return 0;
}


