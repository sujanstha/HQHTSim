

"use strict"; // http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/
var WebSocketServer = require('ws').Server;
var http = require('http');

var BACKEND_STATUS  = 'STATUS: A=1.0, B=[1, 0, 0, 0], C=1.0, D=0.5, E=0.2';
var UI_CONTROL      = 'CONTROL: A=1.0, B=[1, 0, 0, 0], C=1.0';

var ChangeBackendStatus = false;

var server = http.createServer();
var wss = new WebSocketServer({server: server, path: '/foo'});
wss.on('connection', function(ws) {
    console.log('/foo connected');
    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        console.log('>>> ' + data);
        if (data == 'goodbye') { console.log('<<< galaxy'); ws.send('galaxy'); }
        if (data == 'hello') { console.log('<<< world'); ws.send('world'); }

        if (ChangeBackendStatus == true)
        {
          BACKEND_STATUS = data;
          ChangeBackendStatus = false;
          ws.send(BACKEND_STATUS); 
        }

        if (data == 'GET_BACKEND_STATUS')
        {
          ws.send(BACKEND_STATUS);
        }
       
        if (data == 'POST_BACKEND_STATUS')
        {
          ChangeBackendStatus = true;
        }

        if (data == 'GET_UI_CONTROL') 
        {
          ws.send(STATUS); 
        }

        if (data == 'POST_UI_CONTROL')
        {
          UI_CONTROL = data;
        }

    });
    ws.on('close', function() {
      console.log('Connection closed!');
    });
    ws.on('error', function(e) {
    });
});
server.listen(8126);
console.log('Listening on port 8126...');
