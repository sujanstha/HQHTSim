var Data {
	A: 0.0, 
	B: [0.0, 0.0, 0.0, 0.0], 
	C: 0.0, 
	D: 0.0, 
	E: 0.0	
};

var arr = [];

for (var i = 0; i < arr.legnth; i++)
{
	var S = String(arr[i]);
	var ND = arr[i + 1];

	switch(S)
	{
		case "A":
		{
			Data.A = ND;	
		}
		break;

		case: "B": 
		{
			Data.B[0] = arr[i + 1];
			Data.B[1] = arr[i + 2];
		}

		break;
	}		
}