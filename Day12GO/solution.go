package main

import (
	"bufio"
	"log"
	"os"
)

type finalRec struct {
	corner int
	area   int
}

func recursiveFindSimilarPlots(initialValue rune, grid [][]rune, gridChecked [][]bool, curX int, curY int) finalRec {
	//early exit
	if gridChecked[curY][curX] {
		return finalRec{0, 0}
	}
	gridChecked[curY][curX] = true
	currentCorner := 0
	currentArea := 1
	outs := make([]finalRec, 0)
	upAvail := false
	downAvail := false
	leftAvail := false
	rightAvail := false
	if curX > 0 && grid[curY][curX-1] == initialValue {
		leftAvail = true
		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX-1, curY))
	}
	if curY > 0 && grid[curY-1][curX] == initialValue {
		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX, curY-1))
		upAvail = true
	}
	if curX < len(grid[curY])-1 && grid[curY][curX+1] == initialValue {
		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX+1, curY))
		rightAvail = true
	}
	if curY < len(grid)-1 && grid[curY+1][curX] == initialValue {
		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX, curY+1))
		downAvail = true
	}
	//normal corner checks
	if !leftAvail && !upAvail {
		currentCorner++
	}
	if !rightAvail && !upAvail {
		currentCorner++
	}
	if !leftAvail && !downAvail {
		currentCorner++
	}
	if !rightAvail && !downAvail {
		currentCorner++
	}
	//concaved corner checks
	if leftAvail && upAvail && grid[curY-1][curX-1] != initialValue {
		currentCorner++
	}
	if rightAvail && upAvail && grid[curY-1][curX+1] != initialValue {
		currentCorner++
	}
	if leftAvail && downAvail && grid[curY+1][curX-1] != initialValue {
		currentCorner++
	}
	if rightAvail && downAvail && grid[curY+1][curX+1] != initialValue {
		currentCorner++
	}
	for _, outs := range outs {
		currentCorner += outs.corner
		currentArea += outs.area
	}
	return finalRec{area: currentArea, corner: currentCorner}

}
func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	grid := [][]rune{}
	scanner := bufio.NewScanner(file)
	gridChecked := [][]bool{}
	index := 0
	for scanner.Scan() {
		current := scanner.Text()
		grid = append(grid, make([]rune, 0))
		for _, char := range current {
			grid[index] = append(grid[index], char)
		}
		gridChecked = append(gridChecked, make([]bool, len(grid[index])))
		index++
	}
	output := 0
	for y := 0; y < len(grid); y++ {
		for x := 0; x < len(grid[0]); x++ {
			if !gridChecked[y][x] {
				current := recursiveFindSimilarPlots(grid[y][x], grid, gridChecked, x, y)
				println("plotType:", string(grid[y][x]), "firstCord: Y", y, ",X", x, "| corner:", current.corner, " area:", current.area, "output:", current.area*current.corner)
				output += (current.area * current.corner)
			}
		}
	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

//part 1
// type finalRec struct {
// 	perimeter int
// 	area      int
// }

// func recursiveFindSimilarPlots(initialValue rune, grid [][]rune, gridChecked [][]bool, curX int, curY int) finalRec {
// 	//early exit
// 	if gridChecked[curY][curX] {
// 		return finalRec{0, 0}
// 	}
// 	gridChecked[curY][curX] = true
// 	currentParam := 0
// 	currentArea := 1
// 	outs := make([]finalRec, 0)
// 	if curX > 0 && grid[curY][curX-1] == initialValue {
// 		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX-1, curY))
// 	} else {
// 		currentParam += 1
// 	}
// 	if curY > 0 && grid[curY-1][curX] == initialValue {
// 		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX, curY-1))
// 	} else {
// 		currentParam += 1
// 	}
// 	if curX < len(grid[curY])-1 && grid[curY][curX+1] == initialValue {
// 		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX+1, curY))
// 	} else {
// 		currentParam += 1
// 	}
// 	if curY < len(grid)-1 && grid[curY+1][curX] == initialValue {
// 		outs = append(outs, recursiveFindSimilarPlots(initialValue, grid, gridChecked, curX, curY+1))
// 	} else {
// 		currentParam += 1
// 	}
// 	for _, outs := range outs {
// 		currentParam += outs.perimeter
// 		currentArea += outs.area
// 	}
// 	return finalRec{area: currentArea, perimeter: currentParam}

// }
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()
// 	grid := [][]rune{}
// 	scanner := bufio.NewScanner(file)
// 	gridChecked := [][]bool{}
// 	index := 0
// 	for scanner.Scan() {
// 		current := scanner.Text()
// 		grid = append(grid, make([]rune, 0))
// 		for _, char := range current {
// 			grid[index] = append(grid[index], char)
// 		}
// 		gridChecked = append(gridChecked, make([]bool, len(grid[index])))
// 		index++
// 	}
// 	output := 0
// 	for y := 0; y < len(grid); y++ {
// 		for x := 0; x < len(grid[0]); x++ {
// 			if !gridChecked[y][x] {
// 				current := recursiveFindSimilarPlots(grid[y][x], grid, gridChecked, x, y)
// 				println("plotType:", string(grid[y][x]), "firstCord: Y", y, ",X", x, "| parim:", current.perimeter, " area:", current.area, "output:", current.area*current.perimeter)
// 				output += (current.area * current.perimeter)
// 			}
// 		}
// 	}
// 	println(output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
