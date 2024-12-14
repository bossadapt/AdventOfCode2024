#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
   struct ClawMachine{
    long long buttonAX;
    long long buttonAY;
    long long buttonBX;
    long long buttonBY;
    long long prizeX;
    long long prizeY;
    };
using namespace std;
// AxBx + AyBy = Goalx,Goaly
tuple<long long, long long> maxClawProfit(ClawMachine input) {
   
    // input.buttonAX + input.buttonBX = input.prizeX
    // 94x + 22y = 8400 
    // input.buttonAY + input.buttonBY = input.prizeY
    // 34(b) + 67y = 5400

    // 94x + 22y = 8400
    // -
    // (94/34)(34x) + (94/34)(67y) = (94/34)5400

    // 0 + 22y - (94/34)(67y) = 8400 - (94/34)5400

    // 22y - (94/34)(67y) = 8400 - (94/34)5400     * 34

    // (34 * 22)y - (94 * 67)y = (8400 * 34) - (94 * 5400)
    // (8400 * 34) - (94 * 5400) / (34 * 22) - (94 * 67)

    // 94(b) + 22y = 34(b) + 67y + dif(goalx-goaly) 
    long long b = ((input.prizeX * input.buttonAY) - (input.buttonAX * input.prizeY))/((input.buttonAY * input.buttonBX) - (input.buttonAX * input.buttonBY));
    long long a = (input.prizeX - (input.buttonBX*b)) / input.buttonAX;
    long long bMod = ((input.prizeX * input.buttonAY) - (input.buttonAX * input.prizeY))%((input.buttonAY * input.buttonBX) - (input.buttonAX * input.buttonBY));
    long long aMod = (input.prizeX - (input.buttonBX*b)) % input.buttonAX;
    if (bMod !=0){
        return make_tuple(0,0);
    }
    if (aMod !=0){
        return make_tuple(0,0);
    }
    return make_tuple(a,b);
}

int main(int argc, char const *argv[])
{
    //ifstream file("example.txt");
    ifstream file("question.txt");
    vector<ClawMachine> machines;
    string curLine;
    ClawMachine curMachine = ClawMachine();
    int index =0;
    while (getline(file,curLine)){
        if(curLine.length()==0){
            machines.push_back(curMachine);
            curMachine = ClawMachine();
            index =0;
        }
        istringstream ss(curLine);
        string curWord;
        while(ss >> curWord){
            if(curWord[0]=='X'){
                switch (index)
                {
                case 0:
                    curMachine.buttonAX = stol(curWord.substr(2));
                    break;
                case 1:
                    curMachine.buttonBX = stol(curWord.substr(2));
                    break;
                default:
                    curMachine.prizeX = stol(curWord.substr(2))+10000000000000;
                    break;
                }
            }else if(curWord[0]=='Y'){
                 
                switch (index)
                {
                case 0:
                    curMachine.buttonAY = stol(curWord.substr(2));
                    break;
                case 1:
                    curMachine.buttonBY = stol(curWord.substr(2));
                    break;
                default:
                    curMachine.prizeY = stol(curWord.substr(2))+10000000000000;
                    break;
                }
                index= index +1;
            }
        }
    }
     machines.push_back(curMachine);
    long long output = 0;
    for (int i = 0; i < machines.size(); i++)
    {
        cout << "\nMachine " << i << ": " << "(" << machines[i].buttonAX <<","
        << machines[i].buttonAY <<","<< machines[i].buttonBX <<","<< machines[i].buttonBY
        <<","<< machines[i].prizeX<<","<< machines[i].prizeY<<")\n";
        long long a,b;
        auto machine = machines[i];
        tie(a,b) = maxClawProfit(machine);
        printf("a:%lld,b:%lld\n",a,b);
        output += a*3+b;
    }
    printf("final solution: %lld\n",output);
    return 0;
}
//part 1
//    struct ClawMachine{
//     int buttonAX;
//     int buttonAY;
//     int buttonBX;
//     int buttonBY;
//     int prizeX;
//     int prizeY;
//     };
// using namespace std;
// // AxBx + AyBy = Goalx,Goaly
// tuple<int, int> maxClawProfit(ClawMachine input) {
   
//     // input.buttonAX + input.buttonBX = input.prizeX
//     // 94x + 22y = 8400 
//     // input.buttonAY + input.buttonBY = input.prizeY
//     // 34(b) + 67y = 5400

//     // 94x + 22y = 8400
//     // -
//     // (94/34)(34x) + (94/34)(67y) = (94/34)5400

//     // 0 + 22y - (94/34)(67y) = 8400 - (94/34)5400

//     // 22y - (94/34)(67y) = 8400 - (94/34)5400     * 34

//     // (34 * 22)y - (94 * 67)y = (8400 * 34) - (94 * 5400)
//     // (8400 * 34) - (94 * 5400) / (34 * 22) - (94 * 67)

//     // 94(b) + 22y = 34(b) + 67y + dif(goalx-goaly) 
//     int bMod = ((input.prizeX * input.buttonAY) - (input.buttonAX * input.prizeY))%((input.buttonAY * input.buttonBX) - (input.buttonAX * input.buttonBY));
//     int b = ((input.prizeX * input.buttonAY) - (input.buttonAX * input.prizeY))/((input.buttonAY * input.buttonBX) - (input.buttonAX * input.buttonBY));
//     int a = (input.prizeX - (input.buttonBX*b)) / input.buttonAX;
//     if (bMod !=0){
//         return make_tuple(0,0);
//     }
//     return make_tuple(a,b);
// }

// int main(int argc, char const *argv[])
// {
//     //ifstream file("example.txt");
//     ifstream file("question.txt");
//     vector<ClawMachine> machines;
//     string curLine;
//     ClawMachine curMachine = ClawMachine();
//     int index =0;
//     while (getline(file,curLine)){
//         if(curLine.length()==0){
//             machines.push_back(curMachine);
//             curMachine = ClawMachine();
//             index =0;
//         }
//         istringstream ss(curLine);
//         string curWord;
//         while(ss >> curWord){
//             if(curWord[0]=='X'){
//                 switch (index)
//                 {
//                 case 0:
//                     curMachine.buttonAX = stoi(curWord.substr(2));
//                     break;
//                 case 1:
//                     curMachine.buttonBX = stoi(curWord.substr(2));
//                     break;
//                 default:
//                     curMachine.prizeX = stoi(curWord.substr(2));
//                     break;
//                 }
//             }else if(curWord[0]=='Y'){
                 
//                 switch (index)
//                 {
//                 case 0:
//                     curMachine.buttonAY = stoi(curWord.substr(2));
//                     break;
//                 case 1:
//                     curMachine.buttonBY = stoi(curWord.substr(2));
//                     break;
//                 default:
//                     curMachine.prizeY = stoi(curWord.substr(2));
//                     break;
//                 }
//                 index= index +1;
//             }
//         }
//     }
//      machines.push_back(curMachine);
//      int output = 0;
//     for (int i = 0; i < machines.size(); i++)
//     {
//         cout << "\nMachine " << i << ": " << "(" << machines[i].buttonAX <<","
//         << machines[i].buttonAY <<","<< machines[i].buttonBX <<","<< machines[i].buttonBY
//         <<","<< machines[i].prizeX<<","<< machines[i].prizeY<<")\n";
//         int a,b;
//         auto machine = machines[i];
//         tie(a,b) = maxClawProfit(machine);
//         printf("a:%d,b:%d\n",a,b);
//         output += a*3+b;
//     }
//     printf("final solution: %d\n",output);
//     return 0;
// }
