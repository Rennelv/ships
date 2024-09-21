/*Создать класс корабля, который будет размещаться на игровом поле. Корабль
может иметь длину от 1 до 4, а также может быть расположен вертикально или
горизонтально. Каждый сегмент корабля может иметь три различных состояния:
целый, поврежден, уничтожен. Изначально у корабля все сегменты целые. При
нанесении 1 урона по сегменту, он становится поврежденным, а при нанесении 2
урона по сегменту, уничтоженным. Также добавить методы для взаимодействия с
кораблем. Создать класс менеджера кораблей, хранящий информацию о кораблях.
Данный класс в конструкторе принимает количество кораблей и их размеры, которые
нужно расставить на поле. Создать класс игрового поля, которое в конструкторе
принимает размеры. У поля должен быть метод, принимающий корабль, координаты, на
которые нужно поставить, и его ориентацию на поле. Корабли на поле не могут
соприкасаться или пересекаться. Для игрового поля добавить методы для указания
того, какая клетка атакуется. При попадании в сегмент корабля изменения должны
отображаться в менеджере кораблей. Каждая клетка игрового поля имеет три
статуса: неизвестно (изначально вражеское поле полностью неизвестно), пустая
(если на клетке ничего нет) корабль (если в клетке находится один из сегментов
корабля). Для класса игрового поля также необходимо реализовать конструкторы
копирования и перемещения, а также соответствующие им операторы присваивания.
Примечания:
Не забывайте для полей и методов определять модификаторы доступа
Для обозначения переменной, которая принимает небольшое ограниченное количество
значений, используйте enum Не используйте глобальные переменные При реализации
копирования нужно выполнять глубокое копирование При реализации перемещения, не
должно быть лишнего копирования При выделении памяти делайте проверку на
переданные значения У поля не должно быть методов возвращающих указатель на поле
в явном виде, так как это небезопасно
*/

#include <iostream>

#include "modules/ShipField.hpp"
#include "modules/ShipManager.hpp"

int main() {
    // ShipField field(10, 11);
    // ShipManager manager(
    //     10, new int[]{4, 3, 3, 2, 2, 3, 1, 1, 1, 1});
    // // field.setManager(&manager);
    // Ship::Orientation ori[] {Ship::HORIZONTAL, Ship::HORIZONTAL,
    //                             Ship::VERTICAL, Ship::VERTICAL, Ship::VERTICAL,
    //                             Ship::VERTICAL, Ship::VERTICAL, Ship::VERTICAL,
    //                             Ship::VERTICAL, Ship::VERTICAL};
    // for (int i = 0; i < 10; i++) {
    //     field.placeShip(manager.getShip(i), i, i, ori[i]);
    // }
    // field.placeShip(4, 0, 0, Ship::HORIZONTAL);
    // field.placeShip(3, 0, 1, Ship::VERTICAL);
    // field.placeShip(3, 0, 2, Ship::VERTICAL);
    // field.placeShip(2, 0, 3, Ship::VERTICAL);
    // field.placeShip(2, 0, 4, Ship::VERTICAL);
    // field.placeShip(3, 0, 5, Ship::VERTICAL);
    // field.placeShip(1, 1, 6, Ship::VERTICAL);
    // field.placeShip(1, 0, 7, Ship::VERTICAL);
    // field.placeShip(1, 0, 8, Ship::VERTICAL);
    // field.placeShip(1, 0, 9, Ship::VERTICAL);
    // field.printField();
    // while (true) {
    //     int x, y;
    //     std::cin >> x >> y;
    //     field.attackShip(x, y);
    //     field.printField();
    // }

    int lengths[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager manager(sizeof(lengths)/sizeof(int), lengths);

    int width, height;
    std::cout << "Write field size (x,y): \n";
    std::cin >> width >> height;

    ShipField field(width, height);
    std::cout << "Place ships on the field\n";
    for (int i = 0; i < manager.getCount(); i++) {
        int x, y;
        std::cout << "Write x and y for ship " << i << " of lenght " << lengths[i] << " (bottom left corner): ";
        std::cin >> x >> y;
        Ship::Orientation orientation;
        std::cout << "Write orientation for ship " << i << " (0 - HORIZONTAL, 1 - VERTICAL): ";
        int ori;
        std::cin >> ori;
        if (ori == 0) {
            orientation = Ship::HORIZONTAL;
        } else {
            orientation = Ship::VERTICAL;
        }
        bool ret = field.placeShip(manager.getShip(i), x, y, orientation);
        if (!ret) {
            std::cout << "Can't place ship on the field\n";
            i--;
        }
    }
    field.printField(true);
    while (true) {
        int x, y;
        std::cout << "Write x and y for attack: ";
        std::cin >> x >> y;
        field.attackShip(x, y);
        field.printField();
    }
    return 0;
}