var socket;
var STATUS;
try{
var host = "ws://localhost:8126/foo";
socket = new WebSocket(host);

message('Socket Status: '+socket.readyState);

socket.onopen = function(){
		 message('Socket Status: '+socket.readyState+' (open)');
		 socket.send("hello");
}

socket.onmessage = function(msg){
		 message('Received: '+msg.data);
		 var rawData = msg.data.replace(/\s/g, "").replace('STATUS:', '');
		 var json = '{"'+rawData[0] + '":' + rawData.substring(2,5) + ',"' +  rawData[6] + '":' + rawData.substring(8, 17) + ',"' + rawData[18] + '":' + rawData.substring(20, 23) + ',"' + rawData[24] + '":' + rawData.substring(26, 29) + ',"' + rawData[30] + '":' + rawData.substring(32, 35) + '}';
		 STATUS = JSON.parse(json);
		 console.log(STATUS);
}

socket.onclose = function(){
		 message('Socket Status: '+socket.readyState+' (Closed)');
}			

} catch(exception){
		 message('Error'+exception);
}

function message(msg){
	console.log(msg);
}

// Send data to WebSockets every second to get STATUS code
setInterval(function(){ 
	socket.send('GET_BACKEND_STATUS');
}, 1000);


// Toggle Cup Size on button click

$("#button1").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
    if (true) {}
});
$("#button2").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
});
$("#button3").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
});
$("#button4").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
});

$(".cup").click(function(){
	socket.send($(this).attr('id'));
	message('Request Sent: '+$(this).attr('id'));
});
