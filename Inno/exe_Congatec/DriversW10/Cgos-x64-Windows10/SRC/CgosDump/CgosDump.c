// CgosDump.c
// CGOS API Info Dump Utility
// {G)U(2} 2005.05.23

//***************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Cgos.h"

//***************************************************************************

#ifndef TEXT
#define TEXT(s) s
#endif

//***************************************************************************

HCGOS hCgos=0;

//***************************************************************************

void report(char *s)
  {
  printf("%s\n",s);
  }

unsigned int proceed(void)
  {
  fgetc(stdin);
  return 1;
  }

//***************************************************************************

#include "CgosRprt.c"

//***************************************************************************

int main(int argc, char* argv[])
  {
  report(TEXT("CgosDump"));
  Init();
  if (!CgosBoardOpen(0,0,0,&hCgos)) {
    report(TEXT("Could not open a board"));
    }
  else
    DumpAll();
  if (hCgos) CgosBoardClose(hCgos);
  CgosLibUninitialize();
  report(TEXT("Done"));
  return 0;
  }

//***************************************************************************
