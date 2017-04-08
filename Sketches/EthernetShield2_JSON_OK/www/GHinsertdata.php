<html>
<body>
	<?php 
		//..../GHinsertdata.php?l1=1&t1=2&c1=3&h1=4
		$l1 = $_GET["l1"]; //light
		$t1 = $_GET["t1"]; //temperature
		$c1 = $_GET["c1"]; //CO
		$h1 = $_GET["h1"]; //humidity
		//echo "Light      "; 
		//echo $l1;
		//echo "<br>";
		//echo "temperature";
		//echo $t1;
		//echo "<br>";
		//echo "CO         ";
		//echo $c1;
		//echo "<br>";
		//echo "humidity   ";
		//echo $h1;
		//echo "<br>";
		
		$servername = "localhost";
		$username = "root";
		$password = "";
		$database = "sensorserver";
		$table = "sensordata";
		
		// Create connection
		$conn = mysqli_connect($servername, $username, $password,$database);
		//$conn = mysqli_connect("sql301.rf.gd", "rfgd_19734843", "asdfghjk");
		// Check connection
		if (!$conn) {
    		die("Connection failed: " . mysqli_connect_error());
    		echo "<br>";
		}
		//echo "Connected successfully";
		//echo "<br>";

		$sql = "INSERT INTO sensordata (light,temperature,co,humidity) VALUES ($l1,$t1,$c1,$h1)";

		if (mysqli_query($conn, $sql)) {
    		//echo "New record created successfully";
    		//echo "<br>";
    		$response["success"] = 1;
    		// echoing JSON response
    		echo json_encode($response);
		} else {
    		//echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    		//echo "<br>";
    		$response["success"] = 0;
    		// echoing JSON response
    		echo json_encode($response);
		}
		
	?>
</body>
</html>