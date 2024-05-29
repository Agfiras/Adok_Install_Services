const electron = require('electron');
const { app, BrowserWindow } = electron;
const Tray = electron.Tray;
let tray;
let win;

var windowWidth = 300;//400;
var windowHeight = 400;//700;

app.on('ready', () => {
	tray = new Tray(__dirname + "/res/tray.png");

	const screen = electron.screen.getPrimaryDisplay().workAreaSize;

	win = new BrowserWindow({
		x: screen.width - windowWidth - 10,
		y: screen.height - windowHeight - 10,
		width: windowWidth,
		height: windowHeight,
		frame: false,
		show: false,
		alwaysOnTop: true,
		resizable: false,
		skipTaskbar: true,
		icon: "res/ADOK.png"
	});

	win.loadFile('src/index.html');
	win.once('ready-to-show', () => {
		//win.hide();
		//win.show()
	});

	console.log("Start");

	tray.on("click", () => {
		if (win.isVisible())
			win.hide();
		else
			win.show();
	})
})
