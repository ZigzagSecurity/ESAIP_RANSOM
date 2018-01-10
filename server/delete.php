<?php
include 'database.php';
if(isset($_POST['id'])){
	$result = connect("root","")->query("UPDATE `infos` SET `payement` = '1' WHERE `infos`.`id` = ".$_POST['id']);
	header('Location: http://localhost/');
}