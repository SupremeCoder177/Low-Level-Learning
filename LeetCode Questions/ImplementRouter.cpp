#include <vector>
#include <iostream>

using namespace std;

class Router {

    private:
    vector<int> source;
    vector<int> dest;
    vector<int> time;
    int max_size;

    void delete_cell(int index){
        source.erase(source.begin() + index);
        dest.erase(dest.begin() + index);
        time.erase(time.begin() + index);
    }

    public:
    Router(int memoryLimit) {
        max_size = memoryLimit;
    }

    bool addPacket(int incoming, int destination, int timestamp) {
        for(int i = 0; i < source.size(); i++){
            if(source[i] == incoming && dest[i] == destination && time[i] == timestamp) return false;
        }
        if(source.size() >= max_size){
            delete_cell(0);
        }

        source.push_back(incoming);
        dest.push_back(destination);
        time.push_back(timestamp);

        return true;
    }
    
    vector<int> forwardPacket() {
        vector<int> output;
        if(source.size() == 0) return output;

        output.push_back(source[0]);
        output.push_back(dest[0]);
        output.push_back(time[0]);
        delete_cell(0);
        return output;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        int count = 0;
        for(int i = 0; i < source.size(); i++){
            if(dest[i] == destination){
                if(startTime <= time[i] && endTime >= time[i]) count++;
            }
        }
        return count;
    }
};

int main(){

    Router router(100);
    router.addPacket(100, 200, 101);
    int count = router.getCount(200, 100, 200);
    std::cout << count << std::endl;
    vector<int> packet = router.forwardPacket();

    for(int i : packet) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}