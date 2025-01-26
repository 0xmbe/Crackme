# Crackme
My learning process of reverse engineering executable binaries.

## Running
executables are included in bin folder.

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
Simmilar version but a litttle different. A good way to refresh what you have learned before.

### MyCrackme06
Now this challenge takes it to the new level. There are 2 binaires, client and server. First run the server and then the client. In this challenge you are not allowed to hack into server executable, but you can monitor the TCP connection handshake. Mission here is to write a replica "fake" server that will mimic the original server and essentially send the client a correct password, that you can find hardcoded inside the client.

### MyCrackme07
Also here is the simmilar situation as above, but this time the password is encrypted and gets decrypted when needed. You are not allowed to reverse a server. If you take a closer look at how the input is processed you will see that there is a bug regarding password length.

### TODO
