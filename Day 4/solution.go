package main

import (
	"bufio"
	"log"
	"os"
)

func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	xmasGraph := make([]string, 0)
	for scanner.Scan() {
		xmasGraph = append(xmasGraph, scanner.Text())
	}
	output := 0
	for y := 1; y < len(xmasGraph)-1; y++ {
		for x := 1; x < len(xmasGraph[0])-1; x++ {
			//find xmas based on x
			masCounter := 0
			if xmasGraph[y][x] == 'A' {
				//check top left
				if xmasGraph[y+1][x-1] == 'M' {
					if xmasGraph[y-1][x+1] == 'S' {
						masCounter += 1
					}
				}
				//check bottom left
				if xmasGraph[y-1][x-1] == 'M' {
					if xmasGraph[y+1][x+1] == 'S' {
						masCounter += 1
					}
				}
				//check top right
				if xmasGraph[y+1][x+1] == 'M' {
					if xmasGraph[y-1][x-1] == 'S' {
						masCounter += 1
					}

				}

				//check bottom right
				if xmasGraph[y-1][x+1] == 'M' {
					if xmasGraph[y+1][x-1] == 'S' {
						masCounter += 1
					}

				}
			}
			if masCounter == 2 {
				output += 1
			}
		}

	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

// ugly first part, forgot i could just start the iterator and end it earlier
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	xmasGraph := make([]string, 0)
// 	for scanner.Scan() {
// 		xmasGraph = append(xmasGraph, scanner.Text())
// 	}
// 	output := 0
// 	println(xmasGraph[0])
// 	println(xmasGraph[0][0] == 'M')
// 	for y := 0; y < len(xmasGraph); y++ {
// 		for x := 0; x < len(xmasGraph[0]); x++ {
// 			//find xmas based on x
// 			downAvail := false
// 			upAvail := false
// 			if xmasGraph[y][x] == 'X' {
// 				println("x found")
// 				//check down
// 				if y < len(xmasGraph)-3 {
// 					downAvail = true
// 					if xmasGraph[y+1][x] == 'M' {
// 						if xmasGraph[y+2][x] == 'A' {
// 							if xmasGraph[y+3][x] == 'S' {
// 								output += 1
// 							}
// 						}
// 					}
// 				}
// 				//check up
// 				if y > 2 {

// 					upAvail = true
// 					if xmasGraph[y-1][x] == 'M' {
// 						if xmasGraph[y-2][x] == 'A' {
// 							if xmasGraph[y-3][x] == 'S' {
// 								output += 1
// 							}
// 						}
// 					}
// 				}
// 				//check left
// 				if x > 2 {
// 					if xmasGraph[y][x-1] == 'M' {
// 						if xmasGraph[y][x-2] == 'A' {
// 							if xmasGraph[y][x-3] == 'S' {
// 								output += 1
// 							}
// 						}
// 					}
// 					//check top left
// 					if downAvail {
// 						if xmasGraph[y+1][x-1] == 'M' {
// 							if xmasGraph[y+2][x-2] == 'A' {
// 								if xmasGraph[y+3][x-3] == 'S' {
// 									output += 1
// 								}
// 							}
// 						}
// 					}
// 					//check bottom left
// 					if upAvail {
// 						if xmasGraph[y-1][x-1] == 'M' {
// 							if xmasGraph[y-2][x-2] == 'A' {
// 								if xmasGraph[y-3][x-3] == 'S' {
// 									output += 1
// 								}
// 							}
// 						}
// 					}
// 				}
// 				//check right
// 				if x < len(xmasGraph[0])-3 {
// 					if xmasGraph[y][x+1] == 'M' {
// 						if xmasGraph[y][x+2] == 'A' {
// 							if xmasGraph[y][x+3] == 'S' {
// 								output += 1
// 							}
// 						}
// 					}
// 					//check top right
// 					if downAvail {
// 						if xmasGraph[y+1][x+1] == 'M' {
// 							if xmasGraph[y+2][x+2] == 'A' {
// 								if xmasGraph[y+3][x+3] == 'S' {
// 									output += 1
// 								}
// 							}
// 						}
// 					}
// 					//check bottom right
// 					if upAvail {
// 						if xmasGraph[y-1][x+1] == 'M' {
// 							if xmasGraph[y-2][x+2] == 'A' {
// 								if xmasGraph[y-3][x+3] == 'S' {
// 									output += 1
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}

// 	}
// 	println(output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
