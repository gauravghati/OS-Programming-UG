Insert(){
	fn=$1 name=$2 roll=$3 div=$4 mark1=$5 mark2=$6 mark3=$7 mark4=$8 mark5=$9
	
	total=`expr $mark1 + $mark2 + $mark3 + $mark4 + $mark5`
	avg=`expr $total / 5`
	echo "$roll $name $div $mark1 $mark2 $mark3 $mark4 $mark5 $avg" >> $fn
	echo "Inserted sucessfully"
}

Delete(){
	fn=$1
	roll=$2
	
	grep -v "$roll" $fn >> temp
	mv temp $fn
	echo "Deleted sucessfully!"
}

Modify(){
	roll=$2 fn=$1 name=$3 div=$4 mark1=$5 mark2=$6 mark3=$7 mark4=$8 mark5=$9	
	
	total=`expr $mark1 + $mark2 + $mark3 + $mark4 + $mark5`
	avg=`expr $total / 5`
	grep -v "$roll" $fn >> temp
	mv temp $fn
	echo "$roll $name $div $mark1 $mark2 $mark3 $mark4 $mark5 $avg" >> $fn
	echo "Modified sucessfully"
}

search(){
	read -p "Enter roll no to be searched: " empno
    if grep "$empno" $fn
    then
	echo "Record found"
    else
	echo "Record not found"
    fi
}

result() {
    echo "-----------------------------------------------------------------------------------"
    printf "Roll\tName\tDiv\tmark1\tmark2\tmark3\tmark4\tmark5\n"
    echo "-----------------------------------------------------------------------------------"
    while read -ra line; 
    do
        printf "%5d  %5s  %2d " ${line[0]}  ${line[1]}  ${line[2]}
        for ((i=3; i < 8; i++))
        do
            if ((${line[i]} >= 40))
            then 
                #echo -n "Passed  "
                printf "        Passed"
            else
                #echo -n "Failed  "
                printf "        Failed"
            fi 
        done
        echo ""
    done < $1
    echo ""
}
   
avgresult() {
    echo ""
    echo "-------------------------------------"
    echo "Name  Roll No  Div  Average"
    echo "-------------------------------------"
    while read -ra line; do
        printf "%5d  %5s  %2d %7.2f\n" ${line[0]} ${line[1]} ${line[2]} ${line[8]}
    done < $1
        echo ""
}

read -p "Enter filename : " fn

roll=33220
while :
do
echo -e $"<------MENU------> \n 1) Show result \n 2) Insert a record \n 3) Delete a record \n 4) Modify a record \n 5) Search \n 6) Show Avg result \n 7) Exit\n"

read -p "Enter option: " option
case $option in
	1) echo "Showing result passed or not"
		result $fn;;
	
	2) roll=`expr $roll + 1`;
	   read -p "Enter name: " name
          read -p "Enter division: " div
          read -p "Enter Marks 1: " mark1
          read -p "Enter Marks 2: " mark2
          read -p "Enter Marks 3: " mark3
          read -p "Enter Marks 4: " mark4
          read -p "Enter Marks 5: " mark5
          Insert $fn $name $roll $div $mark1 $mark2 $mark3 $mark4 $mark5;;

	3) read -p "Enter roll no to be deleted: " roll
	   Delete $fn $roll;;

	4) read -p "Enter searched Rollno: " roll
	read -p "Enter name : " name
	read -p "Enter division : " div
	read -p "Enter marks1: " mark1
	read -p "Enter marks2: " mark2
	read -p "Enter marks3: " mark3
	read -p "Enter marks4: " mark4
	read -p "Enter marks5: " mark5
	Modify $fn $roll $name $div $mark1 $mark2 $mark3 $mark4 $mark5;;
	
	5) search;;
	
	6) echo "Show avg result"
		avgresult $fn;;
		
	7) exit;;
		
	*)echo "Invalid choice";;
	
esac
done
