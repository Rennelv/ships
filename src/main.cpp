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

void print_field(ShipField *field, bool expose_ships = false) {
    int height = field->getHeight();
    int width = field->getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << " ";
        for (int x = 0; x < width; x++) {
            if (expose_ships) {
                if (field->checkPlace(x, y)) {
                    if (!field->getCell(x,y).ship->isAlive()) {
                        std::cout << "X ";
                    } else {
                        std::cout << field->getCell(x,y).ship->getSegment(field->getCell(x, y).segment_index).hp << " ";
                    }
                } else {
                    std::cout << ". ";
                }
            } else {
                if (field->getCell(x,y).state == FieldElement::VisibilityState::UNKNOWN) {
                    std::cout << ". ";
                } else if (field->getCell(x,y).state == FieldElement::VisibilityState::BLANK) {
                    std::cout << "O ";
                } else {
                    if (field->getCell(x,y).ship->getSegment(field->getCell(x,y).segment_index).hp == 0) {
                        std::cout << "X ";
                    } else {
                        std::cout << "/ ";
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i < width; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    int lengths[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager manager(sizeof(lengths) / sizeof(int), lengths);

    int width, height;
    std::cout << "Write field size (x,y): \n";
    std::cin >> width >> height;

    ShipField field(width, height);
    
    // std::cout << "Place ships on the field\n";
    // for (int i = 0; i < manager.getShipCount(); i++) {
    //     int x, y;
    //     std::cout << "Write x and y for ship " << i << " of lenght " << lengths[i] << " (bottom left corner): ";
    //     std::cin >> x >> y;
    //     Ship::Orientation orientation;
    //     std::cout << "Write orientation for ship " << i << " (0 - HORIZONTAL, 1 - VERTICAL): ";
    //     int ori;
    //     std::cin >> ori;
    //     if (ori == 0) {
    //         orientation = Ship::HORIZONTAL;
    //     } else {
    //         orientation = Ship::VERTICAL;
    //     }
    //     bool ret = field.placeShip(manager.getShip(i), x, y, orientation);
    //     if (!ret) {
    //         std::cout << "Can't place ship on the field\n";
    //         i--;
    //     }
    // }
    Ship::Orientation ori[] {Ship::HORIZONTAL, Ship::HORIZONTAL,
                                Ship::VERTICAL, Ship::VERTICAL, Ship::VERTICAL,
                                Ship::VERTICAL, Ship::VERTICAL, Ship::VERTICAL,
                                Ship::VERTICAL, Ship::VERTICAL};
    for (int i = 0; i < 10; i++) {
        field.placeShip(manager.getShip(i), i, i, ori[i]);
    }

    // ShipField field2 = field;
    // ShipField field3(field);

    print_field(&field, true);
    while (manager.getAliveCount() > 0) {
        int x, y;
        std::cout << "Write x and y for attack: ";
        std::cin >> x >> y;
        field.attackShip(x, y);
        print_field(&field);
    }
    return 0;
}