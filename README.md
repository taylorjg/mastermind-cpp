## Description

C++ implementation of
[Knuth's algorithm](https://en.wikipedia.org/wiki/Mastermind_(board_game)#Five-guess_algorithm)
to solve MasterMind within 5 guesses.

## Building and Running

```
cmake --build cmake-build-debug --target clean
cmake --build cmake-build-debug --target mastermind
cmake --build cmake-build-debug --target tests
cmake-build-debug/mastermind
cmake-build-debug/tests
```

## Exhaustive Test

I added a `-all` command line option. When this is specified, it solves every possible combination (1296 of them).
It then prints an histogram showing numbers of guesses along with the number of combinations that were solved in that
number of guesses.

```
cmake-build-debug/mastermind -all
```

```
1    1
2    6
3   25 **
4  239 *******************
5 1025 *************************************************************************************
```

* 1 combination was solved with 1 guess.   
* 6 combinations were solved with 2 guesses.  
* 25 combinations were solved with 3 guesses.  
* 239 combinations were solved with 4 guesses.  
* 1025 combinations were solved with 5 guesses.  
* 0 combinations needed more than 5 guesses.   

## Screenshot

![Screenshot](Screenshot/MasterMindCppScreenshot.png)

## Links

* [Mastermind (board game)](https://en.wikipedia.org/wiki/Mastermind_(board_game))
* [Five-guess algorithm](https://en.wikipedia.org/wiki/Mastermind_(board_game)#Five-guess_algorithm)
* [Knuth's mastermind algorithm](https://math.stackexchange.com/questions/1192961/knuths-mastermind-algorithm)
* [An implementation of Knuth's five-guess algorithm to solve a mastermind code](https://gist.github.com/firebus/2153677)
* [knuth-mastermind.pdf](https://www.cs.uni.edu/~wallingf/teaching/cs3530/resources/knuth-mastermind.pdf)
* [Mastermind using SVG and Vue.js](https://github.com/taylorjg/mastermind-svg-vue)
