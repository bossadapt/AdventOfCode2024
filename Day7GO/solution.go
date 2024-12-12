package main

import (
	"bufio"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
	"sync"
)

func concatWithMath(first int, second int) int {
	var b float64
	if second < 10 {
		b = 1.
	} else if second < 100 {
		b = 2.
	} else {
		b = 3.
	}
	temp := first*int(math.Pow(10, b)) + second
	return temp
}
func cloneAndSetVal(permutationArray []int, idx int, newVal int) []int {
	newArray := make([]int, len(permutationArray))
	copy(newArray, permutationArray)
	newArray[idx] = newVal
	return newArray
}

func permutateOperatorRecursiveEquals(idx int, permutationArray []int, nums []int, goalValue int) bool {
	if idx == len(permutationArray) {
		total := nums[0]
		for i := 0; i < len(permutationArray); i++ {
			if total > goalValue {
				return false
			}
			switch permutationArray[i] {
			case 0:
				total += nums[i+1]
			case 1:
				total *= nums[i+1]
			case 2:
				total = concatWithMath(total, nums[i+1])
			}
		}
		return total == goalValue
	} else {
		return permutateOperatorRecursiveEquals(idx+1, cloneAndSetVal(permutationArray, idx, 0), nums, goalValue) ||
			permutateOperatorRecursiveEquals(idx+1, cloneAndSetVal(permutationArray, idx, 1), nums, goalValue) ||
			permutateOperatorRecursiveEquals(idx+1, cloneAndSetVal(permutationArray, idx, 2), nums, goalValue)
	}
}
func solution() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	lines := []string{}
	for scanner.Scan() {
		lines = append(lines, scanner.Text())

	}
	out := make(chan int)
	var wg sync.WaitGroup
	wg.Add(len(lines))
	for index := 0; index < len(lines); index++ {
		go func(currentLine string) {
			defer wg.Done()
			firstSplit := strings.Split(currentLine, ":")
			goalNumber, err := strconv.Atoi(firstSplit[0])
			if err == nil {
				numbers := strings.Fields(firstSplit[1])
				nums := []int{}
				for i := 0; i < len(numbers); i++ {
					currentNum, err := strconv.Atoi(numbers[i])
					if err == nil {
						nums = append(nums, currentNum)
					}
				}
				multiplyPermutation := make([]int, len(nums)-1)
				if permutateOperatorRecursiveEquals(0, multiplyPermutation, nums, goalNumber) {
					out <- goalNumber
				}

			}
		}(lines[index])
	}
	go func() {
		wg.Wait()
		close(out)
	}()

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
	output := 0
	for currentOut := range out {
		output += currentOut
	}
	println(output)
}
func main() {
	solution()
}

//Part 1
// func cloneAndSetVal(permutationArray []bool, idx int, newVal bool) []bool {
// 	newArray := make([]bool, len(permutationArray))
// 	for i := 0; i < len(permutationArray); i++ {
// 		newArray[i] = permutationArray[i]
// 	}
// 	newArray[idx] = newVal
// 	return newArray
// }
// func permutationRec(idx int, permutationArray []bool, nums []int, goalValue int) bool {

// 	if idx == len(permutationArray) {
// 		total := nums[0]
// 		for i := 0; i < len(permutationArray); i++ {
// 			if permutationArray[i] {
// 				total += nums[i+1]
// 			} else {
// 				total *= nums[i+1]
// 			}
// 		}
// 		return total == goalValue
// 	} else {
// 		return permutationRec(idx+1, cloneAndSetVal(permutationArray, idx, true), nums, goalValue) || permutationRec(idx+1, cloneAndSetVal(permutationArray, idx, false), nums, goalValue)
// 	}
// }
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	output := 0
// 	for scanner.Scan() {
// 		var currentLine string = scanner.Text()
// 		firstSplit := strings.Split(currentLine, ":")
// 		goalNumber, err := strconv.Atoi(firstSplit[0])
// 		if err == nil {
// 			numbers := strings.Fields(firstSplit[1])
// 			nums := []int{}
// 			for i := 0; i < len(numbers); i++ {
// 				currentNum, err := strconv.Atoi(numbers[i])
// 				if err == nil {
// 					nums = append(nums, currentNum)
// 				}
// 			}
// 			multiplyPermutation := make([]bool, len(nums)-1)
// 			if permutationRec(0, multiplyPermutation, nums, goalNumber) {
// 				output += goalNumber
// 			}

// 		}

// 	}

// 	println(output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
