#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct ComplexNumber {
  double real{};
  double imag{};
};

void printMenu() {
  std::cout << "\n=== Komplexe Zahlen ===\n";
  std::cout << "1) Komplexe Zahl hinzufügen\n";
  std::cout << "2) Liste anzeigen\n";
  std::cout << "3) Liste speichern\n";
  std::cout << "0) Beenden\n";
  std::cout << "Auswahl: ";
}

double readDouble(const std::string &prompt) {
  while (true) {
    std::cout << prompt;
    double value{};
    if (std::cin >> value) {
      return value;
    }
    std::cout << "Ungültige Eingabe. Bitte Zahl eingeben.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void showList(const std::vector<ComplexNumber> &numbers) {
  if (numbers.empty()) {
    std::cout << "Die Liste ist leer.\n";
    return;
  }

  std::cout << "Aktuelle Liste:\n";
  for (std::size_t i = 0; i < numbers.size(); ++i) {
    const auto &n = numbers[i];
    std::cout << i + 1 << ": " << n.real << (n.imag < 0 ? " - " : " + ")
              << (n.imag < 0 ? -n.imag : n.imag) << "i\n";
  }
}

void saveList(const std::vector<ComplexNumber> &numbers) {
  if (numbers.empty()) {
    std::cout << "Nichts zu speichern: Die Liste ist leer.\n";
    return;
  }

  std::cout << "Dateiname: ";
  std::string filename;
  std::getline(std::cin >> std::ws, filename);

  std::ofstream out(filename);
  if (!out) {
    std::cout << "Datei '" << filename << "' konnte nicht geöffnet werden.\n";
    return;
  }

  for (const auto &n : numbers) {
    out << n.real << ' ' << n.imag << '\n';
  }

  std::cout << "Liste gespeichert in '" << filename << "'.\n";
}

int main() {
  std::vector<ComplexNumber> numbers;

  while (true) {
    printMenu();
    int choice = -1;
    if (!(std::cin >> choice)) {
      std::cout << "Ungültige Eingabe. Bitte erneut versuchen.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    switch (choice) {
    case 1: {
      ComplexNumber n;
      n.real = readDouble("Realteil: ");
      n.imag = readDouble("Imaginärteil: ");
      numbers.push_back(n);
      std::cout << "Zahl hinzugefügt.\n";
      break;
    }
    case 2:
      showList(numbers);
      break;
    case 3:
      saveList(numbers);
      break;
    case 0:
      std::cout << "Programm beendet.\n";
      return 0;
    default:
      std::cout << "Unbekannte Auswahl.\n";
      break;
    }
  }
}
