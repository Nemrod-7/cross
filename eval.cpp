#include <iostream>
#include "/home/Nemrod-7/include/interpreter.hpp"

// clang++ -I$HOME/include/ -L$HOME/lib/ -leval -Wl,-rpath,$HOME/lib main.cpp -o eval
namespace txt {

    const std::vector<std::string> help = {
        "",

      "Commands :\n"
          //"exit derivate interpret help clear save show rules time pause\n"
          "general : exit clear save load\n"
          "mode    : evaluate derivate brainfuck\n"
          "info    : help rules mode values base\n"
          "modules : time rain sudoku brainfuck\n"
          "variable: speed\n"
          "\n\n",

        "rules of differentiation : \n\n"
        "Let f be a function.\n"
        "The derivative function, denoted by f′, is the function whose domain\n"
        "consists of those values of x such that the following limit exists:\n"
        "f′(x) = lim h→0 of (f(x + h) − f(x)) / h.\n\n"
        "cst : 1     => 0\n"
        "lin : x     => 1\n"
        "add : a + b => a' + b'\n"
        "sub : a - b => a' - b'\n"
        "mul : a * b => a.b' + a'.b\n"
        "div : a / b => (a'* b − b'* a) / (b * b)\n"
        "exp : x ^ y => x^y . (x'.(y/x) + y'.log(x))\n"
        "log : log x => x' / x\n"
        "sin : sin x => x'.cos x\n"
        "cos : cos x => -x'.sin x\n"
        "tan : tan x => x' / (cos(x))^2\n"
        "cot : cot x => -x' / (sin(x))^2\n"
        "sec : sec x => sec x . tan x . x'\n"
        "csc : csc x => cot x . csc x . x'\n\n" ,

        "Constants :\n" "e pi tau\n\n"
        "Functions :\n"
        "cos sin tan cot sec csc \n"
        "log rad deg sqr         \n"
        //"     cos    acos     deg    abs\n"
        //"     sin    asin    sqrt    rad\n"
        //"     tan    atan     sqr    deg\n\n"
        "Operators :\n"
        "+ - * % / ^ = =>\n\n"
        "lambdas :\n"
        "fn 'name' 'parameters' => 'function'\n"
        "ex : fn avg x y => (x + y) / 2      \n\n",

        "brainfuck rules: \n\n"
            "> : move pointer forward\n"
            "< : move pointer backward\n"
            "+ : increment cell under pointer\n"
            "- : decrement cell under pointer\n"
            ". : output cell under pointer\n"
            ", : input celll under pointer\n"
            "[ : loop until cell equal zero\n"
            "] : move backward if cell is not empty\n",
  };

    const std::string sav =
        "\nsave expression to the base\nformat :\n\n"
        "fn [name](param) => <expression> :: save as lambda.\n"
        "   [name]        =  <expression> :: save as value.\n\n"
        "ex: fn radian x => x * 360.0 * pi\n\n";

    const std::vector<std::string> menu = {"File", "Place","Help","Base","Mode","clear","Time","Module"}; // main menu

    std::vector<std::vector<std::string>> sub { // sub menus
        {"Save","Load","Exit"},{}, {"commands$$", "interpreter"  ,"derivation", "brainfuck$"}, {"values$", "lambdas"}, {"evaluate","derivate$","brainfuck", "sudoku$$$"}, {"input$$", "console"}, {}, {"Rain$$$$", "Password"}
    };

    const std::vector<std::string> mode {"no mode selected", "evaluate", "derivate", "brainfuck", "sudoku"};
    const std::vector<std::string> speed {"disable", "instant", "fast", "medium", "slow", "sluggish"};
    const std::vector<std::string> difficulty = {"beginner", "easy", "medium", "hard", "hell"};
    const std::vector<std::string> sudosub = {"solve", "new", "reset", "level"}; // main menu
}

int main () {

    // Timer clock;
    // clock.start();

    fbase["echo"] = {tokenize("x"), tokenize("x")};
    fbase["inc"] = {tokenize("x"), tokenize("x + 1")};
    fbase["sqr"] = {tokenize("x"), tokenize("x * x")};
    fbase["add"] = {tokenize("x y"), tokenize("x + y")};
    fbase["sub"] = {tokenize("x y"), tokenize("x - y")};
    fbase["mul"] = {tokenize("x y"), tokenize("x * y")};
    fbase["div"] = {tokenize("x y"), tokenize("x / y")};
    fbase["avg"] = {tokenize("x y"), tokenize("(x + y) / 2")};
    fbase["rad"] = {tokenize("x y"), tokenize("x * pi / 180.0")};
    fbase["deg"] = {tokenize("x y"), tokenize("x * 180.0 / pi")};

    enum mode_t { no_mode, evaluate, derivate, brainfck, sudoku };

    std::string input;
    std::stringstream iss;
    //std::cout << interpret("avg 4 2") << "\n";
    int mode = no_mode;
    bool running = true;

    while (running) {
        std::cout << "enter input > ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            running = false;
        } else if (input == "evaluate") {
            mode = evaluate;
        } else if (input == "derivate") {
            mode = derivate;
        } else if (input == "brainfuck") {
            mode = brainfck;
        }

        else if (input == "help") {
            std::cout << txt::help[0];
        } else if (input == "rules") {
            std::cout << txt::help[1];
        } else if (input == "mode") {
            std::cout << txt::mode[mode] << "\n";
        } else if (input == "values") {
            for (auto &[name, value] : values) {
                std::cout << name << " => " << show::expr(value.first) << "\n";
            }
        } else if (input == "base") {
            for (auto &[name,func] : fbase) {
                std::cout << name << " => " << show::expr(func.first) << " | " << show::expr(func.second) << "\n";
            }
        } else {

            try {
                expression code = tokenize(input);
                auto [fx,dx] = interpreter(code);

                switch (mode) {
                    case evaluate : std::cout << "fx : " << show::expr(fx) << "\n"; break;
                    case derivate : std::cout << "dx : " << show::expr(dx) << "\n"; break;
                    default: std::cout << "no mode selected\n"; break;
                }
            } catch (const std::exception &x) {
                std::cout << "error : " << x.what() << "\n";
            }
        }
    }

    // clock.stop();
    // clock.get_duration();
}
