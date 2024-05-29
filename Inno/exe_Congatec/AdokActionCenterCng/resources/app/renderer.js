const electron = require("electron");
const remote = require("electron").remote;
const { exec } = require("child_process");
var nodeConsole = require('console');

//const exec = require('child_process').exec;


const dialog = electron.dialog;

var logger = new nodeConsole.Console(process.stdout, process.stderr);
var windowWidth = 280;
var windowHeight = 342;

var buttonBackgroundColor = "#777777";
var buttonBackgroundColorFocused = "#5872ED";
var permitClick = true;
var commandPath ="ResizingNoDamierCng";
var customResizingCmd = "ProjectorResizingCustomCng";




var i = 0;

function delay(ms) {
  var start = new Date().getTime();
  while (new Date().getTime() - start < ms);
}

/*function execute(command, callback) {
  exec(command, (error, stdout, stderr) => { 
      callback(stdout); 
      logger.log('stderr: ' + stderr);
      logger.log('error: ' + error);
  });
};*/

function updatePosition() {
  delay(500);

  const screen = electron.screen.getPrimaryDisplay().workAreaSize;
  var window = remote.getCurrentWindow();
  window.setBounds({
    x: screen.width - 300 - 10,
    y: screen.height - 350 - 10,
    width: 300,
    height: 400,
  });
}

function execResizing(cmd){

  remote.getCurrentWindow().hide();

    exec(cmd, (error, stdout, stderr) => {
    if (error) {
        logger.log(`error: ${error.message}`);
        return;
    }
    if (stderr) {
      logger.log(`stderr: ${stderr}`);
        return;
    }
    

    logger.log(`stdout: ${stdout}`);
  });

}

document.getElementById("exit").addEventListener("click", function (e) {
  remote.getCurrentWindow().hide();
});

document
  .getElementById("left-rotation")
  .addEventListener("click", function (e) {
    i = (i + 270) % 360;
    exec("display.exe /rotate:" + i);

    updatePosition();
  });


document
  .getElementById("right-rotation")
  .addEventListener("click", function (e) {
    i = (i + 90) % 360;
    exec("display.exe /rotate:" + i);

    updatePosition();
  });

document
  .getElementById("inverse-screen")
  .addEventListener("click", function (e) {

    i = (i + 180) % 360;
    exec("display.exe /rotate:" + i);

    updatePosition();
  });


  document
  .getElementById("small-screen")
  .addEventListener("click", function (e) {
      execResizing(commandPath+" 0800");
  });



  document
  .getElementById("medium-screen")
  .addEventListener("click", function (e) {

execResizing(commandPath+" 1000");
  });

  document
  .getElementById("big-screen")
  .addEventListener("click", function (e) {0

    execResizing(commandPath+" 1280");

  });



  document
  .getElementById("custom-resizing")
  .addEventListener("click", function (e) {
      execResizing(customResizingCmd);
  });
  
document
  .getElementById("get-started-button")
  .addEventListener("click", function (e) {
    button = document.getElementById("get-started-button");
    button.disabled = false;
    remote.getCurrentWindow().hide();
    exec("GettingStarted.lnk");
  });

var slider = document.getElementById("myRange");
var output = document.getElementById("demo");
output.innerHTML = slider.value; // Display the default slider value

// Update the current slider value (each time you drag the slider handle)
slider.oninput = function () {
  output.innerHTML = this.value;
} 