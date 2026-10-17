#include <iostream>
#include <sstream>

int ulianDay(int day, int month, int year) {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    int JD = day + ((153 * m) + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return JD;
}

int dayForGC(int day, int year, int month) {
    int a = (14 - month) / 12;
    int m = month + 12 * a - 2;
    int y = year - a;
    int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    return d;
}

int JDToNormal(int JD, int& daySoon, int& monthSoon) {
    int a = JD + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b) / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;
    daySoon = e - (153 * m + 2) / 5 + 1;
    monthSoon = m + 3 - 12 * (m / 10);
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Unknown" << '\n';
        return 0;
    }

    int day;
    int daySoon = 0;
    int monthSoon = 0;
    int month;
    int year;
    char dot1;
    char dot2;
    std::istringstream iss(argv[1]);
    iss >> day >> dot1 >> month >> dot2 >> year;

    if (dot1 != '.' or dot2 != '.') {
        std::cout << "Unknown" << '\n';
        return 0;
    }

    if (day < 1 or month < 1 or month > 12 or year < 1583) {
        std::cout << "Unknown" << '\n';
        return 0;
    }

    if (!((year % 4 == 0 && year % 100 != 0) || ( year % 400 == 0)))  {
        if (month == 2 && day > 28) {
            std::cout << "Unknown" << '\n';
            return 0;
        }
    }

    int JD = ulianDay(day, month, year);
    int dayOfWeek = dayForGC(day, year, month);

    switch (dayOfWeek) {
    case 0:
        std::cout << "Sunday" << '\n';
        break;
    case 1:
        std::cout << "Monday" << '\n';
        break;
    case 2:
        std::cout << "Tuesday" << '\n';
        break;
    case 3:
        std::cout << "Wednesday" << '\n';
        break;
    case 4:
        std::cout << "Thursday" << '\n';
        break;
    case 5:
        std::cout << "Friday" << '\n';
        break;
    case 6:
        std::cout << "Saturday" << '\n';
        break;
    }

    while (true) {
        year++;
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            JD += 366;
        }
        else {
            JD += 365;
        }
        JDToNormal(JD, daySoon, monthSoon);
        int dayOfWeek = dayForGC(daySoon, year, monthSoon);
        if ((dayOfWeek == 5) && (daySoon == day) && (monthSoon == month)) {
            std::cout << year;
            return 0;
        }
    }
}
