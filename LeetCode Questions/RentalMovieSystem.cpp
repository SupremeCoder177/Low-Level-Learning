#include <map>
#include <vector>
#include <set>
#include <iostream>

using namespace std;


class MovieRentingSystem {

    private:
    map<int, map<vector<int>, bool>> movies_map;
    set<vector<int>> rented;

    public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for(auto v : entries){

            if(movies_map.find(v[1]) != movies_map.end()){
                movies_map[v[1]][v] = false;
            }else{
                map<vector<int>, bool> temp;
                temp[v] = false;
                movies_map[v[1]] = temp;
            }
        }
    }
    
    vector<int> search(int movie) {
        vector<int> output;
        set<vector<int>> storage;
        map<vector<int>, bool> temp = movies_map[movie];

        for(auto [k, v] : temp){
            if(storage.size() < 5 && !v){
                vector<int> holder = {k[2], k[0]};
                storage.insert(holder);
            }
            if(storage.size() == 5) break;
        }
        for(auto v : storage){
            output.push_back(v[1]);
        }

        return output;
    }
    
    void rent(int shop, int movie) {
        map<vector<int>, bool> temp = movies_map[movie];
        for(auto [k, v] : temp){
            if(k[0] == shop && !v){
                movies_map[movie][k] = true;
                vector<int> tmp = {k[0], k[1]};
                rented.insert(tmp);
            }
        }
    }
    
    void drop(int shop, int movie) {
        map<vector<int>, bool> temp = movies_map[movie];
        for(auto [k, v] : temp){
            if(k[0] == shop && v){
                movies_map[movie][k] = false;
                vector<int> tmp = {k[0], k[1]};
                rented.erase(tmp);
            }
        }
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> output;
        for(auto it = rented.begin(); it != rented.end(); it++){
            output.push_back(*it);
            if(output.size() == 5) break;
        }
        return output;
    }

    void printState(){

        cout << "Movies map:" << endl;
        for(auto [k, v] : movies_map){
            cout << k << "->" << endl;
            for(auto [ki, va] : v){
                for(int i : ki) cout << i << " ";
                cout << " : " << va << endl;
            }
        }
    }
};


int main(){

    cout << boolalpha;
    vector<vector<int>> movies = {{0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}};
    MovieRentingSystem rental = MovieRentingSystem(3, movies);
    rental.rent(0, 1);
    rental.rent(1, 2);
    //rental.printState();

    vector<int> temp = rental.search(1);
    for(int i : temp) cout << i << " ";
    cout << endl;

    vector<vector<int>> reports = rental.report();
    cout << endl;
    for(auto v : reports){
        for(int i : v) cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}