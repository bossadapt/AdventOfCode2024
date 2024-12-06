package main

import (
	"bufio"
	"log"
	"os"
)

type Pair struct {
	y int
	x int
}
type PairMove struct {
	y    int
	x    int
	move int
}

func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	grid := [][]rune{}
	starterCurrentLocation := Pair{x: -1, y: -1}
	movements := []Pair{
		{x: 0, y: -1},
		{x: 1, y: 0},
		{x: 0, y: 1},
		{x: -1, y: 0},
	}
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		grid = append(grid, []rune(scanner.Text()))
	}
	//find guard location
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[0]); x++ {
			if grid[y][x] == '^' {
				starterCurrentLocation.x = x
				starterCurrentLocation.y = y
				break
			}
		}
	}
	output := 0
	lastPositionUsed := Pair{-1, -1}
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[0]); x++ {
			locationsVisited := make(map[PairMove]bool)
			if grid[y][x] == '^' || grid[y][x] == '#' {
				continue
			}
			if lastPositionUsed.x != -1 {
				grid[lastPositionUsed.y][lastPositionUsed.x] = '.'
			}
			grid[y][x] = '#'
			lastPositionUsed.x = x
			lastPositionUsed.y = y
			wallRanIntoCount := 0
			guardLocation := PairMove{x: starterCurrentLocation.x, y: starterCurrentLocation.y, move: 0}
			for {
				currentMovementDirectionIndex := wallRanIntoCount % 4
				currentMovementDirection := movements[currentMovementDirectionIndex]
				nextLocation := PairMove{x: (guardLocation.x + currentMovementDirection.x), y: (guardLocation.y + currentMovementDirection.y), move: currentMovementDirectionIndex}
				if nextLocation.x < 0 || nextLocation.y < 0 || nextLocation.x == len(grid[0]) || nextLocation.y == len(grid) {
					locationsVisited[guardLocation] = true
					break
				}
				if grid[nextLocation.y][nextLocation.x] == '#' {
					wallRanIntoCount += 1
				} else {
					if _, ok := locationsVisited[guardLocation]; ok {
						output += 1
						break
					} else {
						locationsVisited[guardLocation] = true
					}
					guardLocation = nextLocation
				}

			}
		}
	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
