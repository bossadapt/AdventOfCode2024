package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func absDiffInt(x, y int) int {
	if x < y {
		return y - x
	}
	return x - y
}
func convertToIntArray(inputLine string) []int {
	var reportLevels = strings.Fields(inputLine)
	var output = make([]int, len(reportLevels))
	for i := 0; i < len(output); i++ {
		temp, err := strconv.Atoi(reportLevels[i])
		if err != nil {
			log.Fatal("convert failure")
		}
		output[i] = temp
	}
	return output
}
func rebuildWithoutIndex(list []int, index int) []int {
	println("before: ", strings.Trim(strings.Join(strings.Fields(fmt.Sprint(list)), ","), "[]"))
	newList := make([]int, 0)
	newList = append(newList, list[:index]...)
	newList = append(newList, list[index+1:]...)
	println("after: ", strings.Trim(strings.Join(strings.Fields(fmt.Sprint(newList)), ","), "[]"))
	return newList
}
func testSafe(reportLevels []int, removalActive bool) bool {
	var initalLevel = reportLevels[0]
	var prevLevel = reportLevels[1]
	var increasing bool = initalLevel < prevLevel
	var dif = absDiffInt(initalLevel, prevLevel)
	if dif < 1 || dif > 3 {
		if removalActive {
			return testSafe(rebuildWithoutIndex(reportLevels, 1), false)
		} else {
			return false
		}
	}
	for i := 2; i < len(reportLevels); i++ {
		var tempLevel = reportLevels[i]
		var dif = absDiffInt(prevLevel, tempLevel)
		if prevLevel < tempLevel != increasing || dif < 1 || dif > 3 {
			if removalActive {
				println("increasing test:", prevLevel < tempLevel != increasing)
				println("dif test:", dif < 1 || dif > 3)
				test1 := testSafe(rebuildWithoutIndex(reportLevels, i-1), false)
				test2 := testSafe(rebuildWithoutIndex(reportLevels, i), false)
				println("testing with removal of ", reportLevels[i-1], ":", test1)
				println("testing with removal of ", reportLevels[i], ":", test2)
				return test1 || test2
			} else {
				return false
			}
		}
		prevLevel = tempLevel
	}
	return true
}
func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var safeCount int = 0
	for scanner.Scan() {
		var currentLine string = scanner.Text()
		var reportLevels = convertToIntArray(currentLine)
		if testSafe(reportLevels, true) || testSafe(rebuildWithoutIndex(reportLevels, 0), false) {
			safeCount += 1
			println("safe")
		} else {
			println("unsafe")
		}

	}

	println(safeCount)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

// part 2
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	var safeCount int = 0
// 	for scanner.Scan() {
// 		var currentLine string = scanner.Text()
// 		var reportLevels = strings.Fields(currentLine)
// 		var initalLevel, err1 = strconv.Atoi(reportLevels[0])
// 		var currentLevel, err2 = strconv.Atoi(reportLevels[1])

// 		var increasing bool = initalLevel < currentLevel

// 		var safe bool = true
// 		var dif = absDiffInt(initalLevel, currentLevel)
// 		if dif < 1 || dif > 3 {
// 			safe = false
// 			println("unsafe")
// 		}
// 		if err1 != nil || err2 != nil {
// 			log.Fatal("broke")
// 		}
// 		for i := 2; i < len(reportLevels); i++ {
// 			var tempLevel, err = strconv.Atoi(reportLevels[i])
// 			if err != nil {
// 				log.Fatal("broke 2")
// 			}
// 			if currentLevel < tempLevel != increasing {
// 				safe = false
// 				println("unsafe")
// 				break
// 			}
// 			var dif = absDiffInt(currentLevel, tempLevel)
// 			if dif < 1 || dif > 3 {
// 				safe = false
// 				println("unsafe")
// 				break
// 			}
// 			currentLevel = tempLevel
// 		}
// 		if safe {
// 			println("safe")
// 			safeCount += 1
// 		}
// 	}
// 	println(safeCount)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
