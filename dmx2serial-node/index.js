const ArtNet = require('./lib/artnet');
const SerialPort = require('serialport');

const config = [
    {
        fromUniverse: 1,
        toUniverse: 6,
        serialPort: "/dev/tty.usbmodem48204301",
        baudRate: 9600
    }
];

var universes = [];

var currentConfig = null
for(var u = 1; currentConfig == null || u < currentConfig.fromUniverse; u++){
    //
}

ArtNet.listen('127.0.0.1', data => {
    
    var firstLight = data.dmx.indexOf(255) / 3;

    console.log({
        s:data.sequence,
        u:data.universe,
        l:data.length,
        o: firstLight > 0 ? firstLight : 0  // offset
    });
    

    //if (data.universe === options.universe) {
    //  this._updateLights(data.dmx, options);
    //}
  });

  console.log('waiting');