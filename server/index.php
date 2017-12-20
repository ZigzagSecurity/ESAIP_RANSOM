<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" type="text/css" href="style.css">
    <title>Index</title>
  </head>
  <form action="post.php" method="POST">
  	<input type="hidden" name="rsa_message" value="test">
  	<input type="hidden" name="rsa_pukey" value="-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQD+0ByQdaNtHNxe+W5XGlb63+jd
P+hn6bj+XdV287WDWPDRXfR8XLnSAij336E8gbUM2+qyBtDqKwf5/MZeObDnpXTI
70PLDBXvPaIBh5OcTggywo69bGd/NAkX0ZyJv35vlqcJNatCgXI+YCjcpuhoxSCy
VvXBW2LCKRmTUaURSwIDAQAB
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
  </form>
  <body>
  </body>
</html>
