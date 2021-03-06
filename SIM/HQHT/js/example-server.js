
"use strict"; // http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/
var WebSocketServer = require('ws').Server;
var http = require('http');



var BACKEND_STATUS  = 'STATUS: A=1.0, B=[1, 0, 0, 0], C=1.0, D=0.5, E=0.2';
var UI_CONTROL      = 'CONTROL: A=1.0, B=[0, 0, 0, 0], C=1.0';

var BACKEND_KEY     = '00';
var UI_KEY          = '01';

var ChangeBackendStatus   = false;
var ChangeUIControl       = false;

var UIControlDirty        = false;
var BackendStatusDirty    = true;

var server = http.createServer();
var wss = new WebSocketServer({server: server, path: '/foo'});
wss.on('connection', function(ws) {
    console.log('/foo connected');
    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        // console.log('>>> ' + data);

        if (ChangeBackendStatus == true)
        {
          BACKEND_STATUS = data;
          ChangeBackendStatus = false;
          BackendStatusDirty = true;
        }

        if (ChangeUIControl == true)
        {
          UI_CONTROL = data;
          ChangeUIControl = false;
          UIControlDirty = true;
        }

        if (data == 'POST_UI_CONTROL')
        {
          ChangeUIControl = true;
        }
       
        if (data == 'POST_BACKEND_STATUS')
        {
          ChangeBackendStatus = true;
        }

        if (data == 'GET_BACKEND_STATUS' && BackendStatusDirty)
        {
          ws.send(BACKEND_STATUS);
          BackendStatusDirty = false;
        }

        if (data == 'GET_UI_CONTROL' && UIControlDirty) 
        {
          ws.send(UI_CONTROL);
          UIControlDirty = false; 
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
