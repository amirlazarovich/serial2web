# Serial to web example project
Thanks to [Tomer Weller](https://github.com/tomerweller/serial-to-socketio)!


### Install
```javascript
sudo npm install
```

### Usage
```javascript
node server [options]

options:
-h,--help			 print usage
-p, --port			 set serial port [default: tty.usbserial*]
-b, --baudrate		 set baudrate [default: 9600]
-w, --webport		 set web port [default: 8000]
```

### Example
```javascript 
node server -b 57600 -w 8008
```

###### Note
For some reason the node-serialport library didn't send the first character correctly to the board. I might overseen something - see if you can find my bug :)
As a temporary workaround, I'm prepending a "0" and ignoring it while reading the value from the serial on the board. 