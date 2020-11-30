
ViewFile(){
    echo ""
    echo "--------------------------------------------------------------------------------"
    echo "EMP ID  NAME     DEPARTMENT  DESIGNATION  SALARY  DA      GROSS SALARY"
    echo "--------------------------------------------------------------------------------"
	cat $1
}

Insert(){
	fn=$1 empno=$2 name=$3 dept=$4 desig=$5 sal=$6 DA=$7 gross=$8	
	echo "$empno  $name     $dept      $desig      $sal    $DA      $gross" >> $fn
	echo "Inserted sucessfully"
}

Delete(){
	fn=$1
	empno=$2
	
	grep -v "$empno" $fn >> temp
	mv temp $fn
	echo "Deleted sucessfully!"
}

Modify(){
	empno=$1 fn=$2 name=$3 dept=$4 desig=$5 sal=$6 DA=$7 gross=$8
	
	grep -v "$empno" $fn >> temp
	mv temp $fn
	
	echo "$empno  $name     $dept      $desig      $sal    $DA      $gross" >> $fn
	echo "Modified sucessfully"
}

search(){
	    empno=$1 fn=$2
	    if grep "$empno" $fn
	    then
		echo "Record found"
	    else
		echo "Record not found"
	    fi
}


read -p "Enter filename : " fn

empno=33200
while :
do
echo -e $"<--EMPLOYEE MENU--> \n 1) View file \n 2) Insert a record \n 3) Delete a record \n 4) Modify a record \n 5) Search \n 6) Exit\n"

read -p "Enter option: " option
case $option in
	1) ViewFile $fn;;
	
	2) empno=`expr $empno + 1`
	     
	    while true
	      do
		read -p "Enter employee name : " name
		if [ -z "$name" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$name" =~ ^[a-zA-Z]+$ ]]
		then 
		    break
		else
		    echo "Only Alphabets!"
		fi 
	    done
	    
	    read -p "Department: " dept
          
            while true
	      do
		read -p "Enter designation : " desig
		if [ -z "$desig" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$desig" =~ ^[a-zA-Z]+$ ]]
		then 
		    break
		else
		    echo "Only Alphabets!"
		fi 
	    done
	    
	    while true
	      do
		read -p "Enter salary : " sal
		if [ -z "$sal" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$sal" =~ ^[0-9]+$ ]]
		then 
		    break
		else
		    echo "Only numbers!"
		fi 
	    done
	    
          da=`echo "$sal * 0.2" | bc` 
    	  hra=`echo "$sal * 0.5" | bc`
	  gross=`echo "$sal + $da + $hra" | bc` 
          Insert $fn $empno $name $dept $desig $sal $DA $gross;;

	3) read -p "Enter employee no to be deleted: " empno
	   Delete $fn $empno;;

	4) read -p "Enter searched Rollno: " empno
	
	    while true
	      do
		read -p "Enter employee name : " name
		if [ -z "$name" ]
		then 
		    echo 'Blanks not allowed!'
		elif [[ "$name" =~ ^[a-zA-Z]+$ ]]
		then 
		    break
		else
		    echo "Only alphabets"
		fi 
	    done
	    
	    read -p "Department: " dept
          
            while true
	      do
		read -p "Enter designation : " desig
		if [ -z "$desig" ]
		then 
		    echo 'Blanks not allowed!'
		elif [[ "$desig" =~ ^[a-zA-Z]+$ ]]
		then 
		    break
		else
		    echo "Only alphabets"
		fi 
	    done
	    
	    while true
	      do
		read -p "Enter salary : " sal
		if [ -z "$sal" ]
		then 
		    echo 'Blank not allowed!'
		elif [[ "$sal" =~ ^[0-9]+$ ]]
		then 
		    break
		else
		    echo "Only numbers!"
		fi 
	    done
          
	  da=`echo "$sal * 0.2" | bc` 
    	  hra=`echo "$sal * 0.5" | bc`
	  gross=`echo "$sal + $da + $hra" | bc` 
         Modify $empno $fn $name $dept $desig $sal $da $gross;;
          
	5) read -p "Enter emp no to be searched: " empno
          search $empno $fn;;
	
	6) exit;;
		
	*)echo "Invalid choice";;
	
esac
done
