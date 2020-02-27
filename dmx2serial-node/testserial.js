const SerialPort = require('serialport');
const port = new SerialPort('/dev/tty.usbmodem48204301',{
    baudRate: 9600
  });

/* port.on('error', function(err) {
console.log('Error: ', err.message)
}) */

port.on('data', function (data) {
    console.log('Data:', data.toString())
  })

port.write(Buffer.from([1]));
port.write(Buffer.from([0,4]));

for(var i = 0; i < 100; i++)
{
    port.write(Buffer.from([2,2,55]));
}

port.write(Buffer.from([1]));