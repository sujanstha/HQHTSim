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
		 var rawList = rawData.split(/[\[\]\s,=]+/);
		 var json = '';
		 json = '{"'+rawList[0] + '":' + rawList[1] + ',"' +  rawList[2] + '":[' + rawList[3] + "," + rawList[4] + "," + rawList[5] + "," + rawList[6] + '],"' + rawList[7] + '":' + rawList[8] + ',"' + rawList[9] + '":' + rawList[10] + ',"' + rawList[11] + '":' + rawList[12] + '}';
		 //json = '{"'+rawData[0] + '":' + rawData.substring(2,5) + ',"' +  rawData[6] + '":' + rawData.substring(8, 17) + ',"' + rawData[18] + '":' + rawData.substring(20, 23) + ',"' + rawData[24] + '":' + rawData.substring(26, 29) + ',"' + rawData[30] + '":' + rawData.substring(32, 35) + '}';
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
	$("#content-level").css("height", STATUS.D*100+"%");
	$("#status").html("Normal");
	$("#coffee-level").html(STATUS.D);
	$("#temperature").html(STATUS.E);
	$("#burner").html(STATUS.C);
	$("#open-valves").html(STATUS.B);
	console.log(STATUS);
}, 1000);

// Toggle Cup Size on button click

$("#button1").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
    if($(this).siblings(".cups").css('display') == "none") 
    {
    	$(this).removeClass('dim');
    }
});
$("#button2").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
    if($(this).siblings(".cups").css('display') == "none") 
    {
    	$(this).removeClass('dim');
    }
});
$("#button3").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
    if($(this).siblings(".cups").css('display') == "none") 
    {
    	$(this).removeClass('dim');
    }
});
$("#button4").click(function(){
	$(this).addClass('dim');
    $(this).siblings(".cups").toggle();
    if($(this).siblings(".cups").css('display') == "none") 
    {
    	$(this).removeClass('dim');
    }
});

$(".cup").click(function(){
	socket.send($(this).attr('id'));
	// socket.send('POST_UI_CONTROL');
	// socket.send('CONTROL: A=1.0, B=[0, 0, 0, 1], C=1.0');
	message('Request Sent: '+$(this).attr('id'));
});
