#include <iostream>
#include <string>


using namespace std;


class Solution {

    private:
    string add(char a, char b, char c){
        int ones = 0;
        if(a == '1') ones++;
        if(b == '1') ones++;
        if(c == '1') ones++;
        if(ones == 0) return "0";
        else if(ones == 1) return "1";
        else return "10";
    }

    public:
    string addBinary(string a, string b) {
        string output = "";

        if(a == b) {
            output = a;
            if(output.size() == 1 && output[0] == '0') return output;
            output.push_back('0');
            return output;
        }

        char carry_over = '0';
        int a_len = a.size();
        int b_len = b.size();
        int a_ptr = a_len - 1;
        int b_ptr = b_len - 1;

        while(a_ptr >= 0 || b_ptr >= 0){
            string temp;
            
            if(a_ptr >= 0 && b_ptr >= 0){
                temp = add(a[a_ptr], b[b_ptr], carry_over);
            }else if(a_ptr >= 0){
                temp = add(a[a_ptr], '0', carry_over);
            }else{
                temp = add(b[b_ptr], '0', carry_over);
            }
            if(temp.size() == 2){
                
                if(a_ptr <= 0 && b_ptr <= 0){
                    output.push_back('1');
                }
                carry_over = '1';
                output.push_back(temp[1]);
            }else{
                output.push_back(temp[0]);
            }
            a_ptr--;
            b_ptr--;
            
        }
        string copy = output;
        output.clear();
        for(int i = copy.size() - 1; i >= 0; i--){
            output.push_back(copy[i]);
        }
        return output;
    }
};


int main(){

    cout << Solution().addBinary("0", "0") << endl;

    return 0;
}