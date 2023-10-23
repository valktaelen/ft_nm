#!/bin/bash

# La commande que vous souhaitez exécuter sur chaque fichier
command_to_run="votre_commande"

# L'extension que vous souhaitez ajouter aux fichiers de sortie
output_extension=".txt"

# Utilisation de find pour parcourir le répertoire et xargs pour exécuter la commande
find "$1" -type f -exec sh -c '
  for file; do
    base_name="diff/$(basename "$file")"

    # Exécution de la commande sur le fichier et redirection de la sortie vers le fichier de sortie
    ./a.out "$file" | sort > "$base_name.1"
    nm -a "$file" | sort > "$base_name.2"
  done
' sh {} +
