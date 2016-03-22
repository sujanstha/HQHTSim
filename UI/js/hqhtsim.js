var socket;
var json = '{"A":1.0,"B":[1,0,0,0],"C":1.0,"D":0.5,"E":0.2}';
var STATUS = JSON.parse('{"A":0.0}');
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
		 var index = new Array();
		 var bool = true;
		 for (var i =  0; i < rawData.length && index.length < 12; i++) {
		 	if (bool) {
		 		index.push(rawData.substring(i, rawData.length).indexOf("=") + index[i]);
		 		bool = false;
		 	}		
		 	else
		 	{
		 		index.push(rawData.substring(i, rawData.length).indexOf(",") + index[i]);l
		 		bool = true;
		 	}
		 }
		 console.log(index);
		 json = '{"'+rawData[index[0]-1] + '":' + rawData.substring(index[1]+1,index[2]) + ',"' +  rawData[index[3]-1] + '":' + rawData.substring(index[4]+1, index[5]) + ',"' + rawData[index[6]-1] + '":' + rawData.substring(index[7]+1, index[8]) + ',"' + rawData[index[9]-1] + '":' + rawData.substring(index[10]+1, index[11]) + ',"' + rawData[index[12]-1] + '":' + rawData.substring(index[13]+1, index[14]) + '}';
		 //json = '{"'+rawData[0] + '":' + rawData.substring(2,5) + ',"' +  rawData[6] + '":' + rawData.substring(8, 17) + ',"' + rawData[18] + '":' + rawData.substring(20, 23) + ',"' + rawData[24] + '":' + rawData.substring(26, 29) + ',"' + rawData[30] + '":' + rawData.substring(32, 35) + '}';
		 //STATUS = JSON.parse(json);
		 console.log(json);
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
	$("#content-level").css("height", STATUS.D*100+"%");
	$("#status").html("Normal");
	$("#coffee-level").html(STATUS.D);
	$("#temperature").html(STATUS.C);
	$("#burner").html(STATUS.C);
	$("#open-valves").html(STATUS.B);
	console.log(STATUS);
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
	// socket.send('POST_UI_CONTROL');
	// socket.send('CONTROL: A=1.0, B=[0, 0, 0, 1], C=1.0');
	message('Request Sent: '+$(this).attr('id'));
});
