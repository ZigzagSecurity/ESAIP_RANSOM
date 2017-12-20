url/ransom/getKey.php retourne une clé publique a utiliser pour chiffrer et sauvegarde la paire (clé privée/clé publique) dans la base de données
url/ransom/index.php envoie des données post pour tester la page post.php
url/ransom/post.php reçoit 2 arguments POST rsa_message & rsa_pukey, retrouve la clé privée correspondante, déchiffre le message et l'affiche
