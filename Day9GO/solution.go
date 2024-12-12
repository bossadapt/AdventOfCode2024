package main

import (
	"bufio"
	"log"
	"math"
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
	newMemory := []int{}
	for scanner.Scan() {
		var currentLine []rune = []rune(scanner.Text())
		for i := 0; i < len(currentLine); i++ {
			//adding memory
			if i%2 == 0 {
				for x := 0; x < int(currentLine[i]-'0'); x++ {
					newMemory = append(newMemory, i/2)
				}
			} else {
				for x := 0; x < int(currentLine[i]-'0'); x++ {
					newMemory = append(newMemory, -1)
				}
			}
		}
		r := len(newMemory) - 1
		lastUsedRID := math.MaxInt
		for r > 0 {
			if newMemory[r] == -1 || lastUsedRID < newMemory[r] {
				r--
			} else {
				lengthFound := 0
				indexStartedR := r
				valueStartedR := newMemory[r]
				lastUsedRID = valueStartedR
				for r > 0 && newMemory[r] == newMemory[indexStartedR] {
					lengthFound += 1
					r--
				}
				l := 0
				for l <= r {
					if newMemory[l] != -1 {
						l++
					} else {
						spaceFoundLength := 0
						indexStartedL := l
						for l < len(newMemory) && newMemory[l] == -1 {
							spaceFoundLength += 1
							l++
						}
						if spaceFoundLength >= lengthFound {
							//overwrite old spot
							for index := range lengthFound {
								newMemory[indexStartedR-index] = -1
							}
							//make new spot

							for index := range lengthFound {
								newMemory[indexStartedL+index] = valueStartedR
							}
							break
						}
					}
				}
			}
		}
	}
	output := 0

	for idx, out := range newMemory {
		if out != -1 {
			output += (idx * out)
		}
	}
	println("output:", output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

//more efficient fragmantation but wrong answer
// func main() {
// 	file, err := os.Open("example.txt")
// 	//file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	newMemory := []int{}
// 	for scanner.Scan() {
// 		var currentLine []rune = []rune(scanner.Text())
// 		for i := 0; i < len(currentLine); i++ {
// 			//adding memory
// 			if i%2 == 0 {
// 				for x := 0; x < int(currentLine[i]-'0'); x++ {
// 					newMemory = append(newMemory, i/2)
// 				}
// 			} else {
// 				for x := 0; x < int(currentLine[i]-'0'); x++ {
// 					newMemory = append(newMemory, -1)
// 				}
// 			}
// 		}
// 		println("before:")
// 		for i := 0; i < len(newMemory); i++ {
// 			print(newMemory[i], ",")
// 		}
// 		println("done printing")
// 		println()
// 		l := 0
// 		println("l:", l)
// 		for l < len(newMemory) {
// 			if newMemory[l] != -1 {
// 				l++
// 			} else {
// 				//count space available
// 				currentSpace := 0
// 				indexStartedL := l
// 				r := len(newMemory) - 1
// 				for l < len(newMemory) && newMemory[l] == -1 {
// 					currentSpace += 1
// 					l++
// 				}
// 				println("looking for something to fill space; len:", currentSpace, "starting at index:", indexStartedL)
// 				for i := 0; i < len(newMemory); i++ {
// 					print(newMemory[i], ",")
// 				}
// 				println()
// 				for r > l {
// 					if newMemory[r] == -1 {
// 						r--
// 					} else {
// 						lengthFound := 0
// 						indexStartedR := r
// 						valueStartedR := newMemory[r]
// 						for r > l && newMemory[r] == newMemory[indexStartedR] {
// 							lengthFound += 1
// 							r--
// 						}
// 						if lengthFound <= currentSpace {
// 							//overwrite old spot
// 							r++
// 							println("found a replacement at index: start:", r, "end", indexStartedR, "with length", lengthFound)
// 							for r < indexStartedR+1 {
// 								newMemory[r] = -1
// 								r++
// 							}
// 							r--
// 							//make new spot
// 							for l-lengthFound+currentSpace > indexStartedL {
// 								newMemory[indexStartedL] = valueStartedR
// 								currentSpace--
// 								indexStartedL++
// 							}
// 							println("currentSpaceLeft:", currentSpace)
// 						}

// 					}
// 				}
// 			}
// 		}
// 	}
// 	println("after:")
// 	for i := 0; i < len(newMemory); i++ {
// 		println(newMemory[i])
// 	}
// 	println("done printing")
// 	output := 0

// 	for i := 0; i < len(newMemory) && newMemory[i] != -1; i++ {
// 		output += (i * newMemory[i])
// 	}
// 	println("output:", output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }

//part 1
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	newMemory := []int{}
// 	for scanner.Scan() {
// 		var currentLine []rune = []rune(scanner.Text())
// 		for i := 0; i < len(currentLine); i++ {
// 			//adding memory
// 			if i%2 == 0 {
// 				for x := 0; x < int(currentLine[i]-'0'); x++ {
// 					newMemory = append(newMemory, i/2)
// 				}
// 			} else {
// 				for x := 0; x < int(currentLine[i]-'0'); x++ {
// 					newMemory = append(newMemory, -1)
// 				}
// 			}
// 		}
// 		println("before:")
// 		for i := 0; i < len(newMemory); i++ {
// 			println(newMemory[i])
// 		}
// 		println("done printing")
// 		println()
// 		l := 0
// 		r := len(newMemory) - 1
// 		println("l:", l)
// 		println("r:", r)
// 		for l < r {
// 			if newMemory[l] != -1 {
// 				l++
// 			} else {
// 				for l < r {
// 					if newMemory[r] == -1 {
// 						r--
// 					} else {
// 						newMemory[l] = newMemory[r]
// 						newMemory[r] = -1
// 						break
// 					}
// 				}
// 			}
// 		}
// 	}
// 	println("after:")
// 	for i := 0; i < len(newMemory); i++ {
// 		println(newMemory[i])
// 	}
// 	println("done printing")
// 	output := 0

// 	for i := 0; i < len(newMemory) && newMemory[i] != -1; i++ {
// 		println(newMemory[i])
// 		output += (i * newMemory[i])
// 		println("line ", i, "=", i*newMemory[i])
// 	}
// 	println("output:", output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
