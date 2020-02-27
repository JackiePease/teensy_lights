const ArtNet = require('./lib/artnet');
const SerialPort = require('serialport');

const config = [
    // keep these in order
    {
        fromUniverse: 1,
        toUniverse: 6,
        universeSize: 510,
        serialPort: "/dev/tty.usbmodem14101",
        baudRate: 115200
    }
];

var universes = ['UnIVerSes sTArt aT oNE'];

for(var t = 0; t < config.length; t++){
    tty = config[t];
    
    tty.port = new SerialPort(tty.serialPort,{ baudRate: tty.baudRate });
    tty.port.on('error', function(err) {
        console.log('Error '+tty.serialPort+': ', err.message)
    });
    
    for(var u = tty.fromUniverse; u <= tty.toUniverse; u++){
        universes.push(tty);
    }
}

ArtNet.listen('127.0.0.1', data => {
    
    var firstLight = data.dmx.indexOf(255) / 3;
    
    var tty = universes[data.universe];

    var offset = (data.universe - tty.fromUniverse) * tty.universeSize;

    console.log({u:data.universe, from: tty.fromUniverse, size: tty.universeSize, offset:offset});

    UpdateUniverse(offset, data.dmx, tty.port);

});

function UpdateUniverse(offset, data, port)
{

    data.unshift(offset);
    data.unshift(offset >> 8);
    console.log(toHexString(data));
    console.log();

    port.write(toHexString(data));
    port.write('\n');
}

function toHexString(byteArray) {
    return Array.from(byteArray, function(byte) {
      return ('0' + (byte & 0xFF).toString(16)).slice(-2);
    }).join('')
}

  console.log('waiting');
