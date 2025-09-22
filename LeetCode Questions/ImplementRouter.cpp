#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Router {

    private:
    map<int, vector<vector<int>>> timestamp_mapping;
    vector<int> timestamps;
    vector<vector<int>> packets;
    int max_size;

    bool checkPacket(int incoming, int destination, int timestamp){
        if(timestamp_mapping.find(timestamp) == timestamp_mapping.end()) return false;
        else{
            for(vector<int> v : timestamp_mapping[timestamp]){
                if(v[0] == incoming && v[1] == destination) return true;
            }
        }
        return false;
    }

    public:
    Router(int memoryLimit) {
        max_size = memoryLimit;
    }

    bool addPacket(int incoming, int destination, int timestamp) {
        if(checkPacket(incoming, destination, timestamp)) return false;

        vector<int> temp = {incoming, destination, timestamp};
        packets.push_back(temp);
        temp.pop_back();
        timestamp_mapping[timestamp].push_back(temp);
        timestamps.push_back(timestamp);

        if(packets.size() > max_size){ 
            forwardPacket();
            packets.shrink_to_fit();
            timestamps.shrink_to_fit();
        }
        
        return true;
    }
    
    vector<int> forwardPacket() {
        vector<int> output;
        if(packets.size() == 0) return output;

        output = {packets[0][0], packets[0][1], packets[0][2]};
        packets.erase(packets.begin());
        timestamps.erase(timestamps.begin());

        int index = 0;
        for(auto v : timestamp_mapping[output[2]]){
            if(v[0] == output[0] && v[1] == output[1]){
                break;
            }
            index++;
        }
        timestamp_mapping[output[2]].erase(timestamp_mapping[output[2]].begin() + index);

        return output;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if(timestamps.size() == 0) return 0;
        int output = 0;

        if(startTime == endTime){
            if(timestamp_mapping.find(startTime) == timestamp_mapping.end()) return 0;

            for(auto v : timestamp_mapping[startTime]){
                if(v[1] == destination) output++;
            }
            return output;
        }


        int left = 0, right = timestamps.size();
        while(left < right){
            if(timestamps[left] == startTime){
                while(left > 0 && timestamps[left - 1] == startTime){
                    left--;
                }
            }
            int mid = left + (right - left) / 2;

            if(timestamps[mid] < startTime){
                left = mid + 1;
            }
            if(timestamps[mid] > startTime){
                right = mid;
            }
        }

        while(left < timestamps.size() && timestamps[left] <= endTime) {

            for(auto v : timestamp_mapping[timestamps[left]]){
                if(v[1] == destination) output++;
            }

            left++;
        }

        return output;
    }

    void printState(){
        cout << "Packets : " << endl;
        for(auto v : packets){
            for(int i : v) cout << i << " ";
            cout << endl;
        }

        cout << "Timestamps : ";
        for(int i : timestamps) cout << i << " ";
        cout << endl;

        cout << "Timestamps mapping :" << endl;
        for(auto [k, v] : timestamp_mapping){
            cout << k << " -> ";
            for(auto vec : v){
                cout << "[ ";
                for(int i : vec) cout << i << " ";
                cout << "] , ";
            }
        }
        cout << endl;
    }
};
    

int main(){

    Router router(3);

    // router.addPacket(4, 1, 5);
    // router.addPacket(3, 1, 9);
    // router.printState();
    
    // int count = router.getCount(1, 2, 9);
    // cout << "Count : " << count << endl;
    
    // router.addPacket(3, 4, 2);
    // router.printState();
    // cout << router.getCount(4, 1, 2) << endl;

    router.addPacket(1, 4, 90);
    router.addPacket(2, 5, 90);
    router.addPacket(1, 4, 90);
    router.addPacket(3, 5, 95);
    router.addPacket(4, 5, 105);


    vector<int> temp = router.forwardPacket();
    cout << "Forwated packet : ";
    for(int i : temp) cout << i << " ";
    cout << endl;

    router.addPacket(5, 2, 110);
    router.printState();

    int count = router.getCount(5, 100, 110);
    cout << "Count : ";
    cout << count << endl;

    return 0;
}