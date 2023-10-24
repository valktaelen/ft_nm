#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: $0 <répertoire> <valeur_de_$2>"
	exit 1
fi

directory="$1"
value="$2"

rm diff/*

find "$directory" -type f -print0 | while IFS= read -r -d $'\0' file; do
	base_name="diff/$(basename "$file")"
	nm_ok=1
	ft_nm_ok=1

	./ft_nm $value "$file" >/tmp/test1 2>/tmp/test2
	if [ $? -eq 0 ]; then
		mv /tmp/test1 "$base_name.1"
	else
		mv /tmp/test2 "$base_name.1_error"
		ft_nm_ok=0
	fi

	nm $value "$file" >/tmp/test1 2>/tmp/test2
	if [ $? -eq 0 ]; then
		mv /tmp/test1 "$base_name.2"
	else
		mv /tmp/test2 "$base_name.2_error"
		nm_ok=0
	fi

	diff "$base_name.1"  "$base_name.2" &>/dev/null
	if [ $? -ne 0 ]; then
		if [ $ft_nm_ok -ne 0 ] && [ $nm_ok -ne 0 ]; then
			echo "$base_name" KO
		fi
	fi
done

