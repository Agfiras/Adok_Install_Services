
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Adok Install Services"
#define MyAppPublisher "Adok SAS"
#define MyAppURL "https://www.getadok.com/"
#define MyAppVersion "1.0.0"
[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{17D6DFC3-FD08-4BA0-9901-B484F0AF2429}}
AppName={#MyAppName}
PrivilegesRequired=admin
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
ArchitecturesAllowed=x64
Uninstallable=yes
AlwaysRestart=yes
SetupIconFile=Setup_ico.ico

OutputBaseFilename=Adok Install Services
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Files]
Source: "exe_Congatec\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{commonstartup}\Adok Action Centre"; Filename: "{app}\AdokActionCenterCng\AdokActionCenter.exe"
Name: "{commonstartup}\Adok Batt"; Filename: "{app}\AdokBatteryIconCng\AdokBatteryIconCng.exe"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{group}\Calib Usine"; Filename: "{app}\Calibration USINE Cng\CalibrationUsineCng.exe"; WorkingDir: "{app}\Calibration USINE Cng"; 
Name: "{group}\ROICalibration"; Filename: "{app}\ROICalibrationV3\ROICalibrationV3.exe"; WorkingDir: "{app}\ROICalibrationV3";


[Run]
Filename: "{app}\AdokWindowsShutdownCng\installutil.exe"; Parameters: "/LogToConsole=false ""{app}\AdokWindowsShutdownCng\AdokWindowsShutdownCng.exe"""; Flags: runhidden postinstall waituntilterminated; Description: "Install Adok ShutDown Service"
Filename: "{app}\AdokStartControlCng\installutil.exe"; Parameters: "/LogToConsole=false ""{app}\AdokStartControlCng\AdokStartControlCng.exe"""; Flags: runhidden postinstall waituntilterminated; Description: "Install Adok Start Control Service"
Filename: "{app}\DriversW10\CgbcSer\setup.exe"; WorkingDir: "{app}\DriversW10\CgbcSer"; Flags: runminimized  postinstall waituntilterminated; Description: "Run setup CgbcSer"
Filename: "{app}\DriversW10\Cgos-x64-Windows10\InstallCGOS.bat"; WorkingDir: "{app}\DriversW10\Cgos-x64-Windows10"; Flags: runminimized postinstall waituntilterminated; Description: "Run InstallCgos"
Filename: "{app}\DriversW10\Intel_drivers_support\SetupChipset.exe"; WorkingDir: "{app}\DriversW10\Intel_drivers_support"; Flags: runminimized postinstall waituntilterminated; Description: "Run Intel driver"

