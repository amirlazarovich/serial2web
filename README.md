# Serial to web
Sample code for AVR serial, web server and a web socket

Thanks to [Tomer Weller](https://github.com/tomerweller/serial-to-socketio)!


### Install
```javascript
sudo npm install
```

### Usage
```javascript
node app [options]

options:
-h,--help			 print usage
-p, --port			 set serial port [default: tty.usb*]
-b, --baudrate		 set baudrate [default: 9600]
-w, --webport		 set web port [default: 8000]
-no-prepend			 disable character prepending
```

### Example
```javascript 
node app
```

###### Note
For some reason the arduino serial library doesn't read a single character correctly. I might have overseen something - see if you can find my bug :)
As a temporary workaround, I'm prepending a "0" and ignoring it while reading the value from the serial on the board. If this doesn't happen to you, use the -no-prepend argument. 