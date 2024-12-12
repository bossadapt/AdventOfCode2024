package main

import (
	"bufio"
	"log"
	"os"
)

// type cord struct {
// 	x int
// 	y int
// }

func main() {
	file, err := os.Open("example.txt")
	//file, err := os.Open("question.txt")
	output := 0
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	// //string start
	// for scanner.Scan() {
	// 	var currentLine string = scanner.Text()
	// 	//comma
	// 	commaSplit := strings.Split(currentLine, ",")
	// 	//white space
	// 	fields := strings.Fields(currentLine)
	// }

	//rune grid start
	// grid := [][]rune{}
	// index := 0
	// for scanner.Scan() {
	// 	current := scanner.Text()
	// 	grid = append(grid, make([]rune, 0))
	// 	for _, char := range current {
	// 		grid[index] = append(grid[index], char)
	// 	}
	// }

	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
