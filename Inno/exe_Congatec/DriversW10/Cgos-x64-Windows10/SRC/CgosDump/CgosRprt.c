// CgosRprt.c
// CGOS Report Helper Functions
// {G)U(2} 2005.04.29

//***************************************************************************

char buf[512];

//***************************************************************************

unsigned long Init(void)
  {
  if (!CgosLibInitialize()) {
    if (!CgosLibInstall(1)) {
      report(TEXT("The driver could not be installed. Check your rights!"));
      return 0;
      }
    report(TEXT("The driver has been installed."));
    if (!CgosLibInitialize()) {
      report(TEXT("Still could not open driver, a reboot might be required!"));
      return 0;
      }
    }
  report(TEXT("CgosLibInitialize successful"));
  return 0;
  }

//***************************************************************************

void LibInfo(void)
  {
  sprintf(buf,
    TEXT("CGOS Library Version: 0x%08lx\n")
    TEXT("CGOS Driver Version: 0x%08lx\n")
    TEXT("Total number of available boards: %lu\n")
    TEXT("Number of primary CPU boards: %lu\n")
    TEXT("Number of primary VGA boards: %lu\n")
    TEXT("Number of boards with CPU functionality: %lu\n")
    TEXT("Number of boards with VGA functionality: %lu\n"),
    CgosLibGetVersion(),
    CgosLibGetDrvVersion(),
    CgosBoardCount(0,0),
    CgosBoardCount(CGOS_BOARD_CLASS_CPU,CGOS_BOARD_OPEN_FLAGS_PRIMARYONLY),
    CgosBoardCount(CGOS_BOARD_CLASS_VGA,CGOS_BOARD_OPEN_FLAGS_PRIMARYONLY),
    CgosBoardCount(CGOS_BOARD_CLASS_CPU,0),
    CgosBoardCount(CGOS_BOARD_CLASS_VGA,0)
    );
  report(buf);
  }

//***************************************************************************

void BoardNames(void)
  {
  unsigned long nBoards;
  unsigned long iBoard;
  HCGOS hCgos;

  // Enumerate Boards
  nBoards=CgosBoardCount(0,0);
  for (iBoard=0; iBoard<nBoards; iBoard++) {
    if (!CgosBoardOpen(0,iBoard,0,&hCgos)) {
      report(TEXT("Could not open board"));
      }
    else {
      char s[CGOS_BOARD_MAX_SIZE_ID_STRING];
      if (!CgosBoardGetNameA(hCgos,s,sizeof(s))) {
        report(TEXT("Could not get board name"));
        }
      sprintf(buf,TEXT("Board Name #%lu: \"%s\""),iBoard,s);
      report(buf);
      }
    CgosBoardClose(hCgos);
    }
  }

char *ClassString(unsigned long dwClass, char *szClass)
  {
  char *names[]={"CPU","VGA","IO",NULL};
  char **name=names;
  *szClass=0;
  while (*name) {
    if (dwClass&1) {
      if (*szClass) strcat(szClass,",");
      strcat(szClass,*name);
      }
    dwClass>>=1;
    name++;
    }
  return szClass;
  }

void BoardInfo(void)
  {
  CGOSBOARDINFOA bi;
  char s[16],ss[64];
  bi.dwSize=sizeof(bi);
  if (!CgosBoardGetInfoA(hCgos, &bi)) {
    report(TEXT("Could not get board info"));
    return;
    }
  sprintf(buf,
    TEXT("Board info\n")
    TEXT("Size of Structure: %lu\n")
    TEXT("Flags: 0x%lx\n")
    TEXT("Primary Class Name: \"%s\"\n")
    TEXT("Class Names: \"%s\"\n")
    TEXT("Board Name: \"%s\"\n")
    TEXT("Board Sub Name: \"%s\"\n")
    TEXT("Manufacturer Name: \"%s\"\n")
    TEXT("Manufacturer Code: %lu\n")
    TEXT("Manufacturing Date: %04d.%02d.%02d\n")
    TEXT("Last Repair Date: %04d.%02d.%02d\n")
    TEXT("Repair Counter: %lu\n")
    TEXT("Serial Number: \"%s\"\n")
    TEXT("Part Number: \"%s\"\n")
    TEXT("EAN: \"%s\"\n")
    TEXT("Product Revision: %c.%c (0x%04x)\n")
    TEXT("System BIOS Revision: %03x\n")
    TEXT("BIOS Interface Revision: %03x\n")
    TEXT("BIOS Interface Build Revision: %03x\n"),
    bi.dwSize,
    bi.dwFlags,
    ClassString(bi.dwPrimaryClass,s),
    ClassString(bi.dwClasses,ss),
    bi.szBoard,
    bi.szBoardSub,
    bi.szManufacturer,
    bi.dwManufacturer,
    bi.stManufacturingDate.wYear,bi.stManufacturingDate.wMonth,bi.stManufacturingDate.wDay,
    bi.stLastRepairDate.wYear,bi.stLastRepairDate.wMonth,bi.stLastRepairDate.wDay,
    bi.dwRepairCounter,
    bi.szSerialNumber,
    bi.szPartNumber,
    bi.szEAN,
    bi.wProductRevision>>8,
    bi.wProductRevision&0xff,
    bi.wProductRevision,
    bi.wSystemBiosRevision,
    bi.wBiosInterfaceRevision,
    bi.wBiosInterfaceBuildRevision
    );
  report(buf);
  }

void BoardCounts(void)
  {
  char szBoardName[CGOS_BOARD_MAX_SIZE_ID_STRING];
  unsigned long dwBootCounter;
  unsigned long dwRunningTime;

  sprintf(buf,
    TEXT("Board is named: \"%s\"\n")
    TEXT("Boot Counter: %d\n")
    TEXT("Running Time Meter: %d hours\n")
    TEXT("Number of VGAs: %lu\n")
    TEXT("Number of Storage Areas: %lu\n")
    TEXT("Number of I2C Buses: %lu\n")
    TEXT("Number of Digital IOs: %lu\n")
    TEXT("Number of Watchdogs: %lu\n")
    TEXT("Number of Temp Sensors: %lu\n")
    TEXT("Number of Fans: %lu\n")
    TEXT("Number of Voltage Sensors: %lu\n"),
    CgosBoardGetNameA(hCgos,szBoardName,sizeof(szBoardName))?szBoardName:TEXT("?"),
    CgosBoardGetBootCounter(hCgos,&dwBootCounter)?(int)dwBootCounter:-1,
    CgosBoardGetRunningTimeMeter(hCgos,&dwRunningTime)?(int)dwRunningTime:-1,
    CgosVgaCount(hCgos),
    CgosStorageAreaCount(hCgos,0),
    CgosI2CCount(hCgos),
    CgosIOCount(hCgos),
    CgosWDogCount(hCgos),
    CgosTemperatureCount(hCgos),
    CgosFanCount(hCgos),
    CgosVoltageCount(hCgos)
    );
  report(buf);
  }

//***************************************************************************

void StorageAreaInfo(unsigned long dwType)
  {
  sprintf(buf,
    TEXT("Storage Area: %lu ")
    TEXT("Type: 0x%08lx ")
    TEXT("Size: %8lu ")
    TEXT("Block Size: %8lu"),
    dwType,
    CgosStorageAreaType(hCgos,dwType),
    CgosStorageAreaSize(hCgos,dwType),
    CgosStorageAreaBlockSize(hCgos,dwType)
    );
  report(buf);
  }

void StorageAreaInfoList(unsigned long dwType)
  {
  unsigned long cnt;
  if (dwType) {
    StorageAreaInfo(dwType);
    return;
    }
  cnt=CgosStorageAreaCount(hCgos,0);
  sprintf(buf,
    TEXT("Number of Storage Areas: %lu"),
    cnt
    );
  report(buf);

  for (dwType=0; dwType<cnt; dwType++)
    StorageAreaInfo(dwType);
  }

//***************************************************************************

void I2CInfo(unsigned long dwType)
  {
  sprintf(buf,
    TEXT("I2C Bus: %lu ")
    TEXT("Type: 0x%08lx"),
    dwType,
    CgosI2CType(hCgos,dwType)
    );
  report(buf);
  }

void I2CInfoList(unsigned long dwType)
  {
  unsigned long cnt;
  if (dwType) {
    I2CInfo(dwType);
    return;
    }
  cnt=CgosI2CCount(hCgos);
  sprintf(buf,
    TEXT("Number of I2C Buses: %lu"),
    cnt
    );
  report(buf);

  for (dwType=0; dwType<cnt; dwType++)
    I2CInfo(dwType);
  }

//***************************************************************************

void WDogInfo(unsigned long dwType)
  {
  CGOSWDINFO info;
  CGOSWDCONFIG config;
  unsigned long i;
//  if (!CgosWDogIsAvailable(hCgos,dwType)) return;
  info.dwSize=sizeof(info);
  if (CgosWDogGetInfo(hCgos,dwType,&info)) {
    sprintf(buf,
      TEXT("Watchdog Info for: %lu\n")
      TEXT("Size of Structure: %lu\n")
      TEXT("Flags: 0x%lx\n")
      TEXT("Min Timeout: %lu\n")
      TEXT("Max Timeout: %lu\n")
      TEXT("Min Delay: %lu\n")
      TEXT("Max Delay: %lu\n")
      TEXT("Supported OpModes: 0x%lx\n")
      TEXT("Max Stage Count: %lu\n")
      TEXT("Supported Events: 0x%lx\n")
      TEXT("Type: 0x%08lx\n"),
      dwType,
      info.dwSize,
      info.dwFlags,
      info.dwMinTimeout,
      info.dwMaxTimeout,
      info.dwMinDelay,
      info.dwMaxDelay,
      info.dwOpModes,
      info.dwMaxStageCount,
      info.dwEvents,
      info.dwType
      );
    report(buf);
    }
  config.dwSize=sizeof(config);
  if (CgosWDogGetConfigStruct(hCgos,dwType,&config)) {
    sprintf(buf,
      TEXT("Watchdog Config for: %lu\n")
      TEXT("Size of Structure: %lu\n")
      TEXT("Timeout: %lu\n")
      TEXT("Delay: %lu\n")
      TEXT("Mode: 0x%lx\n")
      TEXT("OpMode: 0x%lx\n")
      TEXT("Stage Count: %lu\n"),
      dwType,
      config.dwSize,
      config.dwTimeout,
      config.dwDelay,
      config.dwMode,
      config.dwOpMode,
      config.dwStageCount
      );
    report(buf);
    for (i=0; i<config.dwStageCount; i++) {
      sprintf(buf,
        TEXT("Stage: %lu\n")
        TEXT("  Timeout: %lu\n")
        TEXT("  Event: 0x%lx\n"),
        i,
        config.stStages[i].dwTimeout,
        config.stStages[i].dwEvent
        );
      report(buf);
      }
    }
  }

//***************************************************************************

void DumpAll(void)
  {
  LibInfo();
  if (!proceed()) return;
  BoardNames();
  if (!proceed()) return;
  BoardInfo();
  if (!proceed()) return;
  BoardCounts();
  if (!proceed()) return;
  StorageAreaInfoList(0);
  if (!proceed()) return;
  I2CInfoList(0);
  if (!proceed()) return;
  WDogInfo(0);
  if (!proceed()) return;
  }

//***************************************************************************
