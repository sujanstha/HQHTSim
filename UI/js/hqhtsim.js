var socket;
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
