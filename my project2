#include <iostream>
#include <vector>
#include <string>
#include <limits>
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
        int minPrice = numeric_limits<int>::max();
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            }
        }
        return minPrice;
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

    // 사용자의 예산 및 여행 기간에 맞는 여행지 추천
    void suggestDestinations(int budget, int duration) {
        cout << "\nRecommended Destinations within your budget:\n";
        bool found = false;

        for (FlightData* data : flightDataList) {
            int avgPrice = data->calculateAveragePrice();

            // 예산 내에서 항공권 가격 확인
            if (avgPrice <= budget / (duration > 7 ? 1 : 2)) { // Longer trips allow for slightly higher airfare
                cout << "Country: " << data->country << endl;
                cout << "Average Price: $" << avgPrice << endl;
                data->printBestMonths();
                cout << "--------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No destinations found within your budget.\n";
        }
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
    FlightData* canada = new FlightData("Canada", {700, 750, 720, 730, 710}, {"July", "August", "September"});
    FlightData* germany = new FlightData("Germany", {650, 630, 670, 640, 660}, {"April", "June", "September"});
    FlightData* brazil = new FlightData("Brazil", {550, 580, 560, 570, 590}, {"March", "August", "October"});
    FlightData* southAfrica = new FlightData("South Africa", {850, 830, 870, 820, 860}, {"April", "September", "November"});

    // PricePredictor 객체 생성 및 데이터 추가
    PricePredictor predictor;
    predictor.addFlightData(korea);
    predictor.addFlightData(japan);
    predictor.addFlightData(usa);
    predictor.addFlightData(france);
    predictor.addFlightData(thailand);
    predictor.addFlightData(australia);
    predictor.addFlightData(canada);
    predictor.addFlightData(germany);
    predictor.addFlightData(brazil);
    predictor.addFlightData(southAfrica);

    // 사용자 입력 받기
    int budget, duration;
    cout << "Enter your travel budget ($): ";
    cin >> budget;
    cout << "Enter your trip duration (days): ";
    cin >> duration;

    // 추천 수행
    predictor.suggestDestinations(budget, duration);

    // 메모리 해제
    delete korea;
    delete japan;
    delete usa;
    delete france;
    delete thailand;
    delete australia;
    delete canada;
    delete germany;
    delete brazil;
    delete southAfrica;

    return 0;
}
