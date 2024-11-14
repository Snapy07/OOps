1.Print Sum of Digits of a given number using command line argument
PROGARM:

#!/bin/bash
echo "Enter the Number:"  # Prompt user for input
read number  # Read the input number

sum=0  # Initialize sum variable to 0

while [ $number -gt 0 ];  # Loop until number becomes 0
do
    digit=$((number % 10))  # Extract the last digit
    sum=$((sum + digit))  # Add the digit to the sum
    number=$((number / 10))  # Remove the last digit
done

echo "Sum of digits: $sum"  # Output the result

OUTPUT:
Enter the Number:
278273872
Sum of digits:46





2. Write a shell script using function for following:1)average of given numbers 2) Max  digit from given number and 3) min digit  from given number
echo "How many numbers do you want to enter?"

#!/bin/bash
echo "How many numbers do you want to enter?"  # Prompt user for count of numbers
read N  # Read the count

numbers=()  # Initialize an empty array
i=1
echo "Enter those numbers: "
while [ $i -le $N ]; do  # Loop to read each number
    read num  # Read each number
    numbers+=($num)  # Append number to the array
    i=$((i+1))
done

# Function to calculate average
average() {
    sum=0
    for num in "${numbers[@]}"; do  # Loop through each number in array
        sum=$((sum + num))  # Add each number to sum
    done
    echo "Average: $((sum / N))"  # Print the average
}

# Function to find the minimum digit in a given number
findMinDigit() {
    echo "Enter a number to find the minimum digit:"
    read num

    min_digit=9  # Initialize min_digit with the highest single-digit value
    while [ $num -gt 0 ]; do  # Loop until number becomes 0
        digit=$((num % 10))  # Extract the last digit
        if [ $digit -lt $min_digit ]; then
            min_digit=$digit  # Update min_digit if current digit is smaller
        fi
        num=$((num / 10))  # Remove the last digit
    done
    echo "Min digit: $min_digit"  # Print the minimum digit
}

# Function to find the maximum digit in a given number
findMaxDigit() {
    echo "Enter a number to find the maximum digit:"
    read num

    max_digit=0  # Initialize max_digit with the lowest single-digit value
    while [ $num -gt 0 ]; do  # Loop until number becomes 0
        digit=$((num % 10))  # Extract the last digit
        if [ $digit -gt $max_digit ]; then
            max_digit=$digit  # Update max_digit if current digit is larger
        fi
        num=$((num / 10))  # Remove the last digit
    done

    echo "Max digit: $max_digit"  # Print the maximum digit
}

average
findMinDigit
findMaxDigit



3. Perform sorting on given array elements
PROGARM:

#!/bin/bash
echo "Enter Size of array:"  # Prompt for the size of array
read N  # Read size of array

numbers=()  # Initialize an empty array
i=1
echo "Enter those numbers: "
while [ $i -le $N ]; do  # Loop to read each number
    read num  # Read each number
    numbers+=($num)  # Append number to the array
    i=$((i+1))
done

# Function to sort the array
sortArray() {
    sorted_numbers=($(for i in "${numbers[@]}"; do echo $i; done | sort -n))  # Sort array in ascending order
    echo "Sorted numbers: ${sorted_numbers[@]}"  # Print the sorted array
}

sortArray


4.Program to find factorial of a given number with and without recursion
With recursion:

With RECURSSION
#!/bin/bash
echo "Enter the Number:"  # Prompt for input
read Number  # Read the input number

# Recursive function to calculate factorial
factorial() {
    if [ $1 -le 1 ]; then  # Base case: factorial of 0 or 1 is 1
        echo 1
    else
        prev=$(factorial $(( $1 - 1 )))  # Recursive call to calculate (n-1)!
        echo $(( $1 * prev ))  # Multiply current number by factorial of (n-1)
    fi
}

result=$(factorial $Number)  # Store result of factorial function
echo "Factorial of $Number is $result"  # Print the result

WITHOUT RECURSSION

#!/bin/bash
echo "Enter the number:"  # Prompt for input
read Number  # Read the input number

factorial=1  # Initialize factorial as 1

for (( i=1; i<=Number; i++))  # Loop from 1 to Number
do
    factorial=$((factorial * i))  # Multiply factorial by current number
done

echo "Factorial for $Number is $factorial"  # Print the result



5.Program to check file type and permission for a given file

#!/bin/bash
echo "Enter the file name:"  # Prompt for file name
read file  # Read the file name

if [ ! -e "$file" ]; then  # Check if file exists
    echo "File does not exist."
    exit 1
fi

if [ -f "$file" ]; then  # Check if it's a regular file
    echo "$file is a regular file."
elif [ -d "$file" ]; then  # Check if it's a directory
    echo "$file is a directory."
else
    echo "$file is of another type."
fi

# Check read permission
if [ -r "$file" ]; then
    echo "You have read permission on $file."
else
    echo "You do not have read permission on $file."
fi

# Check write permission
if [ -w "$file" ]; then
    echo "You have write permission on $file."
else
    echo "You do not have write permission on $file."
fi

# Check execute permission
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

#!/bin/bash
echo "Enter the string:"  # Prompt for input
read string  # Read the string

len=${#string}  # Length of the string
i=0  # Initialize starting index
flag=0  # Initialize flag as 0

while [ $i -lt $len ]; do  # Loop until reaching the center of the string
    ch1=$(echo "$string" | cut -c $((i + 1)))  # Get character from the beginning
    ch2=$(echo "$string" | cut -c $len)  # Get character from the end

    if [ "$ch1" != "$ch2" ]; then  # Compare characters
        flag=1  # Set flag if characters don't match
        break
    fi

    i=$((i + 1))  # Move forward from the beginning
    len=$((len - 1))  # Move backward from the end
done

if [ $flag -eq 0 ]; then
    echo "$string is a palindrome"  # Print if palindrome
else
    echo "$string is not a palindrome"  # Print if not palindrome
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










