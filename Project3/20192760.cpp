#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Owner{
public:
    Owner(const string& owner, int balance);
    string owner;
    int balance;
    int getObalance();
    void showowners();
    int numpets;
    int temp_sales = 0;
    int sales = 0;
};

Owner::Owner(const string &owner, int balance):owner(owner), balance(balance), sales(0) {}
int Owner::getObalance() {
    return balance;
}
void Owner::showowners() {
    cout << "Owner {name: " << owner << ", balance: " << balance << ", numPetsCheckin: " << numpets << "}\n";
}

class Pet{
public:
    Pet(const string& owner, const string& name, int rate, int nights);
    void getName();
    string name;
    string owner;
    int rate;
    int nights;
    int getpay();
    void showpets();
};

Pet::Pet(const string &owner, const string &name, int rate, int nights): owner(owner), name(name), rate(rate), nights(nights) {}

int Pet::getpay() { //숙박비 계산
    int pay = rate*nights;
    return pay;
}
void Pet::showpets() {
    cout << "Pet {name: " << name << ", owner: " << owner << ", rate: " << rate << ", remainNights: " << nights <<"}\n";
}


int countPets(vector<Pet*> pet, vector<Owner*> owner, int n){
    int count[100] = {0,};
    for(int i= 0; i < pet.size(); i++){
        if(owner[n]->owner == pet[i]->owner) {
            count[n] = count[n] + 1;
        }
    }
    return count[n];
}
void pass(vector<Pet*> pet, vector<Owner*> owner, int days) {
    int i = 0;
    string owner_name[owner.size()];
    int count[100] = {0,};
    cout << days << " days have passed\n";
    while (i < owner.size()) {
        for (int j = 0; j < pet.size(); j++) {
            if (owner[i]->owner == pet[j]->owner) {
                owner_name[i] = owner[i]->owner;
                count[i] += 1;
            }
        }
        i++;
    }

    i = 0;
    while (i <= owner_name->size()) {
        for (int j = 0; j < pet.size(); j++) {
            if (owner_name[i] == pet[j]->owner) {
                while (count[i] > 0) {
                    if (pet[j]->nights <= 0){
                        pet[j]->nights = 0;
                        break;
                    } //balance가 부족해 checkout을 시키지 못한 pet
                    if (days < pet[j]->nights) {
                        owner[i]->temp_sales = pet[j]->rate * days; //경과된 시간만큼의 매출액
                        pet[j]->nights = pet[j]->nights - days;//pet의 남은 날짜
                        break;
                    } //시간이 경과했지만 아직 checkout을 할 날짜가 되지 않은 pet
                    if ((days >= pet[j]->nights) && (days - pet[j]->nights >= 0)) { //checkout 날짜가 됨.
                        if (owner[i]->balance - pet[j]->getpay() >= 0) { //owner의 보유금액 또한 조건이 충족
                            owner[i]->sales = owner[i]->temp_sales + pet[j]->getpay(); //매출액을 구함
                            owner[i]->balance = owner[i]->balance - owner[i]->sales; //owner가 보유한 금액을 줄여줌
                            pet[j]->nights = -1; //객체 삭제를 위해 0보다 작은 값으로 셋팅
                            break;
                        } else if (owner[i]->balance < pet[j]->getpay() && pet[j]->nights >= 0) {
                            pet[j]->nights = 0;
                            break;
                        }
                        count[i] = count[i] - 1; //owner가 checkin시킨 pet의 수를 감소시켜 다음 pet이 조건에 충족하는지 확인
                    }

                }
            }
        }
        i++;
    }
}

int getbalance(vector<Pet*> pet, vector<Owner*> owner, int day){
    int GrossSlaes = 0;
    for(int i = 0; i < owner.size(); i++) {
        GrossSlaes += owner[i]->sales;
    }
    cout << "Working days: " << day << ", Balance: "<< GrossSlaes << "\n";
    return 0;
}


int main() {
    fstream inputStream;
    string data[100];
    inputStream.open("input.txt");
    int day =0;
    vector<Pet*> p;
    vector<Owner*> o;

    for(int i= 0; i < 100; i++){
        inputStream >> data[i];
    }
    for(int i = 0; i < 100; i++){
        if (data[i] == "register"){
            Owner o1(data[i + 1], stoi(data[i + 2]));
            o.push_back(new Owner(o1));
            i+=2;
        }
        if(data[i] == "checkin"){
            Pet p1(data[i+1], data[i+2], stoi(data[i+3]), stoi(data[i+4]));
            p.push_back(new Pet(p1));
            i+=4;
        }
        if(data[i] == "showowners"){
            for(int j = 0; j < o.size(); j++) {
                o[j]-> numpets = countPets(p, o, j);
                o[j]->showowners();
            }
        }
        if(data[i] == "showpets"){
            for(int j = 0; j < p.size(); j++)
                p[j]->showpets();
        }
        if(data[i] == "pass"){
            pass(p, o, stoi(data[i+1]));
            day += stoi(data[i+1]);
            for(vector<Pet*>::iterator iter = p.begin(); iter != p.end();) {
                if ((*iter)->nights < 0) {
                    iter = p.erase(iter);
                }
                else{
                    ++iter;
                }
            }
        }
        if(data[i] == "getbalance"){
            getbalance(p, o, day);
        }
    }
}
