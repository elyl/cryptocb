# cryptocb

Utilisation :
./proc <key1> <key2>
key1 et key2 sont les clefs servant a dechiffrer le fichier "master_key".

Key1 : 0123456789abcdef0123456789abcdef
Key2 : abcdef0123456789abcdef0123456789

Limitations:
Actuellement les clefs sont passes en parametres au lancement du programme, il est donc tres complique d'avoir des clefs non alphanumeriques.
Le fichier secret_file est regenere a chaque lancement du programme avec trois enregistrements.
Les clefs sont generees au lancement egalement pour simplifier les tests.
Impossible d'avoir des espaces dans le nom lors d'une recherche

Commandes supportees:
show_all: Affiche tous les enregistrements presents dans le fichier
show <nom> : Affiche l'enregistrement correspondant au nom <nom>
exit: quitte le programme
add <nom> <cb> <pin> : Ajoute un enregistrement dans le fichier

Fonctionnement:
Le fichier "secret_file" contient tous les enregistrements chiffres en AES256 CBC.
Le fichier "master_key" contient la clef de dechiffrement du fichier des enregistrements, il est chiffre en AES256 CBC

Bugs connus: (beaucoup)
- Plante si aucune commande n'est entree
- Impossible de mettre un espace dans le nom
- Plante si trop peu d'arguments sont passes

LHEUREUX - PLOCKYN