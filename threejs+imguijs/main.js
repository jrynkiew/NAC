const { app, BrowserWindow } = require('electron');

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    transparent: true, // Enable transparency
    frame: false, // Remove window frame if desired
    webPreferences: {
      nodeIntegration: true,
      experimentalFeatures: true, // Required for transparency in some cases
    }
  });

  mainWindow.loadFile('index.html');
}

app.whenReady().then(createWindow);