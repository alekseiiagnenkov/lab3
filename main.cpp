#include "src/Scene/GameScene.h"
#include <iostream>
#include <list>


int main() {

    try {
        //создаем окно и сцену
        Window *window = newWindow({1000, 1000});//создаем окно данных размеров
        GameScene *gameScene = newGameScene();//загружам все нужные файлы

        // Аргумент типа `GameLogic*` будет преобразован в `void*`/основной цикл игры
        mainGameLoop(*window, UpdateCamera, gameScene);

        //очищаем сцену и окно
        destroyGameScene(gameScene);
        destroyWindow(window);
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
