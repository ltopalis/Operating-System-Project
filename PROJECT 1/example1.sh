function mining_usernames {
	awk '{print $3}' access.log | sort | uniq > temp.txt

	while read -r line; do
		echo -e "$line $(awk '{print $3}' access.log | grep $line | wc -l)"
	done < $"temp.txt"
	rm temp.txt
}


function match {
	awk '{print $0}' access.log | grep "$1"
}

function count_browsers {
	for i in Mozilla Chrome Safari Edg 
	do

		echo -e "$i\t$(match $i | wc -l)"
	done
}

if [ $# -eq 0 ]; then
	echo "1084622|1088101"
elif [ $# -ge 1 ]; then
	if [ $1 == *".log" ]; then
		case $# in
		1 )
			cat $1;;
		2 )
			if [ $2 == "--usrid" ]; then
				mining_usernames
			
			elif [ $2 == "--browsers" ]; then
				count_browsers
			elif [ $2 == "--datum" ]; then
				echo "Wrong Date"
			else
				echo "Wrong parameter name"
			fi;;
		3 )
			if [ $2 == "--usrid" ]; then
				cat $1 | grep $3
			elif [ $2 == "-method" ]; then
				if [ $3 == "GET" ] || [ $3 == "POST" ]; then
					cat $1 | grep $3
				else
					echo "Wrong method names."
				fi
			
			elif [ $2 == "--servprot" ]; then
				if [ $3 == "IPv4" ]; then
					awk ' $1 ~ /\./ {print $0} ' access.log
				elif [ $3 == "IPv6" ]; then
					awk ' $1 ~ /:/ {print $0} ' access.log 
				else
					echo "wrong"
				fi
			elif [ $2 == "--datum" ]; then

				if [[ $3 =~ ^(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)$ ]]; then
					awk ' {print $0} ' access.log | grep $3
				else
					echo "Wrong Date"
				fi
			else
				echo "wrong."

	 
			fi;;
		esac


	else
		echo "Wrong document koukle"

	fi
fi
