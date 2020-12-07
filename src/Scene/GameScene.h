#pragma once

#include "../Level/Level.h"
#include <functional>
#include <cfloat> // Константа FLT_EPSILON
#include <cmath>
#include <iostream>

/**
/// Структура, абстрагирующая работу с окном и камерой.
///  Код ниже намеренно написан в процедурном стиле:
///  - используются структуры
///  - используются указатели на функции
///  - используется явный вызов new и delete.
 */
 struct Window {
    sf::RenderWindow window_;
    sf::View camera_;
    sf::Vector2i windowSize_;
    sf::Clock clock_;
};

 /**
/// Структура, абстрагирующая игровую сцену.
///  Код ниже намеренно написан в процедурном стиле:
///  - используются структуры
///  - используется явный вызов new и delete.
*/
  struct GameScene {
    Level level;
    //std::vector<Object> staticObjects;
    //std::vector<Object> dynamicObjects;
};

  /**
/// Создаёт новое окно игры.
   */
Window *newWindow(const sf::Vector2i &windowSize);

/**
 * Загружаем все файлы
 */
GameScene *newGameScene();

/**
//обновление карты (движений и событий объектов)
 */
void updateScene(sf::Clock&, sf::Clock&,sf::Clock&, Level*, sf::RenderWindow*);

/**
//рисуем объекты
 */
void drawObjects(Level, sf::RenderWindow*, sf::Font& font);

/**
/// Объявляем типы указателей на функции-колбеки (callback),
///  вызываемые из основного цикла игры для совершения игровой логики.
/// Параметр userData - произвольный указатель на внешние данные того,
///  кто предоставляет колбек.
 */
using OnUpdate = void (*)(void *pData, Window &window, float deltaSec);
/**
    * Рисуем карту
    */
using OnDraw = void (*)(void *pData, Window &window);

/**
/// Входит в основной цикл игры и возвращается, когда цикл завершён.
 */
void mainGameLoop(Window &window, OnUpdate onUpdate, void *pData);

/**
/// Разрушает окно игры и очищает его данные.
 */
void destroyWindow(Window *&window);

/**
/// Удаление загруженных из файла данных
 */
void destroyGameScene(GameScene *&gameScene);


///////////////////CAMERA/////////////////////////////////////////////////////////
///
/**
/// Проверяет изменения. Применяет их.
 */
void UpdateCamera(void *pData, Window &window, float deltaSec);

/**
/// Выполняет нормализацию вектора (приведение к единичной длине).
  */
sf::Vector2f Normalize(const sf::Vector2f &value);

 /**
/// Округляет компоненты вектора до ближайших целых чисел.
  */
sf::Vector2f Round(const sf::Vector2f &value);

 /**
/// Определяет состояние клавиатуры и выбирает направление движения.
/// Возвращает нормализованный вектор направления игрока.
  */
sf::Vector2f GetWatcherDirection();

 /**
/// Зум камеры
  */
int GetWatcherZoom();

 /**
/// Центрирует камеру в заданной точке
 */
void setCameraCenter(Window &window, const sf::Vector2f &center);

 /**
  *
  * Функция создана чтобы разгрузить главный цикл игры
  *
  * @param flag
  * @param flagClick если куда то тыкнули
  * @param flagZoneClick  если выделили какую либо область
  * @param objects массив объектов, которые было выделены до этого(Находится в главной функции чтобы не потерять выделенные объекты)
  * @param x Х координата клика относительно карты
  * @param y У координата клика относительно карты
  * @param x1 Х координата клика относительно экрана(для создания юнитов)
  * @param y1 У координата клика относительно экрана(для создания юнитов)
  * @param width длинна выделенной области
  * @param height высота выделенной области
  * @param level карта
  * @param window окно(для вырисовки)
  */
void doPlayerEvents(bool* flag, bool* flagClick, bool* flagZoneClick, container<Object *> &objects, float x, float y, float x1, float y1, int width, int height, Level* level, Window* window, sf::Font&);
