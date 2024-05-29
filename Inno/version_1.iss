
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
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf64}\{#MyAppName}
DefaultGroupName={#MyAppName}
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
Uninstallable=yes
SetupIconFile=Setup_ico.ico
OutputBaseFilename=Adok Install Services
Compression=lzma
SolidCompression=yes
WizardStyle=modern
AlwaysRestart = yes
UninstallFilesDir={app}\Uninstall
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Files]
; Source and destination of files to be installed

Source: "exe_Congatec\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs;

[Icons]
; Create shortcuts in the start menu and startup folder

Name: "{commonstartup}\Adok Action Centre"; Filename: "{app}\AdokActionCenterCng\AdokActionCenter.exe"
Name: "{commonstartup}\Adok Batt"; Filename: "{app}\AdokBatteryIconCng\AdokBatteryIconCng.exe"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\Calib Usine"; Filename: "{app}\Calibration USINE Cng\CalibrationUsineCng.exe"; WorkingDir: "{app}\Calibration USINE Cng"; 
Name: "{group}\ROICalibration"; Filename: "{app}\ROICalibrationV3\ROICalibrationV3.exe"; WorkingDir: "{app}\ROICalibrationV3";
[Code]
procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
begin
  if CurStep = ssPostInstall then
  begin
    // Execute each step in sequence, checking for success before proceeding to the next step
    if Exec(ExpandConstant('{app}\AdokWindowsShutdownCng\installutil.exe'), 
            '/LogToConsole=false "' + ExpandConstant('{app}\AdokWindowsShutdownCng\AdokWindowsShutdownCng.exe') + '"', 
            '', SW_HIDE, ewNoWait, ResultCode) then
    begin
      if Exec(ExpandConstant('{app}\AdokStartControlCng\installutil.exe'), 
              '/LogToConsole=false "' + ExpandConstant('{app}\AdokStartControlCng\AdokStartControlCng.exe') + '"', 
              '', SW_HIDE, ewNoWait, ResultCode) then
      begin
      if Exec(ExpandConstant('{app}\DriversW10\Cgos-x64-Windows10\InstallCGOS.bat'), '', 
                  ExpandConstant('{app}\DriversW10\Cgos-x64-Windows10'), SW_SHOW, ewWaitUntilTerminated, ResultCode) then
      begin
        if Exec(ExpandConstant('{app}\DriversW10\CgbcSer\setup.exe'), '', 
                ExpandConstant('{app}\DriversW10\CgbcSer'), SW_SHOW, ewWaitUntilTerminated, ResultCode) then
          
          begin
            Exec(ExpandConstant('{app}\DriversW10\Intel_drivers_support\SetupChipset.exe'), '', 
                 ExpandConstant('{app}\DriversW10\Intel_drivers_support'), SW_SHOW, ewWaitUntilTerminated, ResultCode);
          end;
        end;
      end;
    end;
  end;
  end;

  [UninstallRun]
; Commands to run during uninstallation to stop and delete services and kill processes

Filename: {sys}\sc.exe; Parameters: "stop AdokWindowsShutdownService" ; Flags: runhidden
Filename: {sys}\sc.exe; Parameters: "delete AdokWindowsShutdownService" ; Flags: runhidden

Filename: {sys}\sc.exe; Parameters: "stop AdokStartControlService" ; Flags: runhidden
Filename: {sys}\sc.exe; Parameters: "delete AdokStartControlService" ; Flags: runhidden

Filename: {sys}\taskkill.exe; Parameters: "/F /IM AdokActionCenter.exe"; Flags: runhidden
Filename: {sys}\taskkill.exe; Parameters: "/F /IM AdokBatteryIconCng.exe"; Flags: runhidden
