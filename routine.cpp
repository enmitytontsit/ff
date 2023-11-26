#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
struct Dish {
    std::string name;
    std::string type;
    double price;
};

const std::string menuFilePath = "menu.txt";
const std::string outputFilePath = "output.txt";


void WriteToOutputFile(const std::string& outputFilePath, const std::string& content) {

    std::ofstream output(outputFilePath, std::ios::app);
    output << content << std::endl;
    output.close();
}
void AddDish(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::app);

    Dish dish; 

    
    std::cout << "Введите название блюда (оставьте пустым для завершения): ";
    getline(std::cin, dish.name);

    
    if (dish.name.empty()) return;

    
    std::cout << "Введите тип блюда: ";
    getline(std::cin, dish.type);

    
    std::cout << "Введите цену блюда: ";
    std::cin >> dish.price;
    std::cin.ignore();
    file << dish.name << ";" << dish.type << ";" << dish.price << std::endl;
    WriteToOutputFile(outputFilePath, "Добавлено блюдо: " + dish.name + ", " + dish.type + ", " + std::to_string(dish.price));


    file.close();
}


void SearchDish(const std::string& filePath) {
   
    std::ifstream file(filePath);


    bool found = false;

    std::string name;
    std::cout << "Введите название блюда для поиска: ";
    getline(std::cin, name);


    std::string line;
    
    while (getline(file, line)) {
       
        std::istringstream iss(line);
        Dish dish; 

       
        getline(iss, dish.name, ';');
        getline(iss, dish.type, ';');
        iss >> dish.price;

      
        if (dish.name == name) {
            std::cout << "Блюдо найдено: " << dish.name << ", " << dish.type << ", " << dish.price << std::endl;
   
            WriteToOutputFile(outputFilePath, "Найдено блюдо: " + dish.name + ", " + dish.type + ", " + std::to_string(dish.price));
            found = true;
         
            return;
        }
    }

    
    if (!found) {
        std::cout << "Блюдо не найдено." << std::endl;
        
        WriteToOutputFile(outputFilePath, "Блюдо не найдено: " + name);
    }

   
    file.close();
}


void SortDishes(const std::string& filePath) {
    std::vector<Dish> dishes; 
    std::ifstream file(filePath); 
    std::string line; 


    while (getline(file, line)) {
        std::istringstream iss(line); 
        Dish dish;
        getline(iss, dish.name, ';'); 
        getline(iss, dish.type, ';'); 
        iss >> dish.price; 
        dishes.push_back(dish); 
    }
    file.close();

    int choice;
    std::cout << "Сортировать по (1) типу или (2) цене? ";
    std::cin >> choice;
    std::cin.ignore(); 


    if (choice == 1) {
        
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.type < b.type;
            });
    }
    else if (choice == 2) {
      
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.price < b.price;
            });
    }

    
    std::ofstream outfile(filePath); 
    for (const auto& dish : dishes) {
  
        outfile << dish.name << ";" << dish.type << ";" << dish.price << std::endl;
    }


    if (choice == 1) {
        WriteToOutputFile(outputFilePath, "Сортировка блюд по типу:\n");
    }
    else if (choice == 2) {
        WriteToOutputFile(outputFilePath, "Сортировка блюд по цене:\n");
    }

    outfile.close(); 
}


void OutputDishesByPrice(const std::string& filePath, const std::string& outputFilePath) {
    std::ifstream file(filePath); 
    std::ofstream outputFile(outputFilePath, std::ios::app);

    double maxPrice; 
    std::cout << "Введите максимальную цену: ";
    std::cin >> maxPrice;
    std::cin.ignore(); 

    std::string line; 
    while (getline(file, line)) {
        std::istringstream iss(line); 
        Dish dish; 
        getline(iss, dish.name, ';');
        getline(iss, dish.type, ';'); 
        iss >> dish.price;


        if (dish.price <= maxPrice) {
 
            std::cout << dish.name << ", " << dish.type << ", " << dish.price << std::endl;
  
            outputFile << dish.name << ", " << dish.type << ", " << dish.price << std::endl;
        }
    }

 
    WriteToOutputFile(outputFilePath, "Вывод блюд ценой ниже заданной");

    file.close(); 
    outputFile.close(); 
}


vector<Dish> ReadDishesFromFile(const string& filePath) {
    ifstream file(filePath); 
    vector<Dish> dishes; 
    string line; 


    while (getline(file, line)) {
        stringstream iss(line); 
        Dish dish; 
        getline(iss, dish.name, ';'); 
        getline(iss, dish.type, ';'); 
        iss >> dish.price;
        dishes.push_back(dish); 
    }

    file.close();
    return dishes; 
}


void PrintDishNames(const vector<Dish>& dishes) {

    for (const Dish& dish : dishes) {
        cout << dish.name << endl;
    }
}

int main() {

    int choice;

    do {
        std::cout << "1. Добавить блюдо\n";
        std::cout << "2. Найти блюдо\n";
        std::cout << "3. Сортировать блюда\n";
        std::cout << "4. Вывести блюда по максимальной цене\n";
        std::cout << "5. Вывести все блюда\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            AddDish(menuFilePath);
            break;
        case 2:
            SearchDish(menuFilePath);
            break;
        case 3:
            SortDishes(menuFilePath);
            break;
        case 4:
            OutputDishesByPrice(menuFilePath, outputFilePath);
            break;
        case 5: {
            vector<Dish> dishes = ReadDishesFromFile(menuFilePath);
            cout << "Названия блюд:" << endl;
            PrintDishNames(dishes);
            break;
        }
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
