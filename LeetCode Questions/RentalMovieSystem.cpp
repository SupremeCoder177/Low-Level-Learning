#include <map>
#include <vector>
#include <iostream>

using namespace std;


class MovieRentingSystem {

    private:
    map<int, map<vector<int>, bool>> movies_map;
    int shops;

    public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        shops = n;

        for(auto v : entries){
            if(movies_map.find(v[0]) != movies_map.end()){
                movies_map[v[0]][v] = false;
            }else{
                map<vector<int>, bool> temp;
                temp[v] = false;
                movies_map[v[0]] = temp;
            }
        }
    }
    
    vector<int> search(int movie) {
        vector<int> output;
        map<vector<int>, bool> temp = movies_map[movie];

        for(auto [k, v] : temp){
            if(output.size() < 5 && !v){
                output.push_back(k[0]);
            }
            if(output.size() == 5) break;
        }
        return output;
    }
    
    void rent(int shop, int movie) {
        map<vector<int>, bool> temp = movies_map[movie];
        for(auto [k, v] : temp){
            if(k[1] == shop && !v){
                movies_map[movie][k] = true;
            }
        }
    }
    
    void drop(int shop, int movie) {
        map<vector<int>, bool> temp = movies_map[movie];
        for(auto [k, v] : temp){
            if(k[1] == shop && v){
                movies_map[movie][k] = false;
            }
        }
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> output;
        vector<int> ptrs;
        for(int i = 0; i < movies_map.size(); i++){
            ptrs.push_back(0);
        }

        vector<int> max_ptrs;
        for(auto [k, v] : movies_map){
            max_ptrs.push_back(v.size());
        }

        while(output.size() < 5){

            int min_price;
            int min_movie;
            int min_shop;
            int inc_ptr = 0;

            for(auto [k, v] : movies_map){
                int count = 0;
                for(auto [ke, va] : v){
                    if(count == ptrs[0]){
                        min_movie = ke[0];
                        min_shop = ke[1];
                        min_price = ke[2];
                        break;
                    }
                    count++;
                }
                break;
            }
            
            for(int i = 0; i < ptrs.size(); i++){
                for(auto [k, v] : movies_map){
                    int count = 0;
                    for(auto [ke, va] : v){
                        if(count == ptrs[i] && ptrs[i] < max_ptrs[i]){
                            if(ke[2] < min_price){
                                if(min_shop != ke[0]){
                                    min_price = ke[2];
                                    min_shop = ke[0];
                                    min_movie = ke[1];
                                    inc_ptr = i;
                                }
                                else if(min_shop == ke[0]){
                                    if(ke[0] < min_shop){
                                        min_price = ke[2];
                                        min_shop = ke[0];
                                        min_movie = ke[1];
                                        inc_ptr = i;
                                    }
                                }
                            }
                            break;
                        }
                        else if(count == ptrs[i] && !(ptrs[i] < max_ptrs[i])) break;
                        count++;
                    }
                }
            }

            ptrs[inc_ptr]++;
            vector<int> temp = {min_shop, min_movie};
            output.push_back(temp);

            bool ptrs_exhausted = true;
            for(int i = 0; i < ptrs.size(); i++){
                if(ptrs[i] < max_ptrs[i]) {
                    ptrs_exhausted = false;
                    break;
                }
            }
            if(ptrs_exhausted) break;
        }

        return output;
    }

    void printState(){
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
    rental.rent(1, 0);
    // rental.printState();

    // vector<int> temp = rental.search(0);
    // for(int i : temp) cout << i << " ";
    // cout << endl;

    vector<vector<int>> reports = rental.report();
    cout << endl;
    for(auto v : reports){
        for(int i : v) cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}