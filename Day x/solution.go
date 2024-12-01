package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	file, err := os.Open("example.txt")
	//file, err := os.Open("question.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		var currentLine string = scanner.Text()
		fmt.Println(currentLine)
	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
