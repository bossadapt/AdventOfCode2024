package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	//just testing
	//toposort "github.com/gammazero/toposort"
)

// brute force part 2 without topological sort
func main() {
	rules := make(map[string]map[string]bool)
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	output := 0
	rulesFinished := false
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		var currentLine string = scanner.Text()
		if len(currentLine) == 0 {
			rulesFinished = true
		} else if !rulesFinished {
			splitRule := strings.Split(currentLine, "|")
			if _, ok := rules[splitRule[0]]; ok {
				rules[splitRule[0]][splitRule[1]] = true
			} else {
				rules[splitRule[0]] = make(map[string]bool)
				rules[splitRule[0]][splitRule[1]] = true
			}
		} else {
			splitPages := strings.Split(currentLine, ",")
			brokeRules := false
			println("==================new list=======================================")
			for i := 0; i < len(splitPages); i++ {
				println("ran page with page", splitPages[i])
				if currentDisallowed, ok := rules[splitPages[i]]; ok {
					innerBreakCalled := false
					for x := i - 1; x >= 0 && !innerBreakCalled; x-- {
						//for z := 0; z < len(currentDisallowed); z++ {
						//if splitPages[x] == currentDisallowed[z] {
						if currentDisallowed[splitPages[x]] {
							brokeRules = true
							temp := splitPages[x]
							splitPages[x] = splitPages[i]
							splitPages[i] = temp
							i = x - 1
							innerBreakCalled = true
							println("broke rule when it found:", splitPages[x], " at index ", x)
							break
						}
						//}
					}
				}

			}
			if brokeRules {
				println("rules broken")
				fmt.Printf("%v", splitPages)
				middleVal, err := strconv.Atoi(splitPages[(len(splitPages) / 2)])
				println("middle val:", middleVal)
				if err != nil {
					log.Fatal("ruh roh")
				}
				output += middleVal
			} else {
				println("rules not broken")
			}
		}
	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

//brute forced first part
// func main() {
// 	rules := make(map[string][]string)
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()
// 	output := 0
// 	rulesFinished := false
// 	scanner := bufio.NewScanner(file)
// 	for scanner.Scan() {
// 		var currentLine string = scanner.Text()
// 		if len(currentLine) == 0 {
// 			rulesFinished = true
// 		} else if !rulesFinished {
// 			splitRule := strings.Split(currentLine, "|")
// 			if _, ok := rules[splitRule[0]]; ok {
// 				rules[splitRule[0]] = append(rules[splitRule[0]], splitRule[1])
// 			} else {
// 				rules[splitRule[0]] = []string{splitRule[1]}
// 			}
// 		} else {
// 			splitPages := strings.Split(currentLine, ",")
// 			brokeRules := false
// 			println("==================new list=======================================")
// 			for i := 0; i < len(splitPages) && !brokeRules; i++ {
// 				println("ran page with page", splitPages[i])
// 				if currentDisallowed, ok := rules[splitPages[i]]; ok {
// 					for x := i - 1; x >= 0; x-- {
// 						for z := 0; z < len(currentDisallowed); z++ {
// 							if splitPages[x] == currentDisallowed[z] {
// 								brokeRules = true
// 								println("broke rule when it found:", currentDisallowed[z], " at index ", x)
// 							}
// 						}
// 					}
// 				}

// 			}
// 			if !brokeRules {
// 				println("rules not broken")
// 				middleVal, err := strconv.Atoi(splitPages[(len(splitPages) / 2)])
// 				println("middle val:", middleVal)
// 				if err != nil {
// 					log.Fatal("ruh roh")
// 				}
// 				output += middleVal
// 			} else {
// 				println("rules broken")
// 			}
// 		}
// 	}
// 	println(output)
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
