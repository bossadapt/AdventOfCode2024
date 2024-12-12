package main

import (
	"bufio"
	"log"
	"os"
)

type cord struct {
	x int
	y int
}

func recursiveFindAll9Paths(start cord, current cord, grid [][]int) int {
	//found a goal(base case)
	if grid[current.y][current.x] == 9 {
		return 1
	}
	//looking for goal
	goalsFound := 0
	currentVal := grid[current.y][current.x]
	if current.y < len(grid)-1 && grid[current.y+1][current.x]-currentVal == 1 {
		goalsFound += recursiveFindAll9Paths(start, cord{y: current.y + 1, x: current.x}, grid)
	}
	if current.x < len(grid[current.y])-1 && grid[current.y][current.x+1]-currentVal == 1 {
		goalsFound += recursiveFindAll9Paths(start, cord{y: current.y, x: current.x + 1}, grid)
	}
	if current.y > 0 && grid[current.y-1][current.x]-currentVal == 1 {
		goalsFound += recursiveFindAll9Paths(start, cord{y: current.y - 1, x: current.x}, grid)
	}
	if current.x > 0 && grid[current.y][current.x-1]-currentVal == 1 {
		goalsFound += recursiveFindAll9Paths(start, cord{y: current.y, x: current.x - 1}, grid)
	}
	return goalsFound
}
func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	grid := [][]int{}
	yIndex := 0
	var starterSpots []cord
	for scanner.Scan() {
		var currentLine []rune = []rune(scanner.Text())
		grid = append(grid, []int{})
		for x := 0; x < len(currentLine); x++ {
			if currentLine[x] == '.' {
				grid[yIndex] = append(grid[yIndex], -1)
			} else if currentLine[x] == '0' {
				//add starter spots
				grid[yIndex] = append(grid[yIndex], 0)
				starterSpots = append(starterSpots, cord{y: yIndex, x: x})
			} else if currentLine[x] == '9' {
				//add starter spots
				grid[yIndex] = append(grid[yIndex], 9)
			} else {
				grid[yIndex] = append(grid[yIndex], int(currentLine[x]-'0'))
			}
		}
		yIndex++
	}
	output := 0
	for _, start := range starterSpots {
		output += recursiveFindAll9Paths(start, start, grid)
	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()
// 	scanner := bufio.NewScanner(file)
// 	grid := [][]int{}
// 	yIndex := 0
// 	var starterSpots []cord
// 	endSpotsWithReachedList := make(map[cord][]cord)
// 	for scanner.Scan() {
// 		var currentLine []rune = []rune(scanner.Text())
// 		grid = append(grid, []int{})
// 		for x := 0; x < len(currentLine); x++ {
// 			if currentLine[x] == '.' {
// 				grid[yIndex] = append(grid[yIndex], -1)
// 			} else if currentLine[x] == '0' {
// 				//add starter spots
// 				grid[yIndex] = append(grid[yIndex], 0)
// 				starterSpots = append(starterSpots, cord{y: yIndex, x: x})
// 			} else if currentLine[x] == '9' {
// 				//add starter spots
// 				grid[yIndex] = append(grid[yIndex], 9)
// 				endSpotsWithReachedList[cord{x: x, y: yIndex}] = []cord{}
// 			} else {
// 				grid[yIndex] = append(grid[yIndex], int(currentLine[x]-'0'))
// 			}
// 		}
// 		yIndex++
// 	}
// 	output := 0
// 	for _, start := range starterSpots {
// 		output += recursiveFindAll9Paths(start, start, endSpotsWithReachedList, grid)
// 	}
// 	println(output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
