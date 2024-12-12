package main

import (
	"bufio"
	"log"
	"os"
)

func ringOut(StarterX int, starterY int, grid [][]rune, antiNodeGrid [][]bool) int {
	output := 0
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[0]); x++ {
			if starterY == y && StarterX == x {
				continue
			}
			if grid[starterY][StarterX] == grid[y][x] {
				difX := -(StarterX - x)
				difY := -(starterY - y)
				antiNodeX := difX + x
				antiNodeY := difY + y
				for antiNodeX >= 0 && antiNodeY >= 0 && antiNodeY < len(grid) && antiNodeX < len(grid[0]) {
					if !antiNodeGrid[antiNodeY][antiNodeX] {
						output++
						antiNodeGrid[antiNodeY][antiNodeX] = true
					}
					antiNodeX += difX
					antiNodeY += difY
				}

			}
		}
	}
	return output
}

func solution() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	grid := [][]rune{}
	scanner := bufio.NewScanner(file)
	output := 0
	for scanner.Scan() {
		grid = append(grid, []rune(scanner.Text()))
	}
	checkCount := 0

	antiNodeGrid := make([][]bool, len(grid))
	for i := range antiNodeGrid {
		antiNodeGrid[i] = make([]bool, len(grid[0]))
	}
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[y]); x++ {
			if grid[y][x] != 46 {
				if !antiNodeGrid[y][x] {
					output++
					antiNodeGrid[y][x] = true
				}
				checkCount++
				output += ringOut(x, y, grid, antiNodeGrid)
			}
		}
	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
	println(output)
}
func main() {
	solution()
}
