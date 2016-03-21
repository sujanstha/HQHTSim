// Toggle Cup Size on button click

$("#button1").click(function(){
    $(this).siblings(".cups").toggle();
});
$("#button2").click(function(){
    $(this).siblings(".cups").toggle();
});
$("#button3").click(function(){
    $(this).siblings(".cups").toggle();
});
$("#button4").click(function(){
    $(this).siblings(".cups").toggle();
});

$(".cup").click(function(){
	console.log($(this).attr('id'));
});
