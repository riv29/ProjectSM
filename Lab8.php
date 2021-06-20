

<html>
<head>

<?php
 
if (isset($_POST['mButton']))  // Source Off
{
	$fp = fopen("Soilparameters.conf", "w");

	if ($_POST['minVal'] == "")
		fwrite($fp, "0" . "\n");
	else
		fwrite($fp, $_POST['minVal'] . "\n");

	if ($_POST['maxVal'] == "")
		fwrite($fp, "9999999" . "\n");
	else
		fwrite($fp, $_POST['maxVal'] . "\n");

	fclose( $fp );
}

if (isset($_POST['tButton']))
{
	$fp = fopen("Temperatureparameters.conf", "w");

	if ($_POST['minVal'] == "")
		fwrite($fp, "0" . "\n");
	else
		fwrite($fp, $_POST['minVal'] . "\n");

	if ($_POST['maxVal'] == "")
		fwrite($fp, "9999999" . "\n");
	else
		fwrite($fp, $_POST['maxVal'] . "\n");

	fclose( $fp );
}

?>

  <title>SMlab8_APACHE server for Web of Things </title>
</head>
<body>
<center>
<table witdh="400" border="1" bgcolor="silver">
<td>

<Font color='blue'><b>
<center>
Universitatea Tehnica 'Gh.Asachi' Iasi - Fac. Automatica si Calculatoare<br> 
<br>
<img src="face.jpg" width="200" height="200"> </center>
</Font><b>
<center> <h1> <Font color='navy'>
APACHE Server  for<br> IOT Project <br>

</h1></font>
<center>

<form method="post">
  <table
 style="width: 50%; text-align: left; margin-left: auto; margin-right: auto;"
 border="1" cellpadding="2" cellspacing="2">
      <tr>
        <td style="text-align: center;"><label style="text-align: center;" for="minVal">Minimum value</label><br><input type="text" name="minVal" pattern="[0-9]{1,}" value=""></td>
        <td style="text-align: center;"><label style="text-align: center;" for="maxVal">Maximum value</label><br><input type="text" name="maxVal" pattern="[0-9]{1,}" value=""></button></td>
     </tr>
     <tr>
        <td style="text-align: center;"><button name="mButton"><font color="red"><b>Set Range for Moisture Sensor</button></td>
        <td style="text-align: center;"><button name="tButton"><font color="red"><b>Set Range for Temperature Sensor </button></td>
     </tr>
  </table>

</form>
<font color="navy">
<br>
&copy 2021 Fac. Automatica si Calculatoare
 
</td>
</table>

</body>
</html>


