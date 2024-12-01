package main

//comments = from first 1
import (
	"bufio"
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

func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	var firstColumn []int
	//var secondColumn []int
	secondColumn := make(map[int]int)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		var currentLine string = scanner.Text()
		fields := strings.Fields(currentLine)
		first, err1 := strconv.Atoi(fields[0])
		second, err2 := strconv.Atoi(fields[1])
		if err1 == nil && err2 == nil {
			firstColumn = append(firstColumn, first)
			if num, ok := secondColumn[second]; ok {
				secondColumn[second] = num + 1
			} else {
				secondColumn[second] = 1
			}
		} else {
			log.Println(err1)
			log.Fatal(err2)
		}
	}
	// sort.Slice(firstColumn, func(i, j int) bool {
	// 	return firstColumn[i] < firstColumn[j]
	// })
	// sort.Slice(secondColumn, func(i, j int) bool {
	// 	return secondColumn[i] < secondColumn[j]
	// })
	var output int = 0
	// for i := 0; i < len(firstColumn); i++ {
	// 	output += absDiffInt(firstColumn[i], secondColumn[i])
	// }
	for i := 0; i < len(firstColumn); i++ {
		if num, ok := secondColumn[firstColumn[i]]; ok {
			output += (num * firstColumn[i])
		}
	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
