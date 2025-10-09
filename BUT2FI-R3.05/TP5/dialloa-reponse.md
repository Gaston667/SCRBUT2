Très bien 👍 Voici un **paragraphe clair et concis** pour chaque situation, comme tu pourrais les écrire dans ton compte rendu de TP :

---

### 1. Envoi de **SIGSTOP** puis **SIGCONT** à Pf2

Lorsque le signal **SIGSTOP** est envoyé à Pf2, ce processus est suspendu : il n’écrit plus dans le tube. Le processus Pf1f1, qui lit en continu, se retrouve alors bloqué sur l’appel système `read()`, car le tube est vide et `read()` est bloquant. Dès que le signal **SIGCONT** est envoyé, Pf2 reprend son exécution et recommence à écrire dans le tube ; Pf1f1 recommence immédiatement à recevoir et afficher les PID. Cela montre que la lecture d’un tube dépend de l’activité de l’écrivain.

---

### 2. Envoi de **SIGSTOP** puis **SIGCONT** à Pf1f1

Quand Pf1f1 est suspendu par **SIGSTOP**, le processus Pf2 continue d’écrire dans le tube. Au bout d’un moment, le tampon interne du tube se remplit (environ 64 Ko sous Linux). Une fois plein, l’appel `write()` de Pf2 devient **bloquant**, et Pf2 se met en attente tant que le lecteur ne lit pas. Après l’envoi de **SIGCONT**, Pf1f1 reprend ses lectures ; le tampon se vide, et Pf2 recommence à écrire. On observe donc une synchronisation automatique entre les deux processus via le mécanisme de blocage du tube.

---

### 3. Envoi de **SIGTERM** à Pf2

Quand Pf2 reçoit **SIGTERM**, il se termine et ferme son descripteur d’écriture du tube. Du côté de Pf1f1, le `read()` continue de lire les dernières données présentes dans le tampon, puis finit par renvoyer **0**, indiquant une fin de fichier (EOF). Cela signifie que plus aucun processus n’a le tube ouvert en écriture. Pf1f1 peut alors détecter que l’écrivain n’existe plus et se terminer proprement.

---

### 4. Envoi de **SIGTERM** à Pf1f1

Lorsque Pf1f1 est tué, le tube n’a plus de lecteur. Le prochain `write()` exécuté par Pf2 échoue : le noyau envoie alors automatiquement un signal **SIGPIPE** à Pf2. Si le signal n’est pas ignoré, il provoque la terminaison du processus avec le message d’erreur “Broken pipe”. Cela illustre que le noyau empêche un processus d’écrire dans un tube sans lecteur actif.

---

### 5. Fermeture correcte des descripteurs inutilisés

En modifiant le programme pour que chaque processus ferme les extrémités du tube qu’il n’utilise pas (`close(tube[0])` pour l’écrivain, `close(tube[1])` pour le lecteur), le comportement devient plus propre. Le système détecte correctement la fin de communication : lorsque l’écrivain se termine, le lecteur reçoit bien un `read() = 0`. Sans cette fermeture, le tube peut rester ouvert par inadvertance dans un processus ancêtre, empêchant la détection de la fin et bloquant le lecteur indéfiniment.

---

### 6. Deux écrivains (Pf1 et Pf2) simultanément

Quand Pf1 et Pf2 écrivent tous deux dans le même tube pendant que Pf1f1 lit, les données arrivent de manière alternée et non ordonnée. Chaque `write()` (de petite taille) est atomique, donc les messages ne se mélangent pas, mais l’ordre d’arrivée dépend du planificateur du noyau. À chaque exécution, Pf1f1 peut recevoir les PID dans un ordre différent, ce qui montre que la communication par tube ne garantit pas l’ordre entre plusieurs écrivains.
