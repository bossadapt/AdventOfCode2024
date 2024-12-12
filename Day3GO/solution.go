package main

import (
	"bufio"
	"bytes"
	"log"
	"os"
	"strconv"
)

func main() {
	//file, err := os.Open("example.txt")
	file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	output := 0
	do := true

	doString := "do()"
	doIndex := 0

	dontString := "don't()"
	dontIndex := 0

	mulString := "mul("
	mulIndex := 0
	var currentFirstNum bytes.Buffer
	var currentSecondNum bytes.Buffer
	secondWord := false

	for scanner.Scan() {
		var currentLine string = scanner.Text()
		for i := 0; i < len(currentLine); i++ {
			//matching do()
			if !do {
				if doIndex == len(doString) {
					do = true
					doIndex = 0
				} else if currentLine[i] == doString[doIndex] {
					doIndex += 1
					continue
				} else {
					doIndex = 0
				}
			}
			//matching don't()
			if do {
				if dontIndex == len(doString) {
					do = false
					dontIndex = 0
				} else if currentLine[i] == dontString[dontIndex] {
					dontIndex += 1
					continue
				} else {
					dontIndex = 0
				}
			}

			//matching mul(x,x)
			if mulIndex == len(mulString) {
				if currentLine[i] >= '0' && currentLine[i] <= '9' {
					if secondWord {
						currentSecondNum.WriteByte(currentLine[i])
					} else {
						currentFirstNum.WriteByte(currentLine[i])
					}
				} else if !secondWord && currentLine[i] == ',' && currentFirstNum.Len() > 0 {
					secondWord = true
				} else if secondWord && currentLine[i] == ')' && currentSecondNum.Len() > 0 {
					firstNum, err1 := strconv.Atoi(currentFirstNum.String())
					secondNum, err2 := strconv.Atoi(currentSecondNum.String())
					println(firstNum, ",", secondNum)
					if err1 != nil || err2 != nil {
						log.Fatal("oh no")
					}
					output += (firstNum * secondNum)
					mulIndex = 0
					secondWord = false
					currentFirstNum.Reset()
					currentSecondNum.Reset()
				} else {
					currentFirstNum.Reset()
					currentSecondNum.Reset()
					secondWord = false
					mulIndex = 0
				}

			} else if do {
				//trying to find the first part "mul("
				if currentLine[i] == mulString[mulIndex] {
					mulIndex++
				} else {
					mulIndex = 0
				}
			}
		}
	}
	println(output)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
