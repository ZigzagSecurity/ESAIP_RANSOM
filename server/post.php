<?php
include 'lib/Crypt/RSA.php';
//we get a post with an rsa encrypted message and a public key used
if(isset($_POST['rsa_message']) && isset($_POST['rsa_pukey'])){
	$rsa = new Crypt_RSA();

//==========ENCRYPTION NOT NEEDED AFTER====================
//because rsa_message isn't encrypted yet
	$rsa->loadKey($_POST['rsa_pukey']);
    $ciphertext = $rsa->encrypt($_POST['rsa_message']);
//==========ENDS HERE======================================

    /*we have a public key
    * we need to find the private key corresponding in the database
    * sql connection and request
    * use of the key to decrypt*/
    $con=mysqli_connect("localhost","root","","ransom");
	$result = $con->query("SELECT private_key from db_keys where public_key='".$_POST['rsa_pukey']."'");
	foreach ($result as $row) {
		$tmp_prkey=$row['private_key'];
		$rsa->loadKey($tmp_prkey);
		echo $rsa->decrypt($ciphertext);
		//should replace line above with line below
		//echo $rsa->decrypt($_POST['rsa_message']);
	}

}