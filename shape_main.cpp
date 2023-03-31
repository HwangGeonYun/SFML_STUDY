#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>
#include "shape.h"
#include <SFML/System.hpp>


/*
struct Commander
{
    private:
        std::string command;
        bool quit = false;
    public:
    void console_input_handler() {
        while (true) {
            std::cout << "입력:";
            std::string line;
            std::getline(std::cin, line);
            command = line;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if(quit == true)
                break;
        }
    }
    std::string getCommand(){return command;};
    std::string isQuit(bool quit){  this->quit = quit;};
    void clear(){command.clear();};
};*/
/*
void console(){
    while(true){
        std::string line;
        std::getline(std::cin, line);
        //input = line;
    }
}*/
/*
void console_input_handler(std::string input) {
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        input = line;
    }
}
*/

enum FIRST_COMMAND{RECT = 0, CIRCLE, SORT, ALIGN, PRINT, DRAW, QUIT, INVALID

};

FIRST_COMMAND stringToFirstCommand(std::string firstCommand){
    if(firstCommand == "RECT") return RECT;
    else if(firstCommand == "CIRCLE") return CIRCLE;
    else if(firstCommand == "SORT") return SORT;
    else if(firstCommand == "ALIGN") return ALIGN;
    else if(firstCommand == "PRINT") return PRINT;
    else if(firstCommand == "DRAW") return DRAW;
    else if(firstCommand == "QUIT") return QUIT;
    else return INVALID;
}

void createRectangle(std::stringstream& commandStream){

    int pos1x, pos1y, pos2x, pos2y;

    commandStream >> pos1x;
    commandStream >> pos1y;
    commandStream >> pos2x;
    commandStream >> pos2y;

    create_rectangle(*new Point{pos1x, pos1y},
                     *new Point{pos2x, pos2y});
}

void createCircle(std::stringstream& commandStream){
    int centerx;
    int centery;
    int radius;

    commandStream >> centerx;
    commandStream >> centery;
    commandStream >> radius;

    create_circle(*new Point{centerx, centery}, radius);
}

void executeCommand(std::string command, sf::RenderWindow& window, bool& isQuit, sf::Event& event){
    std::stringstream commandStream;
    commandStream.str(command);

    std::string firstCommandString;
    commandStream >> firstCommandString;

    FIRST_COMMAND firstCommand = stringToFirstCommand(firstCommandString);



    switch (firstCommand) {
        case RECT: createRectangle(commandStream); break;

        case CIRCLE: createCircle(commandStream); break;

        case SORT: sort_shapes(); break;

        case ALIGN: align_shapes(); break;

        case PRINT: print_shapes(); break;

        case DRAW: draw_shapes(window); break;

        case QUIT: isQuit = true; event.type = sf::Event::Closed;break;

        default:std::cout << "Invalid command." << std::endl;break;
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Drawing Shapes");
    sf::View view(sf::FloatRect(0, SCREEN_HEIGHT, SCREEN_WIDTH, -SCREEN_HEIGHT));
    window.display();
    window.setView(view);

    //QUIT입력했을때 종료용
    bool isQuit = false;
    //붙여넣기 입력용
    std::stringstream allCommandsStream;
    std::string commandByPast;
    //타이핑 입력용
    std::string commandByInput;

    while(window.isOpen()&&!isQuit) {

        sf::Event event;


        //std::cout << "hey";
        while(window.pollEvent(event)) {
            int i = 0;
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
             } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.control && event.key.code == sf::Keyboard::V) {       //복사한 텍스트 붙여넣기
                    std::string allCommands = sf::Clipboard::getString();
                    std::cout << allCommands << std::endl;

                    allCommandsStream.str(allCommands);

                    while (std::getline(allCommandsStream, commandByPast, '\n')) {

                        executeCommand(commandByPast, window, isQuit, event);
                    }
                    allCommandsStream.clear();
                }

                else{   //한 글자씩 직접입력
                    if(event.key.code == sf::Keyboard::Enter) {
                        executeCommand(commandByInput, window, isQuit, event);
                        std::cout << "\n";
                        commandByInput.clear();
                    }
                    else if(sf::Keyboard::A<=event.key.code && event.key.code  <= sf::Keyboard::Z) {            //무조건 대문자만 입력
                        char alphabet = (static_cast<char>(event.text.unicode+65));
                        commandByInput += alphabet;
                        std::cout << alphabet;
                    }else if(sf::Keyboard::Num0 <= event.key.code && event.key.code <= sf::Keyboard::Num9) {
                        char number = (static_cast<char>(event.text.unicode+22));
                        commandByInput += number;
                        std::cout << number;
                    }else if(sf::Keyboard::Space) { //공백뛰우기, 지우기 없음 틀리면 다시쳐야함
                        commandByInput += ' ';
                        std::cout << ' ';
                    }
                    //else if(static_cast<char>(event.textunicode))
                }
            }
        }
    }
    return 0;
}