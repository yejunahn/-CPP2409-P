#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> // for sort
using namespace std;

// 항공권 데이터 클래스
class FlightData {
public:
    string country;
    vector<int> prices;        // 항공권 가격 데이터
    vector<string> bestMonths; // 추천 여행 월

    // 생성자
    FlightData(string countryName, vector<int> priceData, vector<string> months)
        : country(countryName), prices(priceData), bestMonths(months) {}

    // 평균 가격 계산 함수
    double calculateAveragePrice() {
        int total = 0;
        for (int price : prices) {
            total += price;
        }
        return prices.empty() ? 0 : static_cast<double>(total) / prices.size();
    }

    // 최저 가격 반환 함수
    int getLowestPrice() {
        return *min_element(prices.begin(), prices.end());
    }

    // 최고 가격 반환 함수
    int getHighestPrice() {
        return *max_element(prices.begin(), prices.end());
    }

    // 추천 월 출력
    void printBestMonths() {
        cout << "Best Months to Visit: ";
        for (const string& month : bestMonths) {
            cout << month << " ";
        }
        cout << endl;
    }
};

// 예측 알고리즘 클래스
class PricePredictor {
private:
    vector<FlightData*> flightDataList;

public:
    void addFlightData(FlightData* data) {
        flightDataList.push_back(data);
    }

    void removeFlightData(const string& country) {
        flightDataList.erase(
            remove_if(flightDataList.begin(), flightDataList.end(),
                      [&](FlightData* data) { return data->country == country; }),
            flightDataList.end());
    }

    // 사용자의 예산 및 여행 기간에 맞는 여행지 추천
    void suggestDestinations(int budget, int duration) {
        cout << "\nRecommended Destinations within your budget:\n";
        bool found = false;

        // 평균 가격 기준으로 정렬
        sort(flightDataList.begin(), flightDataList.end(), [](FlightData* a, FlightData* b) {
            return a->calculateAveragePrice() < b->calculateAveragePrice();
        });

        for (FlightData* data : flightDataList) {
            double avgPrice = data->calculateAveragePrice();
            int lowestPrice = data->getLowestPrice();
            int highestPrice = data->getHighestPrice();

            // 예산 내에서 항공권 가격 확인
            if (avgPrice <= budget / (duration > 7 ? 1 : 2)) {
                cout << "Country: " << data->country << endl;
                cout << "Average Price: $" << avgPrice << endl;
                cout << "Lowest Price: $" << lowestPrice << " | Highest Price: $" << highestPrice << endl;
                data->printBestMonths();
                cout << "--------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No destinations found within your budget.\n";
        }
    }

    // 최저가 여행지 추천
    void suggestLowestPriceDestination(int budget) {
        cout << "\nCheapest Destination within your budget:\n";
        FlightData* cheapest = nullptr;
        int lowestPrice = numeric_limits<int>::max();

        for (FlightData* data : flightDataList) {
            int minPrice = data->getLowestPrice();
            if (minPrice < lowestPrice && minPrice <= budget) {
                lowestPrice = minPrice;
                cheapest = data;
            }
        }

        if (cheapest) {
            cout << "Country: " << cheapest->country << endl;
            cout << "Lowest Price: $" << lowestPrice << endl;
            cheapest->printBestMonths();
        } else {
            cout << "No destinations found within your budget.\n";
        }
    }

    // 특정 월 기준 여행지 추천
    void suggestByMonth(const string& month) {
        cout << "\nDestinations Recommended for " << month << ":\n";
        bool found = false;

        for (FlightData* data : flightDataList) {
            if (find(data->bestMonths.begin(), data->bestMonths.end(), month) != data->bestMonths.end()) {
                cout << "Country: " << data->country << endl;
                cout << "Average Price: $" << data->calculateAveragePrice() << endl;
                data->printBestMonths();
                cout << "--------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No destinations available for the month of " << month << ".\n";
        }
    }

    // 비용 시뮬레이션 기능 추가
    void costSimulation(const string& country, int duration, const string& mealType, const string& accommodationType) {
        cout << "\nCost Simulation for " << country << ":\n";

        // 임의의 비용 계산 로직 (사용자의 요구에 맞게 수정 가능)
        int mealCost = (mealType == "budget") ? 10 : (mealType == "standard") ? 20 : 50;
        int accommodationCost = (accommodationType == "hostel") ? 30 : (accommodationType == "hotel") ? 100 : 200;

        int totalCost = (mealCost * duration) + (accommodationCost * duration);

        cout << "Meal Cost per Day: $" << mealCost << endl;
        cout << "Accommodation Cost per Day: $" << accommodationCost << endl;
        cout << "Total Estimated Cost for " << duration << " days: $" << totalCost << endl;
    }
};

int main() {
    // 항공권 및 추천 월 데이터 초기화
    FlightData* korea = new FlightData("Korea", {200, 180, 210, 190, 220}, {"April", "May", "September"});
    FlightData* japan = new FlightData("Japan", {300, 320, 310, 330, 340}, {"March", "October", "November"});
    FlightData* usa = new FlightData("USA", {800, 780, 820, 810, 790}, {"June", "July", "August"});
    FlightData* france = new FlightData("France", {600, 580, 620, 590, 610}, {"April", "May", "September"});
    FlightData* thailand = new FlightData("Thailand", {400, 420, 390, 410, 430}, {"January", "February", "November"});
    FlightData* australia = new FlightData("Australia", {900, 880, 920, 870, 890}, {"December", "January", "February"});
    FlightData* canada = new FlightData("Canada", {700, 750, 770, 720, 740}, {"May", "June", "September"});
    FlightData* italy = new FlightData("Italy", {550, 570, 580, 560, 590}, {"April", "October", "November"});
    FlightData* germany = new FlightData("Germany", {520, 530, 540, 510, 500}, {"May", "June", "July"});
    FlightData* brazil = new FlightData("Brazil", {450, 470, 480, 460, 440}, {"February", "March", "November"});
    FlightData* southAfrica = new FlightData("South Africa", {800, 820, 830, 810, 790}, {"August", "September", "October"});
    FlightData* india = new FlightData("India", {300, 310, 320, 330, 340}, {"November", "December", "January"});

    // PricePredictor 객체 생성 및 데이터 추가
    PricePredictor predictor;
    predictor.addFlightData(korea);
    predictor.addFlightData(japan);
    predictor.addFlightData(usa);
    predictor.addFlightData(france);
    predictor.addFlightData(thailand);
    predictor.addFlightData(australia);
    predictor.addFlightData(canada);
    predictor.addFlightData(italy);
    predictor.addFlightData(germany);
    predictor.addFlightData(brazil);
    predictor.addFlightData(southAfrica);
    predictor.addFlightData(india);

    // 사용자 입력 받기
    int budget, duration;
    string preferredMonth, mealType, accommodationType;
    cout << "Enter your travel budget ($): ";
    cin >> budget;
    cout << "Enter your trip duration (days): ";
    cin >> duration;
    cin.ignore();
    cout << "Enter your preferred travel month (optional, press enter to skip): ";
    getline(cin, preferredMonth);

    predictor.suggestDestinations(budget, duration);
    predictor.suggestLowestPriceDestination(budget);

    if (!preferredMonth.empty()) {
        predictor.suggestByMonth(preferredMonth);
    }

    cout << "\nWould you like to run a cost simulation? (yes/no): ";
    string simulate;
    cin >> simulate;

    if (simulate == "yes") {
        cin.ignore();
        cout << "Enter the country: ";
        string selectedCountry;
        getline(cin, selectedCountry);
        cout << "Select meal type (budget/standard/luxury): ";
        cin >> mealType;
        cout << "Select accommodation type (hostel/hotel/luxury): ";
        cin >> accommodationType;

        predictor.costSimulation(selectedCountry, duration, mealType, accommodationType);
    }

    // 메모리 해제
    delete korea;
    delete japan;
    delete usa;
    delete france;
    delete thailand;
    delete australia;
    delete canada;
    delete italy;
    delete germany;
    delete brazil;
    delete southAfrica;
    delete india;

    return 0;
}
