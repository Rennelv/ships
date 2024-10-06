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

#include <cstddef>
#include <iostream>
#include <vector>

#include "modules/Ship.hpp"
#include "modules/ShipField.hpp"
#include "modules/ShipManager.hpp"

void print_field(const ShipField *field) {
    const size_t height = field->getHeight();
    const size_t width = field->getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field->getCellVisibilityState(x, y) == ShipField::CellVisibilityState::UNKNOWN) {
                std::cout << ((width > 10) ? ".  " : ". ");
            } else if (field->getCellVisibilityState(x, y) == ShipField::CellVisibilityState::BLANK) {
                std::cout << ((width > 10) ? "O  " : "O ");
            } else {
                const Ship::SegmentState &segment_state = field->getShipSegmentState(x, y);
                if (segment_state == Ship::SegmentState::DESTROYED) {
                    std::cout << ((width > 10) ? "X  " : "X ");
                } else {
                    std::cout << ((width > 10) ? "/  " : "/ ");
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << (height > 10 ? "   " : "  ");
    for (size_t i = 0; i < width; i++) {
        std::cout << i << (width <= 10 ? " ": ((i < 9) ? "  " : " "));
    }
    std::cout << std::endl;
}

void print_field_exposed(const ShipField *field, bool show_hp = false) {
    const size_t height = field->getHeight();
    const size_t width = field->getWidth();
    for (int y = height - 1; y >= 0; y--) {
        std::cout << y << (height <= 10 ? " " : ((y < 10) ? "  " : " "));
        for (size_t x = 0; x < width; x++) {
            if (field->getIsShip(x, y)) {
                const int &segment_hp = field->getShipSegmentHP(x, y);
                std::cout << (show_hp ? std::to_string(segment_hp) : "P") << ((width > 10) ? "  " : " ");
            } else {
                std::cout << "." << ((width > 10) ? "  " : " ");
            }
        }
        std::cout << std::endl;
    }
    std::cout << (height > 10 ? "   " : "  ");
    for (size_t i = 0; i < width; i++) {
        std::cout << i << (width <= 10 ? " ": ((i < 9) ? "  " : " "));
    }
    std::cout << std::endl;
}

int main() {

    int width, height;
    std::cout << "Write field size (x,y): \n";
    std::cin >> width >> height;
    ShipField *field;
    try {
        field = new ShipField(width, height);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    };
    print_field_exposed(field);

    std::vector<size_t> lengths;
    lengths.reserve(10);
    for (size_t i = 4; i > 0; i--) {
        std::cout << "Write how many ships of length " << i << " you want: ";
        int count;
        std::cin >> count;
        for (int j = 0; j < count; j++) {
            lengths.push_back(i);
        }
        
    }
    
    ShipManager *manager = new ShipManager(lengths.size(), lengths);

    std::cout << "Place ships on the field\n";
    for (size_t i = 0; i < manager->getShipCount(); i++) {
        int x, y;
        std::cout << "Write x and y for ship " << i << " of length " << lengths[i] << " (bottom left corner): ";
        std::cin >> x >> y;
        Ship::Orientation orientation;
        if (lengths[i] == 1) {
            orientation = Ship::Orientation::HORIZONTAL;
        } else {
            std::cout << "Write orientation for ship " << i << " (0 - HORIZONTAL, 1 - VERTICAL): ";
            int ori;
            std::cin >> ori;
            if (ori == 0) {
                orientation = Ship::Orientation::HORIZONTAL;
            } else {
                orientation = Ship::Orientation::VERTICAL;
            }
        }
        bool ret = field->placeShip(manager->getShip(i), x, y, orientation);
        if (!ret) {
            std::cout << "Can't place ship on the field\n";
            i--;
            continue;
        }
        print_field_exposed(field);
    }

    ShipField *field2 = new ShipField(*field);              // Use copy constructor
    ShipField *field3 = new ShipField(*field);              // Use copy constructor
    ShipField *field4 = new ShipField(std::move(*field3));  // Use move constructor
    field2->clearField();

    print_field_exposed(field);
    while (manager->getAliveCount() > 0) {
        int x, y;
        std::cout << "Write x and y for attack: \n";
        std::cin >> x >> y;
        field->attackShip(x, y);
        print_field(field);
        std::cout << "Alive ships: " << manager->getAliveCount() << std::endl;
        // print_field(field2);
        // print_field_exposed(field4);
    }
    delete field;
    delete field2;
    delete field3;
    delete field4;
    delete manager;
    return 0;
}