<?php
include('lib/Crypt/RSA.php');
include('database.php');

$rsa = new Crypt_RSA();

extract($rsa->createKey());

//we just give the public key and we save both into database
echo $publickey;
//save pair to database
connect("root","")->query("INSERT INTO `db_keys` (`id`, `private_key`, `public_key`) VALUES (NULL, '".$privatekey."', '".$publickey."');");
?>