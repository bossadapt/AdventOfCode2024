package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

func removeLeadingZero(input string) string {
	indexThatIsNotZero := 0
	for _, char := range input {
		if char != '0' {
			break
		}
		indexThatIsNotZero++
	}
	if indexThatIsNotZero == len(input) {
		return "0"
	}
	return input[indexThatIsNotZero:]
}

//stolen from a rust solution but worse because i didnt dealth with splitting numbers mathmatically
//yoinked specifically from https://github.com/XavilPergis
//it keeps state of a path taken already based on depth x number
// helps alot do the cyclical nature of common problems of the engraving being 0-9 and depth being 0-74 leaving 750 very abused caches, plus a few others
// fn seq_count(cache: &mut AHashMap<u64, u64>, num: u64, depth: u8) -> u64 {
//     if depth == 75 {
//         // base case
//         return 1;
//     }

//     let key = num | (depth as u64) << 56;
//     if let Some(&cached) = cache.get(&key) {
//         return cached;
//     }

//     let res = if num == 0 {
//         seq_count(cache, 1, depth + 1)
//     } else if let Some((l, r)) = split_digits(num) {
//         seq_count(cache, l, depth + 1) + seq_count(cache, r, depth + 1)
//     } else {
//         seq_count(cache, num * 2024, depth + 1)
//     };

//	    cache.insert(key, res);
//	    res
//	}
type recState struct {
	stoneEngravings string
	depth           int
}

func recursiveCachedApproach(cache map[recState]int, stoneEngravings string, depth int) int {
	//base
	if depth == 75 {
		return 1
	}
	//if we have been here before, check skip the rest of the steps
	key := recState{stoneEngravings: stoneEngravings, depth: depth}
	if cachedStoneCount, ok := cache[key]; ok {
		return cachedStoneCount
	}
	var output int
	if stoneEngravings == "0" {
		output = recursiveCachedApproach(cache, "1", depth+1)
	} else if len(stoneEngravings)%2 == 0 {
		output = recursiveCachedApproach(cache, stoneEngravings[:len(stoneEngravings)/2], depth+1) + recursiveCachedApproach(cache, removeLeadingZero(stoneEngravings[len(stoneEngravings)/2:]), depth+1)
	} else {
		int1, err := strconv.Atoi(stoneEngravings)
		if err != nil {
			log.Fatal("brok")
		}
		output = recursiveCachedApproach(cache, strconv.Itoa(int1*2024), depth+1)
	}
	//create a new already cached value of depth x stoneEngraving
	cache[key] = output
	return output

}
func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	//states that have occured and
	cache := make(map[recState]int)
	scanner := bufio.NewScanner(file)
	//load stones into an array
	output := 0
	for scanner.Scan() {
		var currentLine string = scanner.Text()
		stones := strings.Fields(currentLine)
		for _, stone := range stones {
			output += recursiveCachedApproach(cache, stone, 0)
		}
	}
	println(output)
}

// part 1
// func removeLeadingZero(input string) string {
// 	indexThatIsNotZero := 0
// 	for _, char := range input {
// 		if char != '0' {
// 			break
// 		}
// 		indexThatIsNotZero++
// 	}
// 	if indexThatIsNotZero == len(input) {
// 		return "0"
// 	}
// 	return input[indexThatIsNotZero:]
// }
// func main() {
// 	//file, err := os.Open("example.txt")
// 	file, err := os.Open("question.txt")
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	//load stones into an array
// 	stoneArray := []string{}
// 	for scanner.Scan() {
// 		var currentLine string = scanner.Text()
// 		stones := strings.Fields(currentLine)
// 		stoneArray = append(stoneArray, stones...)
// 	}
// 	carriedStones := []string{}
// 	for blinkIdx := 0; blinkIdx < 75; blinkIdx++ {
// 		for i := 0; i < len(stoneArray); i++ {
// 			// If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
// 			if stoneArray[i][0] == byte('0') {
// 				if len(carriedStones) > 0 {
// 					stoneArray[i] = carriedStones[0]
// 					carriedStones = carriedStones[1:]
// 					carriedStones = append(carriedStones, "1")
// 				} else {
// 					stoneArray[i] = "1"
// 				}
// 				continue
// 			} else if len(stoneArray[i])%2 == 0 {
// 				// If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
// 				firstHalf := stoneArray[i][:len(stoneArray[i])/2]
// 				secondHalf := removeLeadingZero(stoneArray[i][len(stoneArray[i])/2:])
// 				if len(carriedStones) > 0 {
// 					stoneArray[i] = carriedStones[0]
// 					carriedStones = carriedStones[1:]
// 					carriedStones = append(carriedStones, firstHalf)
// 					carriedStones = append(carriedStones, secondHalf)
// 				} else {
// 					stoneArray[i] = firstHalf
// 					carriedStones = append(carriedStones, secondHalf)
// 				}
// 			} else {
// 				// If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
// 				int1, err := strconv.Atoi(stoneArray[i])
// 				if err != nil {
// 					log.Fatal("brok")
// 				}
// 				currentInt := strconv.Itoa(int1 * 2024)
// 				if len(carriedStones) > 0 {
// 					stoneArray[i] = carriedStones[0]
// 					carriedStones = carriedStones[1:]
// 					carriedStones = append(carriedStones, currentInt)
// 				} else {
// 					stoneArray[i] = currentInt
// 				}
// 			}
// 		}
// 		//add the rest of the carried stones
// 		stoneArray = append(stoneArray, carriedStones...)
// 		carriedStones = []string{}
// 		// println("Blink ", blinkIdx+1, ":")
// 		// for _, stone := range stoneArray {
// 		// 	print(stone, ",")
// 		// }
// 		// println()
// 	}
// 	println(len(stoneArray))
// 	if err := scanner.Err(); err != nil {
// 		log.Fatal(err)
// 	}
// }
