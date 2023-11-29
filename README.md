# ft_nm

This project is about recoding the command nm

## Compile

```bash
make
```

## Execute

```bash
./ft_nm [flags] [files]
```

The flags:
- `-a`: Display all symbols, even debugger-only symbols; normally these are not listed.
- `-r`: Reverse the order of the sort (whether numeric or alphabetic); let the last come first.
- `-p`: Do not bother to sort the symbols in any order; print them in the order encountered.
- `-u`: Display only undefined symbols (those external to each object file).
- `-g`: Display only external symbols.


## Tests

To run test, execute :
```bash
bash ./test.sh dir/ ''
```
Where dir/ is the directory where you want to test files with nm.
And the second parameter is the flags like '-a -p'.

## How it works

> **La Commande nm :**
>
> La commande nm (nommage) est un utilitaire de ligne de commande qui affiche les symboles d'un fichier objet, souvent utilisé pour les fichiers exécutables ou les bibliothèques partagées.


> **Le Format de Fichier ELF :**
>
> Le format ELF est un format de fichier binaire utilisé pour représenter des fichiers exécutables, des objets partagés et d'autres types de fichiers binaires sous les systèmes d'exploitation de type UNIX.

Voici quelques points clés :

- En-tête ELF : Chaque fichier ELF commence par un en-tête qui contient des informations essentielles sur le fichier, telles que le type du fichier (exécutable, objet, etc.), l'architecture cible, et l'emplacement des tables des sections et des symboles.

- Sections : Les sections sont des unités de données ou de code du programme. Les sections courantes comprennent .text pour le code exécutable, .data pour les données initialisées, et .bss pour les données non initialisées.

- Program Header : Présent uniquement dans les fichiers exécutables, le programme header décrit la disposition en mémoire du fichier lorsqu'il est chargé en mémoire.

- Table des Symboles : La table des symboles contient des informations sur les symboles du programme, y compris les adresses mémoire, les types de symboles (fonction, variable, etc.), et les noms des symboles.

- Table de Réimplantation (Relocation Table) : Utilisée lors de la liaison dynamique, la table de réimplantation contient des informations sur les ajustements d'adresses qui doivent être effectués lors de l'exécution pour corriger les adresses des symboles.
