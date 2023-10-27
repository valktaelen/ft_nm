#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: $0 <répertoire> <flags>"
	exit 1
fi

directory="$1"
value="$2"

rm -r diff
mkdir diff

find "$directory" -type d -name .git -prune -o -type f -print0 | while IFS= read -r -d $'\0' file; do
	relative_path=$(echo "$file" | cut -c$((${#directory}+1))-)
	dir_path=$(dirname "$relative_path")
	mkdir -p diff/$dir_path
	base_name="diff/$relative_path"
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

	if [ $ft_nm_ok -ne $nm_ok ]; then
		echo "$base_name" not same exit status
		exit 0
	fi

	diff "$base_name.1"  "$base_name.2" &>/dev/null
	if [ $? -ne 0 ]; then
		if [ $ft_nm_ok -ne 0 ] && [ $nm_ok -ne 0 ]; then
			echo "$base_name" KO
		fi
	fi
done

