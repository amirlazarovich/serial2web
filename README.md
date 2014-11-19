# serial to web example
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
-p, --port			set serial port [default: tty.usbserial*]
-b, --baudrate		set baudrate [default: 9600]
-w, --webport		 set web port [default: 8000]
```

### Example
```javascript 
node server -b 57600 -w 8008
```