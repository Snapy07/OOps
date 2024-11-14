1.Print Sum of Digits of a given number using command line argument
PROGARM:

echo "Enter the Number:"
read number

sum=0;

while [ $number -gt 0 ];
do
    digit=$((number % 10))
    sum=$((sum + digit))
    number=$((number / 10))
done

echo "Sum of digits:$sum”




OUTPUT:
Enter the Number:
278273872
Sum of digits:46





2. Write a shell script using function for following:1)average of given numbers 2) Max  digit from given number and 3) min digit  from given number
echo "How many numbers do you want to enter?"
read N

numbers=()
i=1
echo "Enter those numbers: "
while [ $i -le $N ]; do
    read num
    numbers+=($num)
    i=$((i+1))
done

average() {
    sum=0
    for num in "${numbers[@]}"; do
        sum=$((sum + num))
    done
    echo "Average: $((sum / N))"
}

findMinDigit() {
    echo "Enter a number to find the minimum digit:"
    read num

    min_digit=9
    while [ $num -gt 0 ]; do
        digit=$((num % 10))
        if [ $digit -lt $min_digit ]; then
            min_digit=$digit
        fi
        num=$((num / 10))
    done
    echo "Min digit: $min_digit"
}

findMaxDigit() {
    echo "Enter a number to find the maximum digit:"
    read num

    max_digit=0
    while [ $num -gt 0 ]; do
        digit=$((num % 10))
        if [ $digit -gt $max_digit ]; then
            max_digit=$digit
        fi
        num=$((num / 10))
    done

    echo "Max digit: $max_digit"
}


average
findMinDigit
findMaxDigit


3. Perform sorting on given array elements
PROGARM:

echo "Enter Size of array:"
read N

numbers=()
i=1
echo "Enter those numbers: "
while [ $i -le $N ]; do
    read num
    numbers+=($num)
    i=$((i+1))
done

sortArray() {
    sorted_numbers=($(for i in "${numbers[@]}"; do echo $i; done | sort -n))
    echo "Sorted numbers: ${sorted_numbers[@]}"
}

sortArray


4.Program to find factorial of a given number with and without recursion
With recursion:

echo "Enter the Number:"
read Number

factorial() {
    if [ $1 -le 1 ]; then
        echo 1
    else
        prev=$(factorial $(( $1 - 1 )))
        echo $(( $1 * prev ))
    fi
}

result=$(factorial $Number)
echo "Factorial of $Number is $result”


Without recursion:
PROGARM:
#!/bin/bash
echo "Enter the number:"
read Number

factorial=1

for (( i=1; i<=Number; i++))
do
factorial=$((factorial * i))
done
echo "Factorial for $Number is $factorial"


5.Program to check file type and permission for a given file
echo "Enter the file name:"
read file

if [ ! -e "$file" ]; then
    echo "File does not exist."
    exit 1
fi

if [ -f "$file" ]; then
    echo "$file is a regular file."
elif [ -d "$file" ]; then
    echo "$file is a directory."
else
    echo "$file is of another type."
fi

if [ -r "$file" ]; then
    echo "You have read permission on $file."
else
    echo "You do not have read permission on $file."
fi

if [ -w "$file" ]; then
    echo "You have write permission on $file."
else
    echo "You do not have write permission on $file."
fi

if [ -x "$file" ]; then
    echo "You have execute permission on $file."
else
    echo "You do not have execute permission on $file."
fi

OUTPUT:
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./filePandT.sh
Enter the file name:
factWrec.sh
factWrec.sh is a regular file.
You have read permission on factWrec.sh.
You have write permission on factWrec.sh.
You have execute permission on factWrec.sh.
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./factWrec.sh
Enter the Number:
^C
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./filePandT.sh
Enter the file name:
mm
mm is a directory.
You have read permission on mm.
You have write permission on mm.
You have execute permission on mm.
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./filePandT.sh
Enter the file name:
mydate
mydate is a regular file.
You have read permission on mydate.
You have write permission on mydate.
You do not have execute permission on mydate.











6.Check entered string is palindrome or not?
PROGARM:
#!/bin/bash

echo "Enter the string:"
read string

len=${#string}
i=0
flag=0

while [ $i -lt $len ]; do
    ch1=$(echo "$string" | cut -c $((i + 1)))
    ch2=$(echo "$string" | cut -c $len)

    if [ "$ch1" != "$ch2" ]; then
        flag=1
        break
    fi

    i=$((i + 1))
    len=$((len - 1))
done

if [ $flag -eq 0 ]; then
    echo "$string is a palindrome"
else
    echo "$string is not a palindrome"
fi

OUTPUT:
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./pal.sh
Enter the string:
aba
aba is a palindrome
(base) pratikvikramdavare@Pratiks-MacBook-Air os % ./pal.sh
Enter the string:
abdsa
abdsa is not a palindrome










