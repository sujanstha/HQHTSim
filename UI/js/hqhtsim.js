var socket;
var json = '{"A":0.0,"B":[0,0,0,0],"C":0.0,"D":0.0,"E":0.0}';
var STATUS = JSON.parse('{"A":0.0,"B":[0,0,0,0],"C":0.0,"D":0.0,"E":0.0}');
var CONTROL = JSON.parse('{"A":0, "B":[0,0,0,0], "C":0}');
var WAIT = false;
var wasWaiting = false;
try{
var host = "ws://localhost:8126/foo";
socket = new WebSocket(host);

message('Socket Status: '+socket.readyState);

socket.onopen = function(){
		 message('Socket Status: '+socket.readyState+' (open)');
}

socket.onmessage = function(msg){
		 message('Received: '+msg.data);
		 var rawData = msg.data.replace(/\s/g, "").replace('STATUS:', '');
		 var rawList = rawData.split(/[\[\]\s,=]+/);
		 var json = '';
		 json = '{"'+rawList[0] + '":' + rawList[1] + ',"' +  rawList[2] + '":[' + rawList[3] + "," + rawList[4] + "," + rawList[5] + "," + rawList[6] + '],"' + rawList[7] + '":' + rawList[8] + ',"' + rawList[9] + '":' + rawList[10] + ',"' + rawList[11] + '":' + rawList[12] + '}';
		 STATUS = JSON.parse(json);
		 CONTROL.B[0] = STATUS.B[0];
		 CONTROL.B[1] = STATUS.B[1];
		 CONTROL.B[2] = STATUS.B[2];
		 CONTROL.B[3] = STATUS.B[3];
		 console.log(CONTROL.B[0]);
		 console.log(CONTROL.B[1]);
		 console.log(CONTROL.B[2]);
		 console.log(CONTROL.B[3]);
}

socket.onclose = function(){
		 message('Socket Status: '+socket.readyState+' (Closed)');
}			

} catch(exception){
		 message('Error: '+exception);
}

function message(msg){
	console.log(msg);
}

// Send data to WebSockets every second to get STATUS code
setInterval(function(){ 
	socket.send('GET_BACKEND_STATUS');
	$("#content-level").css("height", STATUS.D*100+"%");
	// $("#status").html("Normal");
	if (STATUS.A == 1) 
	{
		$('#input-valve').html("Open");
	}
	else
	{
		$('#input-valve').html("Close");
	}
	$("#coffee-level").html(STATUS.D);
	$("#temperature").html(STATUS.E);
	$("#burner").html(STATUS.C);
	$("#open-valves").html(STATUS.B);
	if (STATUS.D < 0.6 && STATUS.E < 83) 
	{
		// waiting for appropriate level and temperature
		$('#wait').html("waiting for appropriate level and temperature");
		WAIT = true;
	}
	else if (STATUS.D < 0.6)
	{
		// waiting for appropriate level
		$('#wait').html("waiting for appropriate level");
		WAIT = true;
	}
	else if (STATUS.E < 83)
	{
		// waiting for appropriate temperature
		$('#wait').html("waiting for appropriate temperature");
		WAIT = true;
	}
	else
	{
		WAIT = false;
	}
	if (WAIT) 
	{
		$("#button1").addClass('dim');
		$("#button2").addClass('dim');
		$("#button3").addClass('dim');
		$("#button4").addClass('dim');
		wasWaiting = true;
	}
	else
	{
		if(wasWaiting)
		{
			$('#wait').html("");
			$("#button1").removeClass('dim');
			$("#button2").removeClass('dim');
			$("#button3").removeClass('dim');
			$("#button4").removeClass('dim');
			wasWaiting = false;
		}
	}
	console.log(STATUS);
	console.log(CONTROL);
}, 1000);

// Toggle Cup Size on button click

$("#button1").click(function(){
	if (!WAIT) 
	{
		$(this).addClass('dim');
	    $(this).siblings(".cups").toggle();
	    if($(this).siblings(".cups").css('display') == "none") 
	    {
	    	$(this).removeClass('dim');
	    }
	}
});
$("#button2").click(function(){
	if (!WAIT) 
	{	
		$(this).addClass('dim');
	    $(this).siblings(".cups").toggle();
	    if($(this).siblings(".cups").css('display') == "none") 
	    {
	    	$(this).removeClass('dim');
	    }
	}
});
$("#button3").click(function(){
	if (!WAIT) 
	{
		$(this).addClass('dim');
	    $(this).siblings(".cups").toggle();
	    if($(this).siblings(".cups").css('display') == "none") 
	    {
	    	$(this).removeClass('dim');
	    }
	}
});
$("#button4").click(function(){
	if (!WAIT) 
	{
		$(this).addClass('dim');
	    $(this).siblings(".cups").toggle();
	    if($(this).siblings(".cups").css('display') == "none") 
	    {
	    	$(this).removeClass('dim');
	    }
	}
});

$(".cup").click(function(){
	if (!WAIT) 
	{
		socket.send($(this).attr('id'));
		var valve = $(this).attr('id');
		if(valve[1] == '1')
		{
			CONTROL.B[0] = 1;
		}
		else if(valve[1] == '2')
		{
			CONTROL.B[1] = 1;
		}
		else if(valve[1] == '3')
		{
			CONTROL.B[2] = 1;
		}
		else if(valve[1] == '4')
		{
			CONTROL.B[3] = 1;
		}
		socket.send('POST_UI_CONTROL');
		socket.send('CONTROL: A=1.0, B=['+ CONTROL.B[0] +", " + CONTROL.B[1] + ", " + CONTROL.B[2] +", "+ CONTROL.B[3] + '], C=1.0');
		message('Request Sent: '+ 'CONTROL: A=1.0, B=['+ CONTROL.B[0] +", " + CONTROL.B[1] + ", " + CONTROL.B[2] +", "+ CONTROL.B[3] + '], C=1.0');

	}
});
