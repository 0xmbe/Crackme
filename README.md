# Crackme
My learning process of reverse engineering executable binaries.
```
╔══════════════════════════════════════════════════════╗
╫~~~~~~~~~~~~~< Crackme by Matija Bensa >~~~~~~~~~~~~~~╫
╚══════════════════════════════════════════════════════╝
                         Mission
  >> Get the correct password.
  >> Write a keygen
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

Enter password:
█
```
## Running
executables are included in bin folder.

## Build
If you want to build your own binary with g++ for example do:
```
g++ -Wall -std=c++14 -c MyCrackmeXX.cpp -o MyCrackmeXX.o
g++ -Wall -std=c++14 -o MyCrackmeXX MyCrackmeXX.o -lgdi32 -luser32
```
# Guide
This is the learning challenge for reverse engineering. I source code is included but don't look at it without trying hard to reverse it! You will not learn like that. Instead drill hard and you will find the solution. There always is, I have tested it. Run the executable to see the challenge. Even though the challenges names are crackme I advice you not to simply patch it but to get the actual login information or as in later challenges write a keygen. That way you will get the most out of it.

## Challenges summary
### MyCrackme01
This is actually not a binary with a password that would unlock you the doors. It is the simplest program with an easter egg that you can find when dissasembling it. If you want to learn to reverse you should start there.

### MyCrackme02
You need correct username and password to win this. They are hardcoded inside the code in std::string type.

### MyCrackme03
Simmilar to previous, but now password and username are hardcoded in char array.

### MyCrackme04
Now this is the 1st real reversing challenge where you will have to reverse the algorithm that crypts your password. But this time password is not to be inputed in the console but saved to the file. You need to find out how it is reading the file and what it reads. Create a file and save the password. Here is the best to write a keygen with an algorithm that crypts your input. Algorithms involved here are repalcing characters, reversing strings, compressing ... .

### MyCrackme05
Write a keygen what will xor your username. Any username is good here, but you need to make a keygen to get the correct password. Key is hardcoded somewhere.

### MyCrackme05.1
Simmilar version but a little different. A good way to refresh what you have learned before.

### MyCrackme06
Now this challenge takes it to the new level. There are 2 binaires, client and server. First run the server and then the client. In this challenge you are not allowed to hack into server executable, but you can monitor the TCP connection handshake. Mission here is to write a replica "fake" server that will mimic the original server and essentially send the client a correct password, that you can find hardcoded inside the client.

### MyCrackme07
Also here is the simmilar situation as above, but this time the password is encrypted and gets decrypted when needed. You are not allowed to reverse a server. If you take a closer look at how the input is processed you will see that there is a bug regarding password length.

### MyCrackme08
Key here is unique, it is generated based on your system information. Then it get ciphered with RC4 algorithm. No info taken for key generation is hardcoded so you will have to understand what info it is os somehow get that. There should be only 1 correct key.

### MyCrackme09
This time function that checks password is encrypted, it gets decrypted on-the-fly to virtual memory. To decrypt it you will have to find the key.

### TODO
