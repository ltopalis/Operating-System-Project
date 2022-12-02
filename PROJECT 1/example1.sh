function mining_usernames {
	while read -d line; do
		echo -e "$line $(awk '{print $3}' access.log | grep $line | wc -l"
	done < $"temp.txt"
}

if [ $# -eq 0 ]; then
	echo "1084622|1088101"
elif [ $# >= 1 ]; then
	if [ $1 == *".log" ]; then
		case $# in
		1 )
			cat $1;;
		2 )
			if [ $2 == "--usrid" ]; then
				mining_usernames;
			else
				echo "Wrong parameter name";;
		3 )
			if [ $2 == "--usrid" ]; then
				cat $1 | grep $3;
			elif [ $2 == "-method"]; then
				if [ $3 == "GET" ] || [ $3 == "POST" ]; then
					cat $1 | grep $3
				else
					echo "Wrong method names."
				fi
			if [ $2 == "--servprot" ]; then
				if [ $3 == "IPv4"]; then
					cat $1 | grep 127.0.0.1
				elif [ $3 


	else
		echo "Wrong document koukle";; 
